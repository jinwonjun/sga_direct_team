#include "stdafx.h"
#include "Inventory.h"
#include "UIImage.h"
#include "ItemImage.h"


Inventory::Inventory()
{
	m_pSprite = NULL;
	m_pRootUI = NULL;
}


Inventory::~Inventory()
{
	SAFE_RELEASE(m_pSprite);

	//m_pRootUI->ReleaseAll();

	SAFE_RELEASE(m_pRootUI);
}

void Inventory::Init()
{
	//불값은 다 false로 초기화 시키고, m_pSprite 저장소 열고
	D3DXCreateSprite(g_pDevice, &m_pSprite);
	openInven = false;
	SwapDoor = false;
	EscapeFor = false;
	pressOn = false;
	alreadyWorkedRbutton = false;
	ItemSizeX = 80;
	ItemSizeY = 80;
	EmptyRcX = ItemSizeX - 5;
	EmptyRcY = ItemSizeY - 5;
	//UIImage 를 담는것.
	{UIImage * pImage = new UIImage(m_pSprite);
	m_pRootUI = pImage;
	}
	GetClientRect(g_hWnd, &clientRect);

	//해상도 변환에 따른 비율을 만든다. 
	Adjust_Display_Mode_X = ((float)clientRect.right - (float)clientRect.left) / (float)OriginX;
	Adjust_Display_Mode_Y = ((float)clientRect.bottom - (float)clientRect.top) / (float)OriginY;

	//인벤토리 초기화 공식
	//보이드도 똑같이 하나 만들어둔다.
	Basic_ScaleX = 0.3f;
	Basic_ScaleY = 0.3f;




	// 1번 아이템 초기화
	Weapons[0].index = 1;
	Weapons[0].name = "Wood";
	Weapons[0].Atk = 10;
	Weapons[0].MaxHp = 0;
	Weapons[0].Hp = 0;
	Weapons[0].Def = 0;

	Weapons[0].ScaleX = 0.3f;
	Weapons[0].ScaleY = 0.3f;
	Weapons[0].PositionX = (OriginX / 3) *Adjust_Display_Mode_X;
	Weapons[0].PositionY = (OriginY / 2) * Adjust_Display_Mode_Y;
	Weapons[0].isClicked = false;
	Weapons[0].isInvenIn = false;
	Weapons[0].Copy_num = 0;
	Weapons[0].Equip_Type = Weapon_Type_LeftHand;


	// 2번아이템 초기화
	Weapons[1] = { 2, "Gun", 15, 20 , 0,0 ,
		((OriginX / 3) + ItemSizeX) * Adjust_Display_Mode_X,
		(OriginY / 2) * Adjust_Display_Mode_Y,
		0.3f,0.3f,false, false ,
		0, Weapon_Type_LeftHand };




	//inventory.push_back(Weapons[0]);

	// 아이템 샵에 2개만 일단 푸시백 콕
	Shop_Item.push_back(Weapons[0]);
	Shop_Item.push_back(Weapons[1]);
	//Weapons[1] = { Weapons[1].Item_rc,"Stick",3,20,0 };
	//Weapons[2] = { Weapons[2].Item_rc,"Chap",5,25,0 };
	//Weapons[3] = { Weapons[3].Item_rc,"Knife",7,30,0 };
	//Weapons[4] = { Weapons[4].Item_rc,"Spoon",9,35,0 };
	//Weapons[5] = { Weapons[5].Item_rc,"DongHee",11,40,0 };
	//Weapons[6] = { Weapons[6].Item_rc,"WonJun",13,45,0 };



	//클라이언트 렉트를 저장한다.
	//나중에 클라리언트 렉트의 비율 기준으로 아이콘이나 그런것들 위치 조율
	// 기준이 되는 클라이언트를 설정하고 
	//이미지의 스케일도 그에 맞춰서 변경 예정
	//ex) 1080 * 600 인데, 우리가 540 * 300 을 사용하게 되면
	// 이미지 스캐일을 X =  0.5 , Y = 0.5 로 설정
	// 단 예외처리는 필요할듯





	CString  Filename = "resources/images/ham1.png";

	//이 친구가 텍스쳐를 파일로부터 읽어오는데...
	//사실 검색해봐도 잘 모르겠음...
	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		Filename,   //LPCTSTR pSrcFile,  파일명을 가져옴
					//이거 CString으로 선언한 변수에다 집어넣고
					// LPCTSTR로 받아서 쓰면
					// 변수로 집어넣어도 작동 됨

		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Shop_Item[0].m_image_Item_Info,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Shop_Item[0].m_pTex_Item);   //LPDIRECT3DTEXTURE9 *ppTexture
									  // 위에서 말한 경로에서 정보를 가져와서 m_image_info에 넣고
									  // 텍스쳐도 m_pTex에 저장




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
		&Shop_Item[1].m_image_Item_Info,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Shop_Item[1].m_pTex_Item);   //LPDIRECT3DTEXTURE9 *ppTexture


	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/inventory/Inven_temp.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&m_image_Inventory_info,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&m_pTex_Inventory);   //LPDIRECT3DTEXTURE9 *ppTexture

	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/inventory/Inven_temp_.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&m_image_Inventory_Chara_info,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&m_pTex_Inventory_Chara);   //LPDIRECT3DTEXTURE9 *ppTexture


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
		&m_image_MouseCursor_Normal_info,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&m_pTex_MouseCursor_Normal);   //LPDIRECT3DTEXTURE9 *ppTexture

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
		&m_image_MouseCursor_ClickedOn_info,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&m_pTex_MouseCursor_ClickedOn);   //LPDIRECT3DTEXTURE9 *ppTexture

										  // 렌더에서 가져 온 것들  // 이미지 정보를 바로 위에 있는 친구들한테
										  //받기 때문에 D3DXCreateTextureFromFileEx 보다 아래에 있어야 한다.

	static float fAngle = 0.0f;



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

			InvenArray[i][j].isInvenOn = false;

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

			Void_Item[i][j].isInvenOn = false;

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
				&InvenArray[i][j].m_image_InvenOn_Info,   //D3DXIMAGE_INFO *pSrcInfo
				NULL,         //PALETTEENTRY *pPalette
				&InvenArray[i][j].m_pTex_InvenOn);   //LPDIRECT3DTEXTURE9 *ppTexture

													 //D3DXCreateTextureFromFileEx(
													 //	g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
													 //	_T("resources/images/InvenLight.png"),   //LPCTSTR pSrcFile,
													 //	D3DX_DEFAULT_NONPOW2,   //UINT Width,
													 //	D3DX_DEFAULT_NONPOW2,   //UINT Height,
													 //	D3DX_DEFAULT,      //UINT MipLevels,
													 //	0,               //DWORD Usage,
													 //	D3DFMT_UNKNOWN,      //D3DFORMAT Format,
													 //	D3DPOOL_MANAGED,   //D3DPOOL Pool
													 //	D3DX_FILTER_NONE,   //DWORD Filter
													 //	D3DX_DEFAULT,      //DWORD MipFilter
													 //	D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
													 //	&Void_Item[i][j].m_image_InvenOn_Info,   //D3DXIMAGE_INFO *pSrcInfo
													 //	NULL,         //PALETTEENTRY *pPalette
													 //	&Void_Item[i][j].m_pTex_InvenOn);   //LPDIRECT3DTEXTURE9 *ppTexture
													 //										// 이거 만들때 얘 스케일은??
													 //	SetRect(&InvenArray[i][j].Item_rc,1000+80*i, 420 + 100 * j, 1080 + 80 * i, 520 + 100 * j);
		}
	}

	//인벤토리 Mat world 계산
	float inven_ScaleX, inven_ScaleY;
	inven_ScaleX = 2.279f *Adjust_Display_Mode_X;
	inven_ScaleY = 2.3f *Adjust_Display_Mode_Y;

	float PositionX_Inven, PositionY_Inven;
	PositionX_Inven = ((clientRect.right *0.738) - (m_image_Inventory_info.Width)*Adjust_Display_Mode_X);
	PositionY_Inven = ((clientRect.bottom *0.055));


	float inven_Chara_ScaleX, inven_Chara_ScaleY;
	inven_Chara_ScaleX = 2.279f *Adjust_Display_Mode_X;
	inven_Chara_ScaleY = 2.3f *Adjust_Display_Mode_Y;

	float PositionX_Inven_Chara, PositionY_Inven_Chara;
	PositionX_Inven_Chara = PositionX_Inven ;
	PositionY_Inven_Chara = PositionY_Inven;


	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, PositionX_Inven_Chara, PositionY_Inven_Chara, 0);
	D3DXMatrixScaling(&matS, inven_Chara_ScaleX, inven_Chara_ScaleY, 1);
	matWorld[matWorld_Inven_Chara] = matS * matR * matT;

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, PositionX_Inven, PositionY_Inven, 0);
	D3DXMatrixScaling(&matS, inven_ScaleX, inven_ScaleY, 1);
	matWorld[matWorld_Inven] = matS * matR * matT;




	Shop_Item[0].Item_rc = RectMake(0, 0, Shop_Item[0].m_image_Item_Info.Width, Shop_Item[0].m_image_Item_Info.Height);
	Shop_Item[1].Item_rc = RectMake(0, 0, Shop_Item[1].m_image_Item_Info.Width, Shop_Item[1].m_image_Item_Info.Height);


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

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT,
		Shop_Item[1].PositionX,
		Shop_Item[1].PositionY,
		0);


	D3DXMatrixScaling(&matS, ShopItem_Display_Mode_X, ShopItem_Display_Mode_Y, 1);

	matWorld[matWorld_ShopItem_2] = matS * matR * matT;


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
			matWorld_InvenItems[i + j * 6] = matS * matR * matT;

		}
	}

	D3DXMatrixRotationZ(&matR, fAngle);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 200, 200, 0);
	D3DXMatrixScaling(&matS, Adjust_Display_Mode_X, Adjust_Display_Mode_Y, 1);
	matWorld[matWorld_Equip_LeftHand] = matS * matR * matT;





}

void Inventory::Update()
{
	SAFE_UPDATE(m_pRootUI);


	if (g_pKeyboard->KeyDown('I'))
	{
		openInven = !openInven;
		// I를 누르면 인벤토리가 열렸다 꺼졌다 그래요
	}


	if (openInven)
	{


		Debug->AddText(pressOn);
		Debug->EndLine();

		GetCursorPos(&mousePoint);
		//마우스 커서 받고
		ScreenToClient(g_hWnd, &mousePoint);
		//스크린에 클ㄹ라이언트... 마우스 커서 쓰려면 필여ㅛ해요 ..
		for (int j = 0; j < INVENVERTI; j++)
		{
			for (int i = 0; i < INVENCORSS; i++)
			{
				if (PtInRect(&Void_Item[i][j].Click_rc, mousePoint))
				{
					Void_Item[i][j].isInvenOn = true;

				}
				else
				{
					Void_Item[i][j].isInvenOn = false;
				}
			}
		}

		//아이템 착용
		if (g_pMouse->ButtonDown(Mouse::RBUTTON))
		{
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
						case Weapon_Type_LeftHand:
							if (Equip_LeftHand.empty())
							{
								Equip_LeftHand.push_back(InvenArray[i][j]);
								Equip_LeftHand[0].ScaleX = 1.0f;
								Equip_LeftHand[0].ScaleY = 1.0f;

								InvenArray[i][j] = Void_Item[i][j];

							}
							else
							{
								swap(Equip_LeftHand[0], InvenArray[i][j]);

								InvenArray[i][j].PositionX = Void_Item[i][j].PositionX;
								InvenArray[i][j].PositionY = Void_Item[i][j].PositionY;
								InvenArray[i][j].ScaleX = Basic_ScaleX* Adjust_Display_Mode_X;
								InvenArray[i][j].ScaleY = Basic_ScaleY* Adjust_Display_Mode_Y;
								Equip_LeftHand[0].ScaleX = 1.0f;
								Equip_LeftHand[0].ScaleY = 1.0f;
							}

							break;
						case Weapon_Type_RightHand:
							Equip_RightHand.push_back(InvenArray[i][j]);

							break;
						case Weapon_Type_Amor:
							Equip_RightHand.push_back(InvenArray[i][j]);

							break;

						default:

							break;

						}
					} // 인벤토리에 있는 아이템 클릭시

					else
					{

					}
				}


			} // for 마지막

			alreadyWorkedRbutton = false; // 오른쪽 버튼이 한번만 사용되게 하기 위해서 사용
		}

		//불로 어떻게 하면 될꺼 같은데 2
		else if (g_pMouse->ButtonDown(Mouse::LBUTTON))
		{
			if (PtInRect(&Shop_Item[0].Click_rc, mousePoint))
			{
				addIndex(Shop_Item[0]);
			}

			else if (PtInRect(&Shop_Item[1].Click_rc, mousePoint))
			{
				addIndex(Shop_Item[1]);
			}
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

							InvenArray[i][j].isInvenOn = false;
							InvenArray[CrossX][VertiY].isInvenOn = true;
						}
					}
				}
				else
				{
					for (int j = 0; j < INVENVERTI; j++)
					{
						for (int i = 0; i < INVENCORSS; i++)
						{

							InvenArray[i][j].isInvenOn = false;
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
				InvenArray[preChosenX][preChosenY].isInvenOn = false;
				InvenArray[CrossX][VertiY].isInvenOn = false;

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

					InvenArray[i][j].isInvenOn = false;
				}
			}
		}




	} // OpenInve 끝
	Debug->AddText(mousePoint.x);
	Debug->EndLine();
	Debug->AddText(mousePoint.y);
	Debug->EndLine();

}

void Inventory::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (openInven)
	{
		
		//===========================

	

		SetRect(&m_rc_Inventory, 0, 0, m_image_Inventory_info.Width, m_image_Inventory_info.Height);


		//m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld[matWorld_Inven]);
		m_pSprite->Draw(
			m_pTex_Inventory,
			&m_rc_Inventory,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255));

		//=======================================

		//g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);


		SetRect(&m_rc_Inventory_Chara, 0, 0, m_image_Inventory_Chara_info.Width, m_image_Inventory_Chara_info.Height);


		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld[matWorld_Inven_Chara]);
		m_pSprite->Draw(
			m_pTex_Inventory_Chara,
			&m_rc_Inventory_Chara,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_ARGB(50, 255, 255, 255));


		g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false); // 라이트를 키면 껌해진다 ...

		m_pSprite->End();
	//	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		//
		//===========================
		//Item
		//g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

		SetRect(&Shop_Item[0].Item_rc, 0, 0, 0 + (Shop_Item[0].m_image_Item_Info.Width), 0 + (Shop_Item[0].m_image_Item_Info.Height /**temp*/));

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld[matWorld_ShopItem_1]);
		m_pSprite->Draw(
			Shop_Item[0].m_pTex_Item,
			&Shop_Item[0].Item_rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			WHITE);
		// 이 부분에 대해 물어보기

		// 샵아이텝 1번
		//D3DXMatrixRotationZ(&matR, fAngle);
		//D3DXMatrixIdentity(&matT);
		//D3DXMatrixTranslation(&matT,
		//	Shop_Item[1].PositionX,
		//	Shop_Item[1].PositionY,
		//	0);


		//D3DXMatrixScaling(&matS, temp, temp, 1);

		//matWorld = matS * matR * matT;

		//m_pSprite->SetTransform(&m_matWorld);

		/*	for (int i = 0; i < inventory.size(); i++)
		{
		SetRect(&inventory[i].Item_rc, m_rc_ItemSet.left + (100 * i), m_rc_ItemSet.top - (100 * i), m_rc_ItemSet.left + (100 * i) + 80, m_rc_ItemSet.top + (100 * i) + 90);
		}*/







		SetRect(&Shop_Item[1].Item_rc, 0, 0, 0 + (Shop_Item[1].m_image_Item_Info.Width), 0 + (Shop_Item[1].m_image_Item_Info.Height /**temp*/));



		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld[matWorld_ShopItem_2]);
		m_pSprite->Draw(
			Shop_Item[1].m_pTex_Item,
			&Shop_Item[1].Item_rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			WHITE);




		//SetRect(&inventory[0].Click_rc, positionX - ((inventory[0].m_image_Item_Info.Width / 2))
		//	, positionY - ((inventory[0].m_image_Item_Info.Height / 2))
		//	, positionX + ((inventory[0].m_image_Item_Info.Width / 2))
		//	, positionY + ((inventory[0].m_image_Item_Info.Height / 2)));


		//윈도우 기준이 아닌, 스크린기준으로 되어있엉
		static float fAngle = 0.0f;

		for (int j = 0; j < INVENVERTI; j++)
		{

			for (int i = 0; i < INVENCORSS; i++)
			{
				if (InvenArray[i][j].isInvenOn || Void_Item[i][j].isInvenOn)
				{


					SetRect(&InvenArray[i][j].isInven_rc, 0, 0, InvenArray[i][j].m_image_InvenOn_Info.Width, InvenArray[i][j].m_image_InvenOn_Info.Height);
					SetRect(&InvenArray[i][j].isInven_show_rc,
						InvenArray[i][j].PositionX + 2,
						InvenArray[i][j].PositionY,
						InvenArray[i][j].PositionX + 2 + (ItemSizeX*(InvenArray[i][j].ScaleX)),
						InvenArray[i][j].PositionY + ItemSizeY*(InvenArray[i][j].ScaleY));
					//ItemSizeX

					m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
					m_pSprite->SetTransform(&matWorld_InvenItems[i + j * 6]);

					m_pSprite->Draw(
						InvenArray[i][j].m_pTex_InvenOn,
						&InvenArray[i][j].isInven_rc,
						&D3DXVECTOR3(0, 0, 0),
						&D3DXVECTOR3(0, 0, 0),
						WHITE);


				}
			}
		}

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
				matWorld_InvenItems[i + j * 6] = matS * matR * matT;


				//Inventory
				SetRect(&InvenArray[i][j].Item_rc, 0, 0, InvenArray[i][j].m_image_Item_Info.Width, InvenArray[i][j].m_image_Item_Info.Height);
				SetRect(&InvenArray[i][j].Click_rc,
					InvenArray[i][j].PositionX + 2,
					InvenArray[i][j].PositionY,
					InvenArray[i][j].PositionX + 2 + ((InvenArray[i][j].m_image_Item_Info.Width)*(InvenArray[i][j].ScaleX)),
					InvenArray[i][j].PositionY + ((InvenArray[i][j].m_image_Item_Info.Height)*(InvenArray[i][j].ScaleY)));

				m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
				m_pSprite->SetTransform(&matWorld_InvenItems[i + j * 6]);

				m_pSprite->Draw(
					InvenArray[i][j].m_pTex_Item,
					&InvenArray[i][j].Item_rc,
					&D3DXVECTOR3(0, 0, 0),
					&D3DXVECTOR3(0, 0, 0),
					WHITE);
			}
		}



		SetRect(&Shop_Item[0].Click_rc, Shop_Item[0].PositionX
			, Shop_Item[0].PositionY
			, Shop_Item[0].PositionX + ((Shop_Item[0].m_image_Item_Info.Width)*ShopItem_Display_Mode_X)
			, Shop_Item[0].PositionY + ((Shop_Item[0].m_image_Item_Info.Height)*ShopItem_Display_Mode_Y));

		SetRect(&Shop_Item[1].Click_rc, Shop_Item[1].PositionX
			, Shop_Item[1].PositionY
			, Shop_Item[1].PositionX + ((Shop_Item[1].m_image_Item_Info.Width)*ShopItem_Display_Mode_X)
			, Shop_Item[1].PositionY + ((Shop_Item[1].m_image_Item_Info.Height)*ShopItem_Display_Mode_Y));

		//============================================

		//	float PositionX_Inven, PositionY_Inven;
		// Equip 한번 가보자으아아아아 


		// EQUIP 왼손에 착용 하기 위한 것을 그려준다 
		if (Equip_LeftHand.empty() == false)
		{


			m_pSprite->SetTransform(&m_matWorld);

			Equip_LeftHand[0].PositionX = 200 / OriginX;
			Equip_LeftHand[0].PositionY = 200 / OriginY;


			//ItemSet
			SetRect(&m_rc_ItemSet, 0, 0, Equip_LeftHand[0].m_image_Item_Info.Width, Equip_LeftHand[0].m_image_Item_Info.Height);
			SetRect(&Equip_LeftHand[0].Click_rc,
				Equip_LeftHand[0].PositionX,
				Equip_LeftHand[0].PositionY,
				Equip_LeftHand[0].PositionX + ((Equip_LeftHand[0].m_image_Item_Info.Width)*(Equip_LeftHand[0].ScaleX)),
				Equip_LeftHand[0].PositionY + ((Equip_LeftHand[0].m_image_Item_Info.Height)*(Equip_LeftHand[0].ScaleY)));

			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			m_pSprite->SetTransform(&matWorld[matWorld_Equip_LeftHand]);

			m_pSprite->Draw(
				Equip_LeftHand[0].m_pTex_Item,
				&Equip_LeftHand[0].Item_rc,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				WHITE);

		}



		if (g_pMouse->ButtonPress(Mouse::LBUTTON))
		{
			D3DXMatrixRotationZ(&matR, fAngle);
			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, mousePoint.x, mousePoint.y, 0);
			D3DXMatrixScaling(&matS, 1.f, 1.f, 1);
			matWorld[matWorld_MouseCursor] = matS * matR * matT;

			//m_pSprite->SetTransform(&matWorld[matWorld_MouseCursor]);

			SetRect(&m_rc_MouseCursor_ClickedOn, 0, 0, m_image_MouseCursor_ClickedOn_info.Width, m_image_MouseCursor_ClickedOn_info.Height);


			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			m_pSprite->SetTransform(&matWorld[matWorld_MouseCursor]);
			m_pSprite->Draw(
				m_pTex_MouseCursor_ClickedOn,
				&m_rc_MouseCursor_ClickedOn,
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

			SetRect(&m_rc_MouseCursor_Normal, 0, 0, m_image_MouseCursor_Normal_info.Width, m_image_MouseCursor_Normal_info.Height);


			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			m_pSprite->SetTransform(&matWorld[matWorld_MouseCursor]);
			m_pSprite->Draw(
				m_pTex_MouseCursor_Normal,
				&m_rc_MouseCursor_Normal,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				WHITE);
		}

	}

	else
	{

	}




	m_pSprite->End();

}

void Inventory::OnClick(UIButton * pSender)
{
}

void Inventory::addIndex(items a)
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

void Inventory::MovingItem(items *a, items* b)
{
	swap(a, b);
}
