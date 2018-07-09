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
	g_pObjMgr->AddToTagList(TAG_GUN, this);
	//무기 초기화
	WeaponStatus = 0;

	m_radius = 5.0f;

	D3DXCreateSphere(g_pDevice, m_radius, 10, 10, &m_pSphereMesh, NULL);

	GetCursorPos(&mousePoint);
}
/*
No Gun = 0;
M4 = 1;
Zod_gun = 2;
Beam_gun = 3;
*/
void Gun::GunEqiupSet(int WeaponStatus)
{
	//int EquipNumber;
	//EquipNumber = g_pInventory->Equip[Equip_Main_Weapon_1].index;




		if (WeaponStatus == 1)
		{
			M4GunInit();
		
		
		}
		else if (WeaponStatus == 2)
		{

			BeamGunInit();
	
		}
		else if (WeaponStatus == 3)
		{

			LaserGunInit();
	
		}
		else
		{
			WeaponStatus = 0;
		}



}

void Gun::BeamGunInit()
{
	D3DXMatrixIdentity(&ApplyMatrix);
	D3DXMatrixIdentity(&CalPrevMat);

	D3DXMATRIXA16 matRY, matRX, matRZ, matS;
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	D3DXMatrixRotationY(&matRY, D3DX_PI / -2);
	D3DXMatrixRotationX(&matRX, D3DX_PI);
	D3DXMatrixRotationZ(&matRZ, D3DX_PI / 2);

	CalPrevMat = matS * matRX *matRY * matRZ;

	ObjLoader loader;
	m_pMeshGun = loader.LoadF_Tri_Mesh("resources/Beam", "Beam_Gun.obj", &ApplyMatrix, m_vecMtlTex);
}

void Gun::LaserGunInit()
{
	D3DXMatrixIdentity(&ApplyMatrix);
	D3DXMatrixIdentity(&CalPrevMat);

	D3DXMATRIXA16 matRY, matRX, matRZ, matS, matT;
	D3DXMatrixScaling(&matS, 50.0f, 50.0f, 50.0f);
	D3DXMatrixRotationX(&matRX, D3DX_PI);
	D3DXMatrixRotationZ(&matRZ, D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, 0, 0, 40);

	CalPrevMat = matS * matRX * matRZ * matT;

	ObjLoader loader;
	m_pMeshGun = loader.LoadF_Tri_Mesh("resources/Zod_Rifle", "zod_gun.obj", &ApplyMatrix, m_vecMtlTex);
}

void Gun::M4GunInit()
{
	D3DXMatrixIdentity(&ApplyMatrix);
	D3DXMatrixIdentity(&CalPrevMat);

	D3DXMATRIXA16 matRX, matRY, matRZ, matS,matR, matT;
	D3DXMatrixScaling(&matS, 10.0f, 10.0f, 10.0f);
	D3DXMatrixRotationX(&matRX, D3DX_PI/-40);
	D3DXMatrixRotationY(&matRY, D3DX_PI);
	D3DXMatrixRotationZ(&matRZ, D3DX_PI / 2 * 3);

	matR = matRX*matRY* matRZ;

	D3DXMatrixTranslation(&matT, 0, 0, 30);

	CalPrevMat = matS* matR * matT;

	ObjLoader loader;
	m_pMeshGun = loader.LoadF_Tri_Mesh("resources/M4a1", "guntest.obj", &ApplyMatrix, m_vecMtlTex);
}


void Gun::Update()
{
<<<<<<< HEAD
	//if (g_pKeyboard->KeyDown('1'))
	//{
	//	GunEqiupSet(1);
	//}
	//if (g_pKeyboard->KeyDown('2'))
	//{
	//	GunEqiupSet(2);
	//}
	//if (g_pKeyboard->KeyDown('3'))
	//{
	//	GunEqiupSet(3);
	//}
=======
	


			



>>>>>>> ce1c101ab13fadcc6dbdd6f4766ff299b1cac5b5
	D3DXMATRIXA16 matT;
	matT = static_cast <Ironman *>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->RightHand;

	ApplyMatrix = CalPrevMat *  matT;
}

void Gun::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetTransform(D3DTS_WORLD, &ApplyMatrix);

	//총 매쉬로 그리기
	for (size_t i = 0; i < m_vecMtlTex.size(); i++)
	{
		g_pDevice->SetMaterial(&m_vecMtlTex[i]->material);
		g_pDevice->SetTexture(0, m_vecMtlTex[i]->pTexture);
		m_pMeshGun->DrawSubset(i);
	}

	g_pDevice->SetTransform(D3DTS_WORLD, &static_cast <Ironman *>(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->RightHand);
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pSphereMesh->DrawSubset(0);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
}
