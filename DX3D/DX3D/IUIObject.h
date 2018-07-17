#pragma once
#include "IDisplayObject.h"
class IUIObject :public IDisplayObject
{
protected:
	LPD3DXSPRITE m_pSprite;


public:
	//스프라이트 뿌려줄때는 그룹으로 묶어서 주루룩 뿌리고, 또다른 그룹 주루룩 뿌려주고
	int m_uiTag;
	//부모랑 자기 위치 합친 포지션
	D3DXVECTOR3 m_combinedPos;
	D3DXVECTOR3 m_pivot;
	D3DXVECTOR2 m_size;
	D3DCOLOR m_color;
	bool isRender;
	bool Exception;
	

	bool m_bDrawBorder;

	IUIObject(LPD3DXSPRITE pSprite, int uiTag = -1);
	virtual ~IUIObject();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void DrawBorder();
	void UpdatecombinedPosition();
	IUIObject * FindChildByUITag(int uiTag);
	void GetFinalRect(RECT * rect);

	const D3DXVECTOR3 & GetCombinedPosition() { return m_combinedPos;}
};

