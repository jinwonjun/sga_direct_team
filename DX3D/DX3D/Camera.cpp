#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	//m_distance = 5.0f;
	m_distance = 0.5f;
	m_basePosY = 10.0f;
	m_eye = D3DXVECTOR3(0, m_basePosY , -m_distance);

	m_lookAt = D3DXVECTOR3(0, 0, 0);
	m_up = D3DXVECTOR3(0, 1, 0);
	m_rotX = 0.0f;
	m_rotY = 0.0f;
	m_isLbuttonDown = false;
	m_pTarget = NULL;
}

Camera::~Camera()
{
}

void Camera::Init()
{
	
	D3DXMatrixLookAtLH(&m_matView,&m_eye, &m_lookAt, &m_up);
	g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMatrixPerspectiveFovLH(&m_matProj,D3DX_PI / 4.0f, rc.right / (float)rc.bottom , 1, 1000);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
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

	m_eye = D3DXVECTOR3(0, m_basePosY, -m_distance);
	D3DXMATRIXA16 matRotX, matRotY, matRot;
	
	//키보드로 회전하기
	//if (m_isLbuttonDown == false)
	//{
	//	m_rotX = g_pObjMgr->FindObjectByTag(TAG_PLAYER)->GetRotation().x ;
	//	m_rotY = g_pObjMgr->FindObjectByTag(TAG_PLAYER)->GetRotation().y ;
	//	D3DXMatrixRotationX(&matRotX, m_rotX);
	//	D3DXMatrixRotationY(&matRotY, m_rotY);
	//}
	////true일때
	//else
	//{
	//	D3DXMatrixRotationX(&matRotX, m_rotX);
	//	D3DXMatrixRotationY(&matRotY, m_rotY);
	//}
	D3DXMatrixRotationX(&matRotX, m_rotX);
	D3DXMatrixRotationY(&matRotY, m_rotY);
	//마우스로 회전하기
	matRot = matRotX * matRotY;

	D3DXVec3TransformCoord(&m_eye, &m_eye, &matRot);

	m_lookAt = D3DXVECTOR3(0, 0, 50.0f);

	if (m_pTarget)
	{
		//static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetForward();
		//Debug->AddText(static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetForward());
		//m_lookAt = *m_pTarget;
		//m_eye = *m_pTarget + m_eye;
		D3DXVECTOR3 temp;
		float distance = 10.0f;
		temp = (static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetForward()) * distance +  (*m_pTarget);
		m_lookAt = D3DXVECTOR3(temp.x, temp.y+10, temp.z);
		m_eye = *m_pTarget + m_eye;
	}

	D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookAt, &m_up);
	g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);
}

void Camera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	printf("이전x좌표 : %d, 이전y좌표 : %d\n", m_ptPrevMouse.x, m_ptPrevMouse.y);

	switch (message)
	{
		//이전 값 계속 받기
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
	//case WM_LBUTTONDOWN:
	//{
	//	m_isLbuttonDown = true;
	//	
	//	m_ptPrevMouse.x = LOWORD(lParam);
	//	m_ptPrevMouse.y = HIWORD(lParam);
	//}
	//break;
	case WM_LBUTTONUP:
	{
		//m_isLbuttonDown = false;
	}
	break;
	case WM_MOUSEMOVE:
	{
		//if (m_isLbuttonDown == false)
		//{
			POINT currPoint;
			currPoint.x = LOWORD(lParam);
			currPoint.y = HIWORD(lParam);

			m_rotY += (currPoint.x - m_ptPrevMouse.x) / 500.0f;
			m_rotX += (currPoint.y - m_ptPrevMouse.y) / 500.0f;

			//if (m_rotX <= -D3DX_PI * 0.5f + D3DX_16F_EPSILON)
			//{
			//	m_rotX = -D3DX_PI * 0.5f + D3DX_16F_EPSILON;
			//}
			//if (m_rotX >= D3DX_PI * 0.3f - D3DX_16F_EPSILON)
			//{
			//	m_rotX = D3DX_PI * 0.3f - D3DX_16F_EPSILON;
			//}

			m_ptPrevMouse = currPoint;
			printf("현재x좌표 : %d, 현재y좌표 : %d\n", currPoint.x, currPoint.y);
			printf("x회전 : %f, y회전 : %f\n", m_rotX, m_rotY);
			//커서 초기화
			if ((currPoint.x <= 0 || currPoint.x >= WINSIZEX-250) || (currPoint.y <= 0 || currPoint.y >= WINSIZEY - 250))
			{
				SetCursorPos(WINSIZEX / 2, WINSIZEY / 2);
			}
		//}
	}
	break;
	case WM_MOUSEWHEEL:
		m_distance -= GET_WHEEL_DELTA_WPARAM(wParam) / 50.0f;
		if (m_distance <= 0.5f) m_distance = 0.5f;
		if (m_distance >= 100) m_distance = 100;
		break;
	}
}

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
