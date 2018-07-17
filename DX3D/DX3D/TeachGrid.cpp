#include "stdafx.h"
#include "TeachGrid.h"


TeachGrid::TeachGrid()
{
}


TeachGrid::~TeachGrid()
{
}

void TeachGrid::Init()
{
	//����
	float interval = 1.0f;
	//�� ����
	int numHalfLine = 50;
	float halfLength = interval * numHalfLine;

	D3DCOLOR c;
	float tmpInterval;
	for (int i = 0; i < numHalfLine; i++)
	{
		tmpInterval = interval * i;
		c = (i % 5 == 0) ? D3DCOLOR_XRGB(255, 255, 255) :
			D3DCOLOR_XRGB(128, 128, 128);
		m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-halfLength, 0.f, tmpInterval), c));
		m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(halfLength, 0.f, tmpInterval), c));

		m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-halfLength, 0.f, -tmpInterval), c));
		m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(halfLength, 0.f, -tmpInterval), c));


		m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(tmpInterval, 0.f, -halfLength), c));
		m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(tmpInterval, 0.f, halfLength), c));

		m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-tmpInterval, 0.f, -halfLength), c));
		m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-tmpInterval, 0.f, halfLength), c));

	}

	//x��
	c = D3DCOLOR_XRGB(255, 0, 0);

	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-halfLength, 0.0f, 0.0f), c));
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(halfLength, 0.0f, 0.0f), c));

	//z��
	//c = D3DCOLOR_XRGB(0, 255, 0);
	//m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, -halfLength, 0.0f), c));
	//m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, halfLength, 0.0f), c));

	//y��
	c = D3DCOLOR_XRGB(0, 0, 255);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, 0.0f, -halfLength), c));
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, 0.0f, halfLength), c));
}

void TeachGrid::Render()
{
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	//DrawPrimitiveUP �ý��� �޸𸮸� ����ؼ� �׸���, UP���� �� ���۸� ����ؼ� �׸���
	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2, &m_vecVertex[0], sizeof(m_vecVertex));
}
