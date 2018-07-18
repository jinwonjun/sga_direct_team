#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	//m_distance = 5.0f;
	mLimitDistance = m_distance = 20.f;
	m_basePosX = 5.0f;
	//origin
	//m_basePosY = 10.0f;
	m_basePosY = 15.0f;
	m_eye = D3DXVECTOR3(m_basePosX, m_basePosY, -m_distance);

	m_lookAt = D3DXVECTOR3(0, 0, 0);
	m_up = D3DXVECTOR3(0, 1, 0);
	m_rotX = 0.0f;
	m_rotY = 0.0f;
	m_isLbuttonDown = false;
	m_pTarget = NULL;

	deltaRotY = 0.f;
	isStart = true;

	tempRotX = 0.f;
	tempRotY = 0.f;

	m_lookatTemp = D3DXVECTOR3(0, 0, 0);
	m_eyeTemp = D3DXVECTOR3(0, 0, 0);

	//mLimitX = 400.f;
	//mLimitY = 200.f;
	//mRCCollCheck = false;
	////���콺 �̵� ���� �� ��Ʈ
	//mRc = { mCenter.x - (LONG)mLimitX, mCenter.y - (LONG)mLimitY, mCenter.x + (LONG)mLimitX, mCenter.y + (LONG)mLimitY };

	//mSensX = 300.f;
	//mSensY = 100.f;

	//sensLevel = 5;
}

Camera::~Camera()
{
}

void Camera::Init()
{

	D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookAt, &m_up);
	g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1, 2000);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);

	// �̰� �̴ֿ��� �ϸ� �ȵǿ�? �����ڿ��� �ϴϱ� Ŭ���̾�Ʈ ��Ʈ�� ���ϳ�
	RECT clientRect;
	GetClientRect(g_hWnd, &clientRect);
	mCenter = { clientRect.right / 2 , clientRect.bottom / 2 };

	//���� ȭ�麸�� ��¦ �۰�
	mLimitX = clientRect.right / 2 - 10;
	mLimitY = clientRect.bottom / 2 - 10;
	mRCCollCheck = false;
	//���콺 �̵� ���� �� ��Ʈ
	mRc = { mCenter.x - (LONG)mLimitX, mCenter.y - (LONG)mLimitY, mCenter.x + (LONG)mLimitX, mCenter.y + (LONG)mLimitY };

	mSensStepX = 100.f;
	mSensStepY = 50.f;

	sensLevel = 5;

	mSensX = mSensStepX * 6;
	mSensY = mSensStepY * 6;


	isColl = false;
}

void Camera::Update()
{
	//m_eye = D3DXVECTOR3(0 , m_basePosY  , -m_distance);
	//D3DXMATRIXA16 matRotX, matRotY, matRot;
	//D3DXMatrixRotationX(&matRotX, m_rotX);
	//D3DXMatrixRotationY(&matRotY, m_rotY);
	//matRot = matRotX * matRotY;
	//D3DXVec3TransformCoord(&m_eye, &m_eye, &matRot);
	//if (m_pTarget)
	//{
	//	m_lookAt = *m_pTarget;
	//	m_eye = *m_pTarget + m_eye;
	//}
	//D3DXMatrixLookAtLH(&m_matView,&m_eye, &m_lookAt, &m_up);
	//g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

	m_eye = D3DXVECTOR3(m_basePosX, m_basePosY, -m_distance);
	m_lookAt = D3DXVECTOR3(m_basePosX, m_basePosY, m_distance);

	D3DXMATRIXA16 matRotX, matRotY, matRot;

	if (GetAsyncKeyState('O') & 0x0001)
	{
		if (sensLevel > 1)
		{
			mSensX += mSensStepX;
			mSensY += mSensStepY;
			sensLevel--;
		}
	}
	else if (GetAsyncKeyState('P') & 0x0001)
	{
		if (sensLevel < 10)
		{
			mSensX -= mSensStepX;
			mSensY -= mSensStepY;
			sensLevel++;
		}
	}

	//���� ���� �� ���� ȸ���� ����
	if (m_pTarget && (g_pKeyboard->KeyUp(VK_LSHIFT)))
	{
		m_rotX = tempRotX;
		m_rotY = tempRotY;
	}

	Debug->AddText("Mouse Sensitivity : " + to_string(sensLevel));
	Debug->EndLine();

	D3DXMatrixRotationX(&matRotX, m_rotX);
	D3DXMatrixRotationY(&matRotY, m_rotY);

	//���콺�� ȸ���ϱ�
	matRot = matRotX * matRotY;

	D3DXVec3TransformCoord(&m_eye, &m_eye, &matRot);
	D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &matRot);



	if (m_pTarget && (g_pKeyboard->KeyPress(VK_LSHIFT)))
	{
		m_lookAt = *m_pTarget + m_lookAt;
		m_eye = *m_pTarget + m_eye;
	}
	else if (m_pTarget && !(g_pKeyboard->KeyPress(VK_LSHIFT)))
	{
		//static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetForward();
		//Debug->AddText(static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetForward());
		//m_lookAt = *m_pTarget;
		//m_eye = *m_pTarget + m_eye;
		//D3DXVECTOR3 temp;
		//float distance = 10.0f;
		//temp = (static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetForward()) * distance +  (*m_pTarget);
		//
		//m_lookAt = D3DXVECTOR3(temp.x, temp.y + 10, temp.z);

		m_lookAt = *m_pTarget + m_lookAt;
		m_eye = *m_pTarget + m_eye;

		m_lookatTemp = m_lookAt;
		m_eyeTemp = m_eye;

		//���������� ���ƿ� �� ����
		tempRotX = m_rotX;
		tempRotY = m_rotY;
	}
	else
	{
		m_pTarget = NULL;
	}



	//------- ���� �浹�ϴ°� ���߿� ����
	////���� �ø����� ���� ������
	//if (m_eye.y <= D3DX_16F_EPSILON)
	//{
	//	if (deltaRotY < D3DX_16F_EPSILON)
	//	{
	//		m_distance -= 0.5f;
	//		m_eye.y = 0.f;
	//		isColl = true;
	//	}
	//}

	////���� ��Ұ� �Ʒ��� ��������
	//if (isColl && (deltaRotY >= 0))
	//{
	//	if (m_distance <= mLimitDistance)
	//	{
	//		m_distance += 0.5f;
	//		m_eye.y = 0.f;
	//	}
	//	else
	//	{
	//		m_distance = mLimitDistance;
	//	}

	//	if (m_eye.y > 0.f)
	//		isColl = false;

	//}



	if (g_pInventory->openInven)
	{
		ShowCursor(true);
	}
	else

	{
		ShowCursor(true);
	}

	D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookAt, &m_up);
	g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

	if (g_pKeyboard->KeyDown('K'))
	{
		m_distance -= 3.0f;
		if (m_distance <= 0.5f) m_distance = 0.5f;
	}
	else if (g_pKeyboard->KeyDown('L'))
	{
		m_distance += 3.0f;
		if (m_distance >= 100) m_distance = 100;
	}

	Debug->AddText("Camera Distance : " + to_string(m_distance));
	Debug->EndLine();
}

void Camera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//printf("����x��ǥ : %d, ����y��ǥ : %d\n", m_ptPrevMouse.x, m_ptPrevMouse.y);
	if (g_pInventory->openInven)
	{
		POINT currPoint;
		switch (message)
		{

			case WM_MOUSEMOVE:
			{
				currPoint.x = LOWORD(lParam);
				currPoint.y = HIWORD(lParam);
			}
		}

	}
	else
	{
		POINT currPoint;

		switch (message)
		{
			//���� �� ��� �ޱ�
			//m_ptPrevMouse.x = LOWORD(lParam);
			//m_ptPrevMouse.y = HIWORD(lParam);
			//case WM_LBUTTONDOWN:
			//{
			//	m_isLbuttonDown = true;
			//	m_ptPrevMouse.x = LOWORD(lParam);
			//	m_ptPrevMouse.y = HIWORD(lParam);
			//}
			//break;
			//case WM_LBUTTONUP:
			//{
			//	m_isLbuttonDown = false;
			//}
			//break;
			case WM_MOUSEMOVE:
			{
				currPoint.x = LOWORD(lParam);
				currPoint.y = HIWORD(lParam);

				//���۽� �����°� ����
				if (isStart)
				{
					//m_ptPrevMouse.x = LOWORD(lParam);
					//m_ptPrevMouse.y = HIWORD(lParam);

					m_ptPrevMouse = currPoint;

					isStart = false;
				}

				if (!mRCCollCheck)
				{
					float prevRotX = m_rotX;

					if (g_pKeyboard->KeyPress(VK_LSHIFT))
					{
						m_rotY += (currPoint.x - m_ptPrevMouse.x) / mSensX;

					}
					else
					{
						m_rotX += (currPoint.y - m_ptPrevMouse.y) / mSensY;
						m_rotY += (currPoint.x - m_ptPrevMouse.x) / mSensX;
					}
					//Xȸ�� ���п� ���� ��ġ���� ���߿� ����

					deltaRotY = m_rotX - prevRotX;
				}

				mRCCollCheck = false;

				if (m_rotX <= -D3DX_PI * 0.4f + D3DX_16F_EPSILON)
				{
					m_rotX = -D3DX_PI * 0.4f + D3DX_16F_EPSILON;
					//m_rotX = -m_rotX;
				}
				else if (m_rotX >= D3DX_PI * 0.4f - D3DX_16F_EPSILON)
				{
					m_rotX = D3DX_PI * 0.4f - D3DX_16F_EPSILON;
					//m_rotX = -m_rotX;
				}
				//Ŀ�� �ʱ�ȭ
				m_ptPrevMouse = currPoint;

				// || (currPoint.y <= 0 || currPoint.y >= WINSIZEY - 250)

				//���콺 �̵� ���� ��Ʈ
				if ((currPoint.x >= mRc.right))
				{
					SetCursorPos(mCenter.x, mCenter.y);//780 445
					mRCCollCheck = true;
				}
				else if (currPoint.x <= mRc.left)
				{
					SetCursorPos(mCenter.x, mCenter.y);//780 445
					mRCCollCheck = true;
				}
				if (currPoint.y <= mRc.top)
				{
					SetCursorPos(mCenter.x, mCenter.y);//780 445
					mRCCollCheck = true;
				}
				else if (currPoint.y >= mRc.bottom)
				{
					SetCursorPos(mCenter.x, mCenter.y);//780 445
					mRCCollCheck = true;
				}
				break;
			}
			case WM_MOUSEWHEEL:
			{
				m_distance -= GET_WHEEL_DELTA_WPARAM(wParam) / 50.0f;
				if (m_distance <= 0.5f) m_distance = 0.5f;
				if (m_distance >= 100) m_distance = 100;
				break;
			}
		}
	}
}

//m_rotX += (currPoint.y - m_ptPrevMouse.y) / mSensY;
//m_distance -= m_rotX;

//Xȸ�� ���п� ���� ��ġ���� ���߿� ����

//if (m_rotX <= -D3DX_PI * 0.3f + D3DX_16F_EPSILON)
//{
//	m_rotX = -D3DX_PI * 0.3f + D3DX_16F_EPSILON;
//	// = -m_rotX;
//}
////if (m_rotX <= -0.5f)
////{
////	m_rotX = -0.5f;
////}
//if (m_rotX >= D3DX_PI * 0.3f - D3DX_16F_EPSILON)
//{
//	m_rotX = D3DX_PI * 0.3f - D3DX_16F_EPSILON;
//	//m_rotX = -m_rotX;
//}
//if ((currPoint.y >= mRc.bottom))
//{
//	SetCursorPos(currPoint.y, mCenter.y);//780 445
//	m_rotX = -D3DX_PI * 0.5f + D3DX_16F_EPSILON;
//	mRCCollCheck = true;
//}
//else if (currPoint.y <= mRc.top)
//{
//	SetCursorPos(currPoint.y, mCenter.y);//780 445
//	m_rotX = D3DX_PI * 0.3f - D3DX_16F_EPSILON;
//	mRCCollCheck = true;
//}

//case WM_MOUSEWHEEL:
//	if (GetAsyncKeyState(VK_TAB))
//	{
//		m_distance -= GET_WHEEL_DELTA_WPARAM(wParam) / 50.0f;
//		if (m_distance <= 5) m_distance = 5;
//		if (m_distance >= 100) m_distance = 100;
//	}
//	else
//	{
//		m_distance = 5.0f;
//	}
//	break;