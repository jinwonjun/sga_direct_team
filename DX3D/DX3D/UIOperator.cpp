#include "stdafx.h"
#include "UIOperator.h"
#include "IUIObject.h"
#include "UIImage.h"
#include <cstring>
UIOperator::UIOperator()
{


}


UIOperator::~UIOperator()
{


}



void UIOperator::Init()
{
	GetClientRect(g_hWnd, &clientRect);
	D3DXCreateSprite(g_pDevice, &Valkire.m_pSprite);
	D3DXCreateSprite(g_pDevice, &Zealot.m_pSprite);
	D3DXCreateSprite(g_pDevice, &Mutant.m_pSprite);

	{
		UIImage * pImage = new UIImage(Valkire.m_pSprite);
		Valkire.m_pRootUI = pImage;
	}
	{
		UIImage * pImage = new UIImage(Zealot.m_pSprite);
		Zealot.m_pRootUI = pImage;
	}
	{
		UIImage * pImage = new UIImage(Mutant.m_pSprite);
		Mutant.m_pRootUI = pImage;
	}


	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Operator/Valkire_Head2.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Valkire.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Valkire.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Operator/Zealot_Head2.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Zealot.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Zealot.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Operator/Mutant_Head2.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Mutant.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Mutant.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

	//Valkire.PointX = clientRect.right * 0.02;

	SizeofImage = Valkire.m_imageInfo.Width;

	Valkire.PointX = clientRect.right * 0.02 + Valkire.m_imageInfo.Width/2;
	Valkire.PointY = (OriginY / 2) + Valkire.m_imageInfo.Height / 2;
	Valkire.ScaleX = 1.0f;
	Valkire.ScaleY = 0.0f;


	Zealot.PointX = -SizeofImage;
	Zealot.PointY = OriginY / 2;
	Zealot.ScaleX = 1.0f;
	Zealot.ScaleY = 1.0f;


	CrossHeadMoving = false;
	ScaleHeadMoving = false;
	ShutCrossHeadMoving = true;
	ShutScaleHeadMoving = true;
}

void UIOperator::Update()
{
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);

	if (g_pKeyboard->KeyDown('C'))
	{
		CrossHeadMoving = true;
	}
	if (CrossHeadMoving)
	{
		CrossHeadMovingFunction(Zealot);
	}

	if (g_pKeyboard->KeyDown('V'))
	{
		ScaleHeadMoving = true;
	}
	if (ScaleHeadMoving)
	{
		SacleHeadMovingFunction(Valkire);
	}
	//if (HeadMoving && Valkire.ScaleY < 1.0f)
			
	if (Valkire.ScreenOn)
	{
		ShutDownSacleHeadMovingFunction(Valkire);
	}
	
	if (Zealot.ScreenOn)
	{

		ShutDownCrossHeadMovingFunction(Zealot);
	}

	SAFE_UPDATE(Valkire.m_pRootUI);
	SAFE_UPDATE(Zealot.m_pRootUI);
	SAFE_UPDATE(Mutant.m_pRootUI);


}

void UIOperator::Render()
{
	g_pDevice->SetTexture(0, NULL);


	DrawValkire();

	DrawZealot();


}

void UIOperator::OnClick(UIButton * pSender)
{

}

void UIOperator::CrossHeadMovingFunction(Draw_UI &Chara)
{
	if (Chara.PointX + 10.f > clientRect.right * 0.02)
	{
		Chara.PointX = clientRect.right * 0.02;
	}

	if (Chara.PointX >= clientRect.right * 0.02)
	{
		Chara.PointX = clientRect.right * 0.02;
		CrossHeadMoving = false;
		Chara.ScreenOn = true;
		return;
	}


	Chara.PointX += 10.f;
	
}

void UIOperator::SacleHeadMovingFunction(Draw_UI & Chara)
{
	

	if (Chara.ScaleY >= 1.0f)
	{
		ScaleHeadMoving = false;
		Chara.ScreenOn = true;
		return;
	}

	Chara.ScaleY += 0.05f;
}

void UIOperator::ShutDownCrossHeadMovingFunction(Draw_UI & Chara)
{
	if (Chara.timer > 10)
	{
		Chara.PointX -= 10.f;

		if (Chara.PointX < -SizeofImage)
		{

			Chara.ScreenOn = false;
			Chara.timer = 0;
			return;
		}
	}

	else
	{
		Chara.timer++;
	}

}

void UIOperator::ShutDownSacleHeadMovingFunction(Draw_UI & Chara)
{

	if (Chara.timer > 10)
	{
		Chara.ScaleY -= 0.05f;

		if (Chara.ScaleY <= 0.0f)
		{
			Chara.ScreenOn = false;
			Chara.timer = 0;
			return;
		}
	}

	else
	{
		Chara.timer++;
	}
}

void UIOperator::DrawValkire()
{

	SetRect(&Valkire.m_Image_rc, 0, 0, Valkire.m_imageInfo.Width, Valkire.m_imageInfo.Height);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Valkire.PointX, Valkire.PointY, 0);
	D3DXMatrixScaling(&matS, Valkire.ScaleX, Valkire.ScaleY, 1);
	Valkire.matWorld = matS * matT;

	//D3DXSPRITE_ALPHABLEND
	Valkire.m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	Valkire.m_pSprite->SetTransform(&Valkire.matWorld);
	Valkire.m_pSprite->Draw(
		Valkire.m_pTex,
		&Valkire.m_Image_rc,
		&D3DXVECTOR3(Valkire.m_imageInfo.Width/2, Valkire.m_imageInfo.Height / 2, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);
	Valkire.m_pSprite->End();

}

void UIOperator::DrawZealot()
{

	SetRect(&Zealot.m_Image_rc, 0, 0, Zealot.m_imageInfo.Width, Zealot.m_imageInfo.Height);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Zealot.PointX, Zealot.PointY, 0);
	D3DXMatrixScaling(&matS, Zealot.ScaleX, Zealot.ScaleY, 1);
	Zealot.matWorld = matS * matT;

	//D3DXSPRITE_ALPHABLEND
	Zealot.m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	Zealot.m_pSprite->SetTransform(&Zealot.matWorld);
	Zealot.m_pSprite->Draw(
		Zealot.m_pTex,
		&Zealot.m_Image_rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);
	Zealot.m_pSprite->End();
}

void UIOperator::DrawMutant()
{
}


