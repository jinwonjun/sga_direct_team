#include "stdafx.h"
#include "Cubeman.h"
#include "CubemanParts.h"
#include "Enemyman.h"

Cubeman::Cubeman()
{
	m_pRootParts = NULL;

	m_isMoving = false;
	//�⺻ �̼�
	//m_moveSpeed = 0.2f;

	m_moveSpeed = 0.5f;

	m_currMoveSpeedRate = 1.0f;
	m_rotationSpeed = 0.1f;

	m_isJumping = false;
	m_jumpPower = 1.0f;
	m_gravity = 0.05f;
	m_currGravity = 0.0f;
	m_maxStepHeight = 0.5f;
}


Cubeman::~Cubeman()
{
	//��� idisplayobject ��ӹ�������
	m_pRootParts->ReleaseAll();
}

void Cubeman::Init()
{	
	g_pObjMgr->AddToTagList(TAG_PLAYER, this);

	g_pCamera->SetTarget(&m_pos);
	//printf("%f %f %f\n", &m_pos.x, &m_pos.y, &m_pos.z);
	//g_pCamera->SetTarget(& D3DXVECTOR3(0, m_pos.y, 0));

	//g_pKeyboardManager->SetMovingTarget(&m_deltaPos, &m_deltaRot , &m_isJumping);
	g_pKeyboardManager->SetMovingTarget(&m_keyState);


	CreateAllParts();
}

void Cubeman::Update()
{
	//UpdatePosition();
	//����� �ڵ� ����
	//Debug->AddText(m_pos);
	//Debug->EndLine();//��� ���� �ٹٲ�
	//printf("%f %f %f\n", m_pos.x, m_pos.y, m_pos.z);
	
	IUnitObject::UpdatePosition();
	IUnitObject::UpdateKeyboardState();

	//���� ����
	if (GetAsyncKeyState('1') & 0x0001)
	{
		m_isTurnedOnLight = !m_isTurnedOnLight;
	}
	if (m_isTurnedOnLight)
	{
		D3DXVECTOR3 pos = m_pos;

		pos.y += 3.0f;
		D3DXVECTOR3 dir = m_forward;
		D3DXCOLOR c = BLUE;
		D3DLIGHT9 light = DXUtil::InitSpot(&dir, &pos, &c);
		
		//�������� �þ߰� �����ϱ�
		light.Phi = D3DX_PI / 2;
		//D3DLIGHT9 light = DXUtil::InitPoint(&dir, &c);

		//������ ��������� ������ ������.
		//0�� ����Ʈ
		g_pDevice->SetLight(10, &light);
	}
	//bool ���� ���� 0������ ������ ������ ���� �״� ��Ʈ�� �غ���
	g_pDevice->LightEnable(10, m_isTurnedOnLight);

	//������ �������� �����̴��� �ƴ��� ���¸� �Ǵ��ؼ� ���ڰ� �Ѱ��ٰž�
	m_pRootParts->SetMovingState(IUnitObject::m_isMoving);
	m_pRootParts->Update();
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		IUnitObject::m_isMoving = true;
		m_pos.x -= 0.5f;

	}
	else if (GetKeyState('E') & 0x8000)
	{
		IUnitObject::m_isMoving = true;
		m_pos.x += 0.5f;
	}

	
}

void Cubeman::Render()
{
	m_pRootParts->Render();
}

void Cubeman::UpdatePosition()
{
	m_rot += m_deltaRot * m_rotationSpeed;

	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matRotY, m_rot.y);
	//���� ���� ���� ��������
	D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRotY);

	D3DXVECTOR3 targetPos;
	float basePosY = 0;

	bool isIntersected = true;
	float height = 0;

	if (m_isJumping)
	{
		m_currMoveSpeedRate = 0.7f;
		targetPos = m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate;//��Ÿ���� z�� Ű����� w�� ���ȳ� �ȴ��ȳ� ���� ������!
		targetPos.y += m_jumpPower - m_currGravity;
		m_currGravity += m_gravity;

		//�̰� �׳� ���� �κ�
		/*if (targetPos.y <= basePosY)
		{
			targetPos.y = basePosY;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}*/
		//�׳� ���� �߰��Ѱ�(����)
		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
		}
		if (isIntersected == false)
		{
			if (g_pCurrentMap != NULL)
			{
				//������ ��ġ���� ���� üũ�� ���ش�.
				isIntersected = g_pCurrentMap->GetHeight(height, m_pos);
			}
			m_pos.y = targetPos.y;
		}
		else
		{
			//�ٴ����� ������ �״�� �� �޾ƿ���
			m_pos = targetPos;
		}
		// m_jumpPower < m_currGravity <- �̰� �ϰ� ���϶��� �ǹ���!
		if (m_pos.y <= height && m_jumpPower < m_currGravity)
		{
			m_pos.y = height;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}
		//if (targetPos.y <= basePosY && ob->GetHeight(targetPos.y, targetPos) == false)
		//{
		//	targetPos.y = basePosY;
		//	m_isJumping = false;
		//	m_currGravity = 0;
		//	m_currMoveSpeedRate = 1.0f;
		//}
		////���� ���¿��� �浹 ������
		//if (targetPos.y <= basePosY && ob->GetHeight(targetPos.y, targetPos) == true)
		//{
		//	targetPos.y *= 2.0f;
		//}
		//m_pos = targetPos;
	}
	else //m_isJumping == false;
	{
		targetPos = m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate;
		
		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
			//���� ���̶� Ÿ��y �� ���̰� Ŀ������ ���ƹ�����
			if (isIntersected == false || fabs(height - m_pos.y) > m_maxStepHeight)
			{

			}
			else
			{
				targetPos.y = height;
				m_pos = targetPos;
			}
		}
		else
		{
			m_pos = targetPos;
		}
		//�׳� ���� �߰��Ѱ�
		/*if (ob->GetHeight(m_pos.y, m_pos) == false)
		{
			m_pos.y = basePosY;
		}*/
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);


	//������ ��Ʈ���غ���
	//�̰� �׳� ������~
	//ob->GetHeight(m_pos.y, m_pos);

	m_matWorld = matRotY * matT;

	//Sq�� ���� ������ ���ĸ� �ܼ��� ���Ƿк��� ū�� ������ ���Ҷ�� �ϴ°���. Sq������ ���״�� ��Ʈ���궧���� ���귮�� ���.
	if (D3DXVec3LengthSq(&m_deltaRot) > D3DX_16F_EPSILON || D3DXVec3LengthSq(&m_deltaPos) > D3DX_16F_EPSILON)
	{
		m_isMoving = true;
	}
	else
		m_isMoving = false;
}
/*
ť��� ���� �κ� ����
���� ������������ �׸��� �ƴ϶�, �ϴ� �⺻���� 0,0,0 �߽����� �׷������� �״ϱ�, ó������(���ý����̽�)������ �׷�����
���� �����̽��� ���� �� ����������� ���ʿ� �پ�� �Ǵϱ�, ���� �����̽� ��������(������ ���彺���̽�) �����̵��� ����
*/
void Cubeman::CreateAllParts()
{
	//�⺻ ĳ���� ����
	CubemanParts* pParts;
	//����
	m_pRootParts = new CubemanParts();
	CreateParts(m_pRootParts, this, D3DXVECTOR3(0.0f, 3.0f, 0.0f),D3DXVECTOR3(1.0f, 1.0f, 0.5f), D3DXVECTOR3(0, 0, 0), uvBody);
	//�Ӹ�
	pParts = new CubemanParts();
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.0f, 1.6f, 0.0f),D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0, 0, 0), uvHead);
	//����
	pParts = new CubemanParts(0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-1.5f, 1.0f, 0.0f),D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLArm);
	//������
	pParts = new CubemanParts(-0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(1.5f, 1.0f, 0.0f),D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRArm);
	//�޴ٸ�
	pParts = new CubemanParts(-0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-0.5f, -1.0f, 0.0f),D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLLeg);
	//�����ٸ�
	pParts = new CubemanParts(0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.5f, -1.0f, 0.0f),D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRLeg);
}

void Cubeman::CreateParts(CubemanParts* &pParts, IDisplayObject* pParent, D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 trans, vector<vector<int>> &vecUV)
{
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&matT, trans.x, trans.y, trans.z);
	mat = matS * matT;
	pParts->Init(&mat, vecUV);
	pParts->SetPosition(&pos);
	pParent->AddChild(pParts);
}