#pragma once
#include "IUIObject.h"

class UIButton;

//어떤 버튼이 눌렸는지 구분해서 처리해주는 용도로 쓰일 클래스여!
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

public:
	IUIButtonDelegate * m_pDelegate;
	//갯수에 따라서 상태가 다르게 보이게 해주자
	LPDIRECT3DTEXTURE9 m_aTexture[COUNT];


	UIButton(IUIButtonDelegate * pDelegate, LPD3DXSPRITE pSprite, int uiTag = -1);
	~UIButton();

	virtual void Update() override;
	virtual void Render() override;

	void SetTexture(string normal, string mouseOver, string selected);
	void SetText(LPD3DXFONT font, LPCTSTR text);
};

