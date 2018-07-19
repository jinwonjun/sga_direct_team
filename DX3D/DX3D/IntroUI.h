#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"
#include "UIText.h"

class IUIObject;

struct Draw_UI
{

	RECT m_Image_rc;
	RECT m_Sacle_rc;

	LPDIRECT3DTEXTURE9 m_pTex;
	D3DXIMAGE_INFO m_imageInfo;

	D3DXMATRIXA16 matWorld;
	LPD3DXSPRITE m_pSprite;
	IUIObject * m_pRootUI;

	float ScaleX; // 이미지 X 스케일
	float ScaleY; // 이미지 Y 스케일
	float PointX; // 이미지 시작 X 좌표
	float PointY; // 이미지 시작 Y 좌표
};

struct Button_UI
{
	RECT rect;
	
	IUIObject * m_pRootUI;
	UIButton * m_pButton;
	LPD3DXSPRITE m_pSprite;
	D3DXMATRIXA16 matWorld;
	wstring Str_; // 이미지 네임 받아줄 str

	float ScaleX; // 이미지 X 스케일
	float ScaleY; // 이미지 Y 스케일
	float PointX; // 이미지 시작 X 좌표
	float PointY; // 이미지 시작 Y 좌표

};



class IntroUI :
	public IDisplayObject, public IUIButtonDelegate
{
private:

	Draw_UI IntroPage;
	RECT clientRect;
	Button_UI PlayButton;
	Button_UI QuitButton;
	POINT mousePoint;

public:
	IntroUI();
	 ~IntroUI();

	 void PlayButtonInit();
	 void QuitButtonInit();
	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IUIButtonDelegate을(를) 통해 상속됨
	virtual void OnClick(UIButton * pSender) override;
};

