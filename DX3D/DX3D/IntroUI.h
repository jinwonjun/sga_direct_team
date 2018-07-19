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
};

struct Button_UI
{
	RECT rect;
	
	IUIObject * m_pRootUI;
	UIButton * m_pButton;
	LPD3DXSPRITE m_pSprite;
	D3DXMATRIXA16 matWorld;
	wstring Str_; // �̹��� ���� �޾��� str

	float ScaleX; // �̹��� X ������
	float ScaleY; // �̹��� Y ������
	float PointX; // �̹��� ���� X ��ǥ
	float PointY; // �̹��� ���� Y ��ǥ

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
	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IUIButtonDelegate��(��) ���� ��ӵ�
	virtual void OnClick(UIButton * pSender) override;
};

