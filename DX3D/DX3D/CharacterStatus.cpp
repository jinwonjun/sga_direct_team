#include "stdafx.h"
#include "CharacterStatus.h"
#include "Gun.h"

CharacterStatus* CharacterStatus::instance = NULL;


CharacterStatus * CharacterStatus::Get()
{
	if (instance == NULL)
		instance = new CharacterStatus();

	return instance;
}

void CharacterStatus::Delete()
{

	SAFE_DELETE(instance);
}


void CharacterStatus::Init()
{
	MyChara = {
		0, //인덱스
		"Hero W. Frame", // 이름
		5, // 기본 공격력
		50, // 최대 HP
		50, // 현재 HP
		5, // 방어력

		5, // 최종 공격력
		50, // 최종 최대 HP
		5, // 최종 방어력
		0, // 공격 타입
	};

	AddAtk = 0;
	AddHp = 0;
	AddMaxHp = 0;
	AddDef = 0;
	isChangeEquip = false;
}

void CharacterStatus::Update()
{
	if (isChangeEquip)
	{
	//추가 스텟을 초기화 시키기 위한 함수
	Initialize_Adds();

	//인벤토리에서 아이템을 장착하면 발동
	Change_Equip();
	
	}

	




}

void CharacterStatus::Render()
{
}

void CharacterStatus::Initialize_Adds()
{
	AddAtk = 0;
	AddHp = 0;
	AddMaxHp = 0;
	AddDef = 0;

}

void CharacterStatus::Change_Equip()
{	

	//아이템에 의한 추가 옵션 계산
		for (int i = 1; i < 7; i++)
		{
			AddAtk += g_pInventory->Equip[i].Atk;
			AddMaxHp += g_pInventory->Equip[i].MaxHp;
			AddDef += g_pInventory->Equip[i].Def;
		}

		// 아이템에 의한 최종 스탯 계산
		MyChara.EndAtk = MyChara.Atk + AddAtk;
		MyChara.EndMaxHp = MyChara.MaxHp + AddMaxHp;
		MyChara.EndDef = MyChara.Def + AddDef;

		//static_cast<Gun*>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GunEqiupSet(g_pStatus->MyChara.Atk);
		isChangeEquip = false;
	
}
