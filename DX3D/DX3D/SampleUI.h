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

	LPDIRECT3DTEXTURE9 m_pTex;
	D3DXIMAGE_INFO m_imageInfo;


	LPD3DXSPRITE m_pSprite_;
	LPDIRECT3DTEXTURE9 m_pTex_;
	D3DXIMAGE_INFO m_imageInfo_;

public:
	SampleUI();
	~SampleUI();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	// IUIButtonDelegate��(��) ���� ��ӵ�
	virtual void OnClick(UIButton * pSender) override;
	wstring s2ws(const string& s);
	int restBullet;
	bool spaceOn;
	int contorller;

	int MaxHp;
	int CurrHp;
	float PercentOfHp;

};
