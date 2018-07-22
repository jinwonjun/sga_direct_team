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
	D3DXCreateSprite(g_pDevice, &IntroPage.m_pSprite);
	D3DXCreateSprite(g_pDevice, &PlayButton.m_pSprite);
	D3DXCreateSprite(g_pDevice, &QuitButton.m_pSprite);

	{
		UIImage * pImage = new UIImage(IntroPage.m_pSprite);
		IntroPage.m_pRootUI = pImage;
	}
	{
		UIImage * pImage = new UIImage(PlayButton.m_pSprite);
		PlayButton.m_pRootUI = pImage;
	}
	{
		UIImage * pImage = new UIImage(QuitButton.m_pSprite);
		QuitButton.m_pRootUI = pImage;
	}

	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/ui/Intro/IntroPage.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&IntroPage.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&IntroPage.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture


	PlayButtonInit();
	QuitButtonInit();
}

void IntroUI::Update()
{
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);

	if (PtInRect(&PlayButton.rect, mousePoint))
	{
		if ((g_pMouse->ButtonUp(Mouse::LBUTTON)))
		{
			g_pSceneManager->SetCurrentScene(SCENE_GRID);
		}
	}

	if (PtInRect(&QuitButton.rect, mousePoint))
	{
		if ((g_pMouse->ButtonUp(Mouse::LBUTTON)))
		{
			DestroyWindow(g_hWnd);
		}
	}
	Debug->AddText("Left¿Í Top");

	Debug->AddText(PlayButton.rect.left);

	Debug->AddText(" , ");
	Debug->AddText(PlayButton.rect.top);

	Debug->AddText("Right¿Í Bottom");
	Debug->AddText(PlayButton.rect.right);
	Debug->AddText(" , ");
	Debug->AddText(PlayButton.rect.bottom);

	Debug->EndLine();
	Debug->AddText("X¿Í Y");

	Debug->AddText(mousePoint.x);

	Debug->AddText(" , ");
	Debug->AddText(mousePoint.y);

	Debug->EndLine();


	SAFE_UPDATE(PlayButton.m_pRootUI);

	SAFE_UPDATE(QuitButton.m_pRootUI);




}

void IntroUI::Render()
{
	g_pDevice->SetTexture(0, NULL);
	D3DXMATRIXA16 matR, matT;
	D3DXMATRIXA16 matS;


	SetRect(&IntroPage.m_Image_rc, 0, 0, IntroPage.m_imageInfo.Width, IntroPage.m_imageInfo.Height);
	IntroPage.ScaleX = clientRect.right/ OriginX;
	IntroPage.ScaleY = clientRect.bottom / OriginY;

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	D3DXMatrixScaling(&matS, IntroPage.ScaleX, IntroPage.ScaleY, 1);
	IntroPage.matWorld = matS * matT;

	//D3DXSPRITE_ALPHABLEND
	IntroPage.m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	IntroPage.m_pSprite->SetTransform(&IntroPage.matWorld);
	IntroPage.m_pSprite->Draw(
		IntroPage.m_pTex,
		&IntroPage.m_Image_rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);
	IntroPage.m_pSprite->End();



	QuitButton.m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	QuitButton.m_pSprite->SetTransform(&QuitButton.matWorld);
	QuitButton.m_pButton->GetFinalRect(&QuitButton.rect);
	SAFE_RENDER(QuitButton.m_pRootUI);

	QuitButton.m_pSprite->End();

	


	PlayButton.m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	PlayButton.m_pSprite->SetTransform(&PlayButton.matWorld);
	PlayButton.m_pButton->GetFinalRect(&PlayButton.rect);
	SAFE_RENDER(PlayButton.m_pRootUI);
	PlayButton.m_pSprite->End();

	SAFE_RENDER(IntroPage.m_pRootUI);
}

void IntroUI::OnClick(UIButton * pSender)
{
}
void IntroUI::PlayButtonInit()
{
	




	PlayButton.m_pButton = new UIButton(this, PlayButton.m_pSprite, 1);
	PlayButton.m_pButton->SetPosition(&D3DXVECTOR3(0,0, 0));


	PlayButton.m_pButton->SetTexture("resources/ui/Intro/Gameplay_Button_Up.png",
		"resources/ui/Intro/Gameplay_Button_Over.png",
		"resources/ui/Intro/Gameplay_Button_Down.png");

	PlayButton.m_pRootUI->AddChild(PlayButton.m_pButton);



	PlayButton.ScaleX = .7f;
	PlayButton.ScaleY = .7f;
	PlayButton.PointX = (OriginX *0.86) - (PlayButton.m_pButton->m_size.x / 2);
	PlayButton.PointY = (OriginY * 0.6);
	//PlayButton.PointX = 0;
	//PlayButton.PointY = 0;
	D3DXMATRIXA16 matS;
	//D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, PlayButton.ScaleX, PlayButton.ScaleY, 1);

	D3DXMATRIXA16 matT;
	//	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, PlayButton.PointX, PlayButton.PointY, 0);
	PlayButton.matWorld = matS * matT;
	//PlayButton.m_pSprite->SetTransform(&PlayButton.matWorld);
	//PlayButton.m_pButton->GetFinalRect(&PlayButton.rect);

}

void IntroUI::QuitButtonInit()
{


	QuitButton.m_pButton = new UIButton(this, QuitButton.m_pSprite, 1);
	QuitButton.m_pButton->SetPosition(&D3DXVECTOR3(0, 0, 0));


	QuitButton.m_pButton->SetTexture("resources/ui/Intro/Quit_Button_Up.png",
		"resources/ui/Intro/Quit_Button_Over.png",
		"resources/ui/Intro/Quit_Button_Down.png");

	QuitButton.m_pRootUI->AddChild(QuitButton.m_pButton);


	QuitButton.ScaleX = .7f;
	QuitButton.ScaleY = .7f;
	QuitButton.PointX = (OriginX *0.86) - (QuitButton.m_pButton->m_size.x / 2);
	QuitButton.PointY = (OriginY * 0.75);
	D3DXMATRIXA16 matS;
	D3DXMatrixIdentity(&matS);


	D3DXMatrixScaling(&matS, QuitButton.ScaleX, QuitButton.ScaleY, 1);

	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);

	D3DXMatrixTranslation(&matT, QuitButton.PointX, QuitButton.PointY, 0);
	QuitButton.matWorld = matS * matT;

}
