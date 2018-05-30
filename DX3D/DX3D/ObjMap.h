#pragma once
#include "IMap.h"
class DrawingGroup;

class ObjMap : public IMap
{
private:

	vector<DrawingGroup * > m_vecDrawingGroup;

	//맵 층의 높이값을 저장해둘 변수 선언하기
	float m_rayOffsetY;

	//매쉬 포인터 변수랑 값 저장할 벡터
	LPD3DXMESH m_pMeshMap;
	vector<MTLTEX * > m_vecMtlTex;

public:
	ObjMap();
	~ObjMap();

	// IMap을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual bool GetHeight(OUT float & height, const D3DXVECTOR3 & pos) override;

	void RenderMesh();
	void RenderDrawingGroup();

	// IMap을(를) 통해 상속됨
	virtual bool CalcPickedPosition(D3DXVECTOR3 & vOut, WORD screenX, WORD screenY) override { return true; }
};

