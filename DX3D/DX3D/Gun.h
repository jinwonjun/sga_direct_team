#pragma once
#include "Ironman.h"
class Gun :public Ironman
{
private:
	LPD3DXMESH m_pMeshGun;
	vector<MTLTEX * > m_vecMtlTex;

	D3DXMATRIXA16 ApplyMatrix;
	D3DXMATRIXA16 CalPrevMat;

	float					m_radius;
	LPD3DXMESH				m_pSphereMesh;

	int WeaponStatus;
	bool checkB;
	bool checkL;

public:
	Gun();
	~Gun();

	void Init();
	void Update();
	void Render();

	void BeamGunInit();
	void LaserGunInit();
};

