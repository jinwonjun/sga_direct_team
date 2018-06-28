#pragma once
#include "IMap.h"
class DrawingGroup;

class ObjMap : public IMap
{
private:

	vector<DrawingGroup * > m_vecDrawingGroup;

	//맵 층의 높이값을 저장해둘 변수 선언하기
	float m_rayOffsetY;

public:
	ObjMap();
	~ObjMap();

	// IMap을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual bool GetHeight(OUT float & height, const D3DXVECTOR3 & pos) override;

	void SetRayDistance(float rayDistance) { m_rayOffsetY = rayDistance; }

	void RenderMesh();
	void RenderDrawingGroup();
	void Init_cs_italy();
	void Init_cs_assault();

	// IMap을(를) 통해 상속됨
	virtual bool CalcPickedPosition(D3DXVECTOR3 & vOut, WORD screenX, WORD screenY) override { return true; }
};

