#pragma once
#include "IScene.h"

class TeachGrid;
class Cube;
class Cubeman;
class Walls;
class Hexagon;
class ActionCube;

class ObjLoader;
class DrawingGroup;

class Frustum;

class SceneGrid : public IScene
{
	//각 정점의 칼라값까지 넣어줄 수도 있는 기능을 한다.
	vector <VERTEX_PC> m_vecVertex;

	//큐브 파츠 그리는 부분의 VERTEX_PC를 VERTEX_PT로 바꾸고, 좌표를 수정해주자
	
	vector<VERTEX_PT> vecPTVertex;
	LPDIRECT3DTEXTURE9 tex;

public:
	SceneGrid();
	//~SceneGrid();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	//큐브 동적 생성
	Cube * pCube;
	Grid * pGrid;
	//일단 큐브 머리
	Cubeman_Head * pCube_head;

	IDisplayObject *pObj;

	TeachGrid * m_pGrid;

	Cubeman * m_pCubeman;

	Walls * m_pWalls;

	Hexagon * m_pHexagon;

	ActionCube* m_pActionCube;

	ObjLoader * ob;

	Frustum * m_pFrustum;

};

