#include "stdafx.h"
#include "ItemManager.h"


//ItemManager* ItemManager::instance = NULL;

InventoryManager * InventoryManager::Get()
{

	if (instance == NULL)
		instance = new InventoryManager();

	return instance;
}

void InventoryManager::Delete()
{

	SAFE_DELETE(instance);
}


ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}
