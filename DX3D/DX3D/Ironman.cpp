#include "stdafx.h"
#include "Ironman.h"

#include "SkinnedMesh.h"
#include "AllocateHierarchy.h"
#include "BoundingBox.h"
#include "Ray.h"
#include "EnemyManager.h"
#include "Enemy.h"


#define SCALE 0.05f

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
}

void Ironman::Init()
{
	g_pObjMgr->AddToTagList(TAG_PLAYER, this);
	g_pCamera->SetTarget(&m_pos);
	g_pKeyboardManager->SetMovingTarget(&m_keyState);
	//�Ž� ĳ���� �ø���
	m_pSkinnedMesh = new SkinnedMesh;
	m_pSkinnedMesh->Init();
	CString path = "resources/zealot/";
	CString filename = "combine_test.X";
	m_pSkinnedMesh->Load(path, filename);

	m_pBox = new BoundingBox(D3DXVECTOR3(2.0f, 1.0f, 2.0f)); m_pBox->Init();

	//��ġ �ʱ�ȭ
	BloodCalPos = D3DXVECTOR3(0, 0, 0);

	D3DXMatrixIdentity(&ApplyMatWorld);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&m_matWorld);
}

void Ironman::Update()
{
	//Ű����� ������ ��Ʈ�� �κ��� ���� �ƴϸ� �ȵǴ� ������ �ִµ� ������ �𸣰���...
	IUnitObject::UpdateKeyboardState();
	IUnitObject::UpdatePosition();

	SAFE_UPDATE(m_pSkinnedMesh);

	if (Keyboard::Get()->KeyPress('W'))
	{
		//m_pAnimController->KeyTrackSpeed(0,5.0f,10,20, D3DXTRANSITION_LINEAR);
		m_pSkinnedMesh->status =  1;
	}
	else if (Keyboard::Get()->KeyPress('S'))
	{
		m_pSkinnedMesh->status = 2;
	}
	else if (Keyboard::Get()->KeyPress(VK_SPACE))
	{
		m_pSkinnedMesh->status = 3;
	}
	//Keyboard::Get()->KeyDown('2') ||
	else if (Mouse::Get()->ButtonDown(Mouse::Get()->LBUTTON))
	{
		//if (m_animIndex > 0)//0
		//m_animIndex--;
		m_pSkinnedMesh->status = 0;
	}
	else//idle���� �����
	{
		m_pSkinnedMesh->status = 4;
	}

	m_pBox->Update();
	m_pBox->SetPosition(&m_pos);

	//��ġ ����ϱ�
	AnimationModify();

	Shoot();

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
	pCurrAnimSet->Release();
}

void Ironman::Render()
{
	SAFE_RENDER(m_pSkinnedMesh);
}

void Ironman::Shoot()
{
	Debug->AddText("ȭ����ǥ x : ");
	Debug->AddText(g_pCamera->GetMCenter().x);
	Debug->AddText("  y : ");
	Debug->AddText(g_pCamera->GetMCenter().y);
	Debug->EndLine();
	Debug->EndLine();


	if (g_pMouse->ButtonDown(Mouse::LBUTTON))
	{
		Ray r = Ray::RayAtWorldSpace(g_pCamera->GetMCenter().x, g_pCamera->GetMCenter().y);

		BoundingSphere* sphere = NULL;
		float minDistance = FLT_MAX;
		float intersectionDistance;
		EnemyManager* em = static_cast <EnemyManager *> (g_pObjMgr->FindObjectByTag(TAG_ENEMY));
		BoundingSphere* temp = NULL;
		for (auto p : em->GetVecEnemy())
		{
			temp = p->GetSphere();
			if (r.CalcIntersectSphere(temp) == true)
			{
				intersectionDistance = D3DXVec3Length(&(temp->center - r.m_pos));
				//printf("�Ÿ� : %f\n", intersectionDistance);
				//�ּҰŸ�
				if (intersectionDistance < minDistance)
				{
					minDistance = intersectionDistance;
					sphere = temp;
				}
				//�Ÿ� ���� ��ġ�� ã��
				BloodCalPos = r.m_dir * (intersectionDistance - temp->radius) + r.m_pos;
			}
			if (sphere != NULL)
			{
				p->MinusHP();
				static_cast<BloodManager*>(g_pObjMgr->FindObjectByTag(TAG_PARTICLE))->Fire();
				break;
			}
		}
	}
	Debug->AddText("��Ʈ��� ��ġ : ");
	Debug->AddText(BloodCalPos);
	Debug->EndLine();
	Debug->EndLine();
}

void Ironman::AnimationModify()
{
	D3DXMATRIXA16 matRotY, matRotX, matRot, m_matWorldT;
	D3DXMatrixRotationY(&matRotY, m_rot.y);
	D3DXMatrixRotationX(&matRotX, m_rot.x);
	matRot = matRotY * matRotX;

	D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRot);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixRotationY(&matR, D3DX_PI);
	D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);

	m_matWorld = matS * matRotY* matR * matT;

	ApplyMatWorld = m_matWorld;
}
