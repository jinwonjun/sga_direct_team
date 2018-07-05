#include "stdafx.h"
#include "IDisplayObject.h"


IDisplayObject::IDisplayObject()
{
	m_pParent = NULL;
	D3DXMatrixIdentity(&m_matWorld);
	
}


IDisplayObject::~IDisplayObject()
{
}

void IDisplayObject::AddChild(IDisplayObject * pChild)
{
	if (pChild == NULL) return;
	m_vecPChild.push_back(pChild);
	pChild->m_pParent = this;
}

void IDisplayObject::AddChild2(IDisplayObject * pChild)
{
	if (pChild == NULL) return;
	m_vecPChild2.push_back(pChild);
	pChild->m_pParent2 = this;
}


void IDisplayObject::AddChild3(IDisplayObject * pChild)
{
	if (pChild == NULL) return;
	m_vecPChild2.push_back(pChild);
	pChild->m_pParent2 = this;
}

void IDisplayObject::ReleaseAll()
{
	for (auto child : m_vecPChild)
		if (child) child->ReleaseAll();

	Release();
}
