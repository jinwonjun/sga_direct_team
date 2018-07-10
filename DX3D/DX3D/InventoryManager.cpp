#include "stdafx.h"
#include "InventoryManager.h"
#include "Gun.h"
#include "UIImage.h"


InventoryManager* InventoryManager::instance = NULL;



InventoryManager * InventoryManager::Get()
{
	if(instance == NULL)
		instance = new InventoryManager();


	return instance;
}

void InventoryManager::Delete()
{
	
	SAFE_DELETE(instance);
}


void InventoryManager::Init()
{
	//�Ұ��� �� false�� �ʱ�ȭ ��Ű��, m_pSprite ����� ����
	D3DXCreateSprite(g_pDevice, &m_pSprite);
	for (int i = 0; i < 6; i++)
	{
		D3DXCreateSprite(g_pDevice, &m_pSprite_Equip[i]);
	}
	openInven = false;
	SwapDoor = false;
	EscapeFor = false;
	pressOn = false;
	alreadyWorkedRbutton = false;
	ItemSizeX = 80;
	ItemSizeY = 80;
	EmptyRcX = ItemSizeX - 5;
	EmptyRcY = ItemSizeY - 5;
	static float fAngle = 0.0f;

	GetClientRect(g_hWnd, &clientRect);

	//�ػ� ��ȯ�� ���� ������ �����. 
	Adjust_Display_Mode_X = ((float)clientRect.right - (float)clientRect.left) / (float)OriginX;
	Adjust_Display_Mode_Y = ((float)clientRect.bottom - (float)clientRect.top) / (float)OriginY;

	//�κ��丮 �ʱ�ȭ ����
	//���̵嵵 �Ȱ��� �ϳ� �����д�.
	Basic_ScaleX = 0.3f;
	Basic_ScaleY = 0.3f;

	g_pItem->ItemTable();


	

	for (int i = 0; i < NumberOfItems; i++)
	{
		if (g_pItem->Items[i].index == NULL)
		{
			continue;
		}
		Shop_Item.push_back(g_pItem->Items[i]);
	}



	//Ŭ���̾�Ʈ ��Ʈ�� �����Ѵ�.
	//���߿� Ŭ�󸮾�Ʈ ��Ʈ�� ���� �������� �������̳� �׷��͵� ��ġ ����
	// ������ �Ǵ� Ŭ���̾�Ʈ�� �����ϰ� 
	//�̹����� �����ϵ� �׿� ���缭 ���� ����
	//ex) 1080 * 600 �ε�, �츮�� 540 * 300 �� ����ϰ� �Ǹ�
	// �̹��� ��ĳ���� X =  0.5 , Y = 0.5 �� ����
	// �� ����ó���� �ʿ��ҵ�



	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
	//	_T("resources/images/inventory/Inven_temp_1.png"),   //LPCTSTR pSrcFile,
		_T("resources/images/inventory/Inven_temp_3.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Inventory.m_image,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Inventory.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/inventory/Inven_temp_2.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Inventory_Chara.m_image,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Inventory_Chara.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture


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

	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Button_Exit.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Exit_Button.m_image,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Exit_Button.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture


	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/inventory/Item_Info_Back.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Item_Info_Back.m_image,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Item_Info_Back.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

	//White_back,Gray_back.png
	for (int i = 0; i < 6; i++) 
	{
		D3DXCreateTextureFromFileEx(
			g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
			_T("resources/images/inventory/White_back.png"),   //LPCTSTR pSrcFile,
			D3DX_DEFAULT_NONPOW2,   //UINT Width,
			D3DX_DEFAULT_NONPOW2,   //UINT Height,
			D3DX_DEFAULT,      //UINT MipLevels,
			0,               //DWORD Usage,
			D3DFMT_UNKNOWN,      //D3DFORMAT Format,
			D3DPOOL_MANAGED,   //D3DPOOL Pool
			D3DX_FILTER_NONE,   //DWORD Filter
			D3DX_DEFAULT,      //DWORD MipFilter
			D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
			&Equiped_Item[i].m_image,   //D3DXIMAGE_INFO *pSrcInfo
			NULL,         //PALETTEENTRY *pPalette
			&Equiped_Item[i].m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

		Equiped_Item[i].ScaleX = 1.5f *Adjust_Display_Mode_X;
		Equiped_Item[i].ScaleY = .3f *Adjust_Display_Mode_Y;
		Equiped_Item[i].PositionX = ((clientRect.right *0.05) * Adjust_Display_Mode_X);
		Equiped_Item[i].PositionY = (clientRect.bottom *(0.055 + (0.15*i)) * Adjust_Display_Mode_Y);
		/*Equiped_Item[i].PositionX = 100;
		Equiped_Item[i].PositionY = 100 + 200 * i;*/

		D3DXCreateTextureFromFileEx(
			g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
			_T("resources/images/inventory/Gray_back.png"),   //LPCTSTR pSrcFile,
			D3DX_DEFAULT_NONPOW2,   //UINT Width,
			D3DX_DEFAULT_NONPOW2,   //UINT Height,
			D3DX_DEFAULT,      //UINT MipLevels,
			0,               //DWORD Usage,
			D3DFMT_UNKNOWN,      //D3DFORMAT Format,
			D3DPOOL_MANAGED,   //D3DPOOL Pool
			D3DX_FILTER_NONE,   //DWORD Filter
			D3DX_DEFAULT,      //DWORD MipFilter
			D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
			&Equiped_Item_BlackBack[i].m_image,   //D3DXIMAGE_INFO *pSrcInfo
			NULL,         //PALETTEENTRY *pPalette
			&Equiped_Item_BlackBack[i].m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

		Equiped_Item_BlackBack[i].ScaleX = .3f *Adjust_Display_Mode_X;
		Equiped_Item_BlackBack[i].ScaleY = .3f *Adjust_Display_Mode_Y;
		Equiped_Item_BlackBack[i].PositionX = (Equiped_Item[i].PositionX + (Equiped_Item[i].m_image.Width *0.05* Adjust_Display_Mode_X));
		Equiped_Item_BlackBack[i].PositionY = (Equiped_Item[i].PositionY + (Equiped_Item[i].m_image.Height *0.04* Adjust_Display_Mode_Y));



	


	}




	//
	//
	//										  // �������� ���� �� �͵�  // �̹��� ������ �ٷ� ���� �ִ� ģ��������
	//										  //�ޱ� ������ D3DXCreateTextureFromFileEx ���� �Ʒ��� �־�� �Ѵ�.
	//}



	


	for (int j = 0; j < INVENVERTI; j++)
	{

		for (int i = 0; i < INVENCORSS; i++)
		{

			InvenArray[i][j].index = 0;
			InvenArray[i][j].name = "no_Name";
			InvenArray[i][j].Atk = 0;
			InvenArray[i][j].MaxHp = 0;
			InvenArray[i][j].Hp = 0;
			InvenArray[i][j].Def = 0;

			InvenArray[i][j].PositionX = (INVENITEMSTART_X + ItemSizeX * i) * Adjust_Display_Mode_X;
			InvenArray[i][j].PositionY = (INVENITEMSTART_Y + ItemSizeY * j) * Adjust_Display_Mode_Y;

			InvenArray[i][j].ScaleX = Basic_ScaleX* Adjust_Display_Mode_X;
			InvenArray[i][j].ScaleY = Basic_ScaleY* Adjust_Display_Mode_Y;
			InvenArray[i][j].isClicked = false;

			InvenArray[i][j].isInvenIn = true;
			InvenArray[i][j].Copy_num = 0;

			InvenArray[i][j].isInvenOver = false;

			SetRect(&InvenArray[i][j].Click_rc,
				InvenArray[i][j].PositionX,
				InvenArray[i][j].PositionY,
				InvenArray[i][j].PositionX + ((InvenArray[i][j].m_image_Item_Info.Width)*(InvenArray[i][j].ScaleX)),
				InvenArray[i][j].PositionY + ((InvenArray[i][j].m_image_Item_Info.Height)*(InvenArray[i][j].ScaleY)));

			SetRect(&InvenArray[i][j].Item_rc,
				0,
				0,
				InvenArray[i][j].m_image_Item_Info.Width,
				InvenArray[i][j].m_image_Item_Info.Height);


			//============================================== 
			// �װ��� ������̾��� ..........................
			//==============================================

			Void_Item[i][j].index = 0;
			Void_Item[i][j].name = "no_Name";
			Void_Item[i][j].Atk = 0;
			Void_Item[i][j].MaxHp = 0;
			Void_Item[i][j].Hp = 0;
			Void_Item[i][j].Def = 0;

			Void_Item[i][j].PositionX = (INVENITEMSTART_X + ItemSizeX * i) *Adjust_Display_Mode_X;
			Void_Item[i][j].PositionY = (INVENITEMSTART_Y + ItemSizeY * j) * Adjust_Display_Mode_Y;
			Void_Item[i][j].ScaleY = Basic_ScaleX* Adjust_Display_Mode_X;
			Void_Item[i][j].ScaleX = Basic_ScaleY* Adjust_Display_Mode_Y;
			Void_Item[i][j].isClicked = false;

			Void_Item[i][j].isInvenIn = true;
			Void_Item[i][j].Copy_num = 0;

			Void_Item[i][j].isInvenOver = false;

			SetRect(&Void_Item[i][j].Click_rc,
				Void_Item[i][j].PositionX,
				Void_Item[i][j].PositionY,
				Void_Item[i][j].PositionX + ItemSizeX,
				Void_Item[i][j].PositionY + ItemSizeY);

			SetRect(&Void_Item[i][j].Item_rc,
				Void_Item[i][j].PositionX,
				Void_Item[i][j].PositionY,
				Void_Item[i][j].PositionX + ItemSizeX,
				Void_Item[i][j].PositionY + ItemSizeY);


			D3DXCreateTextureFromFileEx(
				g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
				_T("resources/images/InvenLight.png"),   //LPCTSTR pSrcFile,
				D3DX_DEFAULT_NONPOW2,   //UINT Width,
				D3DX_DEFAULT_NONPOW2,   //UINT Height,
				D3DX_DEFAULT,      //UINT MipLevels,
				0,               //DWORD Usage,
				D3DFMT_UNKNOWN,      //D3DFORMAT Format,
				D3DPOOL_MANAGED,   //D3DPOOL Pool
				D3DX_FILTER_NONE,   //DWORD Filter
				D3DX_DEFAULT,      //DWORD MipFilter
				D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
				&InvenArray[i][j].m_image_InvenOver_Info,   //D3DXIMAGE_INFO *pSrcInfo
				NULL,         //PALETTEENTRY *pPalette
				&InvenArray[i][j].m_pTex_InvenOver);   //LPDIRECT3DTEXTURE9 *ppTexture

			D3DXCreateTextureFromFileEx(
				g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
				_T("resources/images/InvenLight.png"),   //LPCTSTR pSrcFile,
				D3DX_DEFAULT_NONPOW2,   //UINT Width,
				D3DX_DEFAULT_NONPOW2,   //UINT Height,
				D3DX_DEFAULT,      //UINT MipLevels,
				0,               //DWORD Usage,
				D3DFMT_UNKNOWN,      //D3DFORMAT Format,
				D3DPOOL_MANAGED,   //D3DPOOL Pool
				D3DX_FILTER_NONE,   //DWORD Filter
				D3DX_DEFAULT,      //DWORD MipFilter
				D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
				&Void_Item[i][j].m_image_InvenOver_Info,   //D3DXIMAGE_INFO *pSrcInfo
				NULL,         //PALETTEENTRY *pPalette
				&Void_Item[i][j].m_pTex_InvenOver);   //LPDIRECT3DTEXTURE9 *ppTexture

		}
	}

	//�κ��丮 Mat world ���
	
	Inventory.ScaleX = 2.279f *Adjust_Display_Mode_X;
	Inventory.ScaleY = 2.3f *Adjust_Display_Mode_Y;
	Inventory.PositionX = ((clientRect.right *0.760) - (Inventory.m_image.Width)*Adjust_Display_Mode_X);
	Inventory.PositionY = ((clientRect.bottom *0.055));
	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Inventory.PositionX, Inventory.PositionY, 0);
	D3DXMatrixScaling(&matS, Inventory.ScaleX, Inventory.ScaleY, 1);
	matWorld[matWorld_Inven] = matS * matR * matT;


	Inventory_Chara.ScaleX = 2.279f *Adjust_Display_Mode_X;
	Inventory_Chara.ScaleY = 2.3f *Adjust_Display_Mode_Y;	
	Inventory_Chara.PositionX = Inventory.PositionX;
	Inventory_Chara.PositionY = Inventory.PositionY;
	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Inventory_Chara.PositionX, Inventory_Chara.PositionY, 0);
	D3DXMatrixScaling(&matS, Inventory_Chara.ScaleX, Inventory_Chara.ScaleY, 1);
	matWorld[matWorld_Inven_Chara] = matS * matR * matT;


	Exit_Button.ScaleX = Inventory.ScaleX;
	Exit_Button.ScaleY = Inventory.ScaleY;
	Exit_Button.PositionX = Inventory.PositionX ;
	Exit_Button.PositionY = Inventory.PositionY + (((Inventory.m_image.Height*2.3f)*Adjust_Display_Mode_Y) - Exit_Button.m_image.Height*2.3f);
	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Exit_Button.PositionX, Exit_Button.PositionY, 0);
	D3DXMatrixScaling(&matS, Exit_Button.ScaleX, Exit_Button.ScaleY, 1);
	matWorld[matWorld_Exit_Button] = matS * matR * matT;

	

		

	Item_Info_Back.ScaleX = 1;
	Item_Info_Back.ScaleY = 1;
	Item_Info_Back.PositionX = ((clientRect.right *0.3) * Adjust_Display_Mode_X);
	Item_Info_Back.PositionY = (clientRect.bottom *(0.055) * Adjust_Display_Mode_Y);
	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Item_Info_Back.PositionX, Item_Info_Back.PositionY, 0);
	D3DXMatrixScaling(&matS, Item_Info_Back.ScaleX, Item_Info_Back.ScaleY, 1);
	matWorld[matWorld_Item_Info] = matS * matR * matT;







	for (int i = 0; i < NumberOfItems; i++)
	{
		if (g_pItem->Items[i].index == NULL)
		{
			continue;
		}
		Shop_Item[i].Item_rc = RectMake(0, 0, Shop_Item[i].m_image_Item_Info.Width, Shop_Item[i].m_image_Item_Info.Height);
	}

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT,
		Shop_Item[0].PositionX,
		Shop_Item[0].PositionY,
		0);

	float temp1 = .3f;

	ShopItem_Display_Mode_X = temp1 *Adjust_Display_Mode_X;
	ShopItem_Display_Mode_Y = temp1 *Adjust_Display_Mode_Y;


	D3DXMatrixScaling(&matS, ShopItem_Display_Mode_X, ShopItem_Display_Mode_Y, 1);

	matWorld[matWorld_ShopItem_1] = matS * matR * matT;



	for (int j = 0; j < INVENVERTI; j++)
	{
		Debug->EndLine();
		for (int i = 0; i < INVENCORSS; i++)
		{
			//Debug->AddText(InvenArray[i][j].index);

			D3DXMatrixRotationZ(&matR, fAngle);
			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, InvenArray[i][j].PositionX, InvenArray[i][j].PositionY, 0);
			D3DXMatrixScaling(&matS, InvenArray[i][j].ScaleX, InvenArray[i][j].ScaleY, 1);
			matWorld_InvenItems[matWorld_InvenArray+ i + j * 6] = matS * matR * matT;

		}
	}


	Weapon_Equip_Text();

	//Item_Info_Text();


	


	for (int i = 0; i < 7; i++)
	{
		Equip.push_back(Void_Item[0][0]);
	}


}

void InventoryManager::Update()
{
	//SAFE_UPDATE(m_pRootUI);
	Debug->EndLine();
	Debug->EndLine();
	Debug->AddText(Equip[Weapon_Type_MainWeapons].PositionX);
	Debug->EndLine();
	Debug->AddText(Equip[Weapon_Type_MainWeapons].PositionY);
	Debug->EndLine();

	if (g_pKeyboard->KeyDown('I'))
	{
		openInven = !openInven;
		// I�� ������ �κ��丮�� ���ȴ� ������ �׷���
	}

	if (openInven)
	{
		//Debug->AddText(pressOn);
		//Debug->EndLine();

		GetCursorPos(&mousePoint);
		//���콺 Ŀ�� �ް�
		ScreenToClient(g_hWnd, &mousePoint);
		//��ũ���� Ŭ�����̾�Ʈ... ���콺 Ŀ�� ������ �ʿ����ؿ� ..

	/*	for (int i = 0; i < Equip.size(); i++)
		{
			if (PtInRect(&Equip[i].Click_rc, mousePoint))
			{
				int kd = 0;
			}

		}
*/
		//������ ����
		if (g_pMouse->ButtonDown(Mouse::RBUTTON))
		{

			for (int i = 1; i < 7; i++)
			{
				if (PtInRect(&Equip[i].Click_rc, mousePoint)
					&& Equip[i].isEquiped
					&&alreadyWorkedRbutton == false)
				{
					addIndex(Equip[i]);

					Equip[i] = Void_Item[0][0];
					alreadyWorkedRbutton = true;
				}
			}

			for (int j = 0; j < INVENVERTI; j++)
			{
			
				for (int i = 0; i < INVENCORSS; i++)
				{
					
					// 
					if (PtInRect(&InvenArray[i][j].Click_rc, mousePoint) && alreadyWorkedRbutton == false)
					{
						alreadyWorkedRbutton = true;

						switch (InvenArray[i][j].Equip_Type)
						{
						case Weapon_Type_MainWeapons:
							if (Equip[Weapon_Type_MainWeapons].index == 0)
							{
								swap(Equip[Equip_Main_Weapon_1], InvenArray[i][j]);
								//InvenArray[i][j].index = 0;
								Equip[Weapon_Type_MainWeapons].isEquiped = true;
								InvenArray[i][j] = Void_Item[0][0];
							
								static_cast<Gun*>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GunEqiupSet(Equip[Weapon_Type_MainWeapons].index);

							}
							else
							{
								swap(Equip[Equip_Main_Weapon_1], InvenArray[i][j]);
								Equip[Weapon_Type_MainWeapons].isEquiped = true;

								InvenArray[i][j].isEquiped = false;
								
								static_cast<Gun*>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GunEqiupSet(Equip[Weapon_Type_MainWeapons].index);
							}
						

							break;

						case Weapon_Type_Armor:
							Equip.push_back(InvenArray[i][j]);

							if (Equip[Equip_Armor].index == 0)
							{
								swap(Equip[Equip_Armor], InvenArray[i][j]);

								Equip[Equip_Armor].isEquiped = true;
								InvenArray[i][j] = Void_Item[i][j];
							}
							else
							{
								swap(Equip[Equip_Armor], InvenArray[i][j]);
								Equip[Equip_Armor].isEquiped = true;
								InvenArray[i][j].isEquiped = false;
							}
							break;

						case Equip_Sub_Weapon_2:
							Equip.push_back(InvenArray[i][j]);

							break;



							break;

						default:

							break;

						}



					} // �κ��丮�� �ִ� ������ Ŭ����



					else
					{
						int asdb = 0;
					}
				}


			} // for ������



			alreadyWorkedRbutton = false; // ������ ��ư�� �ѹ��� ���ǰ� �ϱ� ���ؼ� ���
		}

		//�ҷ� ��� �ϸ� �ɲ� ������ 2
		else if (g_pMouse->ButtonDown(Mouse::LBUTTON))
		{



			if (PtInRect(&Shop_Item[0].Click_rc, mousePoint))
			{
				addIndex(Shop_Item[0]);
			}



			/*		else if (PtInRect(&Shop_Item[1].Click_rc, mousePoint))
					{
						addIndex(Shop_Item[1]);
					}*/
			else
			{
				for (int j = 0; j < INVENVERTI; j++)
				{
					for (int i = 0; i < INVENCORSS; i++)
					{
						if (PtInRect(&InvenArray[i][j].Click_rc, mousePoint) && InvenArray[i][j].index != 0)
						{
							preChosenX = i;
							preChosenY = j;
							InvenArray[preChosenX][preChosenY].isClicked = true;
							// Press�� ���� �ǰ� �ϱ� ���ؼ�
							Endfor = true;
							pressOn = true;
						}
						if (Endfor)
						{
							continue;
						}
					}
					if (Endfor)
					{
						continue;
					}
				} // for�� ��
				Endfor = false;
			}

		}

		// ������ �巡���ؼ� �����̰� �ϴ� ģ���� //

		else if (g_pMouse->ButtonPress(Mouse::LBUTTON))
		{
			if (pressOn)
			{
				CrossX = (RectCenter(InvenArray[preChosenX][preChosenY].Click_rc).x - INVENITEMSTART_X) / ItemSizeX;
				VertiY = (RectCenter(InvenArray[preChosenX][preChosenY].Click_rc).y - INVENITEMSTART_Y) / ItemSizeY;

				if (InvenArray[preChosenX][preChosenY].isClicked)
				{
					InvenArray[preChosenX][preChosenY].PositionX = mousePoint.x - 30;
					InvenArray[preChosenX][preChosenY].PositionY = mousePoint.y - 30;
					SetRect(&InvenArray[preChosenX][preChosenY].Click_rc,
						InvenArray[preChosenX][preChosenY].PositionX,
						InvenArray[preChosenX][preChosenY].PositionY,
						InvenArray[preChosenX][preChosenY].PositionX + ((InvenArray[preChosenX][preChosenY].m_image_Item_Info.Width)*(InvenArray[preChosenX][preChosenY].ScaleX)),
						InvenArray[preChosenX][preChosenY].PositionY + ((InvenArray[preChosenX][preChosenY].m_image_Item_Info.Height)*(InvenArray[preChosenX][preChosenY].ScaleY)));

				}
				else
				{

				}

				// �������� �κ� ���� ������ �̰� ���.
				if (((RectCenter(InvenArray[preChosenX][preChosenY].Click_rc).x - INVENITEMSTART_X) >= 0
					&& (RectCenter(InvenArray[preChosenX][preChosenY].Click_rc).y >= 0)
					&& (CrossX <= 5 && VertiY <= 3)))
				{
					for (int j = 0; j < INVENVERTI; j++)
					{
						for (int i = 0; i < INVENCORSS; i++)
						{

							InvenArray[i][j].isInvenOver = false;
							InvenArray[CrossX][VertiY].isInvenOver = true;
						}
					}
				}
				else
				{
					for (int j = 0; j < INVENVERTI; j++)
					{
						for (int i = 0; i < INVENCORSS; i++)
						{

							InvenArray[i][j].isInvenOver = false;
							//InvenArray[CrossX][VertiY].isInvenOn = false;
						}
					}

				}

			}
		}
		else if (g_pMouse->ButtonUp(Mouse::LBUTTON))
		{
			pressOn = false;
			if (InvenArray[preChosenX][preChosenY].isClicked)
			{
				InvenArray[preChosenX][preChosenY].isClicked = false;


				CrossX = (RectCenter(InvenArray[preChosenX][preChosenY].Click_rc).x - INVENITEMSTART_X) / ItemSizeX;
				VertiY = (RectCenter(InvenArray[preChosenX][preChosenY].Click_rc).y - INVENITEMSTART_Y) / ItemSizeY;

				//Ŭ���� �� �Ǹ� ��� false�� �ٷ� �ٲ��ش�. 
				//�̰� ���ϸ�  swap�������� isInvenOn = true ���°� ���ܳ� .
				InvenArray[preChosenX][preChosenY].isInvenOver = false;
				InvenArray[CrossX][VertiY].isInvenOver = false;

				if ((CrossX >= 0 && VertiY >= 0) && (CrossX <= 5 && VertiY <= 3))
				{


					if (InvenArray[CrossX][VertiY].index != 0 && SwapDoor == false)
					{
						swap(InvenArray[preChosenX][preChosenY], InvenArray[CrossX][VertiY]);

						InvenArray[preChosenX][preChosenY].PositionX = (INVENITEMSTART_X + ItemSizeX * preChosenX) *Adjust_Display_Mode_X;
						InvenArray[preChosenX][preChosenY].PositionY = (INVENITEMSTART_Y + ItemSizeY * preChosenY) *Adjust_Display_Mode_Y;
						InvenArray[CrossX][VertiY].PositionX = (INVENITEMSTART_X + ItemSizeX * CrossX) * Adjust_Display_Mode_X;
						InvenArray[CrossX][VertiY].PositionY = (INVENITEMSTART_Y + ItemSizeY * VertiY) * Adjust_Display_Mode_Y;


						SwapDoor = true;
					}
					else if (InvenArray[CrossX][VertiY].index == 0 && SwapDoor == false)
					{
						swap(InvenArray[preChosenX][preChosenY], InvenArray[CrossX][VertiY]);

						InvenArray[preChosenX][preChosenY].PositionX = (INVENITEMSTART_X + ItemSizeX * preChosenX) *Adjust_Display_Mode_X;
						InvenArray[preChosenX][preChosenY].PositionY = (INVENITEMSTART_Y + ItemSizeY * preChosenY) *Adjust_Display_Mode_Y;

						InvenArray[CrossX][VertiY].PositionX = (INVENITEMSTART_X + ItemSizeX * CrossX) * Adjust_Display_Mode_X;
						InvenArray[CrossX][VertiY].PositionY = (INVENITEMSTART_Y + ItemSizeY * VertiY) * Adjust_Display_Mode_Y;

						SwapDoor = true;
					}
					else
					{

						InvenArray[CrossX][VertiY].PositionX = (INVENITEMSTART_X + ItemSizeX * CrossX) * Adjust_Display_Mode_X;
						InvenArray[CrossX][VertiY].PositionY = (INVENITEMSTART_Y + ItemSizeY * VertiY) * Adjust_Display_Mode_Y;
						SwapDoor = true;
					}

					//��� �ѹ� ���ְ� ���Ľ�Ű��.
					for (int j = 0; j < INVENVERTI; j++)
					{
						for (int i = 0; i < INVENCORSS; i++)
						{

							InvenArray[i][j].PositionX = (INVENITEMSTART_X + ItemSizeX * i) * Adjust_Display_Mode_X;
							InvenArray[i][j].PositionY = (INVENITEMSTART_Y + ItemSizeY * j)* Adjust_Display_Mode_X;

						}
					}

				}//(CrossX >= 0 && VertiY >= 0) ��


				else // �������� �κ��丮 ���� ������ �������� ó�� 
				{
					for (int j = 0; j < INVENVERTI; j++)
					{
						for (int i = 0; i < INVENCORSS; i++)
						{

							InvenArray[i][j].PositionX = (INVENITEMSTART_X + ItemSizeX * i) * Adjust_Display_Mode_X;
							InvenArray[i][j].PositionY = (INVENITEMSTART_Y + ItemSizeY * j)* Adjust_Display_Mode_X;
						}
					}
				}
				SwapDoor = false;
			}

		}
		else // ���� ��� ���ۿ��� �ٸ� ���ǿ� �������� ������ �۵� ���Ѵ� 
		{
			for (int j = 0; j < INVENVERTI; j++)
			{
				for (int i = 0; i < INVENCORSS; i++)
				{
					InvenArray[i][j].PositionX = (INVENITEMSTART_X + ItemSizeX * i) * Adjust_Display_Mode_X;
					InvenArray[i][j].PositionY = (INVENITEMSTART_Y + ItemSizeY * j)* Adjust_Display_Mode_Y;

					//InvenArray[i][j].isInvenOver = false;
				}
			}
		}
	} // OpenInve ��
	//Debug->AddText(mousePoint.x);
	//Debug->EndLine();
	//Debug->AddText(mousePoint.y);
	//Debug->EndLine();
	//for (int j = 0; j < INVENVERTI; j++)
	//{
	//	for (int i = 0; i < INVENCORSS; i++)
	//	{
	//		if (PtInRect(&Void_Item[i][j].Click_rc, mousePoint))
	//		{
	//			Void_Item[i][j].isInvenOver = true;
	//		}
	//		//else if (PtInRect(&InvenArray[i][j].Click_rc, mousePoint) && InvenArray[i][j].index == 0)
	//		//{
	//		//	InvenArray[i][j].isInvenOver = true;
	//		//}
	//		else
	//		{
	//			Void_Item[i][j].isInvenOver = false;
	//		}
	//	}
	//}


	for (int j = 0; j < INVENVERTI; j++)
	{
		Debug->EndLine();
		for (int i = 0; i < INVENCORSS; i++)
		{
			Debug->AddText(InvenArray[i][j].index);

		}
	}


	for (int i = 0; i < 6; i++)
	{
	
	SAFE_UPDATE(m_pRootUI_Euip_Text[i]);


	}
}

void InventoryManager::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	for (int i = 0; i < 6; i++)
	{
		m_pSprite_Equip[i]->Begin(D3DXSPRITE_ALPHABLEND);
	}
	

	if (openInven)
	{
		
		//===========================
	

		SetRect(&Inventory.m_rc, 0, 0, Inventory.m_image.Width, Inventory.m_image.Height);


		//m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld[matWorld_Inven]);
		m_pSprite->Draw(
			Inventory.m_pTex,
			&Inventory.m_rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(180, 255, 255, 255));

		//=======================================

		//g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);



		SetRect(&Inventory_Chara.m_rc, 0, 0, Inventory_Chara.m_image.Width, Inventory_Chara.m_image.Height);


		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld[matWorld_Inven_Chara]);
		m_pSprite->Draw(
			Inventory_Chara.m_pTex,
			&Inventory_Chara.m_rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(50, 255, 255, 255));


		SetRect(&Exit_Button.m_rc, 0, 0, Exit_Button.m_image.Width, Exit_Button.m_image.Height);


		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld[matWorld_Exit_Button]);
		m_pSprite->Draw(
			Exit_Button.m_pTex,
			&Exit_Button.m_rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));
		



		//g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		//g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		//g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//g_pDevice->SetRenderState(D3DRS_LIGHTING, false); // ����Ʈ�� Ű�� �������� ...
	
	//	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		//
		//===========================
		//Item


		SetRect(&Shop_Item[0].Item_rc, 0, 0, 0 + (Shop_Item[0].m_image_Item_Info.Width), 0 + (Shop_Item[0].m_image_Item_Info.Height /**temp*/));

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld[matWorld_ShopItem_1]);
		m_pSprite->Draw(
			Shop_Item[0].m_pTex_Item,
			&Shop_Item[0].Item_rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			WHITE);
		// �� �κп� ���� �����


		//������ ������ �ƴ�, ��ũ���������� �Ǿ��־�
		static float fAngle = 0.0f;
		
		for (int j = 0; j < INVENVERTI; j++)
		{
			Debug->EndLine();
			for (int i = 0; i < INVENCORSS; i++)
			{
				Debug->AddText(InvenArray[i][j].index);




				D3DXMatrixRotationZ(&matR, fAngle);
				D3DXMatrixIdentity(&matT);
				D3DXMatrixTranslation(&matT, InvenArray[i][j].PositionX, InvenArray[i][j].PositionY, 0);
				D3DXMatrixScaling(&matS, InvenArray[i][j].ScaleX, InvenArray[i][j].ScaleY, 1);
				matWorld_InvenItems[matWorld_InvenArray+i + j * 6] = matS * matR * matT;


				//Inventory
				SetRect(&InvenArray[i][j].Item_rc, 0, 0, InvenArray[i][j].m_image_Item_Info.Width, InvenArray[i][j].m_image_Item_Info.Height);
				SetRect(&InvenArray[i][j].Click_rc,
					InvenArray[i][j].PositionX + 2,
					InvenArray[i][j].PositionY,
					InvenArray[i][j].PositionX + 2 + ((InvenArray[i][j].m_image_Item_Info.Width)*(InvenArray[i][j].ScaleX)),
					InvenArray[i][j].PositionY + ((InvenArray[i][j].m_image_Item_Info.Height)*(InvenArray[i][j].ScaleY)));



				m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
				m_pSprite->SetTransform(&matWorld_InvenItems[matWorld_InvenArray+i + j * 6]);

				m_pSprite->Draw(
					InvenArray[i][j].m_pTex_Item,
					&InvenArray[i][j].Item_rc,
					&D3DXVECTOR3(0, 0, 0),
					&D3DXVECTOR3(0, 0, 0),
					WHITE);

				if (PtInRect(&InvenArray[i][j].Click_rc, mousePoint) && InvenArray[i][j].index != 0)
				{

					SetRect(&Item_Info_Back.m_rc, 0, 0, Item_Info_Back.m_image.Width, Item_Info_Back.m_image.Height);


					m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
					m_pSprite->SetTransform(&matWorld[matWorld_Item_Info]);
					m_pSprite->Draw(
						Item_Info_Back.m_pTex,
						&Item_Info_Back.m_rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(200, 255, 255, 255));

					float ItemInfoBack_PositionX = Item_Info_Back.PositionX + Item_Info_Back.m_image.Width *0.1;
					float ItemInfoBack_PositionY = Item_Info_Back.PositionY + Item_Info_Back.m_image.Height *0.1;
					float ItemInfoBack_ScaleX = 0.6f;
					float ItemInfoBack_ScaleY = 0.6f;
					D3DXMatrixRotationZ(&matR, fAngle);
					D3DXMatrixIdentity(&matT);
					D3DXMatrixTranslation(&matT, ItemInfoBack_PositionX, ItemInfoBack_PositionY, 0);
					D3DXMatrixScaling(&matS, ItemInfoBack_ScaleX, ItemInfoBack_ScaleY, 1);
					matWorld[matWorld_MouseOver] = matS * matR * matT;

					m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
					m_pSprite->SetTransform(&matWorld[matWorld_MouseOver]);
					m_pSprite->Draw(
						InvenArray[i][j].m_pTex_Item,
						&InvenArray[i][j].Item_rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			}
		}



		SetRect(&Shop_Item[0].Click_rc, Shop_Item[0].PositionX
			, Shop_Item[0].PositionY
			, Shop_Item[0].PositionX + ((Shop_Item[0].m_image_Item_Info.Width)*ShopItem_Display_Mode_X)
			, Shop_Item[0].PositionY + ((Shop_Item[0].m_image_Item_Info.Height)*ShopItem_Display_Mode_Y));


		//============================================

	
		//	float PositionX_Inven, PositionY_Inven;
		// Equip �ѹ� ���������ƾƾƾ� 
		for (int i = 0; i < 6; i++)
			{

			D3DXMatrixRotationZ(&matR, fAngle);
			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, Equiped_Item[i].PositionX, Equiped_Item[i].PositionY, 0);
			D3DXMatrixScaling(&matS, Equiped_Item[i].ScaleX, Equiped_Item[i].ScaleY, 1);
			matWorld[matWorld_Equiped_Item + i] = matS * matR * matT;
				//ItemSet
				SetRect(&Equiped_Item[i].m_rc, 0, 0, Equiped_Item[i].m_image.Width, Equiped_Item[i].m_image.Height);

				SetRect(&Equiped_Item[i].m_rc_click,
					Equiped_Item[i].PositionX,
					Equiped_Item[i].PositionY,
					Equiped_Item[i].PositionX + ((Equiped_Item[i].m_image.Width)*(Equiped_Item[i].ScaleX)),
					Equiped_Item[i].PositionY + ((Equiped_Item[i].m_image.Height)*(Equiped_Item[i].ScaleY)));

				m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
				m_pSprite->SetTransform(&matWorld[matWorld_Equiped_Item + i]);
				m_pSprite->Draw(
					Equiped_Item[i].m_pTex,
					&Equiped_Item[i].m_rc,
					&D3DXVECTOR3(0, 0, 0),
					&D3DXVECTOR3(0, 0, 0),
					D3DCOLOR_ARGB(255, 255, 255, 255));
			



				D3DXMatrixRotationZ(&matR, fAngle);
				D3DXMatrixIdentity(&matT);
				D3DXMatrixTranslation(&matT, Equiped_Item_BlackBack[i].PositionX, Equiped_Item_BlackBack[i].PositionY, 0);
				D3DXMatrixScaling(&matS, Equiped_Item_BlackBack[i].ScaleX, Equiped_Item_BlackBack[i].ScaleY, 1);
				matWorld[matWorld_Equiped_Item_Black + i] = matS * matR * matT;
				//ItemSet
				SetRect(&Equiped_Item_BlackBack[i].m_rc, 0, 0, Equiped_Item_BlackBack[i].m_image.Width, Equiped_Item_BlackBack[i].m_image.Height);

				SetRect(&Equiped_Item_BlackBack[i].m_rc_click,
								Equiped_Item_BlackBack[i].PositionX,
								Equiped_Item_BlackBack[i].PositionY,
								Equiped_Item_BlackBack[i].PositionX + ((Equiped_Item_BlackBack[i].m_image.Width)*(Equiped_Item_BlackBack[i].ScaleX)),
								Equiped_Item_BlackBack[i].PositionY + ((Equiped_Item_BlackBack[i].m_image.Height)*(Equiped_Item_BlackBack[i].ScaleY)));
				
				m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
				m_pSprite->SetTransform(&matWorld[matWorld_Equiped_Item_Black + i]);
				m_pSprite->Draw(
					Equiped_Item_BlackBack[i].m_pTex,
					&Equiped_Item_BlackBack[i].m_rc,
					&D3DXVECTOR3(0, 0, 0),
					&D3DXVECTOR3(0, 0, 0),
					D3DCOLOR_ARGB(180, 255, 255, 255));
			
				
				if (PtInRect(&Equiped_Item[i].m_rc_click, mousePoint) && Equip[i+1].index !=0)
				{		
					SetRect(&Item_Info_Back.m_rc, 0, 0, Item_Info_Back.m_image.Width, Item_Info_Back.m_image.Height);


					m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
					m_pSprite->SetTransform(&matWorld[matWorld_Item_Info]);
					m_pSprite->Draw(
						Item_Info_Back.m_pTex,
						&Item_Info_Back.m_rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(200, 255, 255, 255));

					float ItemInfoBack_PositionX = Item_Info_Back.PositionX + Item_Info_Back.m_image.Width *0.1;
					float ItemInfoBack_PositionY = Item_Info_Back.PositionY + Item_Info_Back.m_image.Height *0.1;
					float ItemInfoBack_ScaleX = 0.6f;
					float ItemInfoBack_ScaleY = 0.6f;
					D3DXMatrixRotationZ(&matR, fAngle);
					D3DXMatrixIdentity(&matT);
					D3DXMatrixTranslation(&matT, ItemInfoBack_PositionX, ItemInfoBack_PositionY, 0);
					D3DXMatrixScaling(&matS, ItemInfoBack_ScaleX, ItemInfoBack_ScaleY, 1);
					matWorld[matWorld_MouseOver] = matS * matR * matT;
					m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
					m_pSprite->SetTransform(&matWorld[matWorld_MouseOver]);
					m_pSprite->Draw(
						Equip[i + 1].m_pTex_Item,
						&Equip[i + 1].Item_rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(255, 255, 255, 255));
				}
			
				

				
			}


		// Enum Equip_Type�� i �� ��� ���
		for (int j = 0; j < 6; j++)
		{
			int i = j + 1;
			int AdjustNum = matWorld_Main_Weapon - i;
			int num = Equip.size();
			if (Equip[i].index != 0)
			{
				if (i < 4)
				{
					Column = 1;
				}
				else if (i > 3)
				{
					Column = 2;
				}
				Cross = (j % 3) +1;

				
				Equip[i].PositionX = Equiped_Item_BlackBack[j].PositionX;
				Equip[i].PositionY = Equiped_Item_BlackBack[j].PositionY;
				Equip[i].ScaleX = .3f * Adjust_Display_Mode_X;
				Equip[i].ScaleY = .3f * Adjust_Display_Mode_Y;
				D3DXMatrixRotationZ(&matR, fAngle);
				D3DXMatrixIdentity(&matT);
				D3DXMatrixTranslation(&matT, Equip[i].PositionX, Equip[i].PositionY, 0);
				D3DXMatrixScaling(&matS, Equip[i].ScaleX, Equip[i].ScaleY, 1);
				matWorld[i+ AdjustNum] = matS * matR * matT;

				//ItemSet
				SetRect(&Equip[i].Item_rc, 0, 0, Equip[i].m_image_Item_Info.Width, Equip[i].m_image_Item_Info.Height);

				SetRect(&Equip[i].Click_rc,
					Equip[i].PositionX,
					Equip[i].PositionY,
					Equip[i].PositionX + ((Equip[i].m_image_Item_Info.Width)*(Equip[i].ScaleX)),
					Equip[i].PositionY + ((Equip[i].m_image_Item_Info.Height)*(Equip[i].ScaleY)));

				m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
				m_pSprite->SetTransform(&matWorld[i+AdjustNum]);

				m_pSprite->Draw(
					Equip[i].m_pTex_Item,
					&Equip[i].Item_rc,
					&D3DXVECTOR3(0, 0, 0),
					&D3DXVECTOR3(0, 0, 0),
					WHITE);

				
			}


	
		}	

	
	



		if (g_pMouse->ButtonPress(Mouse::LBUTTON))
		{
			D3DXMatrixRotationZ(&matR, fAngle);
			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, mousePoint.x, mousePoint.y, 0);
			D3DXMatrixScaling(&matS, 1.f, 1.f, 1);
			matWorld[matWorld_MouseCursor] = matS * matR * matT;

			//m_pSprite->SetTransform(&matWorld[matWorld_MouseCursor]);

			SetRect(&MousCursor_ClickedOn.m_rc, 0, 0, MousCursor_ClickedOn.m_image.Width, MousCursor_ClickedOn.m_image.Height);


			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			m_pSprite->SetTransform(&matWorld[matWorld_MouseCursor]);
			m_pSprite->Draw(
				MousCursor_ClickedOn.m_pTex,
				&MousCursor_ClickedOn.m_rc,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				WHITE);
		}

		else
		{
			D3DXMatrixRotationZ(&matR, fAngle);
			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, mousePoint.x, mousePoint.y, 0);
			D3DXMatrixScaling(&matS, 1.f, 1.f, 1);
			matWorld[matWorld_MouseCursor] = matS * matR * matT;
			//m_pSprite->SetTransform(&matWorld[matWorld_MouseCursor]);

			SetRect(&MouseCursor_Normal.m_rc, 0, 0, MouseCursor_Normal.m_image.Width, MouseCursor_Normal.m_image.Height);
			
			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			m_pSprite->SetTransform(&matWorld[matWorld_MouseCursor]);
			m_pSprite->Draw(
				MouseCursor_Normal.m_pTex,
				&MouseCursor_Normal.m_rc,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				WHITE);
		}
		for (int j = 0; j < INVENVERTI; j++)
		{

			for (int i = 0; i < INVENCORSS; i++)
			{
				if (InvenArray[i][j].index == 0 && PtInRect(&Void_Item[i][j].Item_rc,mousePoint))
				{


					SetRect(&InvenArray[i][j].isInven_rc, 0, 0, InvenArray[i][j].m_image_InvenOver_Info.Width, InvenArray[i][j].m_image_InvenOver_Info.Height);
					SetRect(&InvenArray[i][j].isInven_show_rc,
						InvenArray[i][j].PositionX + 2,
						InvenArray[i][j].PositionY,
						InvenArray[i][j].PositionX + 2 + (ItemSizeX*(InvenArray[i][j].ScaleX)),
						InvenArray[i][j].PositionY + ItemSizeY * (InvenArray[i][j].ScaleY));
					//ItemSizeX

					m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
					m_pSprite->SetTransform(&matWorld_InvenItems[matWorld_InvenArray + i + j * 6]);

					m_pSprite->Draw(
						InvenArray[i][j].m_pTex_InvenOver,
						&InvenArray[i][j].isInven_rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						D3DCOLOR_ARGB(200, 255, 255, 255));

				}
			}
		}

		for (int i = 0; i < 6; i++)
		{

			Equip_Name[i]->SetColor(BLACK);
			Equip_Name[i]->SetPosition(&D3DXVECTOR3(Equiped_Item[i].PositionX*2.5f, Equiped_Item[i].PositionY, 0));

			m_pSprite_Equip[i]->SetTransform(&m_matWorld_Euip_Name_text[i]);			
	
			SAFE_RENDER(m_pRootUI_Euip_Text[i]);
		}
	
	
		
	}

	else
	{
		
	}



	for (int i = 5; i >= 0; i--)
	{
		m_pSprite_Equip[i]->End();
	}
	



	m_pSprite->End();

}



void InventoryManager::addIndex(items a)
{

	D3DXMATRIXA16 matR, matT, matWorld;
	D3DXMATRIXA16 matS;
	//static float fAngle = 0.0f;
	for (int j = 0; j < INVENVERTI; j++)
	{
		for (int i = 0; i < INVENCORSS; i++)
		{
			if (InvenArray[i][j].index == 0)
			{
				InvenArray[i][j] = a;
				InvenArray[i][j].PositionX = (INVENITEMSTART_X + ItemSizeX * i)*Adjust_Display_Mode_X;
				InvenArray[i][j].PositionY = (INVENITEMSTART_Y + ItemSizeY * j)*Adjust_Display_Mode_Y;
				InvenArray[i][j].Copy_num += 1;
				InvenArray[i][j].isInvenIn = true;
				return;
			}

			else if (i == INVENCORSS && j == INVENVERTI)
			{
				std::printf("�κ��丮�� ���� á���ϴ�.");
			}
		}
	}
}


void InventoryManager::MovingItem(items *a, items* b)
{
	swap(a, b);
}



void InventoryManager::Weapon_Equip_Text()
{

	{

		for (int i = 0; i < 6; i++)
		{
			UIImage * pImage = new UIImage(m_pSprite_Equip[i]);
			m_pRootUI_Euip_Text[i] = pImage;
		}

	}

	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.f, 1.f, 1);
	D3DXMATRIXA16 matT;
	//D3DXMatrixTranslation(&matT, Equiped_Item_BlackBack[i].PositionX, Equiped_Item_BlackBack[i].PositionY, 0);
	D3DXMatrixTranslation(&matT, 0, 0, 0);


	Equip_Name_Text[0] = "MainWeapon";
	Equip_Name_Text[1] = "Armor";
	Equip_Name_Text[2] = "Gloves";
	Equip_Name_Text[3] = "Artifact";
	Equip_Name_Text[4] = "Belt";
	Equip_Name_Text[5] = "Boots";

	////�ؽ�Ʈ�� �������
	for (int i = 0; i < 6; i++)
	{
		m_matWorld_Euip_Name_text[i] = matS * matT;
		float Equip_NameRect_StartX = Equiped_Item[i].PositionX + (Equiped_Item[i].m_image.Width*0.3*Adjust_Display_Mode_X);
		float Equip_NameRect_StartY = Equiped_Item[i].PositionY + (Equiped_Item[i].m_image.Height*0.3*Adjust_Display_Mode_Y);
		SetRect(&Equip_Name_Rect[i], Equip_NameRect_StartX, Equip_NameRect_StartY, Equip_NameRect_StartX+ 200, Equip_NameRect_StartY+200);

		Equip_Name[i] = new UIText(g_pFontMgr->GetFont(FONT::Equiped), m_pSprite_Equip[i], 1);
		
			Equip_Name[i]->m_text = Equip_Name_Text[i];
		Equip_Name[i]->m_size = D3DXVECTOR2(200, 100);
		//Equip_Name[i]->Render();
		Equip_Name[i]->RenderingOn = false;
	//SetRect(&Equip_Name[i]->m_pRect, Equiped_Item[i].PositionX + (Equiped_Item[i].m_image.Width*0.3*Adjust_Display_Mode_X),
	//	Equiped_Item[i].PositionY + (Equiped_Item[i].m_image.Height*0.3*Adjust_Display_Mode_Y), Equip_Name[i]->m_size.x, Equip_Name[i]->m_size.y);

		Equip_Name[i]->SetPosition(&D3DXVECTOR3(0,0,0));
		
			
		
		//Equip_Name[i]  g_pFontMgr->GetFont(FONT::Equiped, i), m_pSprite_Equip, 1;
		
		m_pRootUI_Euip_Text[i]->AddChild(Equip_Name[i]);
	
	}
}

//void InventoryManager::Item_Info_Text()
//{
//	for (int i = 0; i < 4; i++)
//	{
//		UIImage * pImage = new UIImage(m_pSprite_Equip[i]);
//		m_pRootUI_Item_Info[i] = pImage;
//	}
//
//	D3DXMATRIXA16 matS;
//	D3DXMatrixScaling(&matS, 1.f, 1.f, 1);
//	D3DXMATRIXA16 matT;
//	//D3DXMatrixTranslation(&matT, Equiped_Item_BlackBack[i].PositionX, Equiped_Item_BlackBack[i].PositionY, 0);
//	D3DXMatrixTranslation(&matT, 0, 0, 0);
//	m_matWorld_Item_Info[ItemName] = matS * matT;
//
//	Item_Info[ItemName] = new UIText(g_pFontMgr->GetFont(FONT::Equiped), m_pSprite_Item_Info[ItemName], 1);
//	
//}



void InventoryManager::Item_Info_Description(items item)
{




}
