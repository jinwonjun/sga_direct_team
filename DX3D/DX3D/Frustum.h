#pragma once
#include "IDisplayObject.h"


//����ü �ø��� �˾ƺ���
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

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void UpdateFrustum();//�����̽��� ������ ����ü ������Ʈ �����ֱ�
	bool IsSphereInsideFrustum(BoundingSphere * pSphere);
};

