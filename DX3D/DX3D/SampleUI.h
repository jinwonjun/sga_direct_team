#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"
#include "UIText.h"

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
	std::wstring WeaponAtk;
	LPD3DXSPRITE m_pSprite;
	LPD3DXSPRITE m_pSprite_Bullet;
	LPD3DXSPRITE m_pSprite_Damage;

	IUIObject * m_pRootUI;
	IUIObject * m_pRootUI_Bullet;
	IUIObject * m_pRootUI_Damage[20];
	//D3DXMATRIXA16 matWorld_2;

	HUD_Ui Cross_Hair;
	HUD_Ui Gun;
	HUD_Ui Character_HP_BackGround;
	HUD_Ui Character_HP_Loss;
	HUD_Ui Character_HP_Remain;
	HUD_Ui Minimap;
	HUD_Ui MiniCHAR;
	HUD_Ui Notice_Msg;

	UIButton * BulletNum;
	UIButton * GetItems;
	UIText * DamageFont;


	int LifeLoss;
	int positionY;
	RECT clientRect;
	float tempX;
	float tempY;

	int MobX;
	int MobY;

	float ScaleX_GetItems;
	float ScaleY_GetItems;

	float ScaleX_BulletNum;
	float ScaleY_BulletNum;
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
	int PreFontNum;

	int MaxHp;
	int CurrHp;
	float PercentOfHp;
	
	bool renderingControl[20];


	void FontInit();
	void FontInit2();
	void FontInit3();
	
	void DamagePositionUpdate(int fontNum);

	D3DXMATRIXA16 CalPlayerPos;
};
