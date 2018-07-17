#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"
#include "IScene.h"

class SceneMainTitle : public IDisplayObject, public IUIButtonDelegate, public IScene
{
public:
	SceneMainTitle();
	~SceneMainTitle();


	LPD3DXSPRITE m_pSprite; // ��������Ʈ
	IUIObject * m_pRootUI; // �̹���

	UIButton * btn_GameStart;


	RECT clientRect;

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;


	// IUIButtonDelegate��(��) ���� ��ӵ�
	virtual void OnClick(UIButton * pSender) override;


	// IScene��(��) ���� ��ӵ�
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

};

