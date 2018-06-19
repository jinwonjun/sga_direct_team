#include "stdafx.h"
#include "MainMenu.h"
#include "IUIObject.h"
#include "UIImage.h"
#include "UIText.h"
#include <cstring>


enum
{
	UITAG_TEXTVIEW,
	UITAG_BUTTON1,
	UITAG_BUTTON2,
	UITAG_BUTTON3,
	UITAG_BUTTON4
};


MainMenu::MainMenu()
{
	m_pSprite = NULL;
	m_pSprite_ = NULL;
	m_pRootUI = NULL;
}


MainMenu::~MainMenu()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pSprite_);
	//SAFE_RELEASE(m_pRootUI);
	//SAFE_RELEASE(pbutt)
	//m_pRootUI->ReleaseAll();
}

void MainMenu::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);

	GetClientRect(g_hWnd, &clientRect);

	//{
	//	UIImage * pImage = new UIImage(m_pSprite);
	//	//pImage->SetTexture("resources/ui/panel-info.png.png");
	//	m_pRootUI = pImage;
	//
	//}

	////텍스트 추가
	//{
	//	//폰트 관리 클래스 만들기
	//	UIText * pText = new UIText(g_pFontMgr->GetFont(FONT::NORMAL), m_pSprite, UITAG_TEXTVIEW);
	//	m_pRootUI->AddChild(pText);
	//	pText->m_text = _T("(Push the Button)");
	//	pText->m_size = D3DXVECTOR2(312, 200);
	//	pText->SetPosition(&D3DXVECTOR3(100, 100, 0));
	//}

	//버튼1
	{
		//UIButton * pButton = new UIButton(this, m_pSprite, UITAG_BUTTON1);
		//m_pRootUI->AddChild(pButton);
		//pButton->SetPosition(&D3DXVECTOR3(WINSIZEX+100, WINSIZEY, 0));
		//pButton->SetTexture("resources/ui/btn-med-up.png.png",
		//	"resources/ui/btn-med-over.png.png",
		//	"resources/ui/btn-med-down.png.png");
		//
		//

		////wchar_t * td;
		//string example = "example";




		/*	AfxMessageBox(tes);*/

		//// 2nd trial
		//string txt = "df";
		//itoa(restBullet, c_int, 10);

		//pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T(temp.c_str()));  // itoa(restBullet, c_int, 10)

		//		std::string newString("wibble");


		//	_itoa_s(restBullet, c_int, 10);		

		//	wchar_t ch[] = _T("asdsd");
		//wchar_t ch[10] = { 0, };
		//_itow_s(a3, ch, 2);

		//pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST),tes);



		//pButton->SetTextW(g_pFontMgr->GetFont(FONT::QUEST), t.c_str());
		// 명형 say -> cmp 깊은 복사?   wstring to lpctstr

	}
	////버튼2
	//{


	//	D3DXMATRIXA16 matS;
	//	D3DXMatrixScaling(&matS, 1.f, 1.5f, 1);
	//	D3DXMATRIXA16 matT;
	//	D3DXMatrixTranslation(&matT, 150, 150, 0);
	//	m_matWorld = matS * matT;

	//	UIButton * pButton = new UIButton(this, m_pSprite, UITAG_BUTTON2);
	//	m_pRootUI->AddChild(pButton);
	//	pButton->SetPosition(&D3DXVECTOR3(135, 400, 0));
	//	pButton->SetTexture("resources/ui/btn-med-up.png.png",
	//		"resources/ui/btn-med-over.png.png",
	//		"resources/ui/btn-med-down.png.png");
	//	pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("Button2"));
	//}

	







	//D3DXCreateTextureFromFile(g_pDevice, _T("resources/images/Gun.png"), &m_pTex);

	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Gun.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

							//이부분이 update에 가있어서 프레임 드랍 원인이었음.
	{
		D3DXMATRIXA16 matS;
		D3DXMatrixScaling(&matS, 2.f, 1.9f, 1);
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, clientRect.right/3, clientRect.bottom/2, 0);
		m_matWorld = matS * matT;

		BulletNum = new UIButton(this, m_pSprite, UITAG_BUTTON4);
		// 널 저주 하겠다.
		//m_pRootUI->AddChild(BulletNum);
		//WINSIZEY / 3
		BulletNum->SetPosition(&D3DXVECTOR3(0, 0, 0));
		BulletNum->SetTexture("resources/ui/btn-med-up.png.png",
			"resources/ui/btn-med-over.png.png",
			"resources/ui/btn-med-down.png.png");

		temp = std::to_wstring(restBullet) + L" / 30";
		BulletNum->SetText(g_pFontMgr->GetFont(FONT::NORMAL), temp.c_str());
	}


}

void MainMenu::Update()
{


	//==========================================
	//==========================================

	//HP bar
	//{

	//	//D3DXMATRIXA16 matS;
	//	//D3DXMatrixScaling(&matS, 0.7f, 0.7f, 1);
	//	//D3DXMATRIXA16 matT;
	//	//D3DXMatrixTranslation(&matT, 150, 150, 0);
	//	//m_matWorld = matS * matT;


	//	PercentOfHp = CurrHp / MaxHp;

	//	UIButton * HpBar = new UIButton(this, m_pSprite, UITAG_BUTTON4);
	//	m_pRootUI->AddChild(HpBar);
	//	HpBar->SetPosition(&D3DXVECTOR3(WINSIZEX - 1850, (WINSIZEY / 3), 0));
	//	HpBar->SetTexture("resources/ui/panel-info.png.png",
	//		"resources/ui/panel-info.png.png",
	//		"resources/ui/panel-info.png.png");

	//	temp = std::to_wstring(restBullet) + L" ";
	//	HpBar->SetText(g_pFontMgr->GetFont(FONT::NORMAL), temp.c_str());
	//}
	//UIButton * pButton = new UIButton(this, m_pSprite, UITAG_BUTTON4);
	//m_pRootUI->AddChild(pButton);
	//pButton->SetPosition(&D3DXVECTOR3(WINSIZEX - 450, (WINSIZEY / 3), 0));
	//pButton->SetTexture("resources/ui/btn-med-up.png.png",
	//	"resources/ui/btn-med-over.png.png",
	//	"resources/ui/btn-med-down.png.png");


	//==========================================
	//==========================================
	SAFE_UPDATE(m_pRootUI);
}

void MainMenu::Render()
{
	g_pDevice->SetTexture(0, NULL); // 다른 색이 뭍어나와서 흰색이 주황색으로
									//스프라이트는 비긴이랑 엔드 사이에서 그려준다.
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);



	D3DXMATRIXA16 matR, matT, matWorld;
	D3DXMATRIXA16 matS;
	static float fAngle = 0.0f;

	//fAngle += 0.1f;
	//D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, (clientRect.right - m_imageInfo_.Width) / 2, ((clientRect.bottom + m_imageInfo_.Height)) / 2, 0);



	D3DXMatrixScaling(&matS, 1.f, 1.0f, 1);
	matWorld = matS * matT;  // 젤 끝에서 시작점으로 이동하는것


	m_pSprite->SetTransform(&m_matWorld);
	SAFE_RENDER(m_pRootUI);

	

	m_pSprite->SetTransform(&matWorld);


	m_pSprite->End();
}

void MainMenu::OnClick(UIButton * pSender)
{
	if (pSender->m_uiTag == UITAG_BUTTON1)
	{
		UIText* pText = (UIText*)m_pRootUI->FindChildByUITag(UITAG_TEXTVIEW);
		pText->m_text = _T("Button1 pushed");

	}
	else if (pSender->m_uiTag == UITAG_BUTTON2)
	{
		UIText* pText = (UIText*)m_pRootUI->FindChildByUITag(UITAG_TEXTVIEW);
		pText->m_text = _T("Button2 pushed");
	}

	else if (pSender->m_uiTag == UITAG_BUTTON3)
	{
		UIText* pText = (UIText*)m_pRootUI->FindChildByUITag(UITAG_TEXTVIEW);
		pText->m_text = _T("Button3 pushed");
	}
}

wstring MainMenu::s2ws(const string & s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;

	return r;
}
