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
	//m_pSprite_ = NULL;
	m_pRootUI = NULL;
}


SampleUI::~SampleUI()
{
	SAFE_RELEASE(m_pSprite);

	m_pRootUI->ReleaseAll();
}

void SampleUI::Init()
{
	D3DXCreateSprite(g_pDevice, &m_pSprite);

	restBullet = 30;
	spaceOn = false;
	contorller = 0;
	char c_int[10];
	MaxHp = 100;
	CurrHp = 100;

	
	LifeLoss = 100;

	{
		UIImage * pImage = new UIImage(m_pSprite);
		//pImage->SetTexture("resources/ui/panel-info.png.png");
		m_pRootUI = pImage;
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
		&Gun.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Gun.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

					// �� �ּ��� �˴� �����
					// ���� ���Ѵٰ� �ڶ��ϳ�??
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
		&Cross_Hair.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Cross_Hair.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture



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
		&Character_HP_BackGround.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Character_HP_BackGround.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture


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
		&Character_HP_Remain.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Character_HP_Remain.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture


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
		&Character_HP_Loss.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Character_HP_Loss.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

	 // �̴ϸ�
	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/minimap/MiniMap_.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Minimap.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Minimap.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture
	
	//�̴ϸ��� ĳ���� ǥ�� �׸���
	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/minimap/MiniChara__.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&MiniCHAR.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&MiniCHAR.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture
	//�÷��̾� ��ġ�� ������ų ��İ� �ʱ�ȭ
	D3DXMatrixIdentity(&CalPlayerPos);




	//�̺κ��� update�� ���־ ������ ��� �����̾���.
	{
		D3DXMATRIXA16 matS;
		D3DXMatrixScaling(&matS, 1.f, 1.2f, 1);
		D3DXMATRIXA16 matT;
		D3DXMatrixTranslation(&matT, (WINSIZEX/5)*4, (WINSIZEY/32) *25, 0);
		m_matWorld = matS * matT;

		BulletNum = new UIButton(this, m_pSprite, UITAG_BUTTON4);
		// �� ���� �ϰڴ�.
		m_pRootUI->AddChild(BulletNum);
		//WINSIZEY / 3
		//BulletNum->SetPosition(&D3DXVECTOR3(WINSIZEX - 450, (WINSIZEY / 4), 0));
		BulletNum->SetPosition(&D3DXVECTOR3(0, 0, 0));

		BulletNum->SetTexture("resources/ui/btn-med-up.png.png",
			"resources/ui/btn-med-over.png.png",
			"resources/ui/btn-med-down.png.png");

		temp = std::to_wstring(restBullet) + L" / 30";
		BulletNum->SetText(g_pFontMgr->GetFont(FONT::NORMAL), temp.c_str());
	}

	GetClientRect(g_hWnd, &clientRect);

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

	//�÷��̾��� ���� ��� ��������
	CalPlayerPos = g_pObjMgr->FindObjectByTag(TAG_PLAYER)->GetWorldMatrix();
	//CalPlayerPos._41//�̰� X��ǥ
	//CalPlayerPos._42//�̰� Y��ǥ
	//CalPlayerPos._43//�̰� Z��ǥ


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
	static float fAngle = 0.0f;

	//fAngle += 0.1f;
	//D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, (clientRect.right  / 2) -15, ((clientRect.bottom / 2) -15), 0);



	D3DXMatrixScaling(&matS, 1.f, 1.0f, 1);
	matWorld = matS * matT;  // �� ������ ���������� �̵��ϴ°�

	// ȸ������, ��ġ�̵� ���ε��� �ֵ�.       ����
	SetRect(&Cross_Hair.m_Image_rc, 0, 0, Cross_Hair.m_imageInfo.Width, Cross_Hair.m_imageInfo.Height);
	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		Cross_Hair.m_pTex,
		&Cross_Hair.m_Image_rc,
		&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);
	//580 -500
	m_pSprite->SetTransform(&m_matWorld);
	SAFE_RENDER(m_pRootUI);

	//	D3DXMATRIXA16 matR, matT, matWorld;
	//	static float fAngle = 0.0f;

	//fAngle += 0.1f;


	// ȸ������, ��ġ�̵� ���ε��� �ֵ�.  ��
	SetRect(&Gun.m_Image_rc, 0, 0, Gun.m_imageInfo.Width, Gun.m_imageInfo.Height);

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, ((clientRect.right - Gun.m_imageInfo.Width)/40)*39, clientRect.bottom/1.5, 0);
	D3DXMatrixScaling(&matS, 1.f, .8f, 1);
	//1325 0  -> 1325 -150
	matWorld = matS* matR * matT;

	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		Gun.m_pTex,
		&Gun.m_Image_rc,
		&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);



	m_pSprite->SetTransform(&matWorld);
	//SAFE_RENDER(m_pRootUI);



	 // ȸ������, ��ġ�̵� ���ε��� �ֵ�.  ü�� ����
	SetRect(&Character_HP_BackGround.m_Image_rc, 0, 0, Character_HP_BackGround.m_imageInfo.Width, Character_HP_BackGround.m_imageInfo.Height);

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, clientRect.right / 12, clientRect.bottom/1.2, 0);
	//250, 850, 0
	D3DXMatrixScaling(&matS, 1.2f, 1.f, 1);

	matWorld = matS* matR * matT;

	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		Character_HP_BackGround.m_pTex,
		&Character_HP_BackGround.m_Image_rc,
		&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);

	m_pSprite->SetTransform(&matWorld);
	//SAFE_RENDER(m_pRootUI);





	// ȸ������, ��ġ�̵� ���ε��� �ֵ�.  ü�� ���� ��
	SetRect(&Character_HP_Loss.m_Image_rc, 0, 0, Character_HP_Loss.m_imageInfo.Width, Character_HP_Loss.m_imageInfo.Height);

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, clientRect.right / 11.4, clientRect.bottom / 1.192, 0);
	////250, 850, 0
	D3DXMatrixScaling(&matS, 1.2f, 1.f, 1);

	matWorld = matS* matR * matT;

	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		Character_HP_Loss.m_pTex,
		&Character_HP_Loss.m_Image_rc,
		&D3DXVECTOR3(0,0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);

	m_pSprite->SetTransform(&matWorld);
	//SAFE_RENDER(m_pRootUI);



	 // ȸ������, ��ġ�̵� ���ε��� �ֵ�.  ü�� ���� ��
	SetRect(&Character_HP_Remain.m_Image_rc, 0, 0, Character_HP_Remain.m_imageInfo.Width * PercentOfHp, Character_HP_Remain.m_imageInfo.Height);

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, clientRect.right / 11.4, clientRect.bottom / 1.192, 0);
	//250, 850, 0
	D3DXMatrixScaling(&matS, 1.2f, 1.f, 1);

	matWorld = matS* matR * matT;

	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		Character_HP_Remain.m_pTex,
		&Character_HP_Remain.m_Image_rc,
		&D3DXVECTOR3(0,0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);

	//�̴ϸ� �׸���
	SetRect(&Minimap.m_Image_rc, 0, 0, Minimap.m_imageInfo.Width, Minimap.m_imageInfo.Height);

	D3DXMatrixRotationZ(&matR, 0);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Minimap.m_imageInfo.Width / 4, Minimap.m_imageInfo.Height / 4, 0);
	//250, 850, 0
	D3DXMatrixScaling(&matS, .5f, .5f, 1);

	matWorld = matS* matR * matT;

	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		Minimap.m_pTex,
		&Minimap.m_Image_rc,
		&D3DXVECTOR3(Minimap.m_imageInfo.Width/2, Minimap.m_imageInfo.Height/2, 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);


	//fAngle -= 0.01;
	float Rotscale = g_pCamera->m_rotY;

	//�̴ϸ� ĳ���� ǥ��
	SetRect(&MiniCHAR.m_Image_rc, 0, 0, MiniCHAR.m_imageInfo.Width, MiniCHAR.m_imageInfo.Height);

	D3DXMatrixRotationZ(&matR, D3DX_PI/-2 + Rotscale * (-1));
	D3DXMatrixIdentity(&matT);
	//D3DXMatrixTranslation(&matT, 10, 10, 0);
	D3DXMatrixTranslation(&matT, (MiniCHAR.m_imageInfo.Width /2) + ((CalPlayerPos._43 / 8.f)*(-1)) +180 , (MiniCHAR.m_imageInfo.Height / 2) +(CalPlayerPos._41 / 6.f) +90, 0);
	D3DXMatrixScaling(&matS, .5f, .5f, 1);

	matWorld = matS* matR * matT;

	MiniCHAR.m_Sacle_rc.left = (360 + (CalPlayerPos._43 / 8.f *(-1))) *0.5f;
	MiniCHAR.m_Sacle_rc.top = (180 + (CalPlayerPos._41 / 6.f))*0.5f;

	//D3DXSPRITE_ALPHABLEND
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld);
	m_pSprite->Draw(
		MiniCHAR.m_pTex,
		&MiniCHAR.m_Image_rc,
		&D3DXVECTOR3(MiniCHAR.m_imageInfo.Width/2, MiniCHAR.m_imageInfo.Height*(0.75f), 0),
		//&D3DXVECTOR3(0, 0, 0),
		//&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);






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
