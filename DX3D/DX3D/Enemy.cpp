#include "stdafx.h"
#include "Enemy.h"
#include "AStar.h"
#include "AStarNode.h"
#include "BoundingBox.h"


//obj파일 불러오기
#include "DrawingGroup.h"
#include "ObjLoader.h"

Enemy::Enemy(D3DXVECTOR3& pos)
{
	m_pVB = NULL;
	m_pIB = NULL;

	m_destPos = m_pos = pos;
	m_moveSpeed = 0.1f;
	m_rotationSpeed = 0.1f;
	m_maxStepHeight = 2.0f;

	m_forward = D3DXVECTOR3(0, 0, 1);

	m_isMoving = false;

	m_HP = 1;
}


Enemy::~Enemy()
{
	SAFE_RELEASE(m_pBox);

	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);

	//obj로드 객체 전부 삭제
	for (auto p : m_vecDrawingGroup)
	{
		SAFE_RELEASE(p);
	}
}

void Enemy::Init()
{
	InitVertex();
	m_pBox = new BoundingBox(D3DXVECTOR3(22.0f, 15.0f, 22.0f)); m_pBox->Init();
	float radius = 1.0f;
	D3DXCreateSphere(g_pDevice, radius, 10, 10, &m_pSphere, NULL);
	m_pBounidngSphere = new BoundingSphere(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), radius);

	D3DXMATRIXA16 matS, matT, matRX, matRY;
	D3DXMatrixScaling(&matS, 5.0f, 5.0f, 5.0f);
	D3DXMatrixRotationX(&matRX, D3DX_PI * 3 / 2);
	//D3DXMatrixRotationY(&matRY, D3DX_PI);
	m_matWorld = matS * matRX;// *matRY;
	//obj객체 로드 부분
	ObjLoader loader;
	loader.Load("resources/obj", "SCV.obj", &m_matWorld, m_vecDrawingGroup);
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
	//g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,m_VBDesc.Size, 0, m_IBDesc.Size / 3);


	//obj객체 그리기
	for (auto p : m_vecDrawingGroup)
	{
		SAFE_RENDER(p);
	}
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

	D3DXMATRIXA16 matT, matR;
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

	if (m_destPos != m_pos)
	{
		m_isMoving = true;
	}
	else
	{
		m_isMoving = false;
	}
	if (m_isMoving)
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
		D3DXVECTOR3 forwardNormalized = forward;
		D3DXVec3Normalize(&forwardNormalized, &forwardNormalized);

		D3DXMATRIXA16 matRotY;
		D3DXMatrixRotationY(&matRotY, m_rot.y);
		//정면 방향 벡터 가져오자
		D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRotY);

		float dot;		//내적의 값
		float radian;	//내적의 값을 역코사인 해서 구한 최종 각도
		dot = D3DXVec3Dot(&m_forward, &forwardNormalized);
		radian = (float)acos(dot);

		D3DXVECTOR3 rightDir;	//우향벡터
		D3DXVec3Cross(&rightDir, &m_forward, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		//우향벡터와 바라보는 벡터의 내적이 0보다 크면 왼쪽
		D3DXVECTOR3 rotY;
		if (D3DXVec3Dot(&rightDir, &forwardNormalized) > 0)
		{
			//왼쪽			
			rotY.y = -radian;
		}
		else
		{
			//오른쪽
			rotY.y = radian;
		}

		D3DXMATRIXA16 matR;
		//if (m_rot.y < radian)
		//{
		//	m_forward = forwardNormalized;
		m_rot += rotY * m_rotationSpeed;
		//}
		//else if (m_rot.y >= radian)
		//{
		//	m_rot.y = radian;
		//}
		//m_rot.y = radian;
		D3DXMatrixRotationY(&matR, m_rot.y);

		m_pos.y = height + 5.0f;
		pos = m_pos + forwardNormalized * m_moveSpeed;
		D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
		m_matWorld = matS * matR * matT;
		SetPosition(&pos);
	}


}

void Enemy::SetDestPos(D3DXVECTOR3 & pos)
{
	if (m_isMoving)
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

