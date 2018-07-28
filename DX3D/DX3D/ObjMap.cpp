#include "stdafx.h"
#include "ObjMap.h"
#include "DrawingGroup.h"


ObjMap::ObjMap()
{
	m_rayOffsetY = 4;
}

ObjMap::~ObjMap()
{
	for (auto p : m_vecDrawingGroup)
		SAFE_RELEASE(p);
	SAFE_RELEASE(m_pMeshMap);
	for (auto p : m_vecMtlTex)
		SAFE_DELETE(p);
}

void ObjMap::Init()
{
	surfaceMode = false;

	g_pObjMgr->AddToTagList(TAG_OBJMAP, this);

	Init_old_town();
	//Init_cs_italy();
	//����
	//Init_cs_assault();
	//���㰡�� ����?
	//Init_cs_havana();
	//���������
	//Init_pk_stadium();
	//�ð��� ����
<<<<<<< HEAD
=======
	//Init_old_town();
>>>>>>> 275996127800454ca9f703f3a8eb452b15539536
	
	//g_pMapManager->AddMap("ObjMap", this);
	//g_pMapManager->SetCurrentMap("ObjMap");

	m_renderMode = RenderMode_ShadowMapping;
	m_specular = 0.0f;
	Shaders::Get()->AddList(this, m_renderMode);

	MapChangeSignal = false;

}

void ObjMap::Update()
{
	if (g_pKeyboard->Get()->KeyDown(VK_F2))
	{
		surfaceMode = !surfaceMode;
	}
	//�� ����Ʈ
	if (g_pKeyboard->KeyDown('1'))
	{
		Init_old_town();
	}



	Debug->EndLine();
	Debug->AddText("���� ����1 : ");
	Debug->AddText((int)m_vecVertex.size());
	Debug->EndLine();
	Debug->EndLine();


	//m_pBox->Update();
	//m_pBox->SetPosition(&m_pos);
}

void ObjMap::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//������ �Լ� 
	//RenderDrawingGroup();
	//�Ž� �Լ�
	RenderMesh();


	//m_pWalls->Render();
	//m_pBox->Render();

	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
}

bool ObjMap::GetHeight(OUT float & height, const D3DXVECTOR3 & pos)
{
	D3DXVECTOR3 rayPos(pos.x, pos.y + m_rayOffsetY, pos.z);
	D3DXVECTOR3 rayDir(0, -1, 0);
	float distance;
	float tmpHeight;
	float highest = -99999;
	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		if (D3DXIntersectTri(&m_vecVertex[i], &m_vecVertex[i + 1], &m_vecVertex[i + 2],
			&rayPos, &rayDir, NULL, NULL, &distance))
		{
			tmpHeight = rayPos.y - distance;
			//�̰� ���� ������(�عٴ�)�� �������� ����ؼ� ������ ���̸� �����ִ� �ڵ�
			//���� ���� ������ ��� ���, ���̰� ����
			if (tmpHeight > highest + FLT_EPSILON)
			{
				highest = tmpHeight;
				height = tmpHeight;
			}
		}
	}

	if (highest == -99999)
		return false;
	else
		return true;
}

void ObjMap::RenderMesh()
{
	if (m_renderMode != RenderMode_Default) return;
	if (surfaceMode)
	{
		g_pDevice->SetFVF(D3DFVF_XYZ);
		g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(D3DXVECTOR3));
	}
	else
	{
		for (size_t i = 0; i < m_vecMtlTex.size(); i++)
		{
			g_pDevice->SetMaterial(&m_vecMtlTex[i]->material);
			g_pDevice->SetTexture(0, m_vecMtlTex[i]->pTexture);
			m_pMeshMap->DrawSubset(i);
		}
	}

}

void ObjMap::RenderDrawingGroup()
{
	for (auto p : m_vecDrawingGroup)
	{
		p->Render();
	}

	//static int nSubSet = 0;
	//if (GetAsyncKeyState(VK_F1) & 0x0001)
	//{
	//	--nSubSet;
	//	if (nSubSet < 0) nSubSet = 0;
	//}
	//else if (GetAsyncKeyState(VK_F2) & 0x0001)
	//{
	//	++nSubSet;
	//	if (nSubSet > m_vecDrawingGroup.size() - 1) nSubSet = m_vecDrawingGroup.size() - 1;
	//}
	//m_vecDrawingGroup[nSubSet]->Render();
}

void ObjMap::Init_cs_italy()
{
	D3DXMATRIXA16 matS, matRY, matT, localMatrix;
	D3DXMatrixScaling(&matS, 0.2f, 0.2f, 0.2f);
	D3DXMatrixRotationY(&matRY, D3DX_PI / 2.0f);
	D3DXMatrixTranslation(&matT, 0, -250, 0);
	localMatrix = matS * matRY * matT;

	//���ǽ� �׸��� ���� ���� ���� �������
	m_vecVertex.clear();

	ObjLoader loader;
	m_pMeshMap = loader.LoadMesh("resources/Maps/cs_italy", "cs_italy.obj", &localMatrix, m_vecMtlTex);

	loader.CreateSurface(m_vecVertex);//���� �������� ������ �ٴ� ����

	g_pMapManager->AddMap("Italy", this);
	g_pMapManager->SetCurrentMap("Italy");

	g_pMapManager->GetCurrentMap();
}

void ObjMap::Init_cs_assault()
{
	D3DXMATRIXA16 matS, matRY, matT, localMatrix;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixRotationY(&matRY, D3DX_PI / 2.0f);
	D3DXMatrixTranslation(&matT, 0, -700, 0);
	localMatrix = matS * matRY * matT;

	m_vecVertex.clear();

	ObjLoader loader;
	m_pMeshMap = loader.LoadMesh("resources/Maps/cs_assault", "cs_assault.obj", &localMatrix, m_vecMtlTex);

	loader.CreateSurface(m_vecVertex);

	g_pMapManager->AddMap("Assult", this);
	g_pMapManager->SetCurrentMap("Assult");
}

void ObjMap::Init_cs_havana()
{
	D3DXMATRIXA16 matS, matRY, matT, localMatrix;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixRotationY(&matRY, D3DX_PI / 2.0f);
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	localMatrix = matS * matRY * matT;

	ObjLoader loader;
	m_pMeshMap = loader.LoadMesh("resources/Maps/cs_havana", "cs_havana.obj", &localMatrix, m_vecMtlTex);

	m_vecVertex.clear();

	loader.CreateSurface(m_vecVertex);

	g_pMapManager->AddMap("Havana", this);
	g_pMapManager->SetCurrentMap("Havana");
}

void ObjMap::Init_pk_stadium()
{
	D3DXMATRIXA16 matS, matRY, matT, localMatrix;
	D3DXMatrixScaling(&matS, 50.0f, 50.0f, 50.0f);
	D3DXMatrixRotationY(&matRY, D3DX_PI / 2.0f);
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	localMatrix = matS * matRY * matT;
	ObjLoader loader;
	m_pMeshMap = loader.LoadMesh("resources/Maps/stadium", "stadium.obj", &localMatrix, m_vecMtlTex);

	//���ǽ� �׸��� ���� ���� ���� �������
	m_vecVertex.clear();

	loader.CreateSurface(m_vecVertex);

	//D3DXVECTOR3 dir = D3DXVECTOR3(0, -1, 0);
	//D3DXVECTOR3 dir2 = D3DXVECTOR3(0, 1, 0);

	//D3DXCOLOR c = WHITE;
	//D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &c);
	//D3DLIGHT9 light2 = DXUtil::InitDirectional(&dir2, &c);
	////DXUtil::InitSpot
	////�������� �þ߰� �����ϱ�
	////light.Phi = D3DX_PI / 2;
	////D3DLIGHT9 light = DXUtil::InitPoint(&dir, &c);

	////������ ��������� ������ ������.
	////0�� ����Ʈ
	//g_pDevice->SetLight(10, &light);
	//g_pDevice->SetLight(9, &light2);
	////bool ���� ���� 0������ ������ ������ ���� �״� ��Ʈ�� �غ���
	//g_pDevice->LightEnable(9, true);
	//g_pDevice->LightEnable(10, true);

	g_pMapManager->AddMap("Stadium", this);
	g_pMapManager->SetCurrentMap("Stadium");
}

//�ϴ� ����
void ObjMap::Init_float_city()
{
	D3DXMATRIXA16 matS, matRY, matT, localMatrix;
	D3DXMatrixScaling(&matS, 2.0f, 2.0, 2.0);
	D3DXMatrixRotationY(&matRY, D3DX_PI / 2.0f);
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	localMatrix = matS * matRY * matT;

	//loader.Load("resources/Maps/floatcity_ver2", "city_ver2.obj", &localMatrix, m_vecDrawingGroup);
	ObjLoader loader;
	m_pMeshMap = loader.LoadMesh("resources/Maps/floatcity_ver2", "city_ver2.obj", &localMatrix, m_vecMtlTex);

	//���ǽ� �׸��� ���� ���� ���� �������
	m_vecVertex.clear();

	loader.CreateSurface(m_vecVertex);

	//g_pMapManager->AddMap("ObjMap", this);
	//g_pMapManager->SetCurrentMap("ObjMap");
}

void ObjMap::Init_old_town()
{
	D3DXMATRIXA16 matS, matRY, matT, localMatrix;
	D3DXMatrixScaling(&matS, 0.03f, 0.03f, 0.03f);
	D3DXMatrixRotationY(&matRY, D3DX_PI / 2.0f);
	D3DXMatrixTranslation(&matT, 0, -100, 0);
	localMatrix = matS * matRY * matT;
	ObjLoader loader;
	m_pMeshMap = loader.LoadMesh("resources/Maps/oldTown", "oldTown.obj", &localMatrix, m_vecMtlTex);

	//���ǽ� �׸��� ���� ���� ���� �������
	m_vecVertex.clear();

	loader.CreateSurface(m_vecVertex);

	g_pMapManager->AddMap("Town", this);
	g_pMapManager->SetCurrentMap("Town");
}


void ObjMap::RenderUseShader_0()
{
	if (m_renderMode == RenderMode_ShadowMapping) return;

	for (size_t i = 0; i < m_vecMtlTex.size(); ++i)
	{
		Shaders::Get()->GetCurrentShader()->SetWorldMatrix(&m_matWorld);
		Shaders::Get()->GetCurrentShader()->SetTexture(m_vecMtlTex[i]->pTexture);
		Shaders::Get()->GetCurrentShader()->SetMaterial(&m_vecMtlTex[i]->material);
		Shaders::Get()->GetCurrentShader()->Commit();
		m_pMeshMap->DrawSubset(i);
	}
}

void ObjMap::RenderUseShader_1()
{
	if (surfaceMode)
	{
		Shaders::Get()->GetCurrentShader()->SetWorldMatrix(&m_matWorld);
		Shaders::Get()->GetCurrentShader()->Commit();
		g_pDevice->SetFVF(D3DFVF_XYZ);
		g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(D3DXVECTOR3));
	}
	else
	{
		for (size_t i = 0; i < m_vecMtlTex.size(); ++i)
		{
			Shaders::Get()->GetCurrentShader()->SetWorldMatrix(&m_matWorld);
			Shaders::Get()->GetCurrentShader()->SetTexture(m_vecMtlTex[i]->pTexture);
			Shaders::Get()->GetCurrentShader()->SetMaterial(&m_vecMtlTex[i]->material);
			Shaders::Get()->GetCurrentShader()->Commit();
			m_pMeshMap->DrawSubset(i);
		}
	}
}

//Map_surface <- z���� �����ϴ� �뵵�� ����!
//loader.Load("resources/obj", "Map.obj", &matWorld, m_vecDrawingGroup);
//loader.LoadSurface("resources/obj/Map_surface.obj", &matWorld, m_vecVertex);
//m_pMeshMap = loader.LoadMesh("resources/obj", "Map.obj", &matWorld, m_vecMtlTex);
//loader.Load("resources/cs_italy", "cs_italy.obj", &localMatrix, m_vecDrawingGroup);
//m_pMeshMap = loader.LoadMesh("resources/cs_assault", "cs_assault.obj", &localMatrix, m_vecMtlTex);
//loader.CreateSurface(m_surfaceVertices);
//loader.CreateSurface(m_vecVertex);
//m_pMeshMap = loader.CreateSurface()
//loader.LoadNoneMtl("resources/obj", "SCV.obj", &matWorld, m_vecDrawingGroup);
//m_pMeshMap = loader.LoadMesh("resources/obj", "UED_SCV_V1.obj", &matWorld, m_vecMtlTex);


//m_vecVertex
//�Լ� ȣ��� ��ǥ 3�� ����ְ� �� �͵�� �ﰢ���� �������. rayPos(��ǥ)�������� rayDir(����)���� ������ ���
//	D3DXIntersectTri(position0, position1, position2, rayPos, rayDir, 0, 0, distance);

//D3DXVECTOR3 temp;
//temp = pos;
//temp.y += 5;
//for (int i = 0; i < m_vecVertex.size(); i += 3)
//{
//	if (D3DXIntersectTri(&m_vecVertex[i], &m_vecVertex[i + 1], &m_vecVertex[i + 2], &temp, &D3DXVECTOR3(0, -1, 0), 0, 0, &height)) return true;
//}
//return false;

//���� �ڵ� �ִ� �ڸ�
/*
D3DXVECTOR3 rayPos(pos.x, pos.y + m_rayOffsetY, pos.z);
D3DXVECTOR3 rayDir(0, -1, 0);
float distance;

for (size_t i = 0; i < m_vecVertex.size(); i+=3)
{
//�浹�ϸ�(true) distance�� �Լ��� �˾Ƽ� ����ؼ� ���� �ش�!
if (D3DXIntersectTri(&m_vecVertex[i], &m_vecVertex[i + 1], &m_vecVertex[i + 2], &rayPos, &rayDir, 0, 0, &distance))
{
height = rayPos.y - distance;
return true;
}
}
return false;
*/