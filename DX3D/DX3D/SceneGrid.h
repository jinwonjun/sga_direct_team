#pragma once
#include "IScene.h"

class TeachGrid;
class Cube;
class Cubeman;
class Walls;
class Hexagon;
class ActionCube;
class Frustum;
class SkyBox;
class HeightMap;
class EnemyManager;

class SkinnedMesh;

class SceneGrid : public IScene
{
	//�� ������ Į�󰪱��� �־��� ���� �ִ� ����� �Ѵ�.
	vector <VERTEX_PC> m_vecVertex;

	//ť�� ���� �׸��� �κ��� VERTEX_PC�� VERTEX_PT�� �ٲٰ�, ��ǥ�� ����������
	
	vector<VERTEX_PT> vecPTVertex;
	LPDIRECT3DTEXTURE9 tex;

public:
	SceneGrid();
	//~SceneGrid();

	// IScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	void BoundingCheck();

	//ť�� ���� ����
	Cube * pCube;
	Grid * pGrid;
	//�ϴ� ť�� �Ӹ�
	Cubeman_Head * pCube_head;

	IDisplayObject *pObj;

	TeachGrid * m_pGrid;

	Cubeman * m_pCubeman;

	Walls * m_pWalls;

	Hexagon * m_pHexagon;

	ActionCube* m_pActionCube;

	Frustum * m_pFrustum;

	SkyBox * m_pSky;

	HeightMap *		m_pHeightMap;

	EnemyManager * m_pEm;

	IDisplayObject *m_Inventory;
	// �̰� �ٲܼ� ������?

	SkinnedMesh * m_pSkinnedMesh;

	BloodManager * m_pBloodMgr;
};

