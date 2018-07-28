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
	//불값은 다 false로 초기화 시키고, m_pSprite 저장소 열고
	D3DXCreateSprite(g_pDevice, &m_pSprite);

	//for (int i = 0; i < 6; i++)
	//{
	//	D3DXCreateSprite(g_pDevice, &m_pSprite_Equip[i]);
	//}

	for (int i = 0; i < NumOfItemTextKind; i++)
	{
		D3DXCreateSprite(g_pDevice, &m_pSprite_Item_Info[i]);
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
	isEquipItemChanged = true;
	GetClientRect(g_hWnd, &clientRect);

	//해상도 변환에 따른 비율을 만든다. 
	Adjust_Display_Mode_X = ((float)clientRect.right - (float)clientRect.left) / (float)OriginX;
	Adjust_Display_Mode_Y = ((float)clientRect.bottom - (float)clientRect.top) / (float)OriginY;

	//인벤토리 초기화 공식
	//보이드도 똑같이 하나 만들어둔다.
	Basic_ScaleX = 0.3f;
	Basic_ScaleY = 0.3f;

	g_pItem->ItemTable();

	

	//클라이언트 렉트를 저장한다.
	//나중에 클라리언트 렉트의 비율 기준으로 아이콘이나 그런것들 위치 조율
	// 기준이 되는 클라이언트를 설정하고 
	//이미지의 스케일도 그에 맞춰서 변경 예정
	//ex) 1080 * 600 인데, 우리가 540 * 300 을 사용하게 되면
	// 이미지 스캐일을 X =  0.5 , Y = 0.5 로 설정
	// 단 예외처리는 필요할듯



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
		_T("resources/images/inventory/Inven_temp_4.png"),   //LPCTSTR pSrcFile,
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
			// 그곳엔 공허뿐이었어 ..........................
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

	//인벤토리 Mat world 계산
	
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


	//Equiped_Side.ScaleX = 1.f;
	//Equiped_Side.ScaleY = 1.f;
	//Equiped_Side.PositionX = clientRect.right * 0.02;
	//Equiped_Side.PositionY = clientRect.bottom * 0.01;
	//D3DXMatrixRotationZ(&matR, fAngle);
	//D3DXMatrixIdentity(&matT);
	//D3DXMatrixTranslation(&matT, Equiped_Side.PositionX, Equiped_Side.PositionY, 0);
	//D3DXMatrixScaling(&matS, Equiped_Side.ScaleX, Equiped_Side.ScaleY, 1);
	//matWorld[matWorld_Equiped_Side] = matS * matR * matT;


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






	float temp1 = .3f;

	ShopItem_Display_Mode_X = temp1 *Adjust_Display_Mode_X;
	ShopItem_Display_Mode_Y = temp1 *Adjust_Display_Mode_Y;


	D3DXMatrixScaling(&matS, ShopItem_Display_Mode_X, ShopItem_Display_Mode_Y, 1);

	matWorld[matWorld_ShopItem_1] = matS * matR * matT;



	for (int j = 0; j < INVENVERTI; j++)
	{
		//Debug->EndLine();
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
	ItemInfoBack_PositionX = Item_Info_Back.PositionX + Item_Info_Back.m_image.Width *0.1;
	ItemInfoBack_PositionY = Item_Info_Back.PositionY + Item_Info_Back.m_image.Height *0.1;
	ItemInfoBack_ScaleX = 0.6f;
	ItemInfoBack_ScaleY = 0.6f;




	// 아이템의 이름과 능력치, 설명을 담기 위해 시작하는 이닛 부분
	Item_Info_Text();


	// 마우스 오버 월드 메트릭스
	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, ItemInfoBack_PositionX, ItemInfoBack_PositionY, 0);
	D3DXMatrixScaling(&matS, ItemInfoBack_ScaleX, ItemInfoBack_ScaleY, 1);
	matWorld[matWorld_MouseOver] = matS * matR * matT;



	//Weapon_Equip_Text();

	


	


	for (int i = 0; i < 7; i++)
	{
		Equip.push_back(Void_Item[0][0]);
	}

}

void InventoryManager::Update()
{
	//SAFE_UPDATE(m_pRootUI);
	//Debug->EndLine();
	//Debug->EndLine();
	//Debug->AddText(Equip[Weapon_Type_MainWeapons].PositionX);
	//Debug->EndLine();
	//Debug->AddText(Equip[Weapon_Type_MainWeapons].PositionY);
	//Debug->EndLine();

	if (g_pKeyboard->KeyDown('I'))
	{
		openInven = !openInven;
		// I를 누르면 인벤토리가 열렸다 꺼졌다 그래요
	}
	


	if (openInven)
	{
		//ESC누르면 꺼짐
		if (g_pKeyboard->KeyDown(VK_ESCAPE))
		{
			openInven = !openInven;
		}
		//Debug->AddText(pressOn);
		//Debug->EndLine();

		GetCursorPos(&mousePoint);
		//마우스 커서 받고
		ScreenToClient(g_hWnd, &mousePoint);
		//스크린에 클ㄹ라이언트... 마우스 커서 쓰려면 필여ㅛ해요 ..

	/*	for (int i = 0; i < Equip.size(); i++)
		{
			if (PtInRect(&Equip[i].Click_rc, mousePoint))
			{
				int kd = 0;
			}

		}
*/
		//아이템 착용
		if (g_pMouse->ButtonDown(Mouse::RBUTTON) && g_pShop->buyItems == false)
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
					static_cast<Gun*>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GunEqiupSet(0);


					isEquipItemChanged = true;
					//g_pStatus->isChangeEquip = true;
				}
			}

			for (int j = 0; j < INVENVERTI; j++)
			{
			
				for (int i = 0; i < INVENCORSS; i++)
				{
					
					// 
					if (PtInRect(&InvenArray[i][j].Click_rc, mousePoint) && alreadyWorkedRbutton == false)
					{
						g_pSoundManager->Play("clothEquip_inventory", 1.0f);

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
								//g_pStatus->isChangeEquip = true;
								static_cast<Gun*>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GunEqiupSet(Equip[Weapon_Type_MainWeapons].index);
								isEquipItemChanged = true;
							}
							else
							{
								swap(Equip[Equip_Main_Weapon_1], InvenArray[i][j]);
								Equip[Weapon_Type_MainWeapons].isEquiped = true;

								InvenArray[i][j].isEquiped = false;
								//g_pStatus->isChangeEquip = true;
								static_cast<Gun*>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GunEqiupSet(Equip[Weapon_Type_MainWeapons].index);
								isEquipItemChanged = true;
							}
						

							break;

						case Weapon_Type_Armor:
							Equip.push_back(InvenArray[i][j]);

							if (Equip[Equip_Armor].index == 0)
							{
								swap(Equip[Equip_Armor], InvenArray[i][j]);

								Equip[Equip_Armor].isEquiped = true;
								InvenArray[i][j] = Void_Item[i][j];
								//g_pStatus->isChangeEquip = true;
								isEquipItemChanged = true;
							}
							else
							{
								swap(Equip[Equip_Armor], InvenArray[i][j]);
								Equip[Equip_Armor].isEquiped = true;
								InvenArray[i][j].isEquiped = false;
								//g_pStatus->isChangeEquip = true;
								isEquipItemChanged = true;
							}
							break;

						case Equip_Glove:
							Equip.push_back(InvenArray[i][j]);
							if (Equip[Equip_Glove].index == 0)
							{
								swap(Equip[Equip_Glove], InvenArray[i][j]);

								Equip[Equip_Glove].isEquiped = true;
								InvenArray[i][j] = Void_Item[i][j];
							//	g_pStatus->isChangeEquip = true;
								isEquipItemChanged = true;
							}
							else
							{
								swap(Equip[Equip_Glove], InvenArray[i][j]);
								Equip[Equip_Glove].isEquiped = true;
								InvenArray[i][j].isEquiped = false;
								//g_pStatus->isChangeEquip = true;
								isEquipItemChanged = true;
							}
							break;

						case Equip_Belt:
							Equip.push_back(InvenArray[i][j]);
							if (Equip[Equip_Belt].index == 0)
							{
								swap(Equip[Equip_Belt], InvenArray[i][j]);

								Equip[Equip_Belt].isEquiped = true;
								InvenArray[i][j] = Void_Item[i][j];
							//	g_pStatus->isChangeEquip = true;
								isEquipItemChanged = true;
							}
							else
							{
								swap(Equip[Equip_Belt], InvenArray[i][j]);
								Equip[Equip_Belt].isEquiped = true;
								InvenArray[i][j].isEquiped = false;
							//	g_pStatus->isChangeEquip = true;
								isEquipItemChanged = true;
							}
							break;

						case Equip_Boots:
							Equip.push_back(InvenArray[i][j]);
							if (Equip[Equip_Boots].index == 0)
							{
								swap(Equip[Equip_Boots], InvenArray[i][j]);

								Equip[Equip_Boots].isEquiped = true;
								InvenArray[i][j] = Void_Item[i][j];
							//	g_pStatus->isChangeEquip = true;
								isEquipItemChanged = true;
							}
							else
							{
								swap(Equip[Equip_Boots], InvenArray[i][j]);
								Equip[Equip_Boots].isEquiped = true;
								InvenArray[i][j].isEquiped = false;
							//	g_pStatus->isChangeEquip = true;
								isEquipItemChanged = true;
							}
							break;
						default:

							break;

						}



					} // 인벤토리에 있는 아이템 클릭시



					else
					{
						int asdb = 0;
					}
				}


			} // for 마지막

			
			alreadyWorkedRbutton = false; // 오른쪽 버튼이 한번만 사용되게 하기 위해서 사용
			g_pShop->buyItems = false;

			}

		//불로 어떻게 하면 될꺼 같은데 2
		else if (g_pMouse->ButtonDown(Mouse::LBUTTON))
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
							// Press가 조작 되게 하기 위해서
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
				} // for문 끝
				Endfor = false;
			

		}

		// 아이템 드래그해서 욺직이게 하는 친구들 //

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

				// 아이템이 인벤 위에 있으면 이거 사용.
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

				//클릭이 온 되면 모두 false로 바로 바꿔준다. 
				//이거 안하면  swap과정에서 isInvenOn = true 상태가 생겨남 .
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

					//계산 한번 해주고 정렬시키기.
					for (int j = 0; j < INVENVERTI; j++)
					{
						for (int i = 0; i < INVENCORSS; i++)
						{

							InvenArray[i][j].PositionX = (INVENITEMSTART_X + ItemSizeX * i) * Adjust_Display_Mode_X;
							InvenArray[i][j].PositionY = (INVENITEMSTART_Y + ItemSizeY * j)* Adjust_Display_Mode_X;

						}
					}

				}//(CrossX >= 0 && VertiY >= 0) 끝


				else // 아이템이 인벤토리 영역 밖으로 나갔을때 처리 
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
		else // 내가 모든 동작에서 다른 조건에 부합하지 않으면 작동 안한다 
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

		for (int i = 0; i <NumOfItemTextKind; i++)
		{
			SAFE_UPDATE(m_pRootUI_Item_Info[i]);
		}

	} // OpenInve 끝

	
}

void InventoryManager::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	

		if (openInven)
		{

			//===========================


			SetRect(&Inventory.m_rc, 0, 0, Inventory.m_image.Width, Inventory.m_image.Height);


			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			m_pSprite->SetTransform(&matWorld[matWorld_Inven]);
			m_pSprite->Draw(
				Inventory.m_pTex,
				&Inventory.m_rc,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				D3DCOLOR_ARGB(50, 255, 255, 255));

			m_pSprite->End();


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
				WHITE);
			m_pSprite->End();

			SetRect(&Exit_Button.m_rc, 0, 0, Exit_Button.m_image.Width, Exit_Button.m_image.Height);


			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			m_pSprite->SetTransform(&matWorld[matWorld_Exit_Button]);
			m_pSprite->Draw(
				Exit_Button.m_pTex,
				&Exit_Button.m_rc,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				D3DCOLOR_ARGB(255, 255, 255, 255));
			m_pSprite->End();

			
			//윈도우 기준이 아닌, 스크린기준으로 되어있엉
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
					matWorld_InvenItems[matWorld_InvenArray + i + j * 6] = matS * matR * matT;


					//Inventory
					SetRect(&InvenArray[i][j].Item_rc, 0, 0, InvenArray[i][j].m_image_Item_Info.Width, InvenArray[i][j].m_image_Item_Info.Height);
					SetRect(&InvenArray[i][j].Click_rc,
						InvenArray[i][j].PositionX + 2,
						InvenArray[i][j].PositionY,
						InvenArray[i][j].PositionX + 2 + ((InvenArray[i][j].m_image_Item_Info.Width)*(InvenArray[i][j].ScaleX)),
						InvenArray[i][j].PositionY + ((InvenArray[i][j].m_image_Item_Info.Height)*(InvenArray[i][j].ScaleY)));



					m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
					m_pSprite->SetTransform(&matWorld_InvenItems[matWorld_InvenArray + i + j * 6]);

					m_pSprite->Draw(
						InvenArray[i][j].m_pTex_Item,
						&InvenArray[i][j].Item_rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						WHITE);

					m_pSprite->End();

					if (PtInRect(&InvenArray[i][j].Click_rc, mousePoint) && InvenArray[i][j].index != 0)
					{
						ShowItemInfo(InvenArray[i][j]);
					}
				}
			}


			// Equip 한번 가보자으아아아아 
			for (int i = 0; i < 6; i++)
			{
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
					m_pSprite->End();
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
					m_pSprite->End();
				}
				for (int j = 0; j < INVENVERTI; j++)
				{

					for (int i = 0; i < INVENCORSS; i++)
					{
						if (InvenArray[i][j].index == 0 && PtInRect(&Void_Item[i][j].Item_rc, mousePoint))
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
							m_pSprite->End();
						}
					}
				}
				m_pSprite->End();
			}
		}
	

		else	
		{
		
		}



	//for (int i = 5; i >= 0; i--)
	//{
	//	m_pSprite_Equip[i]->End();
	//}


	//for (int i = 3; i >= 0; i--)
	//{
	//	m_pSprite_Item_Info[i]->End();
	//}

	m_pSprite->End();


}



void InventoryManager::addIndex(items& a)
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
				std::printf("인벤토리가 가득 찼습니다.");
			}
		}
	}
}


void InventoryManager::MovingItem(items *a, items* b)
{
	swap(a, b);
}

void InventoryManager::ShowItemInfo(items& picked)
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	SetRect(&Item_Info_Back.m_rc, 0, 0, Item_Info_Back.m_image.Width, Item_Info_Back.m_image.Height);


	cstr_Item_Info[ItemName] = picked.name;
	cstr_Item_Info[ATK].Format(_T("ATK:  %d"), picked.Atk);
	cstr_Item_Info[DEF].Format(_T("DEF:  %d"), picked.Def);
	cstr_Item_Info[MHP].Format(_T("MHP:  %d"), picked.MaxHp);
	cstr_Item_Info[Script] = picked.ItemWord;
	
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld[matWorld_Item_Info]);
	m_pSprite->Draw(
		Item_Info_Back.m_pTex,
		&Item_Info_Back.m_rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(100, 255, 255, 255));
	m_pSprite->End();

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&matWorld[matWorld_MouseOver]);
	m_pSprite->Draw(
		picked.m_pTex_Item,
		&picked.Item_rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pSprite->End();


	for (int i = 0; i <NumOfItemTextKind; i++)
	{
		m_pSprite_Item_Info[i]->Begin(D3DXSPRITE_ALPHABLEND);
	}

	for (int i = 0; i <NumOfItemTextKind; i++)
	{

		m_pSprite_Item_Info[i]->SetTransform(&m_matWorld_Item_Info[i]);

	}

	for (int i = 0; i < NumOfItemTextKind; i++)
	{

		SAFE_RENDER(m_pRootUI_Item_Info[i]);


	}


	for (int i = NumOfItemTextKind - 1; i >= 0; i--)
	{
		m_pSprite_Item_Info[i]->End();
	}


}


// 아이템의 이름과 능력치, 설명을 담기 위해 시작하는 이닛 부분
void InventoryManager::Item_Info_Text()
{
	for (int i = 0; i < NumOfItemTextKind; i++)
	{
		UIImage * pImage = new UIImage(m_pSprite_Item_Info[i]);
		m_pRootUI_Item_Info[i] = pImage;
	}

	Item_Info_PositionX[ItemName] = Item_Info_Back.PositionX + Item_Info_Back.m_image.Width *0.5;
	Item_Info_PositionY[ItemName] = Item_Info_Back.PositionY + Item_Info_Back.m_image.Height *0.1;
	Item_Info_PositionX[ATK] = Item_Info_Back.PositionX + Item_Info_Back.m_image.Width *0.45;
	Item_Info_PositionY[ATK] = Item_Info_Back.PositionY + Item_Info_Back.m_image.Height *0.25;
	Item_Info_PositionX[DEF] = Item_Info_Back.PositionX + Item_Info_Back.m_image.Width *0.7;
	Item_Info_PositionY[DEF] = Item_Info_Back.PositionY + Item_Info_Back.m_image.Height *0.25;
	Item_Info_PositionX[MHP] = Item_Info_Back.PositionX + Item_Info_Back.m_image.Width *0.45;
	Item_Info_PositionY[MHP] = Item_Info_Back.PositionY + Item_Info_Back.m_image.Height *0.4;
	Item_Info_PositionX[Script] = Item_Info_Back.PositionX + Item_Info_Back.m_image.Width *0.1;
	Item_Info_PositionY[Script] = Item_Info_Back.PositionY + Item_Info_Back.m_image.Height *0.6;


	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.f, 1.f, 1);
	D3DXMATRIXA16 matT;
	//D3DXMatrixTranslation(&matT, Equiped_Item_BlackBack[i].PositionX, Equiped_Item_BlackBack[i].PositionY, 0);
	for (int i = 0; i < NumOfItemTextKind; i++)
	{
		D3DXMatrixTranslation(&matT, Item_Info_PositionX[i], Item_Info_PositionY[i], 0);
		m_matWorld_Item_Info[i] = matS * matT;
	}

	Item_Info[ItemName] = new UIButton(m_pDelegate_Item_Info[ItemName], m_pSprite_Item_Info[ItemName], 1);
	Item_Info[ATK] = new UIButton(m_pDelegate_Item_Info[ATK], m_pSprite_Item_Info[ATK], 1);
	Item_Info[DEF] = new UIButton(m_pDelegate_Item_Info[DEF], m_pSprite_Item_Info[DEF], 1);
	Item_Info[MHP] = new UIButton(m_pDelegate_Item_Info[MHP], m_pSprite_Item_Info[MHP], 1);
	Item_Info[Script] = new UIButton(m_pDelegate_Item_Info[Script], m_pSprite_Item_Info[Script], g_pFontMgr->GetFont(FONT::DescriptionOfItem), 1);
	//Item_Info[Script] = new UIButton(m_pDelegate_Item_Info[Script], m_pSprite_Item_Info[Script], g_pFontMgr->GetFont(FONT::DescriptionOfItem), 1);

	float R, G, B;
	R = 13.0f / 255.0f;
	G = 136.f / 255.0f;
	B = 185.f / 255.0f;
	
	//Item_Info[ItemName] = new UIText(g_pFontMgr->GetFont(FONT::NameOfItem), m_pSprite_Item_Info[ItemName]);
	cstr_Item_Info[0] = " Initiation 이거슨 초기화 입니다.\n ㄱ 좀 됬으면 좋겠다.";
	cstr_Item_Info[1] = " saasdassss";
	cstr_Item_Info[2] = " sssssssssss";
	cstr_Item_Info[3] = " asasd333333";
	cstr_Item_Info[Script] = "Initiation 이거슨 초기화 입니다.\n ㄱ 좀 됬으면 좋겠다. \n 왜 안초기화됨요?";

	Item_Info[ItemName]->SetTexture("resources/images/inventory/Null_back2.png",
		"resources/images/inventory/Null_back2.png",
		"resources/images/inventory/Null_back2.png");

		Item_Info[ATK]->SetTexture("resources/images/inventory/Null_small_back2.png",
			"resources/images/inventory/Null_small_back2.png",
			"resources/images/inventory/Null_small_back2.png");
	
		Item_Info[DEF]->SetTexture("resources/images/inventory/Null_small_back2.png",
			"resources/images/inventory/Null_small_back2.png",
			"resources/images/inventory/Null_small_back2.png");
		
		Item_Info[MHP]->SetTexture("resources/images/inventory/Null_small_back2.png",
			"resources/images/inventory/Null_small_back2.png",
			"resources/images/inventory/Null_small_back2.png");

		Item_Info[Script]->SetTexture("resources/images/inventory/Null_Description_back2.png",
			"resources/images/inventory/Null_Description_back2.png",
			"resources/images/inventory/Null_Description_back2.png");

	Item_Info[ItemName]->SetText(g_pFontMgr->GetFont(FONT::NameOfItem), cstr_Item_Info[0], WHITE, D3DXVECTOR3(0, 0, 0));

	Item_Info[ATK]->SetText(g_pFontMgr->GetFont(FONT::OptionOfItem), cstr_Item_Info[ATK], WHITE, D3DXVECTOR3(0, 0, 0));
	Item_Info[DEF]->SetText(g_pFontMgr->GetFont(FONT::OptionOfItem), cstr_Item_Info[DEF], WHITE, D3DXVECTOR3(0, 0, 0));
	Item_Info[MHP]->SetText(g_pFontMgr->GetFont(FONT::OptionOfItem), cstr_Item_Info[MHP], WHITE, D3DXVECTOR3(0, 0, 0));
	Item_Info[Script]->SetText(g_pFontMgr->GetFont(FONT::DescriptionOfItem), cstr_Item_Info[Script], WHITE, D3DXVECTOR3(0, 0, 0));


	for (int i = 0; i < NumOfItemTextKind; i++)
	{
		m_pRootUI_Item_Info[i]->AddChild(Item_Info[i]);
	}
}



void InventoryManager::Item_Info_Description(items& item)
{


}
