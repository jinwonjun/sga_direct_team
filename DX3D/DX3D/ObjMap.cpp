#include "stdafx.h"
#include "ObjMap.h"
#include "DrawingGroup.h"
#include "ObjLoader.h"
ObjMap::ObjMap()
{
	m_rayOffsetY = 4;
}


ObjMap::~ObjMap()
{
	for (auto p : m_vecDrawingGroup)
	{
		SAFE_RELEASE(p);
	}
}

void ObjMap::Init()
{
	D3DXMATRIXA16 matRX, matRY, matS, matWorld;
	D3DXMatrixRotationX(&matRX, -D3DX_PI / 2.0f);
	D3DXMatrixRotationY(&matRY, D3DX_PI / 2.0f);
	D3DXMatrixScaling(&matS, 0.04f, 0.04f, 0.04f);
	matWorld = matS * matRX * matRY;

	ObjLoader loader;
	//Map_surface <- z높이 측정하는 용도로 쓰임!
	//loader.Load("resources/obj", "Map.obj", &matWorld, m_vecDrawingGroup);
	//loader.LoadSurface("resources/obj/Map_surface.obj", &matWorld, m_vecVertex);
	//m_pMeshMap = loader.LoadMesh("resources/obj", "Map.obj", &matWorld, m_vecMtlTex);


	loader.Load("resources/cs_italy", "cs_italy.obj", &matWorld, m_vecDrawingGroup);
	m_pMeshMap = loader.LoadMesh("resources/cs_italy", "cs_italy.obj", &matWorld, m_vecMtlTex);
	//for (int i = 0 ; i < loader.m_mapMtlTex.size(); i++)
	//{
	//	m_vecMtlTex[i]->id = loader.m_mapMtlTex;
	//	m_vecMtlTex[i]->material = loader.m_mapMtlTex[i]->;
	//	m_vecMtlTex[i]->pTexture = loader.m_mapMtlTex[i]->id;
	//}

	

	//OBJ맵 적용하기
	g_pMapManager->AddMap("ObjMap", this);
	g_pMapManager->SetCurrentMap("ObjMap");
}

void ObjMap::Update()
{
	
}

void ObjMap::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//렌더링 함수 
	//RenderDrawingGroup();
	//매쉬 함수
	RenderMesh();

	//D3DXCreateSphere(g_pDevice,1.5,);

	//D3DXCreateBox(g_pDevice,5.5f,5.5f,5.5f,m_pMeshMap->CloneMesh,adja)

	//두 함수 돌려서 시간 체크 해보기
	//float start = 0, end = 0, time_data = 0;
	//start = GetTickCount();
	//for (int i = 0; i < 100; i++)
	//{
	//	RenderDrawingGroup();
	//}
	//end = GetTickCount();

	//time_data = end - start;
	//printf("드로잉 렌더 : %f\n", time_data);

	//start = 0;
	//end = 0;
	//float time_data_1 = 0;
	//start = GetTickCount();
	//for (int i = 0; i < 100; i++)
	//{
	//	RenderMesh();
	//}
	//end = GetTickCount();
	//time_data_1 = end - start;
	//printf("매쉬 렌더 : %f\n", time_data_1);
}

bool ObjMap::GetHeight(OUT float & height, const D3DXVECTOR3 & pos)
{
	//m_vecVertex
	//함수 호출시 좌표 3개 찍어주고 그 것들로 삼각형을 만들어줌. rayPos(좌표)지점에서 rayDir(방향)으로 광선을 쏜다
	//	D3DXIntersectTri(position0, position1, position2, rayPos, rayDir, 0, 0, distance);

	//D3DXVECTOR3 temp;
	//temp = pos;
	//temp.y += 5;
	//for (int i = 0; i < m_vecVertex.size(); i += 3)
	//{
	//	if (D3DXIntersectTri(&m_vecVertex[i], &m_vecVertex[i + 1], &m_vecVertex[i + 2], &temp, &D3DXVECTOR3(0, -1, 0), 0, 0, &height)) return true;
	//}
	//return false;

	D3DXVECTOR3 rayPos(pos.x, pos.y + m_rayOffsetY, pos.z);
	D3DXVECTOR3 rayDir(0, -1, 0);
	float distance;

	for (size_t i = 0; i < m_vecVertex.size(); i+=3)
	{
		//충돌하면(true) distance를 함수가 알아서 계산해서 값을 준다!
		if (D3DXIntersectTri(&m_vecVertex[i], &m_vecVertex[i + 1], &m_vecVertex[i + 2], &rayPos, &rayDir, 0, 0, &distance))
		{
			height = rayPos.y - distance;
			return true;
		}
	}
	return false;
}

void ObjMap::RenderMesh()
{
	for (size_t i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pDevice->SetMaterial(&m_vecMtlTex[i]->material);
		g_pDevice->SetTexture(0, m_vecMtlTex[i]->pTexture);
		m_pMeshMap->DrawSubset(i);
	}
}

void ObjMap::RenderDrawingGroup()
{
	for (auto p : m_vecDrawingGroup)
	{
		SAFE_RENDER(p);
	}
}
