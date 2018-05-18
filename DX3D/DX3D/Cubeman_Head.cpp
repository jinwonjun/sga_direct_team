#include "stdafx.h"
#include "Cubeman_Head.h"


Cubeman_Head::Cubeman_Head() : m_rotY(0.0f), RotY(0.0f)
, m_moveSpeed(0.1f), m_vPosition(0, 0, 0)
{
}


Cubeman_Head::~Cubeman_Head()
{
}

void Cubeman_Head::Init()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&mT);
	D3DXMatrixIdentity(&mR);
	
	m_vPosition = Cube::m_vPosition;//몸통의 중심축 좌표값 가져오기

	m_vPosition.y += 1.5f;//몸통 좌표값 가져와서 기준으로 축 이동

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

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f * 0.5, -1.0f* 0.5, -1.0f* 0.5), green));//0
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f* 0.5, 1.0f* 0.5, -1.0f* 0.5), red));//1
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f* 0.5, 1.0f* 0.5, -1.0f* 0.5), blue));//2

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f* 0.5, -1.0f* 0.5, -1.0f* 0.5), green));//0
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f* 0.5, 1.0f* 0.5, -1.0f* 0.5), blue));//2
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f* 0.5, -1.0f* 0.5, -1.0f* 0.5), green));//3

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f* 0.5, -1.0f* 0.5, 1.0f* 0.5), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f* 0.5, 1.0f* 0.5, 1.0f* 0.5), green));//6
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f* 0.5, 1.0f* 0.5, 1.0f* 0.5), blue));//5

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f* 0.5, -1.0f* 0.5, 1.0f* 0.5), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f* 0.5, -1.0f* 0.5, 1.0f* 0.5), red));//7
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f* 0.5, 1.0f* 0.5, 1.0f* 0.5), green));//6

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f* 0.5, -1.0f* 0.5, 1.0f* 0.5), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f* 0.5, 1.0f* 0.5, 1.0f* 0.5), blue));//5
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f* 0.5, 1.0f* 0.5, -1.0f* 0.5), red));//1

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f* 0.5, -1.0f* 0.5, 1.0f* 0.5), red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f* 0.5, 1.0f* 0.5, -1.0f* 0.5), red));//1
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f* 0.5, -1.0f* 0.5, -1.0f* 0.5), green));//0

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f* 0.5, -1.0f* 0.5, -1.0f* 0.5), green));//3
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f* 0.5, 1.0f* 0.5, -1.0f* 0.5), blue));//2
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f* 0.5, 1.0f* 0.5, 1.0f* 0.5), green));//6

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f* 0.5, -1.0f* 0.5, -1.0f* 0.5), green));//3
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f* 0.5, 1.0f* 0.5, 1.0f* 0.5), green));//6
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f* 0.5, -1.0f* 0.5, 1.0f* 0.5), red));//7

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f)* 0.5, red));//1
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, 1.0f)* 0.5, blue));//5
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f)* 0.5, green));//6

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, 1.0f, -1.0f)* 0.5, red));//1
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, 1.0f)* 0.5, green));//6
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, 1.0f, -1.0f)* 0.5, blue));//2

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f)* 0.5, red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, -1.0f)* 0.5, green));//0
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f)* 0.5, green));//3

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-1.0f, -1.0f, 1.0f)* 0.5, red));//4
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, -1.0f)* 0.5, green));//3
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(1.0f, -1.0f, 1.0f)* 0.5, red));//7
}

void Cubeman_Head::Update()
{
	//D3DXMatrixRotationY(&mR, RotY);
	//D3DXMatrixRotationX(&mR, RotX);

	//위치 이동행렬
	D3DXMatrixTranslation(&mT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = mR * mT;
}

void Cubeman_Head::Render()
{
	////월드 매트릭스 설정해주기
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pDevice->SetFVF(VERTEX_PC::FVF);

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//그릴 도형의 타입, 도형의 갯수, 정점 정보의 시작 주소, 정점의 크기
	//그라데이션 형식으로 그려짐.
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(VERTEX_PC));
}
