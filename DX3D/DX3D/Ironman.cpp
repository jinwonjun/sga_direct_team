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

	DamageFontNum = 0;
	m_renderMode = RenderMode_ShadowMapping;
	Shaders::Get()->AddList(this, m_renderMode);

	//매쉬 캐릭터 올리기
	m_pSkinnedMesh = new SkinnedMesh;
	m_pSkinnedMesh->SetRadius(1.5f);
	m_pSkinnedMesh->Init(); 
	m_pSkinnedMesh->SetRenderMode(m_renderMode);
	

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

	timer = 0;//체크 타이머 초기화
	checkTimer = false;
}

void Ironman::Update()
{
	if (DamageFontNum > 19)
	{
		DamageFontNum = 0;
	}

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

	D3DXTRACK_DESC track;
	m_pSkinnedMesh->GetAnimationController()->GetTrackDesc(0, &track);
	LPD3DXANIMATIONSET pCurrAnimSet = NULL;
	m_pSkinnedMesh->GetAnimationController()->GetAnimationSet(0, &pCurrAnimSet);
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
	//위아래 짝꿍
	//해제하기
	//pCurrAnimSet->Release();

	//if (m_animIndex > 0)//0
	//m_animIndex--;

	if (!OpenUI)
	{
		if (Keyboard::Get()->KeyPress('W'))
		{
			checkTimer = true;
			m_pSkinnedMesh->status = 2;
		}
		else if (Keyboard::Get()->KeyPress('S'))
		{
			checkTimer = true;
			m_pSkinnedMesh->status = 7;
		}
		else if (Keyboard::Get()->KeyPress('A'))
		{
			checkTimer = true;
			m_pSkinnedMesh->status = 3;
		}
		else if (Keyboard::Get()->KeyPress('D'))
		{
			checkTimer = true;
			m_pSkinnedMesh->status = 4;
		}
		else if (Keyboard::Get()->KeyPress('R'))
		{
			checkTimer = true;
			timer = -0.17f;
			m_pSkinnedMesh->status = 6;
			m_pSkinnedMesh->GetAnimationController()->SetTrackPosition(0, 0);
		}
		else if (Keyboard::Get()->KeyDown(VK_SPACE))
		{
			checkTimer = true;
			timer = -0.055f;
			m_pSkinnedMesh->status = 5;
		}
		else if (Mouse::Get()->ButtonDown(Mouse::Get()->LBUTTON))
		{
			checkTimer = true;
			timer = 0.015f;
			m_pSkinnedMesh->status = 1;
		}
		if (checkTimer)
		{
			timer += 0.001f;
			if (timer > 0.025f)
			{
				checkTimer = false;
				timer = 0;
			}
		}
		else
		{
			m_pSkinnedMesh->status = 0;
		}
	}

	//Debug->AddText("타이머 체크 : ");
	//Debug->AddText(timer);
	//Debug->EndLine();
	//Debug->EndLine();

	m_pBox->Update();
	m_pBox->SetPosition(&m_pos);

	Shoot();

	//혈흔
	SAFE_UPDATE(m_pBlood);
}

void Ironman::Render()
{
	SAFE_RENDER(m_pSkinnedMesh);
	m_pSkinnedMesh->DrawSphereMatrix(m_pSkinnedMesh->GetRootFrame(), NULL);
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
			//temp = p->GetSphere();
			//보스체크 일단 해보기
			for (int i = 0; i < p->GetBossSphere().size(); i++)
			{
				temp = (p->GetBossSphere())[i];

				if (r.CalcIntersectSphere(temp) == true)
				{
					intersectionDistance = D3DXVec3Length(&(temp->center - r.m_pos));

					//최소거리
					if (intersectionDistance < minDistance)
					{
						minDistance = intersectionDistance;
						//sphere = temp;
						tempEnemy = p;

						//맞으면 플레이어 위치 목적지로 입력
						p->SetDestPos(m_pos);
						//맞았다 체크
						p->SetDamage(true);
					}
					//거리 보정 위치값 찾기
					BloodCalPos = r.m_dir * (minDistance - temp->radius) + r.m_pos;

				}
			}
		}

		if (tempEnemy != NULL)
		{
			g_pItem->MonsterDamaged(DamageFontNum);
			DamageFontNum++;
			g_pItem->getMonsterXY(tempEnemy->GetMonsterX(), tempEnemy->GetMonsterY());
			
			tempEnemy->MinusHP();
			m_pBlood->Fire(BloodCalPos, -m_forward);
			//static_cast<BloodManager*>(g_pObjMgr->FindObjectByTag(TAG_PARTICLE))->Fire();
			//break;
		}
	}
}

void Ironman::AnimationModify()
{
	if (g_pKeyboard->KeyPress(VK_LSHIFT))
	{

	}
	else
	{
		D3DXMatrixRotationY(&matRotY, g_pCamera->m_rotY + D3DX_PI);
		matTemp = matRotY;
	}

	D3DXVECTOR3 m_pos = g_pObjMgr->FindObjectByTag(TAG_PLAYER)->GetPosition();
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixRotationY(&matR, D3DX_PI);
	D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);

	//카메라 고도 경사를 어떻게 해야되나!
	D3DXMatrixRotationX(&matRotX, (-1)*g_pCamera->m_rotX * (0.5f));

	if (g_pKeyboard->KeyPress(VK_LSHIFT))
	{
		m_matWorld = matS *matRotX * matTemp * matT;
	}
	else
	{
		m_matWorld = matS *matRotX * matRotY * matT;
	}

	//skinnedMesh에서 X파일 위치 및 스케일 조정부분.
	m_pSkinnedMesh->SetWorldMatrix(&m_matWorld);
}

void Ironman::RenderUseShader_0()
{
	m_pSkinnedMesh->RenderUseShader_0();
}

void Ironman::RenderUseShader_1()
{
	m_pSkinnedMesh->RenderUseShader_1();
}

