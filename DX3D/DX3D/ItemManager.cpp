#include "stdafx.h"
#include "ItemManager.h"


ItemManager* ItemManager::instance = NULL;

ItemManager * ItemManager::Get()
{

	if (instance == NULL)
		instance = new ItemManager();

	return instance;
}

void ItemManager::Delete()
{

	SAFE_DELETE(instance);
}

void ItemManager::ItemTable()
{

	Weapons[0] = { 1,"wood",10,0,0,0 ,"resources/images/ham1.png",1 };
	Weapons[1] = { 2, "Gun", 15,20, 0, 0, "resources/images/Gun_.png",1 };


	for (int i = 0; i < NumberOfItems; i++)
	{
		if (Weapons[i].index == NULL)
		{
			continue;
		}
		D3DXCreateTextureFromFileEx(
			g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
			Weapons[i].Filename,   //LPCTSTR pSrcFile,  파일명을 가져옴
						//이거 CString으로 선언한 변수에다 집어넣고
						// LPCTSTR로 받아서 쓰면
						// 변수로 집어넣어도 작동 됨

			D3DX_DEFAULT_NONPOW2,   //UINT Width,
			D3DX_DEFAULT_NONPOW2,   //UINT Height,
			D3DX_DEFAULT,      //UINT MipLevels,
			0,               //DWORD Usage,
			D3DFMT_UNKNOWN,      //D3DFORMAT Format,
			D3DPOOL_MANAGED,   //D3DPOOL Pool
			D3DX_FILTER_NONE,   //DWORD Filter
			D3DX_DEFAULT,      //DWORD MipFilter
			D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
			&Weapons[i].m_image_Item_Info,   //D3DXIMAGE_INFO *pSrcInfo
			NULL,         //PALETTEENTRY *pPalette
			&Weapons[i].m_pTex_Item);   //LPDIRECT3DTEXTURE9 *ppTexture
										  // 위에서 말한 경로에서 정보를 가져와서 m_image_info에 넣고
										  // 텍스쳐도 m_pTex에 저장

	}

}

void ItemManager::Init()
{
}

void ItemManager::Update()
{
}

void ItemManager::Render()
{
}
