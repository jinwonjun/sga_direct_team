#pragma once
#include "IDisplayObject.h"
class PortalEffect : public IDisplayObject
{
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	vector<Particle *>		m_vecParticle;
	LPDIRECT3DTEXTURE9		m_pTex;

	D3DXMATRIXA16			m_matPortal;
	BoundingBox*			m_pBox;


public:
	PortalEffect();
	~PortalEffect();

	void Release();
	bool isPortal;


	BoundingBox*	GetBoundingBox() { return m_pBox; }

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

