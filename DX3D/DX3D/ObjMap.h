#pragma once
#include "IMap.h"
class DrawingGroup;

class ObjMap : public IMap
{
private:

	vector<DrawingGroup * > m_vecDrawingGroup;

	//�� ���� ���̰��� �����ص� ���� �����ϱ�
	float m_rayOffsetY;
	bool surfaceMode;

public:
	ObjMap();
	~ObjMap();

	// IMap��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual bool GetHeight(OUT float & height, const D3DXVECTOR3 & pos) override;

	void SetRayDistance(float rayDistance) { m_rayOffsetY = rayDistance; }

	void RenderMesh();
	void RenderDrawingGroup();
	void Init_cs_italy();
	void Init_cs_assault();
	void Init_pk_stadium();

	// IMap��(��) ���� ��ӵ�
	virtual bool CalcPickedPosition(D3DXVECTOR3 & vOut, WORD screenX, WORD screenY) override { return true; }
};

