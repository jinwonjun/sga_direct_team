#include "stdafx.h"
#include "Walls.h"


Walls::Walls()
{
}


Walls::~Walls()
{
}

void Walls::Init()
{
	vector<D3DXVECTOR3> vec;
	/*vec.push_back(D3DXVECTOR3(-1.0f, -1.0f, -1.0f));
	vec.push_back(D3DXVECTOR3(-1.0f, 1.0f, -1.0f));
	vec.push_back(D3DXVECTOR3(1.0f, 1.0f, 0.0f));
	vec.push_back(D3DXVECTOR3(1.0f, -1.0f, 0.0f));*/
	//4, 0, 3, 4, 3, 7	// 하
	vec.push_back(D3DXVECTOR3(-1.0f, -1.0f, 1.0f));
	vec.push_back(D3DXVECTOR3(-1.0f, -1.0f, -1.0f));
	vec.push_back(D3DXVECTOR3(1.0f, -1.0f, -1.0f));
	vec.push_back(D3DXVECTOR3(1.0f, -1.0f, 1.0f));

	//D3DXVECTOR3 n(0, 0, -1);
	D3DXVECTOR3 n(0, 1, -1);

	m_vecWall0.push_back(VERTEX_PN(vec[0], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[1], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[2], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[0], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[2], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[3], D3DXVECTOR3(n)));

	//1, 5, 6, 1, 6, 2,	// 상
	vec.push_back(D3DXVECTOR3(-1.0f, 1.0f, -1.0f));//4
	vec.push_back(D3DXVECTOR3(-1.0f, 1.0f, 1.0f));//5
	vec.push_back(D3DXVECTOR3(1.0f, 1.0f, 1.0f));//6
	vec.push_back(D3DXVECTOR3(1.0f, 1.0f, -1.0f));//7

	m_vecWall0.push_back(VERTEX_PN(vec[4], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[5], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[6], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[4], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[6], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[7], D3DXVECTOR3(n)));

	D3DXMATRIXA16 matT, matR, matS, mat;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, 3, 3, 3);
	D3DXMatrixTranslation(&matT, 0, 15, 0);

	for (size_t i = 0; i < m_vecWall0.size(); i++)
	{
		mat = matS * matT;
		D3DXVec3TransformCoord(&m_vecWall0[i].p, &m_vecWall0[i].p, &mat);
	}

	{
		D3DLIGHT9 light;
		D3DXVECTOR3 pos(0.0f, 1.0f, -3.0f);
		//D3DXCOLOR c = RED;
		//light = DXUtil::InitPoint(&pos, &c);
		//light.Range = 4.0f;
		g_pDevice->SetLight(1, &light);
		g_pDevice->LightEnable(1, true);
	}
}

void Walls::Update()
{
}

void Walls::Render()
{
	//거리가 멀어질수록 광원이 어두워지고 멀어지고~
	//D3DRS_NORMALIZENORMALS : 뷰변환에서 모든 법선을 정규화시킨다. 왜곡을 막기위해 쓰는 상태, 다만 연산량 때문에 느려질 수 있다.

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	
	//환경광 효과 주기
	//g_pDevice->SetRenderState(D3DRS_AMBIENT, 0x00309030);

	//스펙큘러 : 카메라가 보는 방향에 따라서 빛 세기가 달라짐. 
	g_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	g_pDevice->SetMaterial(&DXUtil::GREEN_MTRL);

	g_pDevice->SetFVF(VERTEX_PN::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,m_vecWall0.size() / 3,&m_vecWall0[0], sizeof(VERTEX_PN));
}
