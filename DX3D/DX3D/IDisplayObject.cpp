#include "stdafx.h"
#include "IDisplayObject.h"


IDisplayObject::IDisplayObject()
{
	m_pParent = NULL;
	D3DXMatrixIdentity(&m_matWorld);
	m_renderMode = RenderMode_Default;
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

void IDisplayObject::AddChild_Damage(IDisplayObject * pChild)
{
	if (pChild == NULL) return;
	m_vecPChild_DamageFont.push_back(pChild);
	
	pChild->m_pParent = this;

}

void IDisplayObject::RemoveChild_Damage()
{
	if (m_vecPChild_DamageFont.size() > 0)
	{
		m_vecPChild_DamageFont.erase(m_vecPChild_DamageFont.begin());
	}
}



void IDisplayObject::ReleaseAll()
{
	for (auto child : m_vecPChild)
		if (child) child->ReleaseAll();

	Release();
}
