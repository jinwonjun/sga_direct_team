#include "stdafx.h"
#include "IDisplayObject.h"


IDisplayObject::IDisplayObject()
{
	m_pParent = NULL;
	D3DXMatrixIdentity(&m_matWorld);
	m_renderMode = RenderMode_Default;
	m_specular = 1.0f;
}


IDisplayObject::~IDisplayObject()
{
}

void IDisplayObject::AddChild(IDisplayObject * pChild)
{

	if (pChild == NULL) return;

	m_vecPChild.push_back(pChild);

	//int num = m_vecPChild.size();
	//Debug->AddText("Child가 얼마나 늘어나냐 : ");
	//Debug->AddText(num);


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
