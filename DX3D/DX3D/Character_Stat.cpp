#include "stdafx.h"
#include "Character_Stat.h"
#include "UIImage.h"
#include "Inventory.h"

Character_Stat::Character_Stat()
{
	m_pSprite = NULL;
	m_pRootUI = NULL;
}


Character_Stat::~Character_Stat()
{
	SAFE_RELEASE(m_pSprite);

	//m_pRootUI->ReleaseAll();

	SAFE_RELEASE(m_pRootUI);
}

void Character_Stat::Init()
{
	IronMan = { "IronMan", 1,10,5,30,30,5,5, 1,10,5,30,30,5,5 };
	isEquiped = false;

}

void Character_Stat::Update()
{

	D3DXCreateSprite(g_pDevice, &m_pSprite);

	Equip_LeftHand = static_cast<Inventory*> (g_pObjMgr->FindObjectByTag(TAG_INVEN))->Equip_LeftHand[0];


	IronMan.Atk = IronMan.OriginAtk + Equip_LeftHand.Atk;
	IronMan.MaxHp = IronMan.OriginMaxHp + Equip_LeftHand.MaxHp;

	Debug->AddText("°ø°Ý·Â:");
	Debug->AddText(IronMan.Atk);
	Debug->EndLine;



}

void Character_Stat::Render()
{


}
