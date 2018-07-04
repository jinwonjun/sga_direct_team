#include "stdafx.h"
#include "Ironman.h"

#include "SkinnedMesh.h"
#include "AllocateHierarchy.h"
#include "BoundingBox.h"
#include "Ray.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "BloodEffect.h"

//0.05f
#define SCALE 0.1f

Ironman::Ironman()
{
	//m_baseRotY = D3DX_PI;

	//m_pRootFrame = NULL;
	//m_pAnimController = NULL;
	//m_fBlendTime = 0.3f;
	//m_fPassedBlendTime = 0.0f;
	//m_animIndex = 0;
	//m_bWireFrame = false;
	//m_bDrawFrame = true;
	//m_bDrawSkeleton = false;

	//status = 4;
}


Ironman::~Ironman()
{
	SAFE_RELEASE(m_pBox);
	SAFE_RELEASE(m_pBlood);

	m_pSkinnedMesh->~SkinnedMesh();
}

void Ironman::Init()
{
	g_pObjMgr->AddToTagList(TAG_PLAYER, this);
	g_pCamera->SetTarget(&m_pos);
	g_pKeyboardManager->SetMovingTarget(&m_keyState);
	

	//매쉬 캐릭터 올리기
	m_pSkinnedMesh = new SkinnedMesh;
	m_pSkinnedMesh->Init();
	CString path = "resources/playerX/";
	CString filename = "combine.X";
	//CString path = "resources/zealot/";
	//CString filename = "combine_test.X";

	m_pSkinnedMesh->Load(path, filename);

	m_pBox = new BoundingBox(D3DXVECTOR3(2.0f, 1.0f, 2.0f)); m_pBox->Init();

	m_pBlood = new BloodEffect(); m_pBlood->Init();

	//위치 초기화
	BloodCalPos = D3DXVECTOR3(0, 0, 0);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&m_matWorld);
	


	keyPress = false;

	//시작위치 조정
	m_pos.y = 10;

	//UI 열리면 캐릭터 이동 막기
	OpenUI = false;


	D3DXMatrixIdentity(&matRotY);
	D3DXMatrixIdentity(&matRotX);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matTemp);
}

void Ironman::Update()
{
	/*
	idle = 1;
	shot = 2;
	run = 3;
	left = 4;
	right = 5;
	jump = 6;
	reload = 7;
	back = 8;
	*/
	if (Keyboard::Get()->KeyDown('I'))
	{
		OpenUI = !OpenUI;
	}
	
	if (!OpenUI)
	{
		IUnitObject::UpdateKeyboardState();
		IUnitObject::UpdatePosition();
	}

	AnimationModify();
	SAFE_UPDATE(m_pSkinnedMesh);

	//오른손 좌표 가져오기
	RightHand = m_pSkinnedMesh->GetHandMatrix();


	//D3DXTRACK_DESC track;
	//m_pSkinnedMesh->GetAnimationController()->GetTrackDesc(0, &track);
	//LPD3DXANIMATIONSET pCurrAnimSet = NULL;
	//m_pSkinnedMesh->GetAnimationController()->GetAnimationSet(0, &pCurrAnimSet);
	//pCurrAnimSet->GetPeriod(); //전체 시간
	//Debug->EndLine();
	//Debug->EndLine();
	//Debug->AddText("전체 시간 : ");
	//Debug->AddText(pCurrAnimSet->GetPeriod());
	//Debug->EndLine();
	//Debug->AddText("현재 시간 : ");
	//pCurrAnimSet->GetPeriodicPosition(track.Position); //현재 시간
	//Debug->AddText(pCurrAnimSet->GetPeriodicPosition(track.Position));
	//Debug->EndLine();
	//Debug->EndLine();



	if (!OpenUI)
	{
		if (Keyboard::Get()->KeyPress('W'))
		{
			m_pSkinnedMesh->status = 2;
		}
		else if (Keyboard::Get()->KeyPress('S'))
		{
			m_pSkinnedMesh->status = 7;
		}
		else if (Keyboard::Get()->KeyPress('A'))
		{
			//if (m_animIndex > 0)//0
			//m_animIndex--;
			m_pSkinnedMesh->status = 3;
		}
		else if (Keyboard::Get()->KeyPress('D'))
		{
			//if (m_animIndex > 0)//0
			//m_animIndex--;
			m_pSkinnedMesh->status = 4;
		}
		else if (Keyboard::Get()->KeyPress('R'))
		{
			//if (m_animIndex > 0)//0
			//m_animIndex--;
			m_pSkinnedMesh->status = 6;
		}
		else if (Keyboard::Get()->KeyPress(VK_SPACE))
		{
			m_pSkinnedMesh->status = 5;
		}
		else if (Mouse::Get()->ButtonPress(Mouse::Get()->LBUTTON))
		{
			//if (m_animIndex > 0)//0
			//m_animIndex--;
			m_pSkinnedMesh->status = 1;
		}

		else//idle상태 만들기
		{
			m_pSkinnedMesh->status = 0;
		}
	}

	m_pBox->Update();
	m_pBox->SetPosition(&m_pos);
	
	Shoot();

	//혈흔
	SAFE_UPDATE(m_pBlood);

	//해제하기
	//pCurrAnimSet->Release();
}

void Ironman::Render()
{
	SAFE_RENDER(m_pSkinnedMesh);
	SAFE_RENDER(m_pBlood);
}

void Ironman::Shoot()
{
	if (g_pMouse->ButtonDown(Mouse::LBUTTON))
	{
		Ray r = Ray::RayAtWorldSpace(g_pCamera->GetMCenter().x, g_pCamera->GetMCenter().y);

		BoundingSphere* sphere = NULL;
		float minDistance = FLT_MAX;
		float intersectionDistance;
		EnemyManager* em = static_cast <EnemyManager *> (g_pObjMgr->FindObjectByTag(TAG_ENEMY));
		BoundingSphere* temp = NULL;
		Enemy* tempEnemy = NULL;
		for (auto p : em->GetVecEnemy())
		{
			if (p->GetHP() <= 0) continue;
			temp = p->GetSphere();
			if (r.CalcIntersectSphere(temp) == true)
			{
				intersectionDistance = D3DXVec3Length(&(temp->center - r.m_pos));
				//printf("거리 : %f\n", intersectionDistance);
				//최소거리
				if (intersectionDistance < minDistance)
				{
					minDistance = intersectionDistance;
					//sphere = temp;
					tempEnemy = p;
				}
				//거리 보정 위치값 찾기
				BloodCalPos = r.m_dir * (minDistance - temp->radius) + r.m_pos;

				//적이 그리게 할 수 있는 시그널 주기
				//return true;
			}
		}

		if (tempEnemy != NULL)
		{
			tempEnemy->MinusHP();
			m_pBlood->Fire(BloodCalPos, -m_forward);
			//static_cast<BloodManager*>(g_pObjMgr->FindObjectByTag(TAG_PARTICLE))->Fire();
			//break;
		}
	}
}

void Ironman::AnimationModify()
{
	if (!(g_pKeyboard->KeyPress(VK_LSHIFT)))
	{
		D3DXMatrixRotationY(&matRotY, g_pCamera->m_rotY);
		matTemp = matRotY;
	}
	if (g_pKeyboard->KeyUp(VK_LSHIFT))//시프트키 땔때 누르기 바로 전 값 전달
	{
		matRotY = matTemp;
	}

	D3DXVECTOR3 m_pos = g_pObjMgr->FindObjectByTag(TAG_PLAYER)->GetPosition();
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixRotationY(&matR, D3DX_PI);
	D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);
	
	//카메라 고도 경사를 어떻게 해야되나!
	D3DXMatrixRotationX(&matRotX, (-1)*g_pCamera->m_rotX * (0.5f));

	if (!(g_pKeyboard->KeyPress(VK_LSHIFT)))
	{
		m_matWorld = matS *matRotX * matRotY* matR * matT;
	}
	else
	{
		m_matWorld = matS *matRotX * matTemp* matR * matT;
	}

	//skinnedMesh에서 X파일 위치 및 스케일 조정부분.
	m_pSkinnedMesh->SetWorldMatrix(&m_matWorld);
}

