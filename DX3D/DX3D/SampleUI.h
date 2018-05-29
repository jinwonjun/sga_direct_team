#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"

class IUIObject;

class SampleUI :public IDisplayObject, public IUIButtonDelegate
{
private:
	std::wstring temp;
	LPD3DXSPRITE m_pSprite;
	IUIObject * m_pRootUI;
	IUIObject * m_pRootUI_2;

	D3DXMATRIXA16 matWorld_2;

	LPDIRECT3DTEXTURE9 m_pTex;
	D3DXIMAGE_INFO m_imageInfo;


	LPD3DXSPRITE m_pSprite_;
	LPDIRECT3DTEXTURE9 m_pTex_;
	D3DXIMAGE_INFO m_imageInfo_;


	LPDIRECT3DTEXTURE9 m_pTex_Hp_Back;
	D3DXIMAGE_INFO m_imageInfo_Hp_Back;


	LPDIRECT3DTEXTURE9 m_pTex_Hp_Loss;
	D3DXIMAGE_INFO m_imageInfo_Hp_Loss;

	LPDIRECT3DTEXTURE9 m_pTex_Hp_Remain;
	D3DXIMAGE_INFO m_imageInfo_Hp_Remain;


	UIButton * BulletNum;


	int LifeLoss;
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
