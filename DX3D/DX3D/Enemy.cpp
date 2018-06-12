#include "stdafx.h"
#include "Enemy.h"
#include "AStar.h"
#include "AStarNode.h"
#include "BoundingBox.h"

Enemy::Enemy(D3DXVECTOR3& pos)
{
	m_pVB = NULL;
	m_pIB = NULL;

	m_destPos = m_pos = pos;
	m_moveSpeed = 0.2f;
	m_rotationSpeed = 1.0f;
	m_maxStepHeight = 2.0f;

	m_forward.x = 1;

	m_moving = false;

	m_HP = 1;
}


Enemy::~Enemy()
{
	SAFE_RELEASE(m_pBox);

	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
}

void Enemy::Init()
{
	InitVertex();
	m_pBox = new BoundingBox(D3DXVECTOR3(22.0f, 15.0f, 22.0f)); m_pBox->Init();
	float radius = 1.4f;
	D3DXCreateSphere(g_pDevice, radius, 10, 10, &m_pSphere, NULL);
	m_pBounidngSphere = new BoundingSphere(D3DXVECTOR3(m_pos.x + 5, m_pos.y + 5, m_pos.z + 5), radius);
}

void Enemy::Update()
{
	UpdatePosition();
	m_pBox->Update();
	m_pBox->SetPosition(&m_pos);
	m_pBounidngSphere->center = m_pos;
}

void Enemy::Render()
{
	//m_pBox->Render();

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetTexture(0, NULL);
	m_pSphere->DrawSubset(0);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
	g_pDevice->SetIndices(m_pIB);
	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
		m_VBDesc.Size, 0, m_IBDesc.Size / 3);
}

void Enemy::InitVertex()
{
	vector<D3DXVECTOR3> vecPos;
	for (size_t i = 0; i < CUBE_VERTEX_SIZE; i++)
	{
		vecPos.push_back(g_aCubeVertex[i]);
	}

	SetVertex(m_vecVertex, m_vecIndex, vecPos);
	SetBuffer(m_pVB, m_pIB, m_vecVertex, m_vecIndex);

	m_pVB->GetDesc(&m_VBDesc);
	m_pIB->GetDesc(&m_IBDesc);
}

void Enemy::SetVertex(vector<VERTEX_PC>& vecVertexOut, vector<WORD>& vecIndexOut, vector<D3DXVECTOR3> vecPos)
{
	vecVertexOut.push_back(VERTEX_PC(vecPos[0], BLUE));
	vecVertexOut.push_back(VERTEX_PC(vecPos[1], RED));
	vecVertexOut.push_back(VERTEX_PC(vecPos[2], GREEN));
	vecVertexOut.push_back(VERTEX_PC(vecPos[3], RED));
	vecVertexOut.push_back(VERTEX_PC(vecPos[4], BLUE));
	vecVertexOut.push_back(VERTEX_PC(vecPos[5], RED));
	vecVertexOut.push_back(VERTEX_PC(vecPos[6], GREEN));
	vecVertexOut.push_back(VERTEX_PC(vecPos[7], RED));

	for (size_t i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		vecIndexOut.push_back(g_aCubeIndex[i]);
	}
}

void Enemy::SetBuffer(LPDIRECT3DVERTEXBUFFER9 & pVb, LPDIRECT3DINDEXBUFFER9 & pIb, vector<VERTEX_PC>& vecVertex, vector<WORD>& vecIndex)
{
	g_pDevice->CreateVertexBuffer(vecVertex.size() * sizeof(VERTEX_PC),
		0, VERTEX_PC::FVF, D3DPOOL_MANAGED, &pVb, NULL);

	VERTEX_PC* pVertex;
	pVb->Lock(0, 0, (LPVOID*)&pVertex, 0);
	memcpy(pVertex, &vecVertex[0], vecVertex.size() * sizeof(VERTEX_PC));
	pVb->Unlock();
	vecVertex.clear();

	g_pDevice->CreateIndexBuffer(vecIndex.size() * sizeof(WORD),
		NULL, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIb, NULL);

	WORD* pIndex;
	pIb->Lock(0, 0, (LPVOID*)&pIndex, 0);
	memcpy(pIndex, &vecIndex[0], vecIndex.size() * sizeof(WORD));
	pIb->Unlock();
	vecIndex.clear();
}

void Enemy::UpdatePosition()
{
	D3DXVECTOR3 targetPos;
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 3.0f, 4.0f, 3.0f);

	D3DXMATRIXA16 matT;
	float	height = 0;
	bool isIntersected = true;

	targetPos = m_pos + m_forward  * m_moveSpeed;

	if (g_pCurrentMap != NULL)
	{
		isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
	}

	if (isIntersected == true)
	{

	}
	else
	{
		m_pos = targetPos;
	}

	m_pos.y = height;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = matS * matT;


	if (m_destPos != m_pos)
	{
		m_moving = true;
	}
	else
	{
		m_moving = false;
	}
	if (m_moving)
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
		D3DXVECTOR3 forwardNormalized = forward;
		D3DXVec3Normalize(&forwardNormalized, &forwardNormalized);
		m_forward = forwardNormalized;
		pos = m_pos + forwardNormalized * 0.1f;
		SetPosition(&pos);
	}


}

void Enemy::SetDestPos(D3DXVECTOR3 & pos)
{
	if (m_moving)
	{
		if (m_destPos != pos)
		{
			m_destPos = pos;
		}
	}
	m_destPos = pos;
}

void Enemy::MoveStop()
{
	m_destPos = m_pos;
}

