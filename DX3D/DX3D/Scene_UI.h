#pragma once
#include "IScene.h"

class ObjMap;
class Ironman;
class EnemyManager;

class Scene_UI : public IScene
{
public:
	Scene_UI();
	~Scene_UI();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

	void BoundingCheck();

	IDisplayObject *pObj;
	ObjMap * m_pObjMAp;
	Ironman * m_pCharacter;
	EnemyManager * m_pEm;
};

