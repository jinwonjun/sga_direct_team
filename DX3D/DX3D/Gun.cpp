#include "stdafx.h"
#include "Gun.h"

#include "ObjLoader.h"

Gun::Gun()
{

}


Gun::~Gun()
{
}

void Gun::Init()
{
	g_pObjMgr->AddToTagList(TAG_GUN,this);
	//스케일 조정부분 , 캐릭터 손의 월드값 가져오기
	//캐릭터의 오른손 행렬값 가져오기

	D3DXMatrixIdentity(&ApplyMatrix);
	D3DXMatrixIdentity(&CalPrevMat);

	D3DXMATRIXA16 matRY, matRX,matRZ,matS;
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	D3DXMatrixRotationY(&matRY, D3DX_PI/ -2);
	D3DXMatrixRotationX(&matRX, D3DX_PI);
	D3DXMatrixRotationZ(&matRZ, D3DX_PI/2);

	CalPrevMat = matS * matRX *matRY * matRZ;

	m_radius = 5.0f;

	D3DXCreateSphere(g_pDevice, m_radius, 10, 10, &m_pSphereMesh, NULL);

	ObjLoader loader;
	m_pMeshGun = loader.LoadF_Tri_Mesh("resources/Beam", "Beam_Gun.obj", &ApplyMatrix, m_vecMtlTex);
}

void Gun::Update()
{
	D3DXMATRIXA16 matT;
	matT = static_cast <Ironman *>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->RightHand;

	ApplyMatrix =  CalPrevMat *  matT;
}

void Gun::Render()
{
	//g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetTransform(D3DTS_WORLD, &ApplyMatrix);

	//총 매쉬로 그리기
	for (size_t i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pDevice->SetMaterial(&m_vecMtlTex[i]->material);
		g_pDevice->SetTexture(0, m_vecMtlTex[i]->pTexture);
		m_pMeshGun->DrawSubset(i);
	}

	g_pDevice->SetTransform(D3DTS_WORLD, &ApplyMatrix);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pSphereMesh->DrawSubset(0);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
