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
	
	D3DXCreateSprite(g_pDevice, &m_pSprite);
	openInven = false;
	SwapDoor = false;
	EscapeFor = false;
	pressOn = false;
	alreadyWorkedRbutton = false;
	{UIImage * pImage = new UIImage(m_pSprite);
	m_pRootUI = pImage;	
	}

	//ItemImage * p_Item_Img = new ItemImage(m_pSprite);
	//p_Item_Img->SetTexture("resources/ui/panel-info.png.png");
	//m_pRootUI = p_Item_Img;
	/*PositionX_Inven = 1000 + 80 * i;
	PositionY_Inven = 420 + 100 * j;*/

	for (int j = 0; j < INVENVERTI; j++)
	{

		for (int i = 0; i < INVENCORSS; i++)
		{

			InvenArray[i][j].index = 0;
			InvenArray[i][j].name = "no_Name";
			InvenArray[i][j].Atk = 0;
			InvenArray[i][j].MaxHp = 0;

			InvenArray[i][j].PositionX = INVENITEMSTART_X + 80 * i;
			InvenArray[i][j].PositionY = INVENITEMSTART_Y + 80 * j;
			InvenArray[i][j].ScaleY = 0.3f;
			InvenArray[i][j].ScaleX = 0.3f;
			InvenArray[i][j].isClicked = false;

			InvenArray[i][j].isInvenIn = true;
			InvenArray[i][j].Copy_num = 0;
			
			SetRect(&InvenArray[i][j].Click_rc,
				InvenArray[i][j].PositionX,
				InvenArray[i][j].PositionY,
				InvenArray[i][j].PositionX + 80,
				InvenArray[i][j].PositionY + 80);

			SetRect(&InvenArray[i][j].Item_rc,
				InvenArray[i][j].PositionX,
				InvenArray[i][j].PositionY,
				InvenArray[i][j].PositionX + 80,
				InvenArray[i][j].PositionY + 80);


			//============================================== 
			// 그곳엔 공허뿐이었어 ..........................
			//==============================================

			Void_Item[i][j].index = 0;
			Void_Item[i][j].name = "no_Name";
			Void_Item[i][j].Atk = 0;
			Void_Item[i][j].MaxHp = 0;

			Void_Item[i][j].PositionX = INVENITEMSTART_X + 80 * i;
			Void_Item[i][j].PositionY = INVENITEMSTART_Y + 80 * j;
			Void_Item[i][j].ScaleY = 0.3f;
			Void_Item[i][j].ScaleX = 0.3f;
			Void_Item[i][j].isClicked = false;

			Void_Item[i][j].isInvenIn = true;
			Void_Item[i][j].Copy_num = 0;

			SetRect(&Void_Item[i][j].Click_rc,
				Void_Item[i][j].PositionX,
				Void_Item[i][j].PositionY,
				Void_Item[i][j].PositionX + 80,
				Void_Item[i][j].PositionY + 80);

			SetRect(&Void_Item[i][j].Item_rc,
				Void_Item[i][j].PositionX,
				Void_Item[i][j].PositionY,
				Void_Item[i][j].PositionX + 80,
				Void_Item[i][j].PositionY + 80);
		
			// 이거 만들때 얘 스케일은??
			//	SetRect(&InvenArray[i][j].Item_rc,1000+80*i, 420 + 100 * j, 1080 + 80 * i, 520 + 100 * j);
		}
	}
	


	
	Weapons[0].index = 1;
	Weapons[0].name = "Wood";
	Weapons[0].Atk = 10;
	Weapons[0].MaxHp = 0;
	Weapons[0].ScaleX = 0.3f;
	Weapons[0].ScaleY = 0.3f;
	Weapons[0].PositionX = 500;
	Weapons[0].PositionY = 500;
	Weapons[0].isClicked = false;
	Weapons[0].isInvenIn = false;
	Weapons[0].Copy_num = 0;
	Weapons[0].Equip_Type = Weapon_Type_LeftHand;


	
	Weapons[1] = { 2, "Gun", 15, 20 ,600,600,0.3f,0.3f,false, false , 0, Weapon_Type_LeftHand };

	


	//inventory.push_back(Weapons[0]);
	Shop_Item.push_back(Weapons[0]);
	Shop_Item.push_back(Weapons[1]);
	//Weapons[1] = { Weapons[1].Item_rc,"Stick",3,20,0 };
	//Weapons[2] = { Weapons[2].Item_rc,"Chap",5,25,0 };
	//Weapons[3] = { Weapons[3].Item_rc,"Knife",7,30,0 };
	//Weapons[4] = { Weapons[4].Item_rc,"Spoon",9,35,0 };
	//Weapons[5] = { Weapons[5].Item_rc,"DongHee",11,40,0 };
	//Weapons[6] = { Weapons[6].Item_rc,"WonJun",13,45,0 };


	GetClientRect(g_hWnd, &clientRect);


	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/ham1.png"),   //LPCTSTR pSrcFile,
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
		&Shop_Item[1].m_image_Item_Info,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Shop_Item[1].m_pTex_Item);   //LPDIRECT3DTEXTURE9 *ppTexture


	 D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/inventory/Inven_empty_.png"),   //LPCTSTR pSrcFile,
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
		_T("resources/images/inventory/ItemSet.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&m_image_ItemSet_info,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&m_pTex_ItemSet);   //LPDIRECT3DTEXTURE9 *ppTexture



}

void Inventory::Update()
{
	SAFE_UPDATE(m_pRootUI);


	if (g_pKeyboard->KeyDown('I'))
	{
		openInven = !openInven;		
	}


	if (openInven)
	{
		Debug->AddText(pressOn);
		Debug->EndLine();

		GetCursorPos(&mousePoint);
		ScreenToClient(g_hWnd, &mousePoint);

		
			
		if (g_pMouse->ButtonDown(Mouse::RBUTTON))
		{
			for (int j = 0; j < INVENVERTI; j++)
			{				
				for (int i = 0; i < INVENCORSS; i++)
				{
				
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
								InvenArray[i][j].ScaleX = 0.3f;
								InvenArray[i][j].ScaleY = 0.3f;
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

					
					else if (Equip_LeftHand.empty() == false)
					{
						if (PtInRect(&Equip_LeftHand[0].Click_rc, mousePoint)
							&& alreadyWorkedRbutton == false)
						{
							alreadyWorkedRbutton = true;
							for (int tempj = 0; tempj < INVENVERTI; tempj++)
							{
								if (EscapeFor == true)
									break;

								for (int tempi = 0; tempi < INVENCORSS; tempi++)
								{
									if (EscapeFor == true)
										break;

									if (InvenArray[tempi][tempj].index == 0)
									{
										InvenArray[tempi][tempj] = Equip_LeftHand[0];
										InvenArray[tempi][tempj].PositionX = Void_Item[tempi][tempj].PositionX;
										InvenArray[tempi][tempj].PositionY = Void_Item[tempi][tempj].PositionY;
										InvenArray[tempi][tempj].ScaleX = Void_Item[tempi][tempj].ScaleX;
										InvenArray[tempi][tempj].ScaleY = Void_Item[tempi][tempj].ScaleY;
										Equip_LeftHand.clear();
										EscapeFor = true;
									}
								}
							}
							EscapeFor = false;
						}
						EscapeFor = false;
					}
					else
					{

					}
				}


			} // for 마지막

			alreadyWorkedRbutton = false; // 오른쪽 버튼이 한번만 사용되게 하기 위해서 사용
		}

		//불로 어떻게 하면 될꺼 같은데 2
		if (g_pMouse->ButtonDown(Mouse::LBUTTON))
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

		if (g_pMouse->ButtonUp(Mouse::LBUTTON))
		{
			pressOn = false;
			if (InvenArray[preChosenX][preChosenY].isClicked)
			{
				InvenArray[preChosenX][preChosenY].isClicked = false;
				
				 CrossX = (mousePoint.x - 960) / 85;
				 VertiY = (mousePoint.y - 370) / 90;

				if (CrossX >= 0 && VertiY >= 0)
				{
					if (InvenArray[CrossX][VertiY].index != 0 && SwapDoor == false)
					{			
						swap(InvenArray[preChosenX][preChosenY], InvenArray[CrossX][VertiY]);

						InvenArray[preChosenX][preChosenY].PositionX = INVENITEMSTART_X + 80 * preChosenX;
						InvenArray[preChosenX][preChosenY].PositionY = INVENITEMSTART_Y + 80 * preChosenY;
						InvenArray[CrossX][VertiY].PositionX = INVENITEMSTART_X + 80 * CrossX;
						InvenArray[CrossX][VertiY].PositionY = INVENITEMSTART_Y + 80 * VertiY;


						SwapDoor = true;
					}
					else if (InvenArray[CrossX][VertiY].index == 0 && SwapDoor == false)
					{
						swap(InvenArray[preChosenX][preChosenY], InvenArray[CrossX][VertiY]);

						InvenArray[preChosenX][preChosenY].PositionX = INVENITEMSTART_X + 80 * preChosenX;
						InvenArray[preChosenX][preChosenY].PositionY = INVENITEMSTART_Y + 80 * preChosenY;

						InvenArray[CrossX][VertiY].PositionX = INVENITEMSTART_X + 80 * CrossX;
						InvenArray[CrossX][VertiY].PositionY = INVENITEMSTART_Y + 80 * VertiY;

						SwapDoor = true;
					}
					else
					{
						InvenArray[CrossX][VertiY].PositionX = INVENITEMSTART_X + 80 * CrossX;
						InvenArray[CrossX][VertiY].PositionY = INVENITEMSTART_Y + 80 * VertiY;
						SwapDoor = true;
					}
					for (int j = 0; j < INVENVERTI; j++)
					{
						for (int i = 0; i < INVENCORSS; i++)
						{

							InvenArray[i][j].PositionX = INVENITEMSTART_X + 80 * i;
							InvenArray[i][j].PositionY = INVENITEMSTART_Y + 80 * j;

						}
					}

				}//if 끝
				SwapDoor = false;
			}
			else
			{
				for (int j = 0; j < INVENVERTI; j++)
				{
					for (int i = 0; i < INVENCORSS; i++)
					{

						InvenArray[i][j].PositionX = INVENITEMSTART_X + 80 * i;
						InvenArray[i][j].PositionY = INVENITEMSTART_Y + 80 * j;

					}
				}
			}

		}
		// 아이템 드래그해서 욺직이게 하는 친구들 //


		if (g_pMouse->ButtonPress(Mouse::LBUTTON))
		{
			if (pressOn)
			{
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
	
			}
		}

		if (g_pMouse->ButtonDown(Mouse::LBUTTON))
		{
			if (PtInRect(&Shop_Item[0].Click_rc, mousePoint))
			{
				addIndex(Shop_Item[0]);
			}

		}


		if (g_pMouse->ButtonDown(Mouse::LBUTTON))
		{
			if (PtInRect(&Shop_Item[1].Click_rc, mousePoint))
			{
				addIndex(Shop_Item[1]);
			}
		}

		if (pressOn == false)
		{

		
		}
	} // OpenInve 끝


}

void Inventory::Render()
{
	g_pDevice->SetTexture(0, NULL);
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);







	D3DXMATRIXA16 matR, matT, matWorld;
	D3DXMATRIXA16 matS;
	static float fAngle = 0.0f;

	if (openInven)
	{
		//Inventory
	

		float inven_ScaleX, inven_ScaleY;
		inven_ScaleX = 1.7f;
		inven_ScaleY = 1.7f;

		float PositionX_Inven, PositionY_Inven;
		PositionX_Inven = (clientRect.right - m_image_Inventory_info.Width) - (clientRect.right / 6);
		PositionY_Inven = ((clientRect.bottom / 10));

		D3DXMatrixRotationZ(&matR, fAngle);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, PositionX_Inven, PositionY_Inven, 0);
		D3DXMatrixScaling(&matS, inven_ScaleX, inven_ScaleY, 1);
		matWorld = matS * matR * matT;

		m_pSprite->SetTransform(&m_matWorld);


		//Inventory
		Shop_Item[0].Item_rc = RectMake(0, 0, Shop_Item[0].m_image_Item_Info.Width, Shop_Item[0].m_image_Item_Info.Height);
		Shop_Item[1].Item_rc = RectMake(0, 0, Shop_Item[1].m_image_Item_Info.Width, Shop_Item[1].m_image_Item_Info.Height);

		
		// m_rc_Inventory = temp1;
		SetRect(&m_rc_Inventory, 0, 0, m_image_Inventory_info.Width, m_image_Inventory_info.Height);
		
		

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld);

		m_pSprite->Draw(
			m_pTex_Inventory,
			&m_rc_Inventory,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			WHITE);


		//ItemSet
		D3DXMatrixRotationZ(&matR, fAngle);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, (clientRect.right / 15) , ((clientRect.bottom / 10)), 0);
		D3DXMatrixScaling(&matS, 2.f, 2.f, 1);
		matWorld = matS * matR * matT;


		
		m_pSprite->SetTransform(&m_matWorld);


		//ItemSet
		SetRect(&m_rc_ItemSet, 0, 0, m_image_ItemSet_info.Width, m_image_ItemSet_info.Height);

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld);

		m_pSprite->Draw(
			m_pTex_ItemSet,
			&m_rc_ItemSet,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			WHITE);



		//Item

		//int pointX = 0, pointY =0;

		
		D3DXMatrixRotationZ(&matR, fAngle);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT,
			Shop_Item[0].PositionX,
			Shop_Item[0].PositionY,
		0);

		float temp = .5f;
		D3DXMatrixScaling(&matS, temp, temp, 1);
	
		matWorld = matS * matR * matT;

		m_pSprite->SetTransform(&m_matWorld);

	/*	for (int i = 0; i < inventory.size(); i++)
		{
		SetRect(&inventory[i].Item_rc, m_rc_ItemSet.left + (100 * i), m_rc_ItemSet.top - (100 * i), m_rc_ItemSet.left + (100 * i) + 80, m_rc_ItemSet.top + (100 * i) + 90);
		}*/


		SetRect(&Shop_Item[0].Item_rc, 0, 0, 0 + (Shop_Item[0].m_image_Item_Info.Width  ), 0 + (Shop_Item[0].m_image_Item_Info.Height /**temp*/));
		
	

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld);
		m_pSprite->Draw(
			Shop_Item[0].m_pTex_Item,
			NULL,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			WHITE);
	// 이 부분에 대해 물어보기

		D3DXMatrixRotationZ(&matR, fAngle);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT,
			Shop_Item[1].PositionX,
			Shop_Item[1].PositionY,
			0);

	
		D3DXMatrixScaling(&matS, temp, temp, 1);

		matWorld = matS * matR * matT;

		m_pSprite->SetTransform(&m_matWorld);

		/*	for (int i = 0; i < inventory.size(); i++)
		{
		SetRect(&inventory[i].Item_rc, m_rc_ItemSet.left + (100 * i), m_rc_ItemSet.top - (100 * i), m_rc_ItemSet.left + (100 * i) + 80, m_rc_ItemSet.top + (100 * i) + 90);
		}*/


		
		SetRect(&Shop_Item[1].Item_rc, 0, 0, 0 + (Shop_Item[1].m_image_Item_Info.Width), 0 + (Shop_Item[1].m_image_Item_Info.Height /**temp*/));



		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->SetTransform(&matWorld);
		m_pSprite->Draw(
			Shop_Item[1].m_pTex_Item,
			NULL,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			WHITE);




		//SetRect(&inventory[0].Click_rc, positionX - ((inventory[0].m_image_Item_Info.Width / 2))
		//	, positionY - ((inventory[0].m_image_Item_Info.Height / 2))
		//	, positionX + ((inventory[0].m_image_Item_Info.Width / 2))
		//	, positionY + ((inventory[0].m_image_Item_Info.Height / 2)));


		//윈도우 기준이 아닌, 스크린기준으로 되어있엉
	

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
				matWorld = matS * matR * matT;

				m_pSprite->SetTransform(&m_matWorld);


				//Inventory
				SetRect(&InvenArray[i][j].Item_rc, 0, 0, InvenArray[i][j].m_image_Item_Info.Width, InvenArray[i][j].m_image_Item_Info.Height);
				SetRect(&InvenArray[i][j].Click_rc,
					InvenArray[i][j].PositionX,
					InvenArray[i][j].PositionY,
					InvenArray[i][j].PositionX + ((InvenArray[i][j].m_image_Item_Info.Width)*(InvenArray[i][j].ScaleX)),
					InvenArray[i][j].PositionY + ((InvenArray[i][j].m_image_Item_Info.Height)*(InvenArray[i][j].ScaleY)));

				m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
				m_pSprite->SetTransform(&matWorld);

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
			, Shop_Item[0].PositionX + ((Shop_Item[0].m_image_Item_Info.Width)*temp)
			, Shop_Item[0].PositionY + ((Shop_Item[0].m_image_Item_Info.Height)*temp));
	
		SetRect(&Shop_Item[1].Click_rc, Shop_Item[1].PositionX
			, Shop_Item[1].PositionY
			, Shop_Item[1].PositionX + ((Shop_Item[1].m_image_Item_Info.Width)*temp)
			, Shop_Item[1].PositionY + ((Shop_Item[1].m_image_Item_Info.Height)*temp));

		//============================================

	//	float PositionX_Inven, PositionY_Inven;
		// Equip 한번 가보자으아아아아 


		// EQUIP 왼손에 착용 하기 위한 것을 그려준다 
		if (Equip_LeftHand.empty() == false)
		{

			D3DXMatrixRotationZ(&matR, fAngle);
			D3DXMatrixIdentity(&matT);
			D3DXMatrixTranslation(&matT, 200, 200, 0);
			D3DXMatrixScaling(&matS, 1.f, 1.f, 1);
			matWorld = matS * matR * matT;



			m_pSprite->SetTransform(&m_matWorld);

			Equip_LeftHand[0].PositionX = 200;
			Equip_LeftHand[0].PositionY = 200;


			//ItemSet
			SetRect(&m_rc_ItemSet, 0, 0, Equip_LeftHand[0].m_image_Item_Info.Width, Equip_LeftHand[0].m_image_Item_Info.Height);
			SetRect(&Equip_LeftHand[0].Click_rc,
				Equip_LeftHand[0].PositionX,
				Equip_LeftHand[0].PositionY,
				Equip_LeftHand[0].PositionX + ((Equip_LeftHand[0].m_image_Item_Info.Width)*(Equip_LeftHand[0].ScaleX)),
				Equip_LeftHand[0].PositionY + ((Equip_LeftHand[0].m_image_Item_Info.Height)*(Equip_LeftHand[0].ScaleY)));

			m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
			m_pSprite->SetTransform(&matWorld);

			m_pSprite->Draw(
				Equip_LeftHand[0].m_pTex_Item,
				&Equip_LeftHand[0].Item_rc,
				&D3DXVECTOR3(0, 0, 0),
				&D3DXVECTOR3(0, 0, 0),
				WHITE);

		}

	

	}

	else
	{
		//SetRect(&Weapons[0].Item_rc, 500, 500, 600, 600);
		//SetRect(&inventory[0].Item_rc, 500, 500, 550, 550);
	}




	m_pSprite->End();
	
}

void Inventory::OnClick(UIButton * pSender)
{
}

items Inventory::addIndex(items a)
{

	D3DXMATRIXA16 matR, matT, matWorld;
	D3DXMATRIXA16 matS;
	static float fAngle = 0.0f;
	for (int j = 0; j < INVENVERTI; j++)
	{

		for (int i = 0; i < INVENCORSS; i++)
		{
			if (InvenArray[i][j].index == 0)
			{				
				InvenArray[i][j] = a;
				InvenArray[i][j].PositionX = INVENITEMSTART_X + 80 * i;
				InvenArray[i][j].PositionY = INVENITEMSTART_Y + 80 * j;
				InvenArray[i][j].Copy_num += 1;
			
				InvenArray[i][j].isInvenIn = true;
				return InvenArray[i][j];	
			}


			else if (i == INVENCORSS && j == INVENVERTI)
			{
				std::printf("인벤토리가 가득 찼습니다.");
				return a;
			}
		}	
	}	
}

void Inventory::MovingItem(items *a, items* b)
{



	a;
	b;

	swap(a, b);

	a;
	b;
	
}

void Inventory::ExMovingItem(items * b)
{
	

}

items Inventory::moveItems(items a)
{
	


	return items();
}
