#include "stdafx.h"
#include "UIManager.h"


UIManager* UIManager::instance = NULL;


UIManager * UIManager::Get()
{
	if (instance == NULL)
		instance = new UIManager();

	return instance;
}



void UIManager::Delete()
{
	SAFE_DELETE(instance);
}

void UIManager::Init()
{
	GetClientRect(g_hWnd, &clientRect);
	D3DXCreateSprite(g_pDevice, &pSprite);
	cheatKeyAtk = false;
	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Cursor_Normal.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&MouseCursor_Normal.m_image,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&MouseCursor_Normal.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Cursor_Clicked.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&MousCursor_ClickedOn.m_image,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&MousCursor_ClickedOn.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture
}

void UIManager::Update()
{
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);

	//if (g_pKeyboard->KeyDown('O'))
	//{
	//	cheatKeyAtk = !cheatKeyAtk;
	//}

	//if (cheatKeyAtk)
	//{
	//	IronMan_Atk = 200;
	//}

}

void UIManager::Render()
{
	if (g_pInventory->openInven || g_pShop->ShopOpen || g_pEquip->EquipScreenOn)
	{
		if (g_pMouse->ButtonPress(Mouse::LBUTTON))
		{

			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, mousePoint.x, mousePoint.y, 0);
			D3DXMatrixScaling(&matS, 1.f, 1.f, 1);
			matWorld = matS * matT;

			//m_pSprite->SetTransform(&matWorld[matWorld_MouseCursor]);

			SetRect(&MousCursor_ClickedOn.m_rc, 0, 0, MousCursor_ClickedOn.m_image.Width, MousCursor_ClickedOn.m_image.Height);


			pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			pSprite->SetTransform(&matWorld);
			pSprite->Draw(
				MousCursor_ClickedOn.m_pTex,
				&MousCursor_ClickedOn.m_rc,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				WHITE);
			pSprite->End();
		}
		else
		{

			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, mousePoint.x, mousePoint.y, 0);
			D3DXMatrixScaling(&matS, 1.f, 1.f, 1);
			matWorld = matS * matT;
			//m_pSprite->SetTransform(&matWorld[matWorld_MouseCursor]);

			SetRect(&MouseCursor_Normal.m_rc, 0, 0, MouseCursor_Normal.m_image.Width, MouseCursor_Normal.m_image.Height);

			pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			pSprite->SetTransform(&matWorld);
			pSprite->Draw(
				MouseCursor_Normal.m_pTex,
				&MouseCursor_Normal.m_rc,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				WHITE);
			pSprite->End();
		}
	}
}



