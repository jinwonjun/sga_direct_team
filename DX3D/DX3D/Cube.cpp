#include "stdafx.h"
#include "Cube.h"


Cube::Cube()
	: RotY(0.0f)
	, m_moveSpeed(0.1f),m_vPosition(0,1 + 0.7f * 2,0)
{
	m_basePosY = 1.0f;
	m_isJumping = false;
	m_jumpPower = 0.4f;
	m_gravity = 0.025f;
	m_currGravity = 0.0f;
	m_moveSpeedRate = 1.0f;
}


Cube::~Cube()
{
}

void Cube::Init()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&mT);
	D3DXMatrixIdentity(&mR);
	//D3DXMatrixIdentity()

	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
	//m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, -1.0f),green));//0
	//m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), red));//1
	//m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, -1.0f), blue));//2
	//m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f), green));//3
	//m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	//m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), blue));//5
	//m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6
	//m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, 1.0f), red));//7

	m_vecIndex.push_back(0);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(2);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), green));//0
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), red));//1
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, -1.0f), blue));//2

	m_vecIndex.push_back(0);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), green));//0
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, -1.0f), blue));//2
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f), green));//3

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(5);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), blue));//5

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(6);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, 1.0f), red));//7
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(1);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), blue));//5
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), red));//1

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(0);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), red));//1
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), green));//0

	m_vecIndex.push_back(3);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(6);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f), green));//3
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, -1.0f), blue));//2
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6

	m_vecIndex.push_back(3);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(7);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f), green));//3
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, 1.0f), red));//7

	m_vecIndex.push_back(1);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(6);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), red));//1
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), blue));//5
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6

	m_vecIndex.push_back(1);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(2);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), red));//1
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, -1.0f), blue));//2

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(3);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), green));//0
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f), green));//3

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(7);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f), green));//3
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, 1.0f), red));//7


	//ť�� �Ӹ� �κ�
	m_pCube_Head = new Cubeman_Head;
	m_pCube_Head->Init();
	//ť�� �ٸ� �κ�
	m_pCube_Left_leg = new Cubeman_Left_leg;
	m_pCube_Left_leg->Init();

	m_pCube_Right_leg = new Cubeman_Right_leg;
	m_pCube_Right_leg->Init();

	m_pCube_Left_arm = new Cubeman_Left_arm;
	m_pCube_Left_arm->Init();

	m_pCube_Right_arm = new Cubeman_Right_arm;
	m_pCube_Right_arm->Init();

}

void Cube::Update()
{
	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition.z += m_moveSpeed;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		m_vPosition.z -= m_moveSpeed;
	}
	//���� �̵��� ��ġ
	RotY += 0.05f;
	RotX += 0.05f;


	//printf("%f\n", RotY);
	// ������� ����
	D3DXMatrixRotationY(&mR, RotY);

	m_pCube_Left_arm->RotY = RotY;
	m_pCube_Left_arm->mR = mR;
	m_pCube_Left_arm->m_vPosition_orgin = m_vPosition;


	m_pCube_Right_arm->RotY = RotY;
	m_pCube_Right_arm->mR = mR;
	m_pCube_Right_arm->m_vPosition_orgin = m_vPosition;

	//X�ຯȯ ���� �̱��� �ǵ��� ����
	//D3DXMatrixRotationX(&mR, RotX);

	//��ġ �̵����
	D3DXMatrixTranslation(&mT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld =  mR * mT;

	//ť�� �̵��� ���뿡��
	m_pCube_Head->RotY = RotY;
	m_pCube_Head->RotX = RotX;
	m_pCube_Head->m_vPosition.z = m_vPosition.z;
	
	m_pCube_Left_leg->m_vPosition.z = m_vPosition.z;
	m_pCube_Right_leg->m_vPosition.z = m_vPosition.z;
	m_pCube_Left_arm->m_vPosition.z = m_vPosition.z;
	m_pCube_Right_arm->m_vPosition.z = m_vPosition.z;



	m_pCube_Head->Update();
	m_pCube_Left_leg->Update();
	m_pCube_Right_leg->Update();
	m_pCube_Left_arm->Update();
	m_pCube_Right_arm->Update();
}

void Cube::Render()
{
	////���� ��Ʈ���� �������ֱ�
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pDevice->SetFVF(VERTEX_PC::FVF);

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//g_pDevice->SetFVF(VERTEX_PC::FVF);
	//�׸� ������ Ÿ��, ������ ����, ���� ������ ���� �ּ�, ������ ũ��
	//�׶��̼� �������� �׷���.
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size()/3, &m_vecVertex[0], sizeof(VERTEX_PC));

	//�Ӹ��׸���
	m_pCube_Head->Render();
	m_pCube_Left_leg->Render();
	m_pCube_Right_leg->Render();
	m_pCube_Left_arm->Render();
	m_pCube_Right_arm->Render();
}
