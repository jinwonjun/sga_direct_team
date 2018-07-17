#pragma once
#include "IDisplayObject.h"
class IUIObject :public IDisplayObject
{
protected:
	LPD3DXSPRITE m_pSprite;


public:
	//��������Ʈ �ѷ��ٶ��� �׷����� ��� �ַ�� �Ѹ���, �Ǵٸ� �׷� �ַ�� �ѷ��ְ�
	int m_uiTag;
	//�θ�� �ڱ� ��ġ ��ģ ������
	D3DXVECTOR3 m_combinedPos;
	D3DXVECTOR3 m_pivot;
	D3DXVECTOR2 m_size;
	D3DCOLOR m_color;
	bool isRender;
	bool Exception;
	

	bool m_bDrawBorder;

	IUIObject(LPD3DXSPRITE pSprite, int uiTag = -1);
	virtual ~IUIObject();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void DrawBorder();
	void UpdatecombinedPosition();
	IUIObject * FindChildByUITag(int uiTag);
	void GetFinalRect(RECT * rect);

	const D3DXVECTOR3 & GetCombinedPosition() { return m_combinedPos;}
};

