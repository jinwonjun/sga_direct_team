#include "stdafx.h"
#include "Grid.h"


Grid::Grid()
{
}


Grid::~Grid()
{
}

void Grid::Init()
{
	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
	D3DCOLOR black = D3DCOLOR_XRGB(0, 0, 0);
	D3DCOLOR gray = D3DCOLOR_XRGB(200, 200, 200);

	int NUM_TILE = 10;
	int width = 2.0f;
	int DIM = NUM_TILE + 1;

	//좌표 초기화 및 위치 이동
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixTranslation(&m_matWorld, -NUM_TILE, -1, -NUM_TILE);

	//가로축 그리기
	for (int row = 0; row < DIM; row++)
	{
		if (row % 5==0)
		{
			for (int col = 0; col < 2; col++)
			{
				vecLine_X.push_back(VERTEX_PC(D3DXVECTOR3(col * (width * NUM_TILE), 0, row * width), black));
			}
		}
		else
		{
			for (int col = 0; col < 2; col++)
			{
				vecLine_X.push_back(VERTEX_PC(D3DXVECTOR3(col * (width * NUM_TILE), 0, row * width), gray));
			}
		}
		
	}

	//세로축 그리기
	for (int row = 0; row < DIM; row++)
	{
		if (row % 5 == 0)
		{
			for (int col = 0; col < 2; col++)
			{
				vecLine_Y.push_back(VERTEX_PC(D3DXVECTOR3(row * width, 0, col * width * NUM_TILE), black));
			}
		}
		else
		{
			for (int col = 0; col < 2; col++)
			{
				vecLine_Y.push_back(VERTEX_PC(D3DXVECTOR3(row * width, 0, col * width * NUM_TILE), gray));
			}
		}
	}

	D3DCOLOR c;
	//축 그리기
	//x축
	c = D3DCOLOR_XRGB(255, 0, 0);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(-NUM_TILE, 0.0f, 0.0f), c));
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(NUM_TILE, 0.0f, 0.0f), c));
	//y축
	c = D3DCOLOR_XRGB(0, 255, 0);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, -NUM_TILE, 0.0f), c));
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, NUM_TILE, 0.0f), c));
	//z축
	c = D3DCOLOR_XRGB(0, 0, 255);
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, 0.0f, -NUM_TILE), c));
	m_vecVertex.push_back(VERTEX_PC(D3DXVECTOR3(0.0f, 0.0f, NUM_TILE), c));
}


void Grid::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pDevice->SetFVF(VERTEX_PC::FVF);

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//vecLine.size()/2
	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, vecLine_X.size() / 2, &vecLine_X[0], sizeof(VERTEX_PC));
	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, vecLine_Y.size() / 2, &vecLine_Y[0], sizeof(VERTEX_PC));

	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2, &m_vecVertex[0], sizeof(m_vecVertex));

	//DrawText(g_pDevice->get)

}
