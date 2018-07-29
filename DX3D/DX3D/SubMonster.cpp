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
	m_Hp = MOB_FULL_HP;//���ŵǴ� ���� ü���� ��ũ�ο��� �޾ƿ���
	m_ItemDrop = false;

	m_path = path;			// "resources/zealot/";
	m_filename = fileName;	// "combine_test.X";

	m_radius = 1.7f;
	m_HeadRadius = 0.5f;
	m_CollRadius = 10.f;
	m_SphereHeight = 7.0f;
	m_enemyNum = enemyNum;

	//�浹ó��
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

	//�⺻��ü
	m_pBounidngSphere = new BoundingSphere(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_radius);

	m_renderMode = RenderMode_ShadowMapping;
	m_specular = 3.0f;
	Shaders::Get()->AddList(this, m_renderMode);
	m_pSkinnedMesh = new SkinnedMesh;
	m_pSkinnedMesh->SetRenderMode(m_renderMode);
	m_pSkinnedMesh->Init();

	m_pSkinnedMesh->SetRadius(1.0f);
	m_pSkinnedMesh->Load(m_path, m_filename);

	//�⺻ ��ü �׸���
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

	//���� ���������
	for (int i = 0; i < 8; i++)
	{
		HUD_Ui t;
		HP_Info.push_back(t);
	}
	//�ϰ� �ֱ�
	//1~8����, 0���� 7���� �ε����� �����ϱ�
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

	//��� üũ ���� �ʱ�ȭ
	m_isDead = false;
	DeathTimer = 0.0f;
	DeathCheck = false;

	//���� üũ ���� �ʱ�ȭ
	AtkTimer = 0.0f;
	AtkCheck = false;

	//���� �ִϸ��̼� �ʱ�ȭ�� ����
	m_isAniAttack = false;
	//���� �ִϸ��̼� �Ҹ� �� ������ ���� ����
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

	//���� ��ǥ�� ����Ʈ�� ��������
	WorldToVP();
	//���� ��� ������Ʈ
	UpdateFrameMatrix();
}

void SubMonster::Render()
{

	//����
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	//������ �浹 ����üũ �׷��ֱ�
	MonsterCollideCheckRender();
	//�� ���� ��ü �׷��ֱ�
	DrawRenderSphere();

	//�¿���� �־�����
	//g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	if (!m_isDead)
		SAFE_RENDER(m_pSkinnedMesh);
	//�� ���� �׷��ֱ�
	DrawRenderMobHp();

	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void SubMonster::Hit()
{
	float minDistance = FLT_MAX;
	Ironman* ironman_vec = static_cast <Ironman *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER));
	BoundingSphere* temp = NULL;
	Enemy* tempEnemy = NULL;

	Debug->AddText("���� �ð� : ");
	Debug->AddText(m_pSkinnedMesh->GetCurAnimTime(1));
	//�����ո� ������!
	//���� ���Ҹ� �ѹ��� �������!!!!
	//true�϶� ���� ���̴°� ��� �ɸ�!!!
	for (int i = 15; i < 24; i++)
	{
		for (auto p : ironman_vec->GetVecBoundary())
		{
			if (SphereCollideCheck(*m_vecBoundary[i], *p) == true
				
				//���� �� ���� �� �����·� ���ư��� �ǰݾȵǰ� �ϱ�
				&& m_pSkinnedMesh->GetCurAnimTime(1) < 0.8f)
			{
				p->isPicked = true;
				p->isDamaged = true;
				break;
			}
			//�Ÿ� ���� ��ġ�� ã��
			//BloodCalPos = r.m_dir * (minDistance - temp->radius) + r.m_pos;
		}
	}

	for (auto p : ironman_vec->GetVecBoundary())
	{
		if (p->isDamaged == true && p->isPicked == true)
		{
			//���� ���̴°� ui ����
			static_cast<SampleUI *>(g_pObjMgr->FindObjectByTag(TAG_UI))->CurrHp -= MOB_DAMAGE;

			int temp;
			temp = static_cast<IUnitObject *>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetHp();
			static_cast<IUnitObject *>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->SetHp(temp- MOB_DAMAGE);

			g_pUIOperator->ScreenEffectOn = true;

			p->isDamaged = false;
		}
	}

	Debug->AddText("�÷��̾� ü�� : ");
	Debug->AddText(static_cast<IUnitObject *>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetHp());
	Debug->EndLine();
	Debug->EndLine();
}

void SubMonster::UpdatePosition()
{
	D3DXVECTOR3 targetPos;

	//�̵� �������� ������ �Ÿ�
	float MoveDist = D3DXVec3Length(&(m_destPos - m_pos));

	//�̵� üũ��
	//m_destPos = D3DXVECTOR3(0, 10, 0);

	///////////////// ////////status by ���� //////////////////////////


	if (static_cast<Ironman*>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetCheckDeathTimer() == true
		|| (static_cast<Ironman*>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetIsDead() == true))
	{
		m_pSkinnedMesh->status = 4;
	}
	else
	{
		////�ٿ�� �ڽ��� ��Ұų� �ѿ� �¾Ҵٸ� �̵�
		if (m_isMoving == true || isDamage == true)
		{
			m_pSkinnedMesh->status = 3;	//�̵�

										//�ڽ� �ȿ� �ִٸ� �ѿ� ������ �� : �Ѹ°� ���� ������� ����
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

		//���� ���� ���� �Դٸ� ����
		if (MoveDist <= MOVE_STOP_DISTANCE && MoveDist > D3DX_16F_EPSILON && m_isMoving)
		{
			EnemyAttackSound();
			m_pSkinnedMesh->status = 1; //����
										//ĳ���� ��Ʈ ���� �Լ�

			Hit();
			//�Ÿ��� ��� ������µ�, ���ݸ�� �ϸ� ���� ����� �ϰ��� ����;ߵǴµ�, ���� ���߿� �Ÿ��� ��������,
			//�� �Ÿ��� ������ ���� ���� ����� �ð� �����δٴ� �ǵ�, ���� ����� �� �ϰ� ���� �������ߵǴ°���?
			m_isMoving = false;
		}
		//�ٿ���ڽ� ���̰� �ѿ� �����͵� �ƴ϶��
		else if (m_isMoving == false && isDamage == false)
		{
			m_pSkinnedMesh->status = 4;//����
		}
		else
		{
			m_isAniAttack = false;
		}
		//�� ���� �ð� Ÿ�̸� üũ�ϱ�





		//������ Ÿ�̸� ǥ��
		//if (GetEnemyNum() == 4 && m_Hp <= 0)
		//{
		//	//���ݽ��� �����µ� ���� �ڸ��� ���߰� �ϴ¹�?
		//	m_isMoving = false;
		//	isDamage = false;
		//	DeathCheck = true;
		//	m_pSkinnedMesh->status = 3;//��� ���
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
		//enum4(�̵�) �� 5(����)�� ��Ʈ����
		//�������� enum4 �� ��� enum3�� ���� enum2�� �޸��� enum1�� ���

		//�浹 �ؼ� �о ���� �޾ƿԴٸ� ���� �ް� ����ȭ
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
			//���� ���� ���� ��������
			D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRotY);

			float dot;		//������ ��
			float radian;	//������ ���� ���ڻ��� �ؼ� ���� ���� ����

			dot = D3DXVec3Dot(&m_forward, &forwardNormalized);

			if (dot > 1.f) dot = 1.f;
			else if (dot < -1.f) dot = -1.f;

			radian = (float)acos(dot);

			//Debug->AddText("Radian : " + to_string(radian));
			//Debug->EndLine();

			//Debug->AddText("m_forward: " + to_string(m_forward.x) + ", " + to_string(m_forward.y) + ", " + to_string(m_forward.z));
			//Debug->EndLine();

			D3DXVECTOR3 rightDir;	//���⺤��
			D3DXVec3Cross(&rightDir, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &m_forward);

			//���⺤�Ϳ� �ٶ󺸴� ������ ������ 0���� ũ�� ������
			if (D3DXVec3Dot(&rightDir, &forwardNormalized) > 0)
			{
				//������			
				m_rot.y += radian * m_rotationSpeed;
			}
			else
			{
				//����
				m_rot.y -= radian * m_rotationSpeed;
			}

			//Debug->AddText("m_rot.y : " + to_string(m_rot.y));
			//Debug->EndLine();

			D3DXMatrixRotationY(&matR, m_rot.y);

			//���� ������ ���̶�� 
			if (D3DXVec3Dot(&m_forward, &m_avoid) < -.959f)
			{
				D3DXMATRIXA16 tempRotY;

				//�������� �и��°Ÿ� �� ����
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

			//���� ���� �ӵ�
			velocity = m_forward * m_moveSpeed + m_avoid * MAX_AVOID_FORCE;

			//�浹�ϰ� �з��� �������°� ����
			if (D3DXVec3Length(&velocity) > m_moveSpeed)
			{
				D3DXVECTOR3 nomVel;
				D3DXVec3Normalize(&nomVel, &velocity);
				velocity = nomVel * m_moveSpeed;
			}

			//�ε������� �ӵ� ������ ���̱�
			m_dynamicLength = D3DXVec3Length(&velocity) / m_moveSpeed;

			//���� �̵�
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

		//�浹 ��� ���
		m_frontHead = D3DXVECTOR3(m_pos.x, m_pos.y + m_SphereHeight, m_pos.z) + (m_forward * MAX_SEE_HEAD + m_avoid * MAX_AVOID_FORCE) * m_dynamicLength;
		m_backHead = D3DXVECTOR3(m_pos.x, m_pos.y + m_SphereHeight, m_pos.z) + (m_forward * MAX_SEE_HEAD * 0.5f + m_avoid * MAX_AVOID_FORCE) * m_dynamicLength;

		//���� ���
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
	//������ǥ -> �� ��ǥ -> �������� -> ����Ʈ 
	//g_pDevice->GetTransform(D3DTS_VIEW, &matView);
	//g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj); 
	//ScreenX = projVertex.x * (ViewportWidth / 2) + ViewportLeft + (ViewportWidth / 2)
	//ScreenY = -projVertex.y * (ViewportHeight / 2) + ViewportTop + (ViewportHeight / 2)

	D3DXMATRIXA16 matProj, matWorld, matView, matWVP;
	D3DVIEWPORT9 vp;
	D3DXVECTOR3 v(0, 0, 0);

	matWorld = m_matWorld;//���� �����Ǵ� enemy�� ���� ��İ� �Ѱ��ֱ�

	g_pDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	matWVP = matWorld * matView * matProj;

	D3DXVec3TransformCoord(&v, &v, &matWVP);
	//����Ʈ ������ ��������
	g_pDevice->GetViewport(&vp);

	//��ũ����ǥ ��������
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
		tempCenter = D3DXVECTOR3(0, 0, 0);//�ٽ����� �ʱ�ȭ
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
				//ã������ �ʱ�ȭ�ϱ�
				m_vecBoundary[i]->isPicked = false;
			}
		}
	}
	//Debug->AddText("�����ε��� Ȯ�� :");
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
	//////////////////////////��ü �׷��ֱ�//////////////////////////////
	//�ӽñ�ü��!
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
	//��ü �׸���
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
	//UI�׸���
	////////////////////////////////////////////////////////////////////
	//m_HP = 8 �� ��� �̰� �ε����� ����.

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
	///////////////////////// �ν� �ڽ� �׸��� ///////////////////////////
	if (testNum > 0 && testNum != 3)
		m_pBox->Render();

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	///////////////////////�浹 üũ ��ü �׸���//////////////////////////
	if (testNum > 1 && testNum != 3)
	{

		g_pDevice->SetTransform(D3DTS_WORLD, &m_SphereMat);
		g_pDevice->SetTexture(0, NULL);
		g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_pCollSphereMesh->DrawSubset(0);
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	//////////////////////////��� ��ü �׸���////////////////////////////
	if (testNum > 2)
	{
		//��
		g_pDevice->SetTransform(D3DTS_WORLD, &m_matFrontSphere);
		g_pDevice->SetMaterial(&DXUtil::RED_MTRL);
		g_pDevice->SetTexture(0, NULL);
		m_pFrontSphereMesh->DrawSubset(0);
		//��
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
		// �����ߴٰ� �ٸ� ���·� ���̵Ǿ��� ��
		// ����Ǿ��ִ� �ִϸ��̼� �ٽ� �������� ���� ��
		// 0���� �����ؾߵǱ� ������ �ѹ� �ʱ�ȭ����
		m_pSkinnedMesh->GetAnimationController()->SetTrackPosition(0, 0);
	}
	/*
	LPD3DXANIMATIONSET pAnimSet = NULL;	//1���� ����
	D3DXTRACK_DESC track;				//�ð� ������ DESC
	m_pSkinnedMesh->GetAnimationController()->GetAnimationSet(1, &pAnimSet);
	m_pSkinnedMesh->GetAnimationController()->GetTrackDesc(1, &track);	//DESC �ʱ�ȭ(1���� �����̶�)
	pAnimSet->GetPeriodicPosition(track.Position);		//DESC�� position���� ���� �ִϸ��̼� time ������

	//���� ����Ǵ� ���� �ִϸ��̼��� 0�϶� ���� �Ҹ����

	//Debug->AddText("���� �ð� : ");
	//Debug->AddText(track.Position);



	//���� ����ϴ� �ִϸ��̼��� PeriodicPosition�� 0.1f �����̸�
	//zealot�� ���� ���带 �����Ų ��
	//m_isSoundAttack�� true�� �����, ���� ���� �ѹ��� ���
	//0.1f �̻��� �Ǹ� m_isSoundAttack�� �ٽ� false�� ���� ������ �� 0.1f �����̸� �� �ٽ� ����ǵ���!
	*/
	//if (track.Position <= 0.1f)
	//GetCurAnimTime�� SkinnedMesh �Լ��� �־��...
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
