#include "stdafx.h"
#include "Enemy.h"
#include "AStar.h"
#include "AStarNode.h"
#include "BoundingBox.h"

//obj���� �ҷ�����
#include "DrawingGroup.h"
#include "ObjLoader.h"
#include "SkinnedMesh.h"
#include "Ironman.h"
#include "Ray.h"


Enemy::Enemy(D3DXVECTOR3& pos, CString path, CString fileName, int enemyNum)
{
	m_destPos = m_pos = pos;
	m_moveSpeed = 0.4f;
	m_rotationSpeed = 0.1f;
	m_maxStepHeight = 2.0f;

	m_forward = D3DXVECTOR3(0, 0, 1);
	m_isMoving = false;
	m_HP = MOB_FULL_HP;//���ŵǴ� ���� ü���� ��ũ�ο��� �޾ƿ���
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
}


Enemy::~Enemy()
{
	SAFE_RELEASE(m_pCollSphereMesh);
	SAFE_RELEASE(m_pBackSphereMesh);
	SAFE_RELEASE(m_pFrontSphereMesh);
	SAFE_RELEASE(m_pSphereMesh);
	SAFE_RELEASE(m_pBox);

	//obj�ε� ��ü ���� ����
	//for (auto p : m_vecDrawingGroup)
	//{
	//	SAFE_RELEASE(p);
	//}
}

void Enemy::Init()
{
	m_pBox = new BoundingBox(D3DXVECTOR3(50.0f, 15.0f, 50.0f), m_pos); m_pBox->Init();
	
	D3DXCreateSphere(g_pDevice, m_radius, 10, 10, &m_pSphereMesh, NULL);
	D3DXCreateSphere(g_pDevice, m_HeadRadius, 10, 10, &m_pFrontSphereMesh, NULL);
	D3DXCreateSphere(g_pDevice, m_HeadRadius, 10, 10, &m_pBackSphereMesh, NULL);
	D3DXCreateSphere(g_pDevice, m_CollRadius, 10, 10, &m_pCollSphereMesh, NULL);

	m_pBounidngSphere = new BoundingSphere(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_radius);

	m_renderMode = RenderMode_ShadowMapping;
	Shaders::Get()->AddList(this, m_renderMode);
	m_pSkinnedMesh = new SkinnedMesh; m_pSkinnedMesh->SetRenderMode(m_renderMode);
	m_pSkinnedMesh->Init();
	m_pSkinnedMesh->Load(m_path, m_filename);

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
			&(HP_Info[i-1].m_imageInfo),   //D3DXIMAGE_INFO *pSrcInfo
			NULL,         //PALETTEENTRY *pPalette
			&(HP_Info[i-1].m_pTex));   //LPDIRECT3DTEXTURE9 *ppTexture
	}


	D3DXMatrixIdentity(&matT_UI);
	D3DXMatrixIdentity(&matS_UI);
	D3DXMatrixIdentity(&matR_UI);
	D3DXMatrixIdentity(&matW_UI);
}

void Enemy::Update()
{
	if (g_pKeyboard->KeyDown(VK_F3))
	{
		testNum++;

		if (testNum > 4)
			testNum = 0;
	}

	UpdatePosition();

	m_pBox->Update();
	m_pBox->SetPosition(&m_pos);
	
	m_pBounidngSphere->center = D3DXVECTOR3(m_pos.x, m_pos.y + m_SphereHeight, m_pos.z);
	
	D3DXMatrixTranslation(&m_SphereMat, m_pBounidngSphere->center.x, m_pBounidngSphere->center.y, m_pBounidngSphere->center.z);
	D3DXMatrixTranslation(&m_matFrontSphere, m_frontHead.x, m_frontHead.y, m_frontHead.z);
	D3DXMatrixTranslation(&m_matBackSphere, m_backHead.x, m_backHead.y, m_backHead.z);
	
	AnimationModify();
	SAFE_UPDATE(m_pSkinnedMesh);

	WorldToVP();
}

void Enemy::Render()
{
	///////////////////////// �ν� �ڽ� �׸��� ///////////////////////////
	if (testNum > 0 && testNum != 3)
		m_pBox->Render();
	
	//////////////////////////��ü �׷��ֱ�//////////////////////////////
	
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	g_pDevice->SetTransform(D3DTS_WORLD, &m_SphereMat);
	g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pSphereMesh->DrawSubset(0);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	
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
	
	////////////////////////////////////////////////////////////////////
	
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	SAFE_RENDER(m_pSkinnedMesh);

	//UI�׸���
	////////////////////////////////////////////////////////////////////
	//m_HP = 8 �� ��� �̰� �ε����� ����.

	float HP_Percent = (float)(((float)m_HP / (float)MOB_FULL_HP) * 100);
	
	int Hp_Draw_Idx;
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
	//(m_HP > 0) &&
	//if ( (g_pCamera->GetMCenter().x >= ScreenX - 20.0f &&
	//					g_pCamera->GetMCenter().x <= ScreenX + 20.0f &&
	//					g_pCamera->GetMCenter().y >= ScreenY - 80.0f &&
	//					g_pCamera->GetMCenter().y <= ScreenY))
	//{
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
	/*}*/
}

void Enemy::UpdatePosition()
{
	D3DXVECTOR3 targetPos;
	

	//�̵� �������� ������ �Ÿ�
	float MoveDist = D3DXVec3Length(&(m_destPos - m_pos));

	//�̵� üũ��
	//m_destPos = D3DXVECTOR3(0, 10, 0);
	
	///////////////// ////////status by ���� //////////////////////////

	////�ٿ�� �ڽ��� ��Ұų� �ѿ� �¾Ҵٸ� �̵�
	if (m_isMoving == true || isDamage == true)
	{
		//����
		if (GetEnemyNum() == 4)
		{
			m_pSkinnedMesh->status = 1;
		}
		//��
		else
		{
			m_pSkinnedMesh->status = 3;	//�̵�
		}

		//�ڽ� �ȿ� �ִٸ� �ѿ� ������ �� : �Ѹ°� ���� ������� ����
		if (m_isMoving)
			isDamage = false;
	}

	//���� ���� ���� �Դٸ� ����
	if (MoveDist <= MOVE_STOP_DISTANCE && MoveDist > D3DX_16F_EPSILON)
	{
		//����
		if (GetEnemyNum() == 4)
		{
			m_pSkinnedMesh->status = 2;
		}
		//��
		else
		{
			m_pSkinnedMesh->status = 1; //����
		}
		m_isMoving = false;
	}
	//�ٿ���ڽ� ���̰� �ѿ� �����͵� �ƴ϶��
	else if (m_isMoving == false && isDamage == false)
	{
		//����
		if (GetEnemyNum() == 4)
		{
			m_pSkinnedMesh->status = 0;
		}
		//��
		else
		{
			m_pSkinnedMesh->status = 4;//����
		}
	}
	
	////////////////////////////////////////////////////////////////////

	//enum4(�̵�) �� 5(����)�� ��Ʈ����
	//�������� enum4 �� ��� enum3�� ���� enum2�� �޸��� enum1�� ���
	//�ٿ�� �ڽ��� ������� �Ÿ��� 10���� ũ�� �̵� -> 10���� ������ ����
	//if (D3DXVec3Length(&(m_destPos - m_pos)) > 10.f)
	//{
	//	//����
	//	if (GetEnemyNum() == 4)
	//	{
	//		m_pSkinnedMesh->status = 1;
	//	}
	//	//��
	//	else
	//	{
	//		m_pSkinnedMesh->status = 3;	//�̵�
	//	}
	//	m_isMoving = true;
	//}
	//else
	//{
	//	if (GetEnemyNum() == 4)
	//	{
	//		m_pSkinnedMesh->status = 0;
	//	}
	//	//��
	//	else
	//	{
	//		m_pSkinnedMesh->status = 4; //����
	//	}
	//	m_isMoving = false;
	//}

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

		Debug->AddText("Radian : " + to_string(radian));
		Debug->EndLine();

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

void Enemy::AnimationModify()
{
	//�̸�
	if (GetEnemyNum() < 4)
	{
		D3DXMATRIXA16 matRotY, matRot;
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
	//�����϶�, ���� �����ϸ� �� �ִϸ��̼� �缳��
	else
	{
		if (m_pSkinnedMesh->status == 2)
		{
			D3DXMATRIXA16 matRotY, matRotX,matRot;
			D3DXMatrixRotationY(&matRotY, m_rot.y);
			matRot = matRotY;

			D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRot);
			D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
			D3DXMatrixRotationY(&matR, D3DX_PI);
			D3DXMatrixRotationX(&matRotX, D3DX_PI/-2);
			D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);

			D3DXMATRIXA16 matTemp;
			matTemp = matS *matRotX *matRotY * matR * matT;
			m_pSkinnedMesh->SetWorldMatrix(&matTemp);
		}
		else
		{
			D3DXMATRIXA16 matRotY, matRot;
			D3DXMatrixRotationY(&matRotY, m_rot.y);
			matRot = matRotY;

			D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRot);
			D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
			D3DXMatrixRotationY(&matR, D3DX_PI);
			D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);

			D3DXMATRIXA16 matTemp;
			matTemp = matS * matRotY * matR * matT;
			m_pSkinnedMesh->SetWorldMatrix(&matTemp);
		}
	}
}

void Enemy::WorldToVP()
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

	//��ũ����ǥ �������ϱ� ���� UI�� �Ӹ� ���� �÷�!
	//Debug->EndLine();
	//Debug->EndLine();
	//Debug->AddText("��ũ������ǥ X : ");
	//Debug->AddText(g_pCamera->GetMCenter().x);
	//Debug->AddText("  Y : ");
	//Debug->AddText(g_pCamera->GetMCenter().y);
	//Debug->EndLine();
	//Debug->EndLine();

	//Debug->AddText("�� ��ũ������ǥ X : ");
	//Debug->AddText(ScreenX);
	//Debug->AddText("  Y : ");
	//Debug->AddText(ScreenY);
	//Debug->EndLine();
	//Debug->EndLine();
}



void Enemy::RenderUseShader_0()
{
	m_pSkinnedMesh->RenderUseShader_0();
}

void Enemy::RenderUseShader_1()
{
	m_pSkinnedMesh->RenderUseShader_1();
}
