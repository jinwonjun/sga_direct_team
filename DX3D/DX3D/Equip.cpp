#include "stdafx.h"
#include "Equip.h"
#include "UIImage.h"

Equip* Equip::instance = NULL;

Equip * Equip::Get()
{
	if (instance == NULL)
		instance = new Equip();

	return instance;

}

void Equip::Delete()
{
	SAFE_DELETE(instance);
}

void Equip::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);
	GetClientRect(g_hWnd, &clientRect);

	EquipScreenOn = false;
	for (int i = 0; i < 6; i++)
	{
		D3DXCreateSprite(g_pDevice, &m_pSprite_Equip[i]);
	}

	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/inventory/Purple_Empty_back2.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Equiped_Side.m_image,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Equiped_Side.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

	for (int i = 0; i < 6; i++)
	{
		D3DXCreateTextureFromFileEx(
			g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
			_T("resources/images/inventory/White_back.png"),   //LPCTSTR pSrcFile,
			D3DX_DEFAULT_NONPOW2,   //UINT Width,
			D3DX_DEFAULT_NONPOW2,   //UINT Height,
			D3DX_DEFAULT,      //UINT MipLevels,
			0,               //DWORD Usage,
			D3DFMT_UNKNOWN,      //D3DFORMAT Format,
			D3DPOOL_MANAGED,   //D3DPOOL Pool
			D3DX_FILTER_NONE,   //DWORD Filter
			D3DX_DEFAULT,      //DWORD MipFilter
			D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
			&Equiped_Item[i].m_image,   //D3DXIMAGE_INFO *pSrcInfo
			NULL,         //PALETTEENTRY *pPalette
			&Equiped_Item[i].m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

		Equiped_Item[i].ScaleX = 1.5f ;
		Equiped_Item[i].ScaleY = .3f ;
		Equiped_Item[i].PositionX = ((clientRect.right *0.05));
		Equiped_Item[i].PositionY = (clientRect.bottom *(0.055 + (0.15*i)));
		/*Equiped_Item[i].PositionX = 100;
		Equiped_Item[i].PositionY = 100 + 200 * i;*/

		D3DXCreateTextureFromFileEx(
			g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
			_T("resources/images/inventory/Gray_back.png"),   //LPCTSTR pSrcFile,
			D3DX_DEFAULT_NONPOW2,   //UINT Width,
			D3DX_DEFAULT_NONPOW2,   //UINT Height,
			D3DX_DEFAULT,      //UINT MipLevels,
			0,               //DWORD Usage,
			D3DFMT_UNKNOWN,      //D3DFORMAT Format,
			D3DPOOL_MANAGED,   //D3DPOOL Pool
			D3DX_FILTER_NONE,   //DWORD Filter
			D3DX_DEFAULT,      //DWORD MipFilter
			D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
			&Equiped_Item_BlackBack[i].m_image,   //D3DXIMAGE_INFO *pSrcInfo
			NULL,         //PALETTEENTRY *pPalette
			&Equiped_Item_BlackBack[i].m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

		Equiped_Item_BlackBack[i].ScaleX = .3f ;
		Equiped_Item_BlackBack[i].ScaleY = .3f ;
		Equiped_Item_BlackBack[i].PositionX = (Equiped_Item[i].PositionX + (Equiped_Item[i].m_image.Width *0.05));
		Equiped_Item_BlackBack[i].PositionY = (Equiped_Item[i].PositionY + (Equiped_Item[i].m_image.Height *0.04));
	}

	Equiped_Side.ScaleX = 1.f;
	Equiped_Side.ScaleY = 1.f;
	Equiped_Side.PositionX = clientRect.right * 0.02;
	Equiped_Side.PositionY = clientRect.bottom * 0.01;

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Equiped_Side.PositionX, Equiped_Side.PositionY, 0);
	D3DXMatrixScaling(&matS, Equiped_Side.ScaleX, Equiped_Side.ScaleY, 1);
	matWorld[matWorld_Equiped_Side] = matS * matT;

	Weapon_Equip_Text();
}

void Equip::Update()
{


	for (int i = 0; i < 6; i++)
	{
		SAFE_UPDATE(m_pRootUI_Euip_Text[i]);
	}

	if (g_pKeyboard->KeyDown('E'))
	{
		EquipScreenOn = !EquipScreenOn;
	}



}

void Equip::Render()
{
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);
	if ((g_pInventory->openInven && g_pShop->ShopOpen == false) || EquipScreenOn == true)
	{

		SetRect(&Equiped_Side.m_rc, 0, 0, Equiped_Side.m_image.Width, Equiped_Side.m_image.Height);


		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld[matWorld_Equiped_Side]);
		m_pSprite->Draw(
			Equiped_Side.m_pTex,
			&Equiped_Side.m_rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
		m_pSprite->End();

		for (int i = 0; i < 6; i++)
		{
			m_pSprite_Equip[i]->Begin(D3DXSPRITE_ALPHABLEND);
			m_pSprite_Equip[i]->SetTransform(&m_matWorld_Euip_Name_text[i]);
			//Equip_Name[i]->SetColor(BLACK);
			//Equip_Name[i]->SetPosition(&D3DXVECTOR3(Equiped_Item[i].PositionX*2.5f, Equiped_Item[i].PositionY, 0));
			//m_pRootUI_Euip_Text[i]->m_combinedPos.x -= 100;
			SAFE_RENDER(m_pRootUI_Euip_Text[i]);
			m_pSprite_Equip[i]->End();
		}

		for (int i = 0; i < 6; i++)
		{

			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, Equiped_Item[i].PositionX, Equiped_Item[i].PositionY, 0);
			D3DXMatrixScaling(&matS, Equiped_Item[i].ScaleX, Equiped_Item[i].ScaleY, 1);
			matWorld[matWorld_Equiped_Item + i] = matS * matT;
			//ItemSet
			SetRect(&Equiped_Item[i].m_rc, 0, 0, Equiped_Item[i].m_image.Width, Equiped_Item[i].m_image.Height);

			SetRect(&Equiped_Item[i].m_rc_click,
				Equiped_Item[i].PositionX,
				Equiped_Item[i].PositionY,
				Equiped_Item[i].PositionX + ((Equiped_Item[i].m_image.Width)*(Equiped_Item[i].ScaleX)),
				Equiped_Item[i].PositionY + ((Equiped_Item[i].m_image.Height)*(Equiped_Item[i].ScaleY)));

		
			m_pSprite->SetTransform(&matWorld[matWorld_Equiped_Item + i]);



			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, Equiped_Item_BlackBack[i].PositionX, Equiped_Item_BlackBack[i].PositionY, 0);
			D3DXMatrixScaling(&matS, Equiped_Item_BlackBack[i].ScaleX, Equiped_Item_BlackBack[i].ScaleY, 1);
			matWorld[matWorld_Equiped_Item_Black + i] = matS * matT;
			//ItemSet
			SetRect(&Equiped_Item_BlackBack[i].m_rc, 0, 0, Equiped_Item_BlackBack[i].m_image.Width, Equiped_Item_BlackBack[i].m_image.Height);

			SetRect(&Equiped_Item_BlackBack[i].m_rc_click,
				Equiped_Item_BlackBack[i].PositionX,
				Equiped_Item_BlackBack[i].PositionY,
				Equiped_Item_BlackBack[i].PositionX + ((Equiped_Item_BlackBack[i].m_image.Width)*(Equiped_Item_BlackBack[i].ScaleX)),
				Equiped_Item_BlackBack[i].PositionY + ((Equiped_Item_BlackBack[i].m_image.Height)*(Equiped_Item_BlackBack[i].ScaleY)));

			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			m_pSprite->SetTransform(&matWorld[matWorld_Equiped_Item_Black + i]);
			m_pSprite->Draw(
				Equiped_Item_BlackBack[i].m_pTex,
				&Equiped_Item_BlackBack[i].m_rc,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				D3DCOLOR_ARGB(180, 255, 255, 255));

			m_pSprite->End();
			//if (PtInRect(&Equiped_Item_BlackBack[i].m_rc_click, mousePoint))
			//{
			//	int abvc = 0;
			//}
			
			if (PtInRect(&Equiped_Item_BlackBack[i].m_rc_click, mousePoint) && g_pInventory->Equip[i+1].index != 0)
			{
				g_pInventory->ShowItemInfo(g_pInventory->Equip[i+1]);
			}


			for (int j = 0; j < 6; j++)
			{
				int i = j + 1;
				int AdjustNum = matWorld_Main_Weapon - i;
				int num = g_pInventory->Equip.size();
				if (g_pInventory->Equip[i].index != 0)
				{
					if (i < 4)
					{
						Column = 1;
					}
					else if (i > 3)
					{
						Column = 2;
					}
					Cross = (j % 3) + 1;


					g_pInventory->Equip[i].PositionX = Equiped_Item_BlackBack[j].PositionX;
					g_pInventory->Equip[i].PositionY = Equiped_Item_BlackBack[j].PositionY;
					g_pInventory->Equip[i].ScaleX = .3f * g_pInventory->Adjust_Display_Mode_X;
					g_pInventory->Equip[i].ScaleY = .3f * g_pInventory->Adjust_Display_Mode_Y;

					D3DXMatrixIdentity(&matT);
					D3DXMatrixTranslation(&matT, g_pInventory->Equip[i].PositionX, g_pInventory->Equip[i].PositionY, 0);
					D3DXMatrixScaling(&matS, g_pInventory->Equip[i].ScaleX, g_pInventory->Equip[i].ScaleY, 1);
					matWorld[i + AdjustNum] = matS * matT;

					//ItemSet
					SetRect(&g_pInventory->Equip[i].Item_rc, 0, 0, g_pInventory->Equip[i].m_image_Item_Info.Width, g_pInventory->Equip[i].m_image_Item_Info.Height);

					SetRect(&g_pInventory->Equip[i].Click_rc,
						g_pInventory->Equip[i].PositionX,
						g_pInventory->Equip[i].PositionY,
						g_pInventory->Equip[i].PositionX + ((g_pInventory->Equip[i].m_image_Item_Info.Width)*(g_pInventory->Equip[i].ScaleX)),
						g_pInventory->Equip[i].PositionY + ((g_pInventory->Equip[i].m_image_Item_Info.Height)*(g_pInventory->Equip[i].ScaleY)));

					m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
					m_pSprite->SetTransform(&matWorld[i + AdjustNum]);

					m_pSprite->Draw(
						g_pInventory->Equip[i].m_pTex_Item,
						&g_pInventory->Equip[i].Item_rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						WHITE);
					m_pSprite->End();

					
				}

			}
		

		}
	}

}

void Equip::Weapon_Equip_Text()
{

	{
		for (int i = 0; i < 6; i++)
		{
			UIImage * pImage = new UIImage(m_pSprite_Equip[i]);
			m_pRootUI_Euip_Text[i] = pImage;
		}

	}

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.f, 1.f, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 0, 0);


	Equip_Name_Text[0] = "MainWeapon";
	Equip_Name_Text[1] = "Armor";
	Equip_Name_Text[2] = "Gloves";
	Equip_Name_Text[3] = "Artifact";
	Equip_Name_Text[4] = "Belt";
	Equip_Name_Text[5] = "Boots";

	float fAngle = 0.f;
	////텍스트를 집어넣자
	for (int i = 0; i < 6; i++)
	{
		D3DXMatrixRotationZ(&matR, fAngle);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, Equiped_Item[i].PositionX, Equiped_Item[i].PositionY, 0);
		D3DXMatrixScaling(&matS, 1, 1, 1);

		m_matWorld_Euip_Name_text[i] = matS * matT;
		float Equip_NameRect_StartX = Equiped_Item[i].PositionX + (Equiped_Item[i].m_image.Width*0.3);
		float Equip_NameRect_StartY = Equiped_Item[i].PositionY + (Equiped_Item[i].m_image.Height*0.3);
		//SetRect(&Equip_Name_Rect[i], Equip_NameRect_StartX, Equip_NameRect_StartY, Equip_NameRect_StartX+ 200, Equip_NameRect_StartY+200);

		//Equip_Name[i] = new UIText(g_pFontMgr->GetFont(FONT::Equiped), m_pSprite_Equip[i], 1);
		Equip_Name[i] = new UIButton(m_pDelegate_Equip_Name[i], m_pSprite_Equip[i], 1);

		Equip_Name[i]->SetTexture("resources/images/inventory/White_back3.png",
			"resources/images/inventory/Blue_back.png",
			"resources/images/inventory/Black_back.png");
		//Equip_Name[i]->SetColor(BLACK);


		Equip_Name[i]->SetText(g_pFontMgr->GetFont(FONT::Equiped), Equip_Name_Text[i], BLACK, D3DXVECTOR3(Equiped_Item[i].m_image.Width * 0.45f, 0, 0), 'a');

		//Equip_Name[i]->Render();
		//Equip_Name[i]->RenderingOn = false;
		//  SetRect(&Equip_Name[i]->m_pRect, Equiped_Item[i].PositionX + (Equiped_Item[i].m_image.Width*0.3*Adjust_Display_Mode_X),
		//	Equiped_Item[i].PositionY + (Equiped_Item[i].m_image.Height*0.3*Adjust_Display_Mode_Y), Equip_Name[i]->m_size.x, Equip_Name[i]->m_size.y);

		//Equip_Name[i]->SetPosition(&D3DXVECTOR3(0,0,0));
		//m_pRootUI_Euip_Text[i]->m_pivot.x += 100;


		//Equip_Name[i]  g_pFontMgr->GetFont(FONT::Equiped, i), m_pSprite_Equip, 1;


		m_pRootUI_Euip_Text[i]->AddChild(Equip_Name[i]);
	}
}