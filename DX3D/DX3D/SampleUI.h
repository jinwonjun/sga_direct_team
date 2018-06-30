#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"

class IUIObject;

struct HUD_Ui
{

	RECT m_Image_rc;
	RECT m_Sacle_rc;



	LPDIRECT3DTEXTURE9 m_pTex;
	D3DXIMAGE_INFO m_imageInfo;
};



class SampleUI :public IDisplayObject, public IUIButtonDelegate
{
private:
	std::wstring temp;
	LPD3DXSPRITE m_pSprite;
	IUIObject * m_pRootUI;
	IUIObject * m_pRootUI_2;

	D3DXMATRIXA16 matWorld_2;




	HUD_Ui Cross_Hair;
	HUD_Ui Gun;
	HUD_Ui Character_HP_BackGround;
	HUD_Ui Character_HP_Loss;
	HUD_Ui Character_HP_Remain;

	UIButton * BulletNum;


	int LifeLoss;

	RECT clientRect;
	float tempX;
	float tempY;
public:
	SampleUI();
	~SampleUI();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IUIButtonDelegate을(를) 통해 상속됨
	virtual void OnClick(UIButton * pSender) override;
	wstring s2ws(const string& s);
	int restBullet;
	bool spaceOn;
	int contorller;

	int MaxHp;
	int CurrHp;
	float PercentOfHp;

};
