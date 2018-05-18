#include "stdafx.h"
#include "Cubeman_Right_leg.h"


Cubeman_Right_leg::Cubeman_Right_leg() : m_rotY(0.0f), RotY(0.0f)
, m_moveSpeed(0.1f), m_vPosition(0, 0, 0)
{
}


Cubeman_Right_leg::~Cubeman_Right_leg()
{
}

void Cubeman_Right_leg::Init()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&mT);
	D3DXMatrixIdentity(&mR);
	D3DXMatrixIdentity(&mS);

	m_vPosition = Cube::m_vPosition;//몸통의 중심축 좌표값 가져오기

	m_vPosition.y -= 1.7f;//몸통 좌표값 가져와서 기준으로 축 이동
	m_vPosition.x += 0.5f;

	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), green));//0
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), red));//1
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, -1.0f), blue));//2

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), green));//0
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, -1.0f), blue));//2
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f), green));//3

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), blue));//5

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, 1.0f), red));//7
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), blue));//5
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), red));//1

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), red));//1
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), green));//0

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f), green));//3
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, -1.0f), blue));//2
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f), green));//3
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, 1.0f), red));//7

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), red));//1
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), blue));//5
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), red));//1
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f), green));//6
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, -1.0f), blue));//2

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), green));//0
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f), green));//3

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f), green));//3
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, 1.0f), red));//7


	D3DXMatrixScaling(&mS,  0.3f,  0.7f,  0.3f);
}

void Cubeman_Right_leg::Update()
{
	D3DXMatrixTranslation(&mT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = mS * mR * mT;
}

void Cubeman_Right_leg::Render()
{
	////월드 매트릭스 설정해주기
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pDevice->SetFVF(VERTEX_PC::FVF);

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//그릴 도형의 타입, 도형의 갯수, 정점 정보의 시작 주소, 정점의 크기
	//그라데이션 형식으로 그려짐.
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(VERTEX_PC));
}
