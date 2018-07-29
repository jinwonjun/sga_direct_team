#include "stdafx.h"
#include "SubMonster.h"
#include "BoundingBox.h"
#include "SkinnedMesh.h"
#include "Ray.h"
#include "Ironman.h"

SubMonster::SubMonster(D3DXVECTOR3 & pos, CString path, CString fileName, int enemyNum)
:Enemy(pos, path, fileName, enemyNum)
{
	m_destPos = m_pos = pos;
	m_moveSpeed = 0.4f;
	m_rotationSpeed = 0.1f;
	m_maxStepHeight = 2.0f;

	m_forward = D3DXVECTOR3(0, 0, 1);
	m_isMoving = false;
	m_Hp = MOB_FULL_HP;//갱신되는 몹의 체력을 매크로에서 받아오기
	m_ItemDrop = false;

	m_path = path;			// "resources/zealot/";
	m_filename = fileName;	// "combine_test.X";

	m_radius = 1.7f;
	m_HeadRadius = 0.5f;
	m_CollRadius = 10.f;
	m_SphereHeight = 7.0f;
	m_enemyNum = enemyNum;

	//충돌처리
	m_frontHead = D3DXVECTOR3(0, 0, 1);
	m_backHead = D3DXVECTOR3(0, 0, 1);
	m_avoid = D3DXVECTOR3(0, 0, 0);
	velocity = D3DXVECTOR3(0, 0, m_moveSpeed);
	m_dynamicLength = 1.f;

	testNum = 0;

	isDamage = false;

	check = -1;
	SphereDrawRender = false;
	isTest = false;

}

SubMonster::~SubMonster()
{
	SAFE_RELEASE(m_pCollSphereMesh);
	SAFE_RELEASE(m_pBackSphereMesh);
	SAFE_RELEASE(m_pFrontSphereMesh);
	SAFE_RELEASE(m_pSphereMesh);
	SAFE_RELEASE(m_pBox);
}

void SubMonster::Init()
{
	m_pBox = new BoundingBox(D3DXVECTOR3(50.0f, 30.0f, 50.0f), m_pos); m_pBox->Init();
	D3DXCreateSphere(g_pDevice, m_HeadRadius, 10, 10, &m_pFrontSphereMesh, NULL);
	D3DXCreateSphere(g_pDevice, m_HeadRadius, 10, 10, &m_pBackSphereMesh, NULL);
	D3DXCreateSphere(g_pDevice, m_CollRadius, 10, 10, &m_pCollSphereMesh, NULL);

	//기본구체
	m_pBounidngSphere = new BoundingSphere(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_radius);

	m_renderMode = RenderMode_ShadowMapping;
	m_specular = 3.0f;
	Shaders::Get()->AddList(this, m_renderMode);
	m_pSkinnedMesh = new SkinnedMesh;
	m_pSkinnedMesh->SetRenderMode(m_renderMode);
	m_pSkinnedMesh->Init();

	m_pSkinnedMesh->SetRadius(1.0f);
	m_pSkinnedMesh->Load(m_path, m_filename);

	//기본 구체 그리기
	D3DXCreateSphere(g_pDevice, m_pSkinnedMesh->GetRadius(), 10, 10, &m_pSphereMesh, NULL);

	for (int k = 0; k < (m_pSkinnedMesh->GetSubMobMatrix()).size(); k++)
	{
		BoundingSphere* t = new BoundingSphere(D3DXVECTOR3(k, k, k), m_pSkinnedMesh->GetRadius());
		m_vecBoundary.push_back(t);
	}

	D3DXMatrixIdentity(&ApplyMatWorld);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&m_matWorld);

	D3DXMatrixScaling(&matS, m_radius, m_radius, m_radius);


	D3DXMatrixIdentity(&m_SphereMat);
	D3DXMatrixIdentity(&m_matFrontSphere);
	D3DXMatrixIdentity(&m_matBackSphere);

	D3DXCreateSprite(g_pDevice, &m_pSprite);

	//벡터 사이즈잡기
	for (int i = 0; i < 8; i++)
	{
		HUD_Ui t;
		HP_Info.push_back(t);
	}
	//일괄 넣기
	//1~8까지, 0부터 7까지 인덱스로 접근하기
	for (int i = 1; i < 9; i++)
	{
		wstring strPath = L"resources/mobHp/";
		wstring modName = L".bmp";
		wstring fullPath = strPath + (to_wstring(i)) + modName;

		D3DXCreateTextureFromFileEx(
			g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
			(fullPath.c_str()),   //LPCTSTR pSrcFile,
			D3DX_DEFAULT_NONPOW2,   //UINT Width,
			D3DX_DEFAULT_NONPOW2,   //UINT Height,
			D3DX_DEFAULT,      //UINT MipLevels,
			0,               //DWORD Usage,
			D3DFMT_UNKNOWN,      //D3DFORMAT Format,
			D3DPOOL_MANAGED,   //D3DPOOL Pool
			D3DX_FILTER_NONE,   //DWORD Filter
			D3DX_DEFAULT,      //DWORD MipFilter
			D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
			&(HP_Info[i - 1].m_imageInfo),   //D3DXIMAGE_INFO *pSrcInfo
			NULL,         //PALETTEENTRY *pPalette
			&(HP_Info[i - 1].m_pTex));   //LPDIRECT3DTEXTURE9 *ppTexture
	}


	D3DXMatrixIdentity(&matT_UI);
	D3DXMatrixIdentity(&matS_UI);
	D3DXMatrixIdentity(&matR_UI);
	D3DXMatrixIdentity(&matW_UI);

	//사망 체크 변수 초기화
	m_isDead = false;
	DeathTimer = 0.0f;
	DeathCheck = false;

	//공격 체크 변수 초기화
	AtkTimer = 0.0f;
	AtkCheck = false;

	//공격 애니메이션 초기화할 변수
	m_isAniAttack = false;
	//공격 애니메이션 소리 낼 조건을 위한 변수
	m_isAniSoundAttack = false;

	isTest = false;
}

void SubMonster::Update()
{
	if (g_pKeyboard->KeyDown(VK_F3))
	{
		testNum++;

		if (testNum > 4)
			testNum = 0;
	}

	if (g_pKeyboard->KeyDown(VK_F5))
	{
		isTest = !isTest;
	}

	Debug->AddText(isTest);
	Debug->EndLine();

	UpdatePosition();

	m_pBox->Update();
	m_pBox->SetPosition(&m_pos);

	m_pBounidngSphere->center = D3DXVECTOR3(m_pos.x, m_pos.y + m_SphereHeight, m_pos.z);

	D3DXMatrixTranslation(&m_SphereMat, m_pBounidngSphere->center.x, m_pBounidngSphere->center.y, m_pBounidngSphere->center.z);
	D3DXMatrixTranslation(&m_matFrontSphere, m_frontHead.x, m_frontHead.y, m_frontHead.z);
	D3DXMatrixTranslation(&m_matBackSphere, m_backHead.x, m_backHead.y, m_backHead.z);

	AnimationModify();
	SAFE_UPDATE(m_pSkinnedMesh);

	//월드 좌표를 뷰포트로 가져오기
	WorldToVP();
	//몹의 행렬 업데이트
	UpdateFrameMatrix();
}

void SubMonster::Render()
{

	//조명
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	//몹끼리 충돌 판정체크 그려주기
	MonsterCollideCheckRender();
	//몹 구성 구체 그려주기
	DrawRenderSphere();

	//셋월드는 왜쓴거지
	//g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (!m_isDead)
		SAFE_RENDER(m_pSkinnedMesh);
	//몹 피통 그려주기
	DrawRenderMobHp();

	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void SubMonster::Hit()
{
	float minDistance = FLT_MAX;
	Ironman* ironman_vec = static_cast <Ironman *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER));
	BoundingSphere* temp = NULL;
	Enemy* tempEnemy = NULL;

	Debug->AddText("공격 시간 : ");
	Debug->AddText(m_pSkinnedMesh->GetCurAnimTime(1));
	//오른손만 돌리자!
	//피통 감소를 한번만 해줘야함!!!!
	//true일때 피통 까이는거 계속 걸림!!!
	for (int i = 15; i < 24; i++)
	{
		for (auto p : ironman_vec->GetVecBoundary())
		{
			if (SphereCollideCheck(*m_vecBoundary[i], *p) == true
				
				//질럿 손 공격 후 원상태로 돌아갈때 피격안되게 하기
				&& m_pSkinnedMesh->GetCurAnimTime(1) < 0.8f)
			{
				p->isPicked = true;
				p->isDamaged = true;
				break;
			}
			//거리 보정 위치값 찾기
			//BloodCalPos = r.m_dir * (minDistance - temp->radius) + r.m_pos;
		}
	}

	for (auto p : ironman_vec->GetVecBoundary())
	{
		if (p->isDamaged == true && p->isPicked == true)
		{
			//피통 줄이는거 ui 접근
			static_cast<SampleUI *>(g_pObjMgr->FindObjectByTag(TAG_UI))->CurrHp -= MOB_DAMAGE;

			int temp;
			temp = static_cast<IUnitObject *>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetHp();
			static_cast<IUnitObject *>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->SetHp(temp- MOB_DAMAGE);

			g_pUIOperator->ScreenEffectOn = true;

			p->isDamaged = false;
		}
	}

	Debug->AddText("플레이어 체력 : ");
	Debug->AddText(static_cast<IUnitObject *>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetHp());
	Debug->EndLine();
	Debug->EndLine();
}

void SubMonster::UpdatePosition()
{
	D3DXVECTOR3 targetPos;

	//이동 목적지와 몬스터의 거리
	float MoveDist = D3DXVec3Length(&(m_destPos - m_pos));

	//이동 체크용
	//m_destPos = D3DXVECTOR3(0, 10, 0);

	///////////////// ////////status by 명훈 //////////////////////////


	if (static_cast<Ironman*>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetCheckDeathTimer() == true
		|| (static_cast<Ironman*>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetIsDead() == true))
	{
		m_pSkinnedMesh->status = 4;
	}
	else
	{
		////바운딩 박스에 닿았거나 총에 맞았다면 이동
		if (m_isMoving == true || isDamage == true)
		{
			m_pSkinnedMesh->status = 3;	//이동

										//박스 안에 있다면 총에 맞은거 끔 : 총맞고 벗어 났을경우 위해
			if (m_isMoving)
				isDamage = false;

			else if (m_isMoving == false && isDamage)
			{
				if (MoveDist <= MOVE_STOP_DISTANCE)
				{
					isDamage = false;
				}
			}
		}

		//공격 범위 까지 왔다면 공격
		if (MoveDist <= MOVE_STOP_DISTANCE && MoveDist > D3DX_16F_EPSILON && m_isMoving)
		{
			EnemyAttackSound();
			m_pSkinnedMesh->status = 1; //어택
										//캐릭터 히트 판정 함수

			Hit();
			//거리는 계속 따라오는데, 공격모션 하면 공격 모션을 하고나서 따라와야되는데, 공격 도중에 거리가 벌어지면,
			//그 거리를 좁히기 위해 공격 모션을 씹고 움직인다는 건데, 공격 모션을 다 하고 나서 움직여야되는거지?
			m_isMoving = false;
		}
		//바운딩박스 밖이고 총에 맞은것도 아니라면
		else if (m_isMoving == false && isDamage == false)
		{
			m_pSkinnedMesh->status = 4;//멈춤
		}
		else
		{
			m_isAniAttack = false;
		}
		//쫄 어택 시간 타이머 체크하기





		//사망모션 타이머 표현
		//if (GetEnemyNum() == 4 && m_Hp <= 0)
		//{
		//	//슬금슬금 기어오는데 죽은 자리에 멈추게 하는법?
		//	m_isMoving = false;
		//	isDamage = false;
		//	DeathCheck = true;
		//	m_pSkinnedMesh->status = 3;//사망 모션
		//}
		//if (DeathCheck)
		//{
		//	DeathTimer += 0.001f;
		//	if (DeathTimer > 0.160f)
		//	{
		//		m_isDead = true;
		//		if (m_isDead)
		//		{
		//			DeathCheck = false;
		//			DeathTimer = 0;
		//		}
		//	}
		//}
		//enum4(이동) 랑 5(멈춤)로 컨트롤중
		//보스기준 enum4 가 사망 enum3이 공격 enum2가 달리기 enum1이 대기

		//충돌 해서 밀어낼 벡터 받아왔다면 방향 받고 정규화
		if (m_avoid != D3DXVECTOR3(0, 0, 0))
		{
			D3DXVec3Normalize(&m_avoid, &m_avoid);
		}

		if (m_isMoving || isDamage)
		{
			D3DXVECTOR3 forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
			D3DXVECTOR3 forwardNormalized;
			D3DXVec3Normalize(&forwardNormalized, &forward);

			D3DXMATRIXA16 matRotY;
			D3DXMatrixRotationY(&matRotY, m_rot.y);
			//정면 방향 벡터 가져오자
			D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRotY);

			float dot;		//내적의 값
			float radian;	//내적의 값을 역코사인 해서 구한 최종 각도

			dot = D3DXVec3Dot(&m_forward, &forwardNormalized);

			if (dot > 1.f) dot = 1.f;
			else if (dot < -1.f) dot = -1.f;

			radian = (float)acos(dot);

			//Debug->AddText("Radian : " + to_string(radian));
			//Debug->EndLine();

			//Debug->AddText("m_forward: " + to_string(m_forward.x) + ", " + to_string(m_forward.y) + ", " + to_string(m_forward.z));
			//Debug->EndLine();

			D3DXVECTOR3 rightDir;	//우향벡터
			D3DXVec3Cross(&rightDir, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &m_forward);

			//우향벡터와 바라보는 벡터의 내적이 0보다 크면 오른쪽
			if (D3DXVec3Dot(&rightDir, &forwardNormalized) > 0)
			{
				//오른쪽			
				m_rot.y += radian * m_rotationSpeed;
			}
			else
			{
				//왼쪽
				m_rot.y -= radian * m_rotationSpeed;
			}

			//Debug->AddText("m_rot.y : " + to_string(m_rot.y));
			//Debug->EndLine();

			D3DXMatrixRotationY(&matR, m_rot.y);

			//거의 일직선 상이라면 
			if (D3DXVec3Dot(&m_forward, &m_avoid) < -.959f)
			{
				D3DXMATRIXA16 tempRotY;

				//왼쪽으로 밀리는거면 더 돌림
				if (D3DXVec3Dot(&rightDir, &m_avoid) > 0)
				{
					D3DXMatrixRotationY(&tempRotY, -D3DX_PI / 2);
				}
				else
				{
					D3DXMatrixRotationY(&tempRotY, D3DX_PI / 2);
				}

				D3DXVec3TransformNormal(&m_avoid, &m_avoid, &tempRotY);
			}

			//몬스터 최종 속도
			velocity = m_forward * m_moveSpeed + m_avoid * MAX_AVOID_FORCE;

			//충돌하고 밀려서 빨라지는거 막기
			if (D3DXVec3Length(&velocity) > m_moveSpeed)
			{
				D3DXVECTOR3 nomVel;
				D3DXVec3Normalize(&nomVel, &velocity);
				velocity = nomVel * m_moveSpeed;
			}

			//부딪혔을때 속도 비율로 줄이기
			m_dynamicLength = D3DXVec3Length(&velocity) / m_moveSpeed;

			//최종 이동
			m_pos = m_pos + velocity * m_dynamicLength;
			//m_pos = m_pos + m_forward * m_moveSpeed + m_avoid * MAX_AVOID_FORCE;

			D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
		}//m_isMoving || isDamage
		else
		{
			velocity = D3DXVECTOR3(0, 0, 0);
			m_destPos.y = m_pos.y;
			//D3DXMatrixIdentity(&matR);
		}

		m_matWorld = matS * matR * matT;

		//충돌 헤드 계산
		m_frontHead = D3DXVECTOR3(m_pos.x, m_pos.y + m_SphereHeight, m_pos.z) + (m_forward * MAX_SEE_HEAD + m_avoid * MAX_AVOID_FORCE) * m_dynamicLength;
		m_backHead = D3DXVECTOR3(m_pos.x, m_pos.y + m_SphereHeight, m_pos.z) + (m_forward * MAX_SEE_HEAD * 0.5f + m_avoid * MAX_AVOID_FORCE) * m_dynamicLength;

		//높이 계산
		float height = 0;

		targetPos = m_pos + m_forward  * m_moveSpeed;

		if (g_pCurrentMap != NULL)
			g_pCurrentMap->GetHeight(height, targetPos);

		m_pos.y = height; //+ 5.0f;
	}

}

void SubMonster::AnimationModify()
{
	D3DXMATRIXA16 matRotY, matRot;
	D3DXMatrixRotationY(&matRotY, m_rot.y);
	matRot = matRotY;

	D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRot);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixRotationY(&matR, D3DX_PI);
	D3DXMatrixScaling(&matS, MOB_SCALE, MOB_SCALE, MOB_SCALE);

	D3DXMATRIXA16 matTemp;
	matTemp = matS * matRotY * matR * matT;
	m_pSkinnedMesh->SetWorldMatrix(&matTemp);
}

void SubMonster::WorldToVP()
{
	//월드좌표 -> 뷰 좌표 -> 프로젝션 -> 뷰포트 
	//g_pDevice->GetTransform(D3DTS_VIEW, &matView);
	//g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj); 
	//ScreenX = projVertex.x * (ViewportWidth / 2) + ViewportLeft + (ViewportWidth / 2)
	//ScreenY = -projVertex.y * (ViewportHeight / 2) + ViewportTop + (ViewportHeight / 2)

	D3DXMATRIXA16 matProj, matWorld, matView, matWVP;
	D3DVIEWPORT9 vp;
	D3DXVECTOR3 v(0, 0, 0);

	matWorld = m_matWorld;//지금 생성되는 enemy의 월드 행렬값 넘겨주기

	g_pDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	matWVP = matWorld * matView * matProj;

	D3DXVec3TransformCoord(&v, &v, &matWVP);
	//뷰포트 정보값 가져오기
	g_pDevice->GetViewport(&vp);

	//스크린좌표 가져오기
	ScreenX = (v.x * 0.5f + 0.5f) * vp.Width;
	ScreenY = ((-1)*v.y * 0.5f + 0.5f) * vp.Height;
}

void SubMonster::UpdateFrameMatrix()
{
	for (int i = 0; i < m_pSkinnedMesh->GetSubMobMatrix().size(); i++)
	{
		D3DXVECTOR3 tempCenter;
		D3DXVec3TransformCoord(&tempCenter, &tempCenter, &(m_pSkinnedMesh->GetSubMobMatrix())[i]);
		m_vecBoundary[i]->center = tempCenter;
		tempCenter = D3DXVECTOR3(0, 0, 0);//다썼으면 초기화
	}

	if (g_pKeyboard->KeyDown('N'))
	{
		check++;
		m_vecBoundary[check]->isPicked = true;
		if (m_vecBoundary.size() - 1 == check)
		{
			check = -1;
			for (int i = 0; i < m_vecBoundary.size(); i++)
			{
				//찾았으면 초기화하기
				m_vecBoundary[i]->isPicked = false;
			}
		}
	}
	//Debug->AddText("현재인덱스 확인 :");
	//Debug->AddText(check);
	//Debug->EndLine();
	//Debug->EndLine();
}

bool SubMonster::SphereCollideCheck(BoundingSphere player, BoundingSphere Monster)
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

void SubMonster::DrawRenderSphere()
{
	//////////////////////////구체 그려주기//////////////////////////////
	//임시구체임!
	//g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	//g_pDevice->SetTransform(D3DTS_WORLD, &m_SphereMat);
	//g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
	//g_pDevice->SetTexture(0, NULL);
	//g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_pSphereMesh->DrawSubset(0);
	//g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	if (g_pKeyboard->KeyDown(VK_F4))
	{
		SphereDrawRender = !SphereDrawRender;
	}
	//구체 그리기
	if (SphereDrawRender)
	{
		for (auto p : m_vecBoundary)
		{

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

		}
	}
}

void SubMonster::DrawRenderMobHp()
{
	//UI그리기
	////////////////////////////////////////////////////////////////////
	//m_HP = 8 로 잡고 이걸 인덱스로 삼자.

	float HP_Percent = (float)(((float)m_Hp / (float)MOB_FULL_HP) * 100);

	int Hp_Draw_Idx = 0;
	if (HP_Percent <= 100 && HP_Percent > 87.5)
	{
		Hp_Draw_Idx = 7;
	}
	else if (HP_Percent <= 87.5 && HP_Percent > 75)
	{
		Hp_Draw_Idx = 6;
	}
	else if (HP_Percent <= 75 && HP_Percent > 62.5)
	{
		Hp_Draw_Idx = 5;
	}
	else if (HP_Percent <= 62.5 && HP_Percent > 50)
	{
		Hp_Draw_Idx = 4;
	}
	else if (HP_Percent <= 50 && HP_Percent > 37.5)
	{
		Hp_Draw_Idx = 3;
	}
	else if (HP_Percent <= 37.5 && HP_Percent > 25)
	{
		Hp_Draw_Idx = 2;
	}
	else if (HP_Percent <= 25 && HP_Percent > 12.5)
	{
		Hp_Draw_Idx = 1;
	}
	else if (HP_Percent <= 12.5 && HP_Percent > 0)
	{
		Hp_Draw_Idx = 0;
	}

	if ((m_Hp> 0) && (g_pCamera->GetMCenter().x >= ScreenX - 20.0f &&
		g_pCamera->GetMCenter().x <= ScreenX + 20.0f &&
		g_pCamera->GetMCenter().y >= ScreenY - 80.0f &&
		g_pCamera->GetMCenter().y <= ScreenY))
	{
		SetRect(&HP_Info[Hp_Draw_Idx].m_Image_rc, 0, 0, HP_Info[Hp_Draw_Idx].m_imageInfo.Width, HP_Info[Hp_Draw_Idx].m_imageInfo.Height);
		//D3DXMatrixRotationZ(&matR, fAngle);
		D3DXMatrixIdentity(&matT_UI);
		D3DXMatrixTranslation(&matT_UI, ScreenX - HP_Info[Hp_Draw_Idx].m_imageInfo.Width / 2, ScreenY, 0);
		//D3DXMatrixTranslation(&matT,0, 0, 0);

		//250, 850, 0
		D3DXMatrixScaling(&matS_UI, 1.0f, 1.0f, 1);

		matW_UI = matS_UI* matR_UI * matT_UI;

		//D3DXSPRITE_ALPHABLEND
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matW_UI);
		m_pSprite->Draw(HP_Info[Hp_Draw_Idx].m_pTex, &HP_Info[Hp_Draw_Idx].m_Image_rc, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 0, 0), WHITE);
		m_pSprite->End();
	}
}

void SubMonster::MonsterCollideCheckRender()
{
	///////////////////////// 인식 박스 그리기 ///////////////////////////
	if (testNum > 0 && testNum != 3)
		m_pBox->Render();

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	///////////////////////충돌 체크 구체 그리기//////////////////////////
	if (testNum > 1 && testNum != 3)
	{

		g_pDevice->SetTransform(D3DTS_WORLD, &m_SphereMat);
		g_pDevice->SetTexture(0, NULL);
		g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_pCollSphereMesh->DrawSubset(0);
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	//////////////////////////헤드 구체 그리기////////////////////////////
	if (testNum > 2)
	{
		//앞
		g_pDevice->SetTransform(D3DTS_WORLD, &m_matFrontSphere);
		g_pDevice->SetMaterial(&DXUtil::RED_MTRL);
		g_pDevice->SetTexture(0, NULL);
		m_pFrontSphereMesh->DrawSubset(0);
		//뒤
		g_pDevice->SetTransform(D3DTS_WORLD, &m_matBackSphere);
		g_pDevice->SetTexture(0, NULL);
		m_pBackSphereMesh->DrawSubset(0);
	}
}

void SubMonster::RenderUseShader_0()
{
	m_pSkinnedMesh->RenderUseShader_0();
}

void SubMonster::RenderUseShader_1()
{
	m_pSkinnedMesh->RenderUseShader_1();
}

void SubMonster::EnemyAttackSound()
{
	if (m_isAniAttack == false)
	{
		// 공격했다가 다른 상태로 전이되었을 시
		// 재생되어있는 애니메이션 다시 공격으로 했을 때
		// 0부터 시작해야되기 때문에 한번 초기화해줌
		m_pSkinnedMesh->GetAnimationController()->SetTrackPosition(0, 0);
	}
	/*
	LPD3DXANIMATIONSET pAnimSet = NULL;	//1번은 공격
	D3DXTRACK_DESC track;				//시간 가져올 DESC
	m_pSkinnedMesh->GetAnimationController()->GetAnimationSet(1, &pAnimSet);
	m_pSkinnedMesh->GetAnimationController()->GetTrackDesc(1, &track);	//DESC 초기화(1번이 공격이라)
	pAnimSet->GetPeriodicPosition(track.Position);		//DESC의 position으로 현재 애니메이션 time 가져옴

	//현재 재생되는 공격 애니메이션이 0일때 공격 소리재생

	//Debug->AddText("현재 시간 : ");
	//Debug->AddText(track.Position);



	//현재 재생하는 애니메이션의 PeriodicPosition이 0.1f 이하이면
	//zealot의 공격 사운드를 재생시킨 후
	//m_isSoundAttack을 true로 만들어, 공격 사운드 한번만 재생
	//0.1f 이상이 되면 m_isSoundAttack을 다시 false로 만들어서 다음에 또 0.1f 이하이면 또 다시 재생되도록!
	*/
	//if (track.Position <= 0.1f)
	//GetCurAnimTime은 SkinnedMesh 함수에 넣어둠...
	if (m_pSkinnedMesh->GetCurAnimTime(1) <= 0.1f)
	{
		if (m_isAniSoundAttack == false) g_pSoundManager->Play("zealot_attack", 0.5f);
		m_isAniSoundAttack = true;
	}
	else
	{
		m_isAniSoundAttack = false;
	}

	m_isAniAttack = true;
}
