#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"
#include "IScene.h"

class SceneMainTitle : public IDisplayObject, public IUIButtonDelegate, public IScene
{
public:
	SceneMainTitle();
	~SceneMainTitle();


	LPD3DXSPRITE m_pSprite; // 스프라이트
	IUIObject * m_pRootUI; // 이미지

	UIButton * btn_GameStart;


	RECT clientRect;

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;


	// IUIButtonDelegate을(를) 통해 상속됨
	virtual void OnClick(UIButton * pSender) override;


	// IScene을(를) 통해 상속됨
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

};

