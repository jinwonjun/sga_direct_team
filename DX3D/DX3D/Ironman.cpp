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
	m_specular = 10.0f;
	Shaders::Get()->AddList(this, m_renderMode);

	//매쉬 캐릭터 올리기
	m_pSkinnedMesh = new SkinnedMesh;
	m_pSkinnedMesh->SetRadius(0.5f);
	m_pSkinnedMesh->Init(); 
	m_pSkinnedMesh->SetRenderMode(m_renderMode);
	
	//기본 구체 그리기
	D3DXCreateSphere(g_pDevice, m_pSkinnedMesh->GetRadius(), 10, 10, &m_pSphereMesh, NULL);
	for (int k = 0; k < (m_pSkinnedMesh->GetPlayerMatrix()).size(); k++)
	{
		BoundingSphere* s = new BoundingSphere(D3DXVECTOR3(k, k, k), m_pSkinnedMesh->GetRadius());
		s->isDamaged = false;
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
	m_pos.y = 0;
	m_pos.x = -100;
	m_pos.z = 50;

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
	check = -1;
	SphereDrawRender = false;

	//사운드를 위해 만든 bool 변수들
	isRun = false;

	//반동 변수들
	isShoot = false;
	shootTime = 0;
	endTime = 10;
	recoilPower = 0.02f;

	srand(time(NULL));
}

void Ironman::Update()
{
	if (DamageFontNum > 19)
	{
		DamageFontNum = 0;
	}

	
	IUnitObject::UpdateKeyboardState();
	IUnitObject::UpdatePosition();

	AnimationModify();
	AnimationKeySetting();
	SoundSetting();
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
	
	m_pBox->Update();
	m_pBox->SetPosition(&m_pos);

	// 아이템을착용하면 스텟이 변해야지
	if (g_pInventory->isEquipItemChanged)
	{
		Status();

		g_pUIManager->Get_IronManAtk(m_Atk);
		g_pUIManager->Get_IronManDef(m_Def);

		g_pInventory->isEquipItemChanged = false;
	}

	//무기 들었을때
	if (static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus() != 0)
	{
		
			Shoot();
		
		if (shootTime > endTime) isShoot = false;

		if (isShoot)
		{
			// Y = b - aX  : ( Y = m_rotX, X = shootTime , b = recoilPower, a = 2b / endTime)
			g_pCamera->m_rotX -= (recoilPower - 2 * recoilPower / endTime * shootTime);
			shootTime++;
		}
	}
	else
	{
		Hit();
	}



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

	if (g_pKeyboard->KeyDown(VK_F4))
	{
		SphereDrawRender = !SphereDrawRender;
	}
	//구체 그리기
	if (SphereDrawRender)
	{
		//구체 그리기
		for (auto p : m_vecBoundary)
		{
			g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
			D3DXMATRIXA16 mat;
			D3DXMatrixTranslation(&mat, p->center.x, p->center.y, p->center.z);
			g_pDevice->SetTransform(D3DTS_WORLD, &mat);
			//g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
			if (p->isPicked == true)
			{
				g_pDevice->SetMaterial(&DXUtil::RED_MTRL);
			}
			else
			{
				g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
			}
			g_pDevice->SetTexture(0, NULL);
			g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			m_pSphereMesh->DrawSubset(0);
			g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		}
	}
}

void Ironman::Shoot()
{
	if (g_pMouse->ButtonDown(Mouse::LBUTTON))
	{
		if ( (static_cast <Gun *>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GetWeaponStatus() == 1))
			g_pSoundManager->Play("m4al_1", 0.3f);

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
			g_pUIOperator->BattleOn_Zealot = true;

			if (tempEnemy->GetEnemyNum() == 4)
			{
				g_pUIOperator->BattleOn_Mutant = true;
			}
			
			DamageFontNum++;

			g_pItem->getMonsterXY(tempEnemy->GetMonsterX(), tempEnemy->GetMonsterY());
			
			//tempEnemy->MinusHP();
			AttackCalcultate(tempEnemy);

			m_pBlood->Fire(BloodCalPos, -m_forward);
			//static_cast<BloodManager*>(g_pObjMgr->FindObjectByTag(TAG_PARTICLE))->Fire();
			//break;
		}

		//총 반동 온
		isShoot = true;
		shootTime = 0;
	}
}

//m_vecBoundary 벡터에서 28~43 인덱스 부분이 오른손이야!
void Ironman::Hit()
{
	if (g_pMouse->ButtonDown(Mouse::LBUTTON))
	{
		Ray r = Ray::RayAtWorldSpace(g_pCamera->GetMCenter().x, g_pCamera->GetMCenter().y);
		float minDistance = FLT_MAX;
		EnemyManager* em = static_cast <EnemyManager *> (g_pObjMgr->FindObjectByTag(TAG_ENEMY));
		BoundingSphere* temp = NULL;
		Enemy* tempEnemy = NULL;

		//오른손만 돌리자!
		for(int i = 28; i < 44;i++)
		{ 
			for (auto p : em->GetVecEnemy())
			{
				if (p->GetHP() <= 0) continue;

				for (int i = 0; i < p->GetSphereVector().size(); i++)
				{
					//적 임시 변수
					temp = (p->GetSphereVector())[i];

					if (SphereCollideCheck(*m_vecBoundary[i], *temp) == true)
					{
						tempEnemy = p;
						//맞으면 플레이어 위치 목적지로 입력
						p->SetDestPos(m_pos);
						//맞았다 체크
						p->SetDamage(true);

						temp->isPicked = true;
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

	int tempAtk = AddAtk;
	int tempMaxHp = AddMaxHp;
	int tempDef = AddDef;

	m_MaxHp = 100 + tempMaxHp;
	m_Def = 5+ tempDef;
	m_Atk = 5+ tempAtk;
}

bool Ironman::SphereCollideCheck(BoundingSphere player, BoundingSphere Monster)
{
	float SumRadius;
	SumRadius = (player.radius + Monster.radius);

	D3DXVECTOR3 difference = player.center - Monster.center;

	float TwoDistance;
	TwoDistance = D3DXVec3Length(&difference);
	if (SumRadius >= TwoDistance)
	{
		return true;
	}

	return false;
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
	no_death = 16;
	death = 17;
	맨손일때는 리로드 애니가 없음!
	*/
		if (Keyboard::Get()->KeyPress('W'))
		{
			isRun = true;	//뛰는소리
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
			isRun = true;	//뛰는소리
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
			isRun = true;	//뛰는소리
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
			isRun = true;	//뛰는소리
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
			g_pSoundManager->Play("m4a1_reload", 0.3f);
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
				g_pSoundManager->Play("swing", 1.0f);
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
			if (timer >0.025f)
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

void Ironman::SoundSetting()
{

	//KeyPress 때문에 사운드를 재생하기 위해서는 bool변수를 둬서 한번만 재생하도록 해주기 위함
	//KeyPress에서 true로 만들고, KeyUp에서 false처리
	if (Keyboard::Get()->KeyUp('W')
		|| Keyboard::Get()->KeyUp('S')
		|| Keyboard::Get()->KeyUp('A')
		|| Keyboard::Get()->KeyUp('D')
		)
	{
		isRun = false;
		g_pSoundManager->Stop("footstep");
	}

	if (isRun == true && g_pSoundManager->IsPlaySound("footstep") == false)
	{
		g_pSoundManager->Play("footstep", 1.0f);
	}
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

//플레이어 행렬 인덱스 확인용
//if (g_pKeyboard->KeyDown('N'))
//{
//	check++;
//	m_vecBoundary[check]->isPicked = true;
//	if (m_vecBoundary.size() - 1 == check)
//	{
//		check = -1;
//		for (int i = 0; i < m_vecBoundary.size(); i++)
//		{
//			//찾았으면 초기화하기
//			m_vecBoundary[i]->isPicked = false;
//		}
//	}
//}