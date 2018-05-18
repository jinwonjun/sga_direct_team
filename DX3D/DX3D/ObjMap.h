#pragma once
#include "IMap.h"
class DrawingGroup;

class ObjMap : public IMap
{
private:

	vector<DrawingGroup * > m_vecDrawingGroup;

	//�� ���� ���̰��� �����ص� ���� �����ϱ�
	float m_rayOffsetY;

	//�Ž� ������ ������ �� ������ ����
	LPD3DXMESH m_pMeshMap;
	vector<MTLTEX * > m_vecMtlTex;

public:
	ObjMap();
	~ObjMap();

	// IMap��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual bool GetHeight(OUT float & height, const D3DXVECTOR3 & pos) override;

	void RenderMesh();
	void RenderDrawingGroup();

	// IMap��(��) ���� ��ӵ�
	virtual bool CalcPickedPosition(D3DXVECTOR3 & vOut, WORD screenX, WORD screenY) override { return true; }
};

