#include "stdafx.h"
#include "Ironman.h"
#include "SkinnedMesh.h"
#include "AllocateHierarchy.h"
#include "BoundingBox.h"
#include "Ray.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "BloodEffect.h"

//무기의 장착 상태 가져오는 용도
#include "Gun.h"

#define SCALE 0.1f

Ironman::Ironman()
{

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
	m_pSkinnedMesh->SetRadius(0.1f);
	m_pSkinnedMesh->Init(); 
	m_pSkinnedMesh->SetRenderMode(m_renderMode);
	
	//기본 구체 그리기
	D3DXCreateSphere(g_pDevice, m_pSkinnedMesh->GetRadius(), 10, 10, &m_pSphereMesh, NULL);
	for (int k = 0; k < (m_pSkinnedMesh->GetPlayerMatrix()).size(); k++)
	{
		BoundingSphere* s = new BoundingSphere(D3DXVECTOR3(k, k, k), m_pSkinnedMesh->GetRadius());
		m_vecBoundary.push_back(s);
	}

	CString path = "resources/playerX/";
	CString filename = "combine_All.X";
	m_pSkinnedMesh->Load(path, filename);

	m_pBox = new BoundingBox(D3DXVECTOR3(2.0f, 1.0f, 2.0f)); m_pBox->Init();

	m_pBlood = new BloodEffect(); m_pBlood->Init();

	//위치 초기화
	BloodCalPos = D3DXVECTOR3(0, 0, 0);
	keyPress = false;

	//시작위치 조정
	m_pos.y = 10;

	m_Hp = 100;
	m_MaxHp = 100;
	m_Def = 5;
	m_Atk = 5;
	

	D3DXMatrixIdentity(&matRotY);
	D3DXMatrixIdentity(&matRotX);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matTemp);
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixScaling(&matS, 0.25f, 0.25f, 0.25f);

	timer = 0;//체크 타이머 초기화
	checkTimer = false;
}

void Ironman::Update()
{
	if (DamageFontNum > 19)
	{
		DamageFontNum = 0;
	}

	if (!g_pInventory->Get()->openInven)




	if (!g_pInventory->openInven)
	{
		IUnitObject::UpdateKeyboardState();
		IUnitObject::UpdatePosition();

		AnimationModify();
		AnimationKeySetting();
		SAFE_UPDATE(m_pSkinnedMesh);

		//오른손 좌표 가져오기 - 무기를 착용할때만 돌리기
		if (static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus() != 0)
		{
			RightHand = m_pSkinnedMesh->GetHandMatrix();
		}
		//임시 방편의 산물!, 크기를 없애서 안보이게 만든다!
		else
		{
			D3DXMatrixIdentity(&RightHand);
			RightHand._11 = 0;
			RightHand._22 = 0;
			RightHand._33 = 0;
		}
	}


	D3DXTRACK_DESC track;
	m_pSkinnedMesh->GetAnimationController()->GetTrackDesc(0, &track);
	LPD3DXANIMATIONSET pCurrAnimSet = NULL;
	m_pSkinnedMesh->GetAnimationController()->GetAnimationSet(0, &pCurrAnimSet);

	m_pBox->Update();
	m_pBox->SetPosition(&m_pos);

	// 아이템을착용하면 스텟이 변해야지
	Status();

	Shoot();



	//혈흔
	SAFE_UPDATE(m_pBlood);

	//구체 위치 행렬 받아서 업데이트 해주기
	for (int i = 0; i < m_pSkinnedMesh->GetPlayerMatrix().size(); i++)
	{
		D3DXVECTOR3 tempCenter;
		D3DXVec3TransformCoord(&tempCenter, &tempCenter, &(m_pSkinnedMesh->GetPlayerMatrix())[i]);
		m_vecBoundary[i]->center = tempCenter;
		tempCenter = D3DXVECTOR3(0, 0, 0);//다썼으면 초기화
	}


}

void Ironman::Render()
{
	SAFE_RENDER(m_pSkinnedMesh);
	//m_pSkinnedMesh->DrawSphereMatrix(m_pSkinnedMesh->GetRootFrame(), NULL);
	SAFE_RENDER(m_pBlood);

	//구체 그리기
	for (auto p : m_vecBoundary)
	{
		g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
		D3DXMATRIXA16 mat;
		D3DXMatrixTranslation(&mat, p->center.x, p->center.y, p->center.z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
		g_pDevice->SetTexture(0, NULL);
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_pSphereMesh->DrawSubset(0);
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	}
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
			
			for (int i = 0; i < p->GetSphereVector().size(); i++)
			{
				temp = (p->GetSphereVector())[i];

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
			
			//tempEnemy->MinusHP();
			AttackCalcultate(tempEnemy);

			m_pBlood->Fire(BloodCalPos, -m_forward);
			//static_cast<BloodManager*>(g_pObjMgr->FindObjectByTag(TAG_PARTICLE))->Fire();
			//break;
		}
	}
}

void Ironman::Status()
{
	AddAtk = 0;
	AddMaxHp = 0;
	AddDef = 0;

	for (int i = 1; i < 7; i++)
	{
		AddAtk += g_pInventory->Equip[i].Atk;
		AddMaxHp += g_pInventory->Equip[i].MaxHp;
		AddDef += g_pInventory->Equip[i].Def;
	}

	m_MaxHp = 100 + AddMaxHp;
	m_Def = 5+ AddDef;
	m_Atk = 5+ AddAtk; 

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

	if (static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus() != 0)
	{
		D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	}
	else
	{
		D3DXMatrixScaling(&matS, 0.25f, 0.25f, 0.25f);
	}

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
	D3DXMatrixScaling(&matS, 0, 0, 0);
}

//플레이어 키에 따른 키값 셋팅
void Ironman::AnimationKeySetting()
{
	/*
	인덱스 열람
	idle = 1;
	shot = 2;
	run = 3;
	left = 4;
	right = 5;
	jump = 6;
	reload = 7;
	back = 8;
	===========no_weapons=========
	no_idle = 9;
	no_shot = 10;
	no_run = 11;
	no_left = 12;
	no_right = 13;
	no_jump = 14;
	no_back = 15;
	맨손일때는 리로드 애니가 없음!
	*/
	if (!g_pInventory->openInven)
	{
		if (Keyboard::Get()->KeyPress('W'))
		{
			checkTimer = true;
			if (static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus() == 0)
			{
				m_pSkinnedMesh->status = 10;
			}
			else
			{
				m_pSkinnedMesh->status = 2;
			}
		}
		else if (Keyboard::Get()->KeyPress('S'))
		{
			checkTimer = true;
			if (static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus() == 0)
			{
				m_pSkinnedMesh->status = 14;
			}
			else
			{
				m_pSkinnedMesh->status = 7;
			}
		}
		else if (Keyboard::Get()->KeyPress('A'))
		{
			checkTimer = true;
			if (static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus() == 0)
			{
				m_pSkinnedMesh->status = 11;
			}
			else
			{
				m_pSkinnedMesh->status = 3;
			}
		}
		else if (Keyboard::Get()->KeyPress('D'))
		{
			checkTimer = true;
			if (static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus() == 0)
			{
				m_pSkinnedMesh->status = 12;
			}
			else
			{
				m_pSkinnedMesh->status = 4;
			}
		}
		else if (Keyboard::Get()->KeyPress('R') && static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus() != 0)
		{
			checkTimer = true;
			timer = -0.17f;
			m_pSkinnedMesh->status = 6;
			m_pSkinnedMesh->GetAnimationController()->SetTrackPosition(0, 0);
		}
		else if (Keyboard::Get()->KeyDown(VK_SPACE))
		{
			checkTimer = true;
			if (static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus() == 0)
			{
				timer = -0.02f;
				m_pSkinnedMesh->status = 13;
			}
			else
			{
				timer = -0.055f;
				m_pSkinnedMesh->status = 5;
			}
			m_pSkinnedMesh->GetAnimationController()->SetTrackPosition(0, 0);
		}
		else if (Mouse::Get()->ButtonDown(Mouse::Get()->LBUTTON))
		{
			checkTimer = true;
			if (static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus() == 0)
			{
				timer = -0.02f;
				m_pSkinnedMesh->status = 9;
				m_pSkinnedMesh->GetAnimationController()->SetTrackPosition(0, 0);
			}
			else
			{
				timer = 0.015f;
				m_pSkinnedMesh->status = 1;
			}
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
			if (static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus() == 0)
			{
				m_pSkinnedMesh->status = 8;
			}
			else
			{
				m_pSkinnedMesh->status = 0;
			}
		}
	}
	//Debug->AddText("총 인덱스 값 찍어보기 :");
	//Debug->AddText(static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus());
	//Debug->EndLine();
	//Debug->EndLine();
}

void Ironman::RenderUseShader_0()
{
	m_pSkinnedMesh->RenderUseShader_0();
}

void Ironman::RenderUseShader_1()
{
	m_pSkinnedMesh->RenderUseShader_1();
}


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