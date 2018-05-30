#pragma once
#include "IDisplayObject.h"


//절두체 컬링을 알아보자
class Frustum :public IDisplayObject
{
	vector<D3DXVECTOR3> m_vecProjVtx;
	vector<D3DXVECTOR3> m_vecWorldVtx;
	vector<D3DXPLANE> m_vecPlane;
	vector<BoundingSphere *> m_vecBoundary;
	LPD3DXMESH m_pMesh;

public:
	Frustum();
	~Frustum();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void UpdateFrustum();//스페이스바 누르면 절두체 업데이트 시켜주기
	bool IsSphereInsideFrustum(BoundingSphere * pSphere);
};

