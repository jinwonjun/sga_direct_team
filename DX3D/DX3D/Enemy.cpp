#include "stdafx.h"
#include "Enemy.h"
#include "AStar.h"
#include "AStarNode.h"
#include "BoundingBox.h"

//obj파일 불러오기
#include "DrawingGroup.h"
#include "ObjLoader.h"

#include "SkinnedMesh.h"

#include "Ironman.h"

#define SCALE 10.00f
#define MOB_FULL_HP 100//몹의 전체 피통

Enemy::Enemy(D3DXVECTOR3& pos, CString path, CString fileName, int enemyNum)
{
	m_destPos = m_pos = pos;
	m_moveSpeed = 0.4f;
	m_rotationSpeed = 0.1f;
	m_maxStepHeight = 2.0f;

	m_forward = D3DXVECTOR3(0, 0, 1);
	m_isMoving = false;
	m_HP = MOB_FULL_HP;//갱신되는 몹의 체력을 매크로에서 받아오기
	m_ItemDrop = false;

	m_path = path;			// "resources/zealot/";
	m_filename = fileName;	// "combine_test.X";

	m_radius = 1.7f;
	m_SphereHeight = 7.0f;
	m_enemyNum = enemyNum;
}


Enemy::~Enemy()
{
	SAFE_RELEASE(m_pSphereMesh);
	SAFE_RELEASE(m_pBox);

	//obj로드 객체 전부 삭제
	//for (auto p : m_vecDrawingGroup)
	//{
	//	SAFE_RELEASE(p);
	//}
}

void Enemy::Init()
{
	m_pBox = new BoundingBox(D3DXVECTOR3(50.0f, 15.0f, 50.0f)); m_pBox->Init();
	D3DXCreateSphere(g_pDevice, m_radius, 10, 10, &m_pSphereMesh, NULL);
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
	UpdatePosition();
	m_pBox->Update();
	m_pBox->SetPosition(&m_pos);
	m_pBounidngSphere->center = D3DXVECTOR3(m_pos.x, m_pos.y + m_SphereHeight, m_pos.z);
	D3DXMatrixTranslation(&m_SphereMat, m_pBounidngSphere->center.x, m_pBounidngSphere->center.y, m_pBounidngSphere->center.z);

	AnimationModify();
	SAFE_UPDATE(m_pSkinnedMesh);

	WorldToVP();
}

void Enemy::Render()
{
	//m_pBox->Render();
	//////////////////////////구체 그려주기//////////////////////////////
	g_pDevice->SetTransform(D3DTS_WORLD, &m_SphereMat);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pSphereMesh->DrawSubset(0);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	////////////////////////////////////////////////////////////////////

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	SAFE_RENDER(m_pSkinnedMesh);

	//UI그리기
	////////////////////////////////////////////////////////////////////
	//m_HP = 8 로 잡고 이걸 인덱스로 삼자.

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

	//Debug->AddText("데미지 표시 : ");
	//Debug->AddText(HP_Percent);
	//Debug->EndLine();
	//Debug->EndLine();


	if ((m_HP > 0) && (g_pCamera->GetMCenter().x >= ScreenX - 20.0f &&
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

void Enemy::UpdatePosition()
{
	D3DXVECTOR3 targetPos;
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, m_radius, m_radius, m_radius);

	D3DXMATRIXA16 matT, matR;
	float	height = 0;
	bool isIntersected = true;

	targetPos = m_pos + m_forward  * m_moveSpeed;

	if (g_pCurrentMap != NULL)
	{
		isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
	}

	//if (isIntersected == true)
	//{

	//}
	//else
	//{
	//	m_pos = targetPos;
	//}

	//바운딩 박스에 닿았을때 거리가 10보다 크면 이동 -> 10보다 작으면 멈춤
	if (D3DXVec3Length(&(m_destPos - m_pos)) > 10.f)
	{
		m_pSkinnedMesh->status = 3;	//이동
		m_isMoving = true;
	}
	else
	{
		m_pSkinnedMesh->status = 4; //멈춤
		m_isMoving = false;
	}

	if (m_isMoving)
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
		D3DXVECTOR3 forwardNormalized;
		D3DXVec3Normalize(&forwardNormalized, &forward);

		D3DXMATRIXA16 matRotY;
		D3DXMatrixRotationY(&matRotY, m_rot.y);
		//정면 방향 벡터 가져오자
		D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRotY);

		float dot;		//내적의 값
		float radian;	//내적의 값을 역코사인 해서 구한 최종 각도
		
		D3DXVECTOR3 m_forwardNormalized;
		D3DXVec3Normalize(&m_forwardNormalized, &m_forward);

		dot = D3DXVec3Dot(&m_forwardNormalized, &forwardNormalized);
		radian = (float)acos(dot);

		Debug->AddText("Radian : " + to_string(radian));
		Debug->EndLine();

		D3DXVECTOR3 rightDir;	//우향벡터
		D3DXVec3Cross(&rightDir, &m_forward, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		//우향벡터와 바라보는 벡터의 내적이 0보다 크면 왼쪽
		//D3DXVECTOR3 rotY;
		if (D3DXVec3Dot(&rightDir, &forwardNormalized) > 0)
		{
			//왼쪽			
			m_rot.y -= radian * m_rotationSpeed;
		}
		else
		{
			//오른쪽
			m_rot.y += radian * m_rotationSpeed;
		}

		D3DXMATRIXA16 matR;

		D3DXMatrixRotationY(&matR, m_rot.y);

		m_pos.y = height; //+ 5.0f;
		pos = m_pos + forwardNormalized * m_moveSpeed;
		D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
		m_matWorld = matS * matR * matT;
		SetPosition(&pos);
	}
}

void Enemy::SetDestPos(D3DXVECTOR3 & pos)
{
	if (m_isMoving)
	{
		if (m_destPos != pos)
		{
			m_destPos = pos;
		}
	}
	m_destPos = pos;
}

void Enemy::MoveStop()
{
	m_destPos = m_pos;
}

void Enemy::AnimationModify()
{
	D3DXMATRIXA16 matRotY, matRot, m_matWorldT;
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

void Enemy::WorldToVP()
{
	//월드좌표 -> 뷰 좌표 -> 프로젝션 -> 뷰포트 
	//g_pDevice->GetTransform(D3DTS_VIEW, &matView);
	//g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj); 
	//ScreenX = projVertex.x * (ViewportWidth / 2) + ViewportLeft + (ViewportWidth / 2)
	//ScreenY = -projVertex.y * (ViewportHeight / 2) + ViewportTop + (ViewportHeight / 2)

	D3DXMATRIXA16 matProj, matWorld, matView, matWVP;
	D3DVIEWPORT9 vp;
	D3DXVECTOR3 v(0, 0, 0);

	matWorld = m_matWorld;//0번 인덱스 놈의 월드 행렬 가져오기

	g_pDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	matWVP = matWorld * matView * matProj;

	D3DXVec3TransformCoord(&v, &v, &matWVP);

	g_pDevice->GetViewport(&vp);//뷰포트 정보값 가져오기

								//스크린좌표 가져오기
	ScreenX = (v.x * 0.5f + 0.5f) * vp.Width;
	ScreenY = ((-1)*v.y * 0.5f + 0.5f) * vp.Height;

	//스크린좌표 구했으니까 피통 UI를 머리 위로 올려!
	Debug->EndLine();
	Debug->EndLine();
	Debug->AddText("스크린상좌표 X : ");
	Debug->AddText(g_pCamera->GetMCenter().x);
	Debug->AddText("  Y : ");
	Debug->AddText(g_pCamera->GetMCenter().y);
	Debug->EndLine();
	Debug->EndLine();

	Debug->AddText("몹 스크린상좌표 X : ");
	Debug->AddText(ScreenX);
	Debug->AddText("  Y : ");
	Debug->AddText(ScreenY);
	Debug->EndLine();
	Debug->EndLine();
}

void Enemy::RenderUseShader_0()
{
	m_pSkinnedMesh->RenderUseShader_0();
}

void Enemy::RenderUseShader_1()
{
	m_pSkinnedMesh->RenderUseShader_1();
}
