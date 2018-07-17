#pragma once

#include "UIText.h"
#include "UIButton.h"
#include "ItemManager.h"

#define g_pShop Shop::Get()



class Shop
{

private:
	static Shop * instance;


	D3DXMATRIXA16 matR, matT, matS, matWorld;
	float fAngle;

public:

	static Shop* Get();
	static void Delete();

	vector<items> Shop_Item;

	void Init();
	void Update();
	void Render();



};

