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
	POINT mousePoint; //마우스 포인트 위치를 가져오기 위해서

	bool alreadyWorkedRbutton_In_Gun; //외부에서 정보를 담아줄 변수
	

public:
	Gun();
	~Gun();

	void Init();
	void Update();
	void Render();

	void GunEqiupSet(int WeaponStatus);
	void BeamGunInit();
	void LaserGunInit();
	void M4GunInit();
	void VoidInit();
};

