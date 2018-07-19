#pragma once
#include "IScene.h"



class Scene_Intro :
	public IScene
{
public:
	Scene_Intro();
	virtual ~Scene_Intro();

	IDisplayObject *pObject;


	// IScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

