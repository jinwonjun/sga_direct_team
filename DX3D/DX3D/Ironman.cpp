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

<<<<<<< HEAD
	keyPress = false;
=======
	//������ġ ����
	m_pos.y = 10;
>>>>>>> e3ffa1e7e57e428163f2187197e4249949ba77f6
}

void Ironman::Update()
{
	//Ű����� ������ ��Ʈ�� �κ��� ���� �ƴϸ� �ȵǴ� ������ �ִµ� ������ �𸣰���...
	IUnitObject::UpdateKeyboardState();
	IUnitObject::UpdatePosition();

	SAFE_UPDATE(m_pSkinnedMesh);

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

	if (Keyboard::Get()->KeyPress('W'))
	{
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
	else if (Mouse::Get()->ButtonPress(Mouse::Get()->LBUTTON))
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

	Shoot();

	//�����ϱ�
	pCurrAnimSet->Release();
}

void Ironman::Render()
{
	SAFE_RENDER(m_pSkinnedMesh);
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

