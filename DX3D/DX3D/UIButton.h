#pragma once
#include "IUIObject.h"

class UIButton;

//� ��ư�� ���ȴ��� �����ؼ� ó�����ִ� �뵵�� ���� Ŭ������!
class IUIButtonDelegate
{
public:
	virtual void OnClick(UIButton * pSender) = 0;
};

class UIButton :public IUIObject
{
private:
	enum ButtonState
	{
		NORMAL, MOUSEOVER, SELECTED, COUNT
	};
	
	ButtonState m_buttonState;
	//static UIText * pText;

public:
	IUIButtonDelegate * m_pDelegate;
	//������ ���� ���°� �ٸ��� ���̰� ������
	LPDIRECT3DTEXTURE9 m_aTexture[COUNT];
	//void SetColor(D3DXCOLOR c) { m_color = c; }



	UIButton(IUIButtonDelegate * pDelegate, LPD3DXSPRITE pSprite, int uiTag = -1);
	
	UIButton(IUIButtonDelegate * pDelegate, LPD3DXSPRITE pSprite, LPD3DXFONT font, int uiTag = -1);
	~UIButton();

	virtual void Update() override;
	virtual void Render() override;

	void SetTexture(string normal, string mouseOver, string selected);
	void SetTexture(string normal, string mouseOver, string selected, int Alpha);
	void SetText(LPD3DXFONT font, LPCWSTR text, D3DXCOLOR _c);
	void SetText(LPD3DXFONT font, LPCWSTR text, D3DXCOLOR _c, D3DXVECTOR3 _pos);
//	void SetText_Description(LPD3DXFONT font, LPCWSTR text, D3DXCOLOR _c, D3DXVECTOR3 _pos);
	void SetText(LPD3DXFONT font, LPCWSTR text, D3DXCOLOR _c, D3DXVECTOR3 _pos, char word);
	//void SetItemInfo(LPCWSTR text) { pText->m_text = text; }

};

