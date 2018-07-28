#include "stdafx.h"
#include "SampleUI.h"
#include "IUIObject.h"
#include "UIImage.h"
#include "Gun.h"
#include <cstring>

//�ʺ�ȯ ���� üũ��
#include "ObjMap.h"
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
	//m_pRootUI_2 = NULL;
}


SampleUI::~SampleUI()
{
	SAFE_RELEASE(m_pSprite);

	m_pRootUI->ReleaseAll();
	//m_pRootUI_2->ReleaseAll();
}

void SampleUI::Init()
{
	//�ܺο��� ���� �����ϴ� �뵵
	g_pObjMgr->AddToTagList(TAG_UI,this);

	D3DXCreateSprite(g_pDevice, &m_pSprite);
	D3DXCreateSprite(g_pDevice, &m_pSprite_Bullet);
	D3DXCreateSprite(g_pDevice, &m_pSprite_Damage);
	D3DXCreateSprite(g_pDevice, &m_pSprite_Atk);
	D3DXCreateSprite(g_pDevice, &m_pSprite_Def);
	for (int i = 0; i < 20; i++)
	{
		g_pItem->FontController[i] = false;
	}
	restBullet = 30;
	spaceOn = false;
	contorller = 0;
	char c_int[10];
	MaxHp = 100;
	CurrHp = 100;

	
	LifeLoss = 100;

	{
		UIImage * pImage = new UIImage(m_pSprite);
		m_pRootUI = pImage;	
	}
	{
		UIImage * pImage = new UIImage(m_pSprite_Bullet);
		m_pRootUI_Bullet = pImage;
	}


		
	{
		UIImage * pImage = new UIImage(m_pSprite_Damage);
		for (int i = 0; i < 20; i++)
		{
			
			m_pRootUI_Damage[i] = pImage;
		}
	}

	{
		UIImage * pImage = new UIImage(m_pSprite_Atk);
		m_pRootUI_Atk = pImage;
	}

	{
		UIImage * pImage = new UIImage(m_pSprite_Def);
		m_pRootUI_Def = pImage;
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

	// �̴ϸ�-�̸�
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
	//�̴ϸ�-����
	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/minimap/Boss_Minimap_.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Mini_Boss.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Mini_Boss.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

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


	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/ui/back.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Notice_Msg.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Notice_Msg.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture



	GetClientRect(g_hWnd, &clientRect);

	FontInit();
	FontInit2();
	FontInit3();
	Font_Stat_Atk();
	Font_Stat_Def();


}

void SampleUI::Update()
{
	//�Ѱ� �Ѿ� 	
	//==========================================
	//==========================================
	if (spaceOn && contorller == 1)
	{
		if (g_pInventory->Equip[1].index != 0 &&
			g_pEquip->EquipScreenOn == 0 &&
			g_pInventory->openInven == 0 &&
			g_pShop->ShopOpen == 0)
		{
			restBullet--;
			spaceOn = false;
		}
	}


	MobX = g_pItem->SetX();
	MobY = g_pItem->SetY();


	positionY = g_pItem->timer;
	//GetItems->SetPosition(&D3DXVECTOR3(0, -200 - ((400 - positionY) / 8), 0));

	AtkDamage = std::to_wstring(g_pUIManager->AnswerDmg);

	temp = std::to_wstring(restBullet) + L" / 30";

	GetItems->SetPosition(&D3DXVECTOR3((MobX - Notice_Msg.m_imageInfo.Width/2) / ScaleX_GetItems, ((MobY- Notice_Msg.m_imageInfo.Height-50) / ScaleY_GetItems) - ((30-g_pItem->timer)), 0));
	

	// ���� �ڸ� ���ڷ� ���߱� ���ؼ� ���
	if (g_pUIManager->IronMan_Atk < 10)
	{
		Str_StatAtk = L"ATK :0" + std::to_wstring(g_pUIManager->IronMan_Atk);
	}
	else
	{
		Str_StatAtk = L"ATK :" + std::to_wstring(g_pUIManager->IronMan_Atk);
	}

	if (g_pUIManager->IronMan_Def < 10)
	{
		Str_StatDef = L"DEF :0" + std::to_wstring(g_pUIManager->IronMan_Def);
	}
	else
	{
		Str_StatDef = L"DEF :" + std::to_wstring(g_pUIManager->IronMan_Def);
	}
	//DamageFont->SetPosition(&D3DXVECTOR3(500,500, 0));

	
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
		
	}
	

	//if (g_pKeyboard->KeyDown('G'))
	//{
	//	CurrHp = CurrHp - 5;
	//	//��Ʈ�� ����
	//}
	if (CurrHp < 0)
	{
		CurrHp = 0;
	}

	PercentOfHp = (float)CurrHp / (float)MaxHp;



	//�÷��̾��� ���� ��� ��������
	CalPlayerPos = g_pObjMgr->FindObjectByTag(TAG_PLAYER)->GetWorldMatrix();
	//CalPlayerPos._41//�̰� X��ǥ
	//CalPlayerPos._42//�̰� Y��ǥ
	//CalPlayerPos._43//�̰� Z��ǥ


	//==========================================
	//==========================================

	SAFE_UPDATE(m_pRootUI);
	SAFE_UPDATE(m_pRootUI_Bullet);
	for (int i = 0; i < 20; i++)
	{
		if (g_pItem->MonsterDamageTimer[i] != 0)
		{
			g_pItem->MonsterDamageTimer[i]--;
		}
		
		
		SAFE_UPDATE(m_pRootUI_Damage[i]);
	}

	//�������ͽ� atk�� def
	SAFE_UPDATE(m_pRootUI_Atk);
	SAFE_UPDATE(m_pRootUI_Def);
}
void SampleUI::DamagePositionUpdate(int fontNum)
{

	for (int i = 0; i < 20; i++)
	{		

		if ((g_pItem->MonsterDamageTimer[i] == 0))
		{
			DamageFont[i]->SetPosition(&D3DXVECTOR3((MobX - 50), ((MobY - 100)), 0));
		}		
	
		else if (g_pItem->MonsterDamageTimer[i] != 0 )
		{
			DamageFont[i]->SetPosition(&D3DXVECTOR3((MobX - 50), ((MobY - 100)) - ((40 - g_pItem->MonsterDamageTimer[i])), 0));

		}
	}
		/*}
	*/

}

void SampleUI::Render()
{

	g_pDevice->SetTexture(0, NULL); // �ٸ� ���� ����ͼ� ����� ��Ȳ������
	//��������Ʈ�� ����̶� ���� ���̿��� �׷��ش�.
//	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite_Bullet->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSprite_Damage->Begin(D3DXSPRITE_ALPHABLEND);
	



	D3DXMATRIXA16 matR, matT, matWorld;
	D3DXMATRIXA16 matS;
	static float fAngle = 0.0f;

	//fAngle += 0.1f;
	//D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, (clientRect.right  / 2) -15, ((clientRect.bottom / 2) -15), 0);
	D3DXMatrixScaling(&matS, 1.f, 1.0f, 1);
	matWorld = matS * matT;  // �� ������ ���������� �̵��ϴ°�

	//������ ���� ��������� ������
	if (g_pInventory->Equip[1].index != 0)
	{
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
		m_pSprite->End();
	}
	//580 -500
	//=======================================================

	m_pSprite->SetTransform(&m_matWorld);
	m_pSprite->SetTransform(&m_matWorld_DamageFont);
	m_pSprite->SetTransform(&m_matWorld_Bullet);

	m_pSprite_Atk->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite_Atk->SetTransform(&m_matWorld_StatAtk);
	SAFE_RENDER(m_pRootUI_Atk);
	m_pSprite_Atk->End();
	
	m_pSprite_Def->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite_Def->SetTransform(&m_matWorld_StatDef);
	SAFE_RENDER(m_pRootUI_Def);
	m_pSprite_Def->End();




	if (g_pItem->timer > 0)
	{

		SAFE_RENDER(m_pRootUI);
		g_pItem->timer--;
		Debug->AddText(g_pItem->timer);
	}

	SAFE_RENDER(m_pRootUI_Bullet);

	/*if (PreFontNum != g_pItem->FontNum)
	{*/
		
		



	for (int i = 0; i < 20; i++)
	{
		if (g_pItem->MonsterDamageTimer[i] > 0)
		{
		
			DamagePositionUpdate(i);
			SAFE_RENDER(m_pRootUI_Damage[i]);
		}
		
	
	}
	
	//}
	//PreFontNum = g_pItem->FontNum;


	//===============================================
		for (int i = 0; i < 20; i++)
		{
		
		}


	
	//	D3DXMATRIXA16 matR, matT, matWorld;
	//	static float fAngle = 0.0f;

	//fAngle += 0.1f;


	// ȸ������, ��ġ�̵� ���ε��� �ֵ�.  ��
		if (g_pInventory->Equip[Weapon_Type_MainWeapons].index != 0)

		{
			SetRect(&Gun.m_Image_rc, 0, 0, Gun.m_imageInfo.Width, Gun.m_imageInfo.Height);

			D3DXMatrixRotationZ(&matR, fAngle);
			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, ((clientRect.right - Gun.m_imageInfo.Width) / 40) * 39, clientRect.bottom / 1.5, 0);
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
			m_pSprite->End();
		}
	//m_pSprite->SetTransform(&m_matWorld);

	//m_pSprite->SetTransform(&matWorld);
	//SAFE_RENDER(m_pRootUI);



	 // ȸ������, ��ġ�̵� ���ε��� �ֵ�.  ü�� ����
	SetRect(&Character_HP_BackGround.m_Image_rc, 0, 0, Character_HP_BackGround.m_imageInfo.Width, Character_HP_BackGround.m_imageInfo.Height);

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, clientRect.right / 12, clientRect.bottom/1.2, 0);
	//D3DXMatrixTranslation(&matT,0, 0, 0);

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
	m_pSprite->End();
	//m_pSprite->SetTransform(&matWorld);
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
	m_pSprite->End();

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
	m_pSprite->End();

	//�̴ϸ� �׸���- � ���� �ѷ��ִ� ���� ���ؼ� ���ǰ� �ʿ���
	if (static_cast <ObjMap *>(g_pObjMgr->FindObjectByTag(TAG_OBJMAP))->GetMapChangeSignal() == false)
	{
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
			&D3DXVECTOR3(Minimap.m_imageInfo.Width / 2, Minimap.m_imageInfo.Height / 2, 0),
			//&D3DXVECTOR3(0, 0, 0),
			//&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			WHITE);
		m_pSprite->End();
	}
	else//������ �̴ϸ� �׷��ֱ�
	{
		//�̴ϸ� �׸���- � ���� �ѷ��ִ� ���� ���ؼ� ���ǰ� �ʿ���
		SetRect(&Mini_Boss.m_Image_rc, 0, 0, Mini_Boss.m_imageInfo.Width, Mini_Boss.m_imageInfo.Height);

		D3DXMatrixRotationZ(&matR, 0);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, Mini_Boss.m_imageInfo.Width / 4, Mini_Boss.m_imageInfo.Height / 4, 0);
		//250, 850, 0
		D3DXMatrixScaling(&matS, .5f, .5f, 1);

		matWorld = matS* matR * matT;

		//D3DXSPRITE_ALPHABLEND
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld);
		m_pSprite->Draw(
			Mini_Boss.m_pTex,
			&Mini_Boss.m_Image_rc,
			&D3DXVECTOR3(Mini_Boss.m_imageInfo.Width / 2, Mini_Boss.m_imageInfo.Height / 2, 0),
			//&D3DXVECTOR3(0, 0, 0),
			//&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			WHITE);
		m_pSprite->End();
	}

	//fAngle -= 0.01;
	float Rotscale = g_pCamera->m_rotY;

	//�̴ϸ� ĳ���� ǥ��
	SetRect(&MiniCHAR.m_Image_rc, 0, 0, MiniCHAR.m_imageInfo.Width, MiniCHAR.m_imageInfo.Height);

	D3DXMatrixRotationZ(&matR, D3DX_PI/-2 + Rotscale);
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
	m_pSprite->End();



	int a = clientRect.right;


	//SAFE_RENDER(m_pRootUI_Def);
	//SAFE_RENDER(m_pRootUI);
	m_pSprite_Damage->End();
	m_pSprite_Bullet->End();
	m_pSprite->End();
	
	
}

void SampleUI::OnClick(UIButton * pSender)
{
	//if (pSender->m_uiTag == UITAG_BUTTON1)
	//{
	//	UIText* pText = (UIText*)m_pRootUI->FindChildByUITag(UITAG_TEXTVIEW);
	//	pText->m_text = _T("Button1 pushed");
	//}
	//else if (pSender->m_uiTag == UITAG_BUTTON2)
	//{
	//	UIText* pText = (UIText*)m_pRootUI->FindChildByUITag(UITAG_TEXTVIEW);
	//	pText->m_text = _T("Button2 pushed");
	//}

	//else if (pSender->m_uiTag == UITAG_BUTTON3)
	//{
	//	UIText* pText = (UIText*)m_pRootUI->FindChildByUITag(UITAG_TEXTVIEW);
	//	pText->m_text = _T("Button3 pushed");
	//}
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

void SampleUI::FontInit()
{
	
	ScaleX_GetItems = 1.f;
	ScaleY_GetItems = 1.f;
		D3DXMATRIXA16 matS;
		D3DXMATRIXA16 matT;
		D3DXMatrixScaling(&matS, ScaleX_GetItems, ScaleY_GetItems, 1);
		D3DXMatrixTranslation(&matT, 0, 0, 0);
		m_matWorld = matS * matT;
		GetItems = new UIButton(this, m_pSprite, UITAG_BUTTON1);
		GetItems->SetTexture("resources/ui/back.png",
			"resources/ui/back.png",
			"resources/ui/back.png");
		GetItems->SetText(g_pFontMgr->GetFont(FONT::Item), _T("Item Get"),WHITE);
		m_pRootUI->AddChild(GetItems);
}

void SampleUI::FontInit2()
{
	ScaleX_BulletNum = 1.f;
	ScaleY_BulletNum = 1.f;
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, ScaleX_BulletNum, ScaleY_BulletNum, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	m_matWorld_Bullet = matS * matT;

	BulletNum = new UIButton(this, m_pSprite_Bullet, UITAG_BUTTON4);
	BulletNum->SetPosition(&D3DXVECTOR3(((WINSIZEX / 5) * 4)  , ((WINSIZEY / 32) * 25) , 0));


	BulletNum->SetTexture("resources/ui/btn-med-up.png.png",
		"resources/ui/btn-med-up.png.png",
		"resources/ui/btn-med-up.png.png");

	temp = std::to_wstring(restBullet) + L" / 30";
	BulletNum->SetText(g_pFontMgr->GetFont(FONT::NORMAL), temp.c_str(), WHITE);
	m_pRootUI_Bullet->AddChild(BulletNum);


}

void SampleUI::FontInit3()
{


	ScaleX_BulletNum = 1.f;
	ScaleY_BulletNum = 1.f;
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, ScaleX_BulletNum, ScaleY_BulletNum, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	m_matWorld_DamageFont = matS * matT;

	for (int i = 0; i < 20; i++)
	{
		DamageFont[i] = new UIText(g_pFontMgr->GetFont(FONT::QUEST), m_pSprite_Damage, UITAG_TEXTVIEW);
		/*WeaponAtk = std::to_wstring(g_pInventory->Equip[0].Atk);*/

		DamageFont[i]->SetColor(RED);
		DamageFont[i]->m_text = AtkDamage.c_str();
		DamageFont[i]->m_size = D3DXVECTOR2(100, 50);
		DamageFont[i]->RenderingOn = false;
		m_pRootUI_Damage[i]->AddChild_Damage(DamageFont[i]);

	}


	//	UIText * pText = new UIText(g_pFontMgr->GetFont(FONT::NORMAL), m_pSprite, UITAG_TEXTVIEW);
	//	m_pRootUI->AddChild(pText);
	//	pText->m_text = _T("(Push the Button)");
	//	pText->m_size = D3DXVECTOR2(312, 200);
	//	pText->SetPosition(&D3DXVECTOR3(100, 100, 0));
}

void SampleUI::Font_Stat_Atk()
{
	ScaleX_StatAtk = 1.f;
	ScaleY_StatAtk = 1.f;
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, ScaleX_StatAtk, ScaleY_StatAtk, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0,0, 0);
	m_matWorld_StatAtk = matS * matT;

	Stat_Atk = new UIButton(this, m_pSprite_Atk, UITAG_BUTTON4);
	Stat_Atk->SetPosition(&D3DXVECTOR3(clientRect.right * 0.14, clientRect.bottom *0.9, 0));

	//BulletNum->SetTexture("resources/ui/btn-med-up.png.png",
	//	"resources/ui/btn-med-over.png.png",
	//	"resources/ui/btn-med-down.png.png");

	Stat_Atk->SetTexture("resources/images/inventory/Null_back_ATK.png",
		"resources/images/inventory/Null_back_ATK.png",
		"resources/images/inventory/Null_back_ATK.png");

	Str_StatAtk = L"ATK : " + std::to_wstring(g_pUIManager->IronMan_Atk);
	Stat_Atk->SetText(g_pFontMgr->GetFont(FONT::NORMAL), Str_StatAtk.c_str(), WHITE);
	m_pRootUI_Atk->AddChild(Stat_Atk);
		
}

void SampleUI::Font_Stat_Def()
{
	ScaleX_StatDef = 1.f;
	ScaleY_StatDef = 1.f;
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, ScaleX_StatDef, ScaleY_StatDef, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 0, 0);
	m_matWorld_StatDef = matS * matT;

	Stat_Def = new UIButton(this, m_pSprite_Def, UITAG_BUTTON4);
	Stat_Def->SetPosition(&D3DXVECTOR3(clientRect.right * 0.21, clientRect.bottom *0.9, 0));

	//BulletNum->SetTexture("resources/ui/btn-med-up.png.png",
	//	"resources/ui/btn-med-over.png.png",
	//	"resources/ui/btn-med-down.png.png");

	Stat_Def->SetTexture("resources/images/inventory/Null_back_ATK.png",
		"resources/images/inventory/Null_back_ATK.png",
		"resources/images/inventory/Null_back_ATK.png");

	Str_StatDef = L"DEF : " + std::to_wstring(g_pUIManager->IronMan_Def);
	Stat_Def->SetText(g_pFontMgr->GetFont(FONT::NORMAL), Str_StatDef.c_str(), WHITE);
	m_pRootUI_Def->AddChild(Stat_Def);

}

