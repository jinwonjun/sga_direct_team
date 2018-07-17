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
		0, //�ε���
		"Hero W. Frame", // �̸�
		5, // �⺻ ���ݷ�
		50, // �ִ� HP
		50, // ���� HP
		5, // ����

		5, // ���� ���ݷ�
		50, // ���� �ִ� HP
		5, // ���� ����
		0, // ���� Ÿ��
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
	//�߰� ������ �ʱ�ȭ ��Ű�� ���� �Լ�
	Initialize_Adds();

	//�κ��丮���� �������� �����ϸ� �ߵ�
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

	//�����ۿ� ���� �߰� �ɼ� ���
		for (int i = 1; i < 7; i++)
		{
			AddAtk += g_pInventory->Equip[i].Atk;
			AddMaxHp += g_pInventory->Equip[i].MaxHp;
			AddDef += g_pInventory->Equip[i].Def;
		}

		// �����ۿ� ���� ���� ���� ���
		MyChara.EndAtk = MyChara.Atk + AddAtk;
		MyChara.EndMaxHp = MyChara.MaxHp + AddMaxHp;
		MyChara.EndDef = MyChara.Def + AddDef;

		//static_cast<Gun*>(g_pObjMgr->FindObjectByTag(TAG_GUN))->GunEqiupSet(g_pStatus->MyChara.Atk);
		isChangeEquip = false;
	
}
