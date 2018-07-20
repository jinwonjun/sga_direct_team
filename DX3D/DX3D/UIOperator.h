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

	int timer = 0;
	bool ScreenOn = false;
};

class UIOperator :
	public IDisplayObject, public IUIButtonDelegate
{
private:
	RECT clientRect;
	POINT mousePoint;
	D3DXMATRIXA16 matR, matT,matS;


	bool CrossHeadMoving; // 머리 이미지 이동하기 위한 트리거
	bool ShutCrossHeadMoving;
	
	bool ScaleHeadMoving;
	bool ShutScaleHeadMoving;

	float SizeofImage;

public:
	UIOperator();
	~UIOperator();


	Draw_UI Valkire;
	Draw_UI Zealot;
	Draw_UI Mutant;


	void CrossHeadMovingFunction(Draw_UI &Chara);
	void SacleHeadMovingFunction(Draw_UI &Chara);
	

	void ShutDownCrossHeadMovingFunction(Draw_UI &Chara);
	void ShutDownSacleHeadMovingFunction(Draw_UI &Chara);


	void DrawValkire();
	void DrawZealot();
	void DrawMutant();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IUIButtonDelegate을(를) 통해 상속됨
	virtual void OnClick(UIButton * pSender) override;
};

