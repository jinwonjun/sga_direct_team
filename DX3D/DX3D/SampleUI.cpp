#include "stdafx.h"
#include "SampleUI.h"
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


SampleUI::SampleUI()
{
	m_pSprite = NULL;
	m_pSprite_ = NULL;
	m_pRootUI = NULL;
}


SampleUI::~SampleUI()
{
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pSprite_);
	//SAFE_RELEASE(m_pRootUI);
	//SAFE_RELEASE(pbutt)
	m_pRootUI->ReleaseAll();
}

void SampleUI::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);
	D3DXCreateSprite(g_pDevice, &m_pSprite_);
	restBullet = 30;
	spaceOn = false;
	contorller = 0;
	char c_int[10];
	MaxHp = 100;
	CurrHp = 100;
	PercentOfHp = CurrHp / MaxHp;

	{
		UIImage * pImage = new UIImage(m_pSprite);
		//pImage->SetTexture("resources/ui/panel-info.png.png");
		m_pRootUI = pImage;
	}

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
	//	UIButton * pButton = new UIButton(this, m_pSprite, UITAG_BUTTON2);
	//	m_pRootUI->AddChild(pButton);
	//	pButton->SetPosition(&D3DXVECTOR3(135, 400, 0));
	//	pButton->SetTexture("resources/ui/btn-med-up.png.png",
	//		"resources/ui/btn-med-over.png.png",
	//		"resources/ui/btn-med-down.png.png");
	//	pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("Button2"));
	//}

	////버튼3
	//{
	//	UIButton * pButton = new UIButton(this, m_pSprite, UITAG_BUTTON3);
	//	m_pRootUI->AddChild(pButton);
	//	pButton->SetPosition(&D3DXVECTOR3(135, 260, 0));
	//	pButton->SetTexture("resources/ui/btn-med-up.png.png",
	//		"resources/ui/btn-med-over.png.png",
	//		"resources/ui/btn-med-down.png.png");
	//	pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("Button3"));
	//}

	//내가 만들어 본 것
	{



		//int restBullet = 10;
		//CString tes;
		//tes.Format(L"%d", restBullet);



		/*	printf("%d\n", restBullet);
		printf("%s\n", tes);*/

		//printf("깨짐? : %c", temp);
		//size_t cn;
		//char *str = "기억나";
		//wchar_t warr[100] = L"";
		//setlocale(LC_ALL, "Korean");//로케일 설정
		//mbstowcs_s(&cn, warr, 100, str, 100);
		//wprintf(L"%s\n", warr);//유니코드 문자열 출력
		//const char * t = str;
		//pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), warr);

		//CA2T wt(i.c_str());

		//	pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), wt);


	}


	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.f, 1.9f, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 150, 150, 0);
	m_matWorld = matS * matT;


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


	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Cross_Aim_sm.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&m_imageInfo_,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&m_pTex_);   //LPDIRECT3DTEXTURE9 *ppTexture
}

void SampleUI::Update()
{
	//총과 총알 	
	//==========================================
	//==========================================
	if (spaceOn & contorller == 1)
	{
		restBullet--;
		spaceOn = false;
	}
	//총 쏘는 키 체크
	if (g_pMouse->ButtonDown(Mouse::Get()->LBUTTON))
	{
		spaceOn = true;
		contorller++;
	}

	//if (Keyboard::Get()->KeyPress(VK_SPACE))
	//{
	//	spaceOn = true;
	//	contorller++;
	//}
	//if (GetAsyncKeyState(VK_SPACE))
	//{
	//	spaceOn = true;
	//	contorller++;
	//}
	//if (!GetAsyncKeyState(VK_SPACE))
	else
	{
		contorller = 0;
	}

	if (GetAsyncKeyState('R'))
	{
		restBullet = 30;
	}

	if (restBullet < 0)
	{
		restBullet = 0;
	}

	{
		D3DXMATRIXA16 matS;
		D3DXMatrixScaling(&matS, 1.f, 1.9f, 1);
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, 150, 150, 0);
		m_matWorld = matS * matT;

		UIButton * BulletNum = new UIButton(this, m_pSprite, UITAG_BUTTON4);
		m_pRootUI->AddChild(BulletNum);
		//원래(WINSIZEY / 3)이었음
		BulletNum->SetPosition(&D3DXVECTOR3(WINSIZEX - 450, (WINSIZEY / 4), 0));
		BulletNum->SetTexture("resources/ui/btn-med-up.png.png",
			"resources/ui/btn-med-over.png.png",
			"resources/ui/btn-med-down.png.png");

		temp = std::to_wstring(restBullet) + L" / 30";
		BulletNum->SetText(g_pFontMgr->GetFont(FONT::NORMAL), temp.c_str());


	}

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

void SampleUI::Render()
{

	g_pDevice->SetTexture(0, NULL); // 다른 색이 뭍어나와서 흰색이 주황색으로
									//스프라이트는 비긴이랑 엔드 사이에서 그려준다.
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite->SetTransform(&m_matWorld);
	SAFE_RENDER(m_pRootUI);
	m_pSprite->End();









	RECT clientRect;
	GetClientRect(g_hWnd, &clientRect);

	D3DXMATRIXA16 matR, matT, matWorld;
	static float fAngle = 0.0f;
	//fAngle += 0.1f;
	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, clientRect.right - m_imageInfo.Width, 0, 0);
	matWorld = matR * matT;

	RECT rc_; // 회전중점, 위치이동 따로따로 있따.
	SetRect(&rc_, 0, 0, m_imageInfo_.Width, m_imageInfo_.Height);
	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		m_pTex_,
		&rc_,
		&D3DXVECTOR3(580, -500, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);


	RECT rc; // 회전중점, 위치이동 따로따로 있따.
	SetRect(&rc, 0, 0, m_imageInfo.Width, m_imageInfo.Height);
	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(m_pTex,&rc,&D3DXVECTOR3(m_imageInfo.Width / 4, -500, 0), &D3DXVECTOR3(0, 0, 0),WHITE);
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
	//-670



	m_pSprite->End();

}

void SampleUI::OnClick(UIButton * pSender)
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

wstring SampleUI::s2ws(const string & s)
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
