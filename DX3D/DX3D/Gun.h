#pragma once
#include "Ironman.h"
class Gun :public Ironman
{
private:
	LPD3DXMESH m_pMeshGun;
	vector<MTLTEX * > m_vecMtlTex;

	D3DXMATRIXA16 ApplyMatrix;
	D3DXMATRIXA16 CalPrevMat;

public:
	Gun();
	~Gun();

	void Init();
	void Update();
	void Render();
};

