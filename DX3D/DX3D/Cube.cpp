#include "stdafx.h"
#include "Cube.h"


Cube::Cube()
	: RotY(0.0f), m_moveSpeed(0.1f),m_vPosition(0,1 + 0.7f * 2,0)
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
	//this->Release();
}

void Cube::Init()
{
	g_pObjMgr->AddToTagList(TAG_ENEMY1, this);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&mT);
	D3DXMatrixIdentity(&mR);
	D3DXMatrixIdentity(&mS);
	//D3DXMatrixIdentity()

	go_Right = true;
	go_Left = false;

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



	//큐브 머리 부분
	//m_pCube_Head = new Cubeman_Head;
	//m_pCube_Head->Init();
	////큐브 다리 부분
	//m_pCube_Left_leg = new Cubeman_Left_leg;
	//m_pCube_Left_leg->Init();
	//
	//m_pCube_Right_leg = new Cubeman_Right_leg;
	//m_pCube_Right_leg->Init();
	//
	//m_pCube_Left_arm = new Cubeman_Left_arm;
	//m_pCube_Left_arm->Init();
	//
	//m_pCube_Right_arm = new Cubeman_Right_arm;
	//m_pCube_Right_arm->Init();
	//구그리기
	float radius = 3.0f;
	D3DXCreateSphere(g_pDevice, radius, 10, 10, &m_pSphere, NULL);
	BoundingSphere* s = new BoundingSphere(D3DXVECTOR3(m_vPosition.x + 5, m_vPosition.y + 5, m_vPosition.z + 5), radius);

	pSphere = s;
}

void Cube::Update()
{
	//if (GetKeyState('W') & 0x8000)
	//{
	//	m_vPosition.z += m_moveSpeed;
	//}
	//else if (GetKeyState('S') & 0x8000)
	//{
	//	m_vPosition.z -= m_moveSpeed;
	//}
	//내가 이동할 위치
	// RotY += 0.05f;
	// RotX += 0.05f;
	

	//printf("%f\n", RotY);
	// 월드행렬 지정
	//D3DXMatrixRotationY(&mR, RotY);

	//m_pCube_Left_arm->RotY = RotY;
	//m_pCube_Left_arm->mR = mR;
	//m_pCube_Left_arm->m_vPosition_orgin = m_vPosition;
	//
	//
	//m_pCube_Right_arm->RotY = RotY;
	//m_pCube_Right_arm->mR = mR;
	//m_pCube_Right_arm->m_vPosition_orgin = m_vPosition;

	//X축변환 아직 미구현 건들지 말기
	//D3DXMatrixRotationX(&mR, RotX);

	//위치 이동행렬
	if (go_Right)
	{
		m_vPosition.x += 0.1f;
	}
	if (go_Left)
	{
		m_vPosition.x -= 0.1f;
	}

	if (m_vPosition.x >= 1.0f)
	{
		go_Right = false;
		go_Left = true;
	}

	if (m_vPosition.x <= -1.0f)
	{
		go_Right = true;
		go_Left = false;
	}

	m_pos = m_vPosition;
	m_pos.y = m_vPosition.y + 10.0f;
	pSphere->center = m_pos;

	D3DXMatrixTranslation(&mT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	D3DXMatrixScaling(&mS, 2.0f, 10.0f, 2.0f);

	m_matWorld =  mS* mR * mT;


	//큐브 이동을 몸통에서
//m_pCube_Head->RotY = RotY;
//m_pCube_Head->RotX = RotX;
//m_pCube_Head->m_vPosition.z = m_vPosition.z;
	
//	m_pCube_Left_leg->m_vPosition.z = m_vPosition.z;
//	m_pCube_Right_leg->m_vPosition.z = m_vPosition.z;
//	m_pCube_Left_arm->m_vPosition.z = m_vPosition.z;
//	m_pCube_Right_arm->m_vPosition.z = m_vPosition.z;
//
//
//
//	m_pCube_Head->Update();
//	m_pCube_Left_leg->Update();
//	m_pCube_Right_leg->Update();
//	m_pCube_Left_arm->Update();
//	m_pCube_Right_arm->Update();
}

void Cube::Render()
{
	if (pSphere->isPicked == true)
	{
		g_pDevice->SetMaterial(&DXUtil::RED_MTRL);
	}
	else
	{
		g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
	}
	D3DXMATRIXA16 mat;
	D3DXMatrixTranslation(&mat, pSphere->center.x, pSphere->center.y, pSphere->center.z);
	g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pDevice->SetTexture(0, NULL);
	m_pSphere->DrawSubset(0);

	////월드 매트릭스 설정해주기
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//g_pDevice->SetFVF(VERTEX_PC::FVF);
	//그릴 도형의 타입, 도형의 갯수, 정점 정보의 시작 주소, 정점의 크기
	//그라데이션 형식으로 그려짐.
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size()/3, &m_vecVertex[0], sizeof(VERTEX_PC));

	//머리그리기
//	m_pCube_Head->Render();
//	m_pCube_Left_leg->Render();
//	m_pCube_Right_leg->Render();
//	m_pCube_Left_arm->Render();
//	m_pCube_Right_arm->Render();
}
