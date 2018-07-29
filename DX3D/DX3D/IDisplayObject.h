#pragma once
#include "BaseObject.h"

class IDisplayObject : public BaseObject
{
public:
	enum RenderMode
	{
		RenderMode_Default,
		RenderMode_Lighting,
		RenderMode_ShadowMapping
	};

protected:
	D3DXVECTOR3				m_pos;
	D3DXVECTOR3				m_rot;
	D3DXMATRIXA16			m_matWorld;
	D3DXMATRIXA16			m_matWorld_Bullet;
	D3DXMATRIXA16			m_matWorld_DamageFont;
	D3DXMATRIXA16			m_matWorld_StatAtk;
	D3DXMATRIXA16			m_matWorld_StatDef;

	IDisplayObject*			m_pParent;

	vector<IDisplayObject*> m_vecPChild;
	vector<IDisplayObject*> m_vecPChild_DamageFont;

	vector<VERTEX_PC> m_vecVertex;

	RenderMode				m_renderMode;
	float					m_specular;

	//Frustum Culling을 해서 육면체 밖에있으면 렌더링x, 육면체 안에있으면 렌더링 o
	bool					m_isFrustumRender;
public:
	IDisplayObject();
	virtual ~IDisplayObject();


	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void AddChild(IDisplayObject* pChild);
	virtual void AddChild_Damage(IDisplayObject* pChild);
	virtual void RemoveChild_Damage();

	//virtual void AddChild2(IDisplayObject* pChild);
	//virtual void AddChild3(IDisplayObject* pChild);
	virtual void ReleaseAll();

	virtual void RenderUseShader_0() {};
	virtual void RenderUseShader_1() {};

	D3DXVECTOR3		GetPosition() { return m_pos; }
	void			SetPosition(D3DXVECTOR3* pos) { m_pos = *pos; }
	D3DXVECTOR3		GetRotation() { return m_rot; }
	D3DXMATRIXA16	GetWorldMatrix() { return m_matWorld ; }

	vector<VERTEX_PC> GetCubeVertex() { return m_vecVertex; }

	float			GetSpecular() { return m_specular; }
	void			SetFrustumRender(bool value) { m_isFrustumRender = value; }
	bool			GetFrustumRender() { return m_isFrustumRender; }
};

