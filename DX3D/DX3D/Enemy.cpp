#include "stdafx.h"
#include "Enemy.h"
#include "AStar.h"
#include "AStarNode.h"
#include "BoundingBox.h"


//obj파일 불러오기
#include "DrawingGroup.h"
#include "ObjLoader.h"

#include "SkinnedMesh.h"

#define SCALE 10.00f

Enemy::Enemy(D3DXVECTOR3& pos, CString path, CString fileName, int enemyNum)
{
	m_destPos = m_pos = pos;
	m_moveSpeed = 0.4f;
	m_rotationSpeed = 0.1f;
	m_maxStepHeight = 2.0f;

	m_forward = D3DXVECTOR3(0, 0, 1);
	m_isMoving = false;
	m_HP = 1;
	m_ItemDrop = false;

	m_path = path;			// "resources/zealot/";
	m_filename = fileName;	// "combine_test.X";

	m_radius = 1.7f;
	m_SphereHeight = 7.0f;

	m_enemyNum = enemyNum;
}


Enemy::~Enemy()
{
	SAFE_RELEASE(m_pSphereMesh);
	SAFE_RELEASE(m_pBox);

	//obj로드 객체 전부 삭제
	//for (auto p : m_vecDrawingGroup)
	//{
	//	SAFE_RELEASE(p);
	//}
}

void Enemy::Init()
{
	m_pBox = new BoundingBox(D3DXVECTOR3(50.0f, 15.0f, 50.0f)); m_pBox->Init();
	D3DXCreateSphere(g_pDevice, m_radius, 10, 10, &m_pSphereMesh, NULL);
	m_pBounidngSphere = new BoundingSphere(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_radius);

	//D3DXMATRIXA16 matS, matT, matRX, matRY;
	//D3DXMatrixScaling(&matS, 5.0f, 5.0f, 5.0f);
	//D3DXMatrixRotationX(&matRX, D3DX_PI * 3 / 2);
	//D3DXMatrixRotationY(&matRY, D3DX_PI);
	//m_matWorld = matS * matRX;// *matRY;


	//obj객체 로드 부분
	//ObjLoader loader;
	//loader.Load("resources/obj", "SCV.obj", &m_matWorld, m_vecDrawingGroup);
	m_pSkinnedMesh = new SkinnedMesh;
	m_pSkinnedMesh->Init();
	m_pSkinnedMesh->Load(m_path, m_filename);

	D3DXMatrixIdentity(&ApplyMatWorld);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&m_matWorld);
}

void Enemy::Update()
{
	UpdatePosition();
	m_pBox->Update();
	m_pBox->SetPosition(&m_pos);
	m_pBounidngSphere->center = D3DXVECTOR3(m_pos.x, m_pos.y + m_SphereHeight, m_pos.z);
	D3DXMatrixTranslation(&m_SphereMat, m_pBounidngSphere->center.x, m_pBounidngSphere->center.y, m_pBounidngSphere->center.z);

	AnimationModify();
	SAFE_UPDATE(m_pSkinnedMesh);
}

void Enemy::Render()
{
	//m_pBox->Render();
	//////////////////////////구체 그려주기//////////////////////////////
	g_pDevice->SetTransform(D3DTS_WORLD, &m_SphereMat);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pSphereMesh->DrawSubset(0);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	////////////////////////////////////////////////////////////////////



	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	SAFE_RENDER(m_pSkinnedMesh);



	
}

void Enemy::UpdatePosition()
{
	D3DXVECTOR3 targetPos;
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, m_radius, m_radius, m_radius);

	D3DXMATRIXA16 matT, matR;
	float	height = 0;
	bool isIntersected = true;

	targetPos = m_pos + m_forward  * m_moveSpeed;

	if (g_pCurrentMap != NULL)
	{
		isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
	}

	//if (isIntersected == true)
	//{

	//}
	//else
	//{
	//	m_pos = targetPos;
	//}

	//바운딩 박스에 닿았을때 거리가 10보다 크면 이동 -> 10보다 작으면 멈춤
	if (D3DXVec3Length(&(m_destPos - m_pos)) > 10.f)
	{
		m_pSkinnedMesh->status = 3;	//이동
		m_isMoving = true;
	}
	else
	{
		m_pSkinnedMesh->status = 4; //멈춤
		m_isMoving = false;
	}

	if (m_isMoving)
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
		D3DXVECTOR3 forwardNormalized;
		D3DXVec3Normalize(&forwardNormalized, &forward);

		D3DXMATRIXA16 matRotY;
		D3DXMatrixRotationY(&matRotY, m_rot.y);
		//정면 방향 벡터 가져오자
		D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRotY);

		float dot;		//내적의 값
		float radian;	//내적의 값을 역코사인 해서 구한 최종 각도
		
		D3DXVECTOR3 m_forwardNormalized;
		D3DXVec3Normalize(&m_forwardNormalized, &m_forward);

		dot = D3DXVec3Dot(&m_forwardNormalized, &forwardNormalized);
		radian = (float)acos(dot);

		Debug->AddText("Radian : " + to_string(radian));
		Debug->EndLine();

		D3DXVECTOR3 rightDir;	//우향벡터
		D3DXVec3Cross(&rightDir, &m_forward, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		//우향벡터와 바라보는 벡터의 내적이 0보다 크면 왼쪽
		//D3DXVECTOR3 rotY;
		if (D3DXVec3Dot(&rightDir, &forwardNormalized) > 0)
		{
			//왼쪽			
			m_rot.y -= radian * m_rotationSpeed;
		}
		else
		{
			//오른쪽
			m_rot.y += radian * m_rotationSpeed;
		}

		D3DXMATRIXA16 matR;

		D3DXMatrixRotationY(&matR, m_rot.y);

		m_pos.y = height; //+ 5.0f;
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

void Enemy::AnimationModify()
{
	D3DXMATRIXA16 matRotY, matRot, m_matWorldT;
	D3DXMatrixRotationY(&matRotY, m_rot.y);
	matRot = matRotY;

	D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRot);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixRotationY(&matR, D3DX_PI);
	D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);

	D3DXMATRIXA16 matTemp;
	matTemp = matS * matRotY * matR * matT;

	m_pSkinnedMesh->SetWorldMatrix(&matTemp);
}
