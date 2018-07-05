#pragma once
#include "BaseObject.h"

class IDisplayObject : public BaseObject
{
protected:
	D3DXVECTOR3				m_pos;
	D3DXVECTOR3				m_rot;
	D3DXMATRIXA16			m_matWorld;
	
	IDisplayObject*			m_pParent;
	IDisplayObject*			m_pParent2;
	IDisplayObject*			m_pParent3;

	vector<IDisplayObject*> m_vecPChild;
	vector<IDisplayObject*> m_vecPChild2;
	vector<IDisplayObject*> m_vecPChild3;

	vector<VERTEX_PC> m_vecVertex;

public:
	IDisplayObject();
	virtual ~IDisplayObject();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void AddChild(IDisplayObject* pChild);
	virtual void AddChild2(IDisplayObject* pChild);
	virtual void AddChild3(IDisplayObject* pChild);
	virtual void ReleaseAll();


	D3DXVECTOR3		GetPosition() { return m_pos; }
	void			SetPosition(D3DXVECTOR3* pos) { m_pos = *pos; }
	D3DXVECTOR3		GetRotation() { return m_rot; }
	D3DXMATRIXA16	GetWorldMatrix() { return m_matWorld ; }

	vector<VERTEX_PC> GetCubeVertex() { return m_vecVertex; }

};

