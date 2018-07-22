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

	float ScaleX; // �̹��� X ������
	float ScaleY; // �̹��� Y ������
	float PointX; // �̹��� ���� X ��ǥ
	float PointY; // �̹��� ���� Y ��ǥ

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


	bool CrossHeadMoving; // �Ӹ� �̹��� �̵��ϱ� ���� Ʈ����
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

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IUIButtonDelegate��(��) ���� ��ӵ�
	virtual void OnClick(UIButton * pSender) override;
};

