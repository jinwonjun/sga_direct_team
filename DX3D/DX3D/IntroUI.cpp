#include "stdafx.h"
#include "IntroUI.h"
#include "IUIObject.h"
#include "UIImage.h"
#include <cstring>



IntroUI::IntroUI()
{

}


IntroUI::~IntroUI()
{
}

void IntroUI::Init()
{
	GetClientRect(g_hWnd, &clientRect);
	D3DXCreateSprite(g_pDevice, &temp.m_pSprite);
	D3DXCreateSprite(g_pDevice, &temp2.m_pSprite);
	{
		UIImage * pImage = new UIImage(temp.m_pSprite);
		temp.m_pRootUI = pImage;
	}
	{
		UIImage * pImage = new UIImage(temp2.m_pSprite);
		temp2.m_pRootUI = pImage;
	}



	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Gun_.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&temp.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&temp.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture


	FontInit2();
}

void IntroUI::Update()
{
	SAFE_UPDATE(temp2.m_pRootUI);
	//SAFE_UPDATE(temp.m_pRootUI);
}

void IntroUI::Render()
{
	g_pDevice->SetTexture(0, NULL);
	D3DXMATRIXA16 matR, matT;
	D3DXMATRIXA16 matS;

	temp2.m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);


	temp2.m_pSprite->SetTransform(&temp2.matWorld);
	SAFE_RENDER(temp2.m_pRootUI);

	temp2.m_pSprite->End();



	SetRect(&temp.m_Image_rc, 0, 0, temp.m_imageInfo.Width, temp.m_imageInfo.Height);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT,  100,250, 0);
	D3DXMatrixScaling(&matS, 1.f, .8f, 1);
	temp.matWorld = matS * matT;

	//D3DXSPRITE_ALPHABLEND
	temp.m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	temp.m_pSprite->SetTransform(&temp.matWorld);
	temp.m_pSprite->Draw(
		temp.m_pTex,
		&temp.m_Image_rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);
	temp.m_pSprite->End();


	//SAFE_RENDER(temp.m_pRootUI);
	
	

}

void IntroUI::OnClick(UIButton * pSender)
{
}
void IntroUI::FontInit2()
{
	float ScaleX_BulletNum, ScaleY_BulletNum;
	ScaleX_BulletNum = 1.f;
	ScaleY_BulletNum = 1.f;
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.f, 1.f, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	temp2.matWorld = matS * matT;

	temp2.m_pButton = new UIButton(this, temp2.m_pSprite, 1);
	temp2.m_pButton->SetPosition(&D3DXVECTOR3(0,0, 0));
	

	temp2.m_pButton->SetTexture("resources/ui/Gameplay_Button_Up.png.png",
		"resources/ui/Gameplay_Button_Over.png.png",
		"resources/ui/Gameplay_Button_Down.png.png");

	//temp2.m_pButton->SetTexture("resources/ui/Gameplay_Button_Up.png.png",
	//	"resources/ui/Gameplay_Button_Over.png.png",
	//	"resources/ui/Gameplay_Button_Down.png.png");
	//temp2.m_pButton->SetText(g_pFontMgr->GetFont(FONT::NORMAL), L"FINE", WHITE);
	temp2.m_pRootUI->AddChild(temp2.m_pButton);


}