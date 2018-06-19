#include "stdafx.h"
#include "SceneMainTitle.h"
#include "IUIObject.h"
#include "UIImage.h"
#include "UIText.h"
#include <cstring>


enum
{
	UITAG_BUTTON1,
	UITAG_BUTTON2,
	UITAG_BUTTON3,
	UITAG_BUTTON4

};


SceneMainTitle::SceneMainTitle()
{
	//m_pSprite = NULL;
	//m_pRootUI = NULL;
}


SceneMainTitle::~SceneMainTitle()
{

	m_pRootUI->ReleaseAll();
	//SAFE_RELEASE(m_pSprite);
	//SAFE_RELEASE(m_pRootUI);
	//SAFE_RELEASE(btn_GameStart);
	
}

void SceneMainTitle::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);

	{
		UIImage * pImage = new UIImage(m_pSprite);
		m_pRootUI = pImage;

	}

	{
		D3DXMATRIXA16 matS;
		D3DXMatrixScaling(&matS, 1.f, 1.9f, 1);
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, 150, 150, 0);
		m_matWorld = matS * matT;

		btn_GameStart = new UIButton(this, m_pSprite, UITAG_BUTTON4);
		// 널 저주 하겠다.
		m_pRootUI->AddChild(btn_GameStart);
		//WINSIZEY / 3
		btn_GameStart->SetPosition(&D3DXVECTOR3(0, 0, 0));
		btn_GameStart->SetTexture("resources/ui/btn-med-up.png.png",
			"resources/ui/btn-med-over.png.png",
			"resources/ui/btn-med-down.png.png");

		//temp = std::to_wstring(restBullet) + L" / 30";
		btn_GameStart->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("GameStart"));
	
	}


	GetClientRect(g_hWnd, &clientRect);
}

void SceneMainTitle::Update()
{
}

void SceneMainTitle::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIXA16 matR, matT, matWorld;
	D3DXMATRIXA16 matS;
	static float fAngle = 0.0f;


	
	m_pSprite->SetTransform(&m_matWorld);
	SAFE_RENDER(m_pRootUI);
}

void SceneMainTitle::OnClick(UIButton * pSender)
{
}

void SceneMainTitle::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
\