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
	

	//�Ž� ĳ���� �ø���
	m_pSkinnedMesh = new SkinnedMesh;
	m_pSkinnedMesh->Init();
	CString path = "resources/playerX/";
	CString filename = "combine.X";
	//CString path = "resources/zealot/";
	//CString filename = "combine_test.X";

	m_pSkinnedMesh->Load(path, filename);

	m_pBox = new BoundingBox(D3DXVECTOR3(2.0f, 1.0f, 2.0f)); m_pBox->Init();

	m_pBlood = new BloodEffect(); m_pBlood->Init();

	//��ġ �ʱ�ȭ
	BloodCalPos = D3DXVECTOR3(0, 0, 0);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&m_matWorld);
	


	keyPress = false;

	//������ġ ����
	m_pos.y = 10;

	//UI ������ ĳ���� �̵� ����
	OpenUI = false;

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
	if (Keyboard::Get()->KeyPress('I'))
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

	//������ ��ǥ ��������
	RightHand = m_pSkinnedMesh->GetHandMatrix();


	D3DXTRACK_DESC track;
	m_pSkinnedMesh->GetAnimationController()->GetTrackDesc(0, &track);
	LPD3DXANIMATIONSET pCurrAnimSet = NULL;
	m_pSkinnedMesh->GetAnimationController()->GetAnimationSet(0, &pCurrAnimSet);
	pCurrAnimSet->GetPeriod(); //��ü �ð�
	Debug->EndLine();
	Debug->EndLine();
	Debug->AddText("��ü �ð� : ");
	Debug->AddText(pCurrAnimSet->GetPeriod());
	Debug->EndLine();
	Debug->AddText("���� �ð� : ");
	pCurrAnimSet->GetPeriodicPosition(track.Position); //���� �ð�
	Debug->AddText(pCurrAnimSet->GetPeriodicPosition(track.Position));
	Debug->EndLine();
	Debug->EndLine();



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

		else//idle���� �����
		{
			m_pSkinnedMesh->status = 0;
		}
	}

	Debug->AddText("ĳ��������  :  ");
	Debug->AddText(m_pos);
	Debug->EndLine();
	Debug->EndLine();

	m_pBox->Update();
	m_pBox->SetPosition(&m_pos);

	Shoot();

	//����
	SAFE_UPDATE(m_pBlood);

	//�����ϱ�
	pCurrAnimSet->Release();
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
				//printf("�Ÿ� : %f\n", intersectionDistance);
				//�ּҰŸ�
				if (intersectionDistance < minDistance)
				{
					minDistance = intersectionDistance;
					//sphere = temp;
					tempEnemy = p;
				}
				//�Ÿ� ���� ��ġ�� ã��
				BloodCalPos = r.m_dir * (minDistance - temp->radius) + r.m_pos;
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
	Debug->AddText("��Ʈ��� ��ġ : ");
	Debug->AddText(BloodCalPos);
	Debug->EndLine();
	Debug->EndLine();
}

void Ironman::AnimationModify()
{
	//���̾���� ���� ���� ����� ��������
	D3DXMATRIXA16 matRotY, matT, matR, matS;
	//, matRotX, matRot, m_matWorld;

	D3DXMatrixRotationY(&matRotY, g_pCamera->m_rotY);
	//D3DXMatrixRotationX(&matRotX, m_rot.x);
	//matRot = matRotY * matRotX;
	//D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRot);
	D3DXVECTOR3 m_pos = g_pObjMgr->FindObjectByTag(TAG_PLAYER)->GetPosition();
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixRotationY(&matR, D3DX_PI);
	
	D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);

	m_matWorld = matS * matRotY* matR * matT;

	//skinnedMesh���� X���� ��ġ �� ������ �����κ�.
	m_pSkinnedMesh->SetWorldMatrix(&m_matWorld);
}

