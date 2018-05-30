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
	//SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pSprite_);
	//SAFE_RELEASE(m_pRootUI);
	//SAFE_RELEASE(pbutt)
	
	m_pRootUI->ReleaseAll();
	m_pRootUI_2->ReleaseAll();
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
	GetClientRect(g_hWnd, &clientRect);
	
	LifeLoss = 100;

	{
		UIImage * pImage = new UIImage(m_pSprite);
		//pImage->SetTexture("resources/ui/panel-info.png.png");
		m_pRootUI = pImage;

	}

	{
		UIImage * pImage = new UIImage(m_pSprite);
		m_pRootUI_2 = pImage;
	}


	////�ؽ�Ʈ �߰�
	//{
	//	//��Ʈ ���� Ŭ���� �����
	//	UIText * pText = new UIText(g_pFontMgr->GetFont(FONT::NORMAL), m_pSprite, UITAG_TEXTVIEW);
	//	m_pRootUI->AddChild(pText);
	//	pText->m_text = _T("(Push the Button)");
	//	pText->m_size = D3DXVECTOR2(312, 200);
	//	pText->SetPosition(&D3DXVECTOR3(100, 100, 0));
	//}

	//��ư1
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
		// ���� say -> cmp ���� ����?   wstring to lpctstr

	}
	////��ư2
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

	////��ư3
	//{







	//	UIButton * pButton = new UIButton(this, m_pSprite, UITAG_BUTTON3);
	//	m_pRootUI_2->AddChild(pButton);
	//	pButton->SetPosition(&D3DXVECTOR3(135, 260, 0));
	//	pButton->SetTexture("resources/ui/btn-med-up.png.png",
	//		"resources/ui/btn-med-over.png.png",
	//		"resources/ui/btn-med-down.png.png");
	//	pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("Button3___"));
	//}

	//���� ����� �� ��
	{



		//int restBullet = 10;
		//CString tes;
		//tes.Format(L"%d", restBullet);



		/*	printf("%d\n", restBullet);
		printf("%s\n", tes);*/

		//printf("����? : %c", temp);
		//size_t cn;
		//char *str = "��ﳪ";
		//wchar_t warr[100] = L"";
		//setlocale(LC_ALL, "Korean");//������ ����
		//mbstowcs_s(&cn, warr, 100, str, 100);
		//wprintf(L"%s\n", warr);//�����ڵ� ���ڿ� ���
		//const char * t = str;
		//pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), warr);

		//CA2T wt(i.c_str());

		//	pButton->SetText(g_pFontMgr->GetFont(FONT::QUEST), wt);


	}




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

	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/ironMan_head.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&m_imageInfo_IronMan_Head,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&m_pTex_IronMan_Head);   //LPDIRECT3DTEXTURE9 *ppTexture



					 // ü�� ����
	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Ui_Back.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&m_imageInfo_Hp_Back,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&m_pTex_Hp_Back);   //LPDIRECT3DTEXTURE9 *ppTexture


							// ü�� ���� ��
	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Ui_RemainHp.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&m_imageInfo_Hp_Remain,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&m_pTex_Hp_Remain);   //LPDIRECT3DTEXTURE9 *ppTexture


							  // ü�� ���� ��
	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Ui_LossHp.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&m_imageInfo_Hp_Loss,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&m_pTex_Hp_Loss);   //LPDIRECT3DTEXTURE9 *ppTexture

	//�̺κ��� update�� ���־ ������ ��� �����̾���.
	{
		D3DXMATRIXA16 matS;
		D3DXMatrixScaling(&matS, 1.f, 1.f, 1);
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, clientRect.right/1.25, clientRect.bottom/1.1 , 0);
		m_matWorld_1 = matS * matT;

		BulletNum = new UIButton(this, m_pSprite, UITAG_BUTTON4);

		m_pRootUI->AddChild(BulletNum);
		//WINSIZEY / 3
		BulletNum->SetPosition(&D3DXVECTOR3(0, 0, 0));
		BulletNum->SetTexture("resources/ui/btn-med-up.png.png",
			"resources/ui/btn-med-over.png.png",
			"resources/ui/btn-med-down.png.png");

		temp = std::to_wstring(restBullet) + L" / 30";
		BulletNum->SetText(g_pFontMgr->GetFont(FONT::NORMAL), temp.c_str());
	}


	{
		//���� UI
		D3DXMATRIXA16 matS;
		D3DXMatrixScaling(&matS, 1.3f, 1.f, 1);
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, clientRect.right / 9.8, clientRect.bottom / 1.18, 0);
		m_matWorld_2 = matS * matT;

		CharaName = new UIButton(this, m_pSprite, UITAG_BUTTON4);

		m_pRootUI_2->AddChild(CharaName);
		//WINSIZEY / 3
		CharaName->SetPosition(&D3DXVECTOR3(0, 0, 0));
		CharaName->SetTexture("resources/ui/btn-med-up.png.png",
			"resources/ui/btn-med-over.png.png",
			"resources/ui/btn-med-down.png.png");

		CharaName->SetText(g_pFontMgr->GetFont(FONT::QUEST), _T("IronMan"));
		//temp = L" IronMan";
	//	CharaName->SetText(g_pFontMgr->GetFont(FONT::NORMAL), temp.c_str());
	}
}

void SampleUI::Update()
{
	//�Ѱ� �Ѿ� 	
	//==========================================
	//==========================================
	if (spaceOn & contorller == 1)
	{
		restBullet--;
		spaceOn = false;
	}
	//if (GetAsyncKeyState(VK_SPACE))
	//{
	//	spaceOn = true;
	//	contorller++;
	//}
	if (g_pMouse->ButtonDown(Mouse::LBUTTON))
	{
		spaceOn = true;
		contorller++;
	}
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


	//�Ѿ� ���ڰ� �پ��°� �Ϸ��� ������Ʈ�� �̳༮���� �־�� �Ǵµ�!
	temp = std::to_wstring(restBullet) + L" / 30";
	//BulletNum->SetText(g_pFontMgr->GetFont(FONT::NORMAL), temp.c_str());

	if (g_pKeyboard->KeyDown('G'))
	{
		CurrHp = CurrHp - 5;
		//��Ʈ�� ����
		if (CurrHp < 0)
		{
			CurrHp = 0;
		}
	}

	PercentOfHp = (float)CurrHp / (float)MaxHp;

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

	g_pDevice->SetTexture(0, NULL); // �ٸ� ���� ����ͼ� ����� ��Ȳ������
	//��������Ʈ�� ����̶� ���� ���̿��� �׷��ش�.
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);


	D3DXMATRIXA16 matR, matT, matWorld;
	D3DXMATRIXA16 matS;










	//D3DXMATRIXA16 matR, matT, matWorld;
	//D3DXMATRIXA16 matS;

	static float fAngle = 0.0f;

	//fAngle += 0.1f;
	//D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, (clientRect.right-m_imageInfo_.Width) /2, ((clientRect.bottom + m_imageInfo_.Height)) / 2, 0);
	D3DXMatrixScaling(&matS, 1.f, 1.0f, 1);
	matWorld = matT * matS;  // �� ������ ���������� �̵��ϴ°�


	


	RECT rc_; // ȸ������, ��ġ�̵� ���ε��� �ֵ�.       ����
	SetRect(&rc_, 0, 0, m_imageInfo_.Width, m_imageInfo_.Height);
	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		m_pTex_,
		&rc_,
		&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);
	//580 -500


	m_matWorld = m_matWorld_1;
	m_pSprite->SetTransform(&m_matWorld);
	SAFE_RENDER(m_pRootUI);



	m_matWorld = m_matWorld_2;
	m_pSprite->SetTransform(&m_matWorld);
	SAFE_RENDER(m_pRootUI_2);

	//	D3DXMATRIXA16 matR, matT, matWorld;
	//	static float fAngle = 0.0f;

	//fAngle += 0.1f;


	RECT rc; // ȸ������, ��ġ�̵� ���ε��� �ֵ�.  ��
	SetRect(&rc, 0, 0, m_imageInfo.Width, m_imageInfo.Height);

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, ((clientRect.right - m_imageInfo.Width)*18.5)/20, clientRect.bottom/1.2, 0);
	D3DXMatrixScaling(&matS, 1.2f, 0.5f, 1);
	//1325 0  -> 1325 -150
	matWorld = matS* matR * matT;

	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		m_pTex,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);



	m_pSprite->SetTransform(&matWorld);
//	SAFE_RENDER(m_pRootUI);



	RECT ironMan_head; // ȸ������, ��ġ�̵� ���ε��� �ֵ�.  ü�� ����
	SetRect(&rc, 0, 0, m_imageInfo_IronMan_Head.Width, m_imageInfo_IronMan_Head.Height);

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, clientRect.right / 45, clientRect.bottom / 1.2, 0);
	//250, 850, 0
	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 1);

	matWorld = matS* matR * matT;

	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		m_pTex_IronMan_Head,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);

	m_pSprite->SetTransform(&matWorld);


	RECT Hp_Back; // ȸ������, ��ġ�̵� ���ε��� �ֵ�.  ü�� ����
	SetRect(&rc, 0, 0, m_imageInfo_Hp_Back.Width, m_imageInfo_Hp_Back.Height);

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, clientRect.right / 11, clientRect.bottom/1.1, 0);
	//250, 850, 0
	D3DXMatrixScaling(&matS, 1.2f, 1.f, 1);

	matWorld = matS* matR * matT;

	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		m_pTex_Hp_Back,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);

	m_pSprite->SetTransform(&matWorld);
//	SAFE_RENDER(m_pRootUI);





	RECT Hp_Loss; // ȸ������, ��ġ�̵� ���ε��� �ֵ�.  ü�� ���� ��
	SetRect(&rc, 0, 0, m_imageInfo_Hp_Loss.Width, m_imageInfo_Hp_Loss.Height);

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, clientRect.right / 10.5, clientRect.bottom / 1.095, 0);
	////250, 850, 0
	D3DXMatrixScaling(&matS, 1.2f, 1.f, 1);

	matWorld = matS* matR * matT;

	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		m_pTex_Hp_Loss,
		&rc,
		&D3DXVECTOR3(0,0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);

	m_pSprite->SetTransform(&matWorld);
//	SAFE_RENDER(m_pRootUI);



	RECT Hp_Remain; // ȸ������, ��ġ�̵� ���ε��� �ֵ�.  ü�� ���� ��
	SetRect(&rc, 0, 0, m_imageInfo_Hp_Remain.Width * PercentOfHp, m_imageInfo_Hp_Remain.Height);

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, clientRect.right / 10.5, clientRect.bottom / 1.095, 0);
	//250, 850, 0
	D3DXMatrixScaling(&matS, 1.2f, 1.f, 1);

	matWorld = matS* matR * matT;

	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		m_pTex_Hp_Remain,
		&rc,
		&D3DXVECTOR3(0,0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);

	m_pSprite->SetTransform(&matWorld);
	//SAFE_RENDER(m_pRootUI);


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
