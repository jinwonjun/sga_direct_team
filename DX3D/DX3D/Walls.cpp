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
	vec.push_back(D3DXVECTOR3(-1.0f, -1.0f, -1.0f));
	vec.push_back(D3DXVECTOR3(-1.0f, 1.0f, -1.0f));
	vec.push_back(D3DXVECTOR3(1.0f, 1.0f, 0.0f));
	vec.push_back(D3DXVECTOR3(1.0f, -1.0f, 0.0f));

	D3DXVECTOR3 n(0, 0, -1);

	m_vecWall0.push_back(VERTEX_PN(vec[0], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[1], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[2], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[0], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[2], D3DXVECTOR3(n)));
	m_vecWall0.push_back(VERTEX_PN(vec[3], D3DXVECTOR3(n)));

	//vector<D3DXVECTOR3> vec;

	vec.push_back(D3DXVECTOR3(-1.0f*2 , 0.0f , -1.0f * 2));//4
	vec.push_back(D3DXVECTOR3(-1.0f * 2, 2.0f , -1.0f * 2));//5
	vec.push_back(D3DXVECTOR3(1.0f * 2, 2.0f , 0.0f * 2));//6
	vec.push_back(D3DXVECTOR3(1.0f * 2, 0.0f , 0.0f * 2));//7

	D3DXVECTOR3 v(1, 0, -1);
	// 0 1 2 0 2 3
	// 4 5 6 4 6 7
	m_vecWall0.push_back(VERTEX_PN(vec[4], D3DXVECTOR3(v)));
	m_vecWall0.push_back(VERTEX_PN(vec[5], D3DXVECTOR3(v)));
	m_vecWall0.push_back(VERTEX_PN(vec[6], D3DXVECTOR3(v)));
	m_vecWall0.push_back(VERTEX_PN(vec[4], D3DXVECTOR3(v)));
	m_vecWall0.push_back(VERTEX_PN(vec[6], D3DXVECTOR3(v)));
	m_vecWall0.push_back(VERTEX_PN(vec[7], D3DXVECTOR3(v)));

	D3DXMATRIXA16 matT, matR, matS, mat;
	
	D3DXMatrixScaling(&matS, 3, 3, 3);

	for (size_t i = 0; i < m_vecWall0.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecWall0[i].p, &m_vecWall0[i].p, &matS);
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
	//�Ÿ��� �־������� ������ ��ο����� �־�����~

	//D3DRS_NORMALIZENORMALS : �亯ȯ���� ��� ������ ����ȭ��Ų��. �ְ��� �������� ���� ����, �ٸ� ���귮 ������ ������ �� �ִ�.

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	
	//ȯ�汤 ȿ�� �ֱ�
	//g_pDevice->SetRenderState(D3DRS_AMBIENT, 0x00309030);

	//����ŧ�� : ī�޶� ���� ���⿡ ���� �� ���Ⱑ �޶���. 
	g_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);

	g_pDevice->SetFVF(VERTEX_PN::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,m_vecWall0.size() / 3,&m_vecWall0[0], sizeof(VERTEX_PN));


}
