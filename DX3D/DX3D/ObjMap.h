#pragma once
#include "IMap.h"
#include "ObjLoader.h"
class DrawingGroup;
class ObjLoader;
class Walls;
class BoundingBox;

class ObjMap : public IMap
{
private:

	vector<DrawingGroup * > m_vecDrawingGroup;

	//�� ���� ���̰��� �����ص� ���� �����ϱ�
	float m_rayOffsetY;
	bool surfaceMode;

	Walls * m_pWalls;
	BoundingBox * m_pBox;
	
	bool MapChangeSignal;

public:
	ObjMap();
	~ObjMap();

	// IMap��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual bool GetHeight(OUT float & height, const D3DXVECTOR3 & pos) override;

	bool GetMapChangeSignal() { return MapChangeSignal; }
	void SetMapChangeSignal(bool Condition) { MapChangeSignal = Condition; }
	void SetRayDistance(float rayDistance) { m_rayOffsetY = rayDistance; }
	

	void RenderMesh();
	void RenderDrawingGroup();
	void Init_cs_italy();
	void Init_cs_assault();
	void Init_cs_havana();
	void Init_pk_stadium();
	void Init_float_city();
	void Init_old_town();

	// IMap��(��) ���� ��ӵ�
	virtual bool CalcPickedPosition(D3DXVECTOR3 & vOut, WORD screenX, WORD screenY) override { return true; }

	void RenderUseShader_0();
	void RenderUseShader_1();
};

