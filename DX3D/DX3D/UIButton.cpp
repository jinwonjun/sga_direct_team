#include "stdafx.h"
#include "UIButton.h"
#include "UIText.h"

//int uiTag = -1
UIButton::UIButton(IUIButtonDelegate * pDelegate, LPD3DXSPRITE pSprite, int uiTag)
	:IUIObject(pSprite, uiTag),m_pDelegate(pDelegate),m_buttonState(NORMAL)
{
}


UIButton::~UIButton()
{
}

void UIButton::Update()
{
	IUIObject::Update();
	//������Ʈ ���� ���콺 ������ ��ġ�� ã�Ƽ� ��ȯ�ϰ� �غ���.
	RECT rect;
	GetFinalRect(&rect);

	POINT mousePoint;
	//������ ������ �ƴ�, ��ũ���������� �Ǿ��־�
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);
	//���콺 �����Ͱ� ��ư ���� �ȿ� ���� ��
	if (PtInRect(&rect, mousePoint))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			//�����ȿ� �ִµ�, �������� Ŭ���� �ȰŰ���?
			if (m_buttonState == MOUSEOVER)
			{
				m_buttonState = SELECTED;
			}
		}
		else
		{
			//�����ٰ� �� ����
			if (m_buttonState == SELECTED)
			{
				//�� �ڽ��� Ŭ���� �Ǿ��ٰ� �˷��ֱ�
				if (m_pDelegate) m_pDelegate->OnClick(this);
			}
			m_buttonState = MOUSEOVER;
		}
	}
	//selected ���¸� Ǯ������� �ȱ׷� ��� �� �����ϱ�
	//���콺 �����Ͱ� ��ư ���� �ۿ� ���� ��
	else
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{

		}
		//��ư�� �������¿��� ������ ������ ���� �ȵǰ� ������
		else
		{
			m_buttonState = NORMAL;
		}
	}
}

void UIButton::Render()
{
	if (m_aTexture[m_buttonState])
	{
		RECT rect;
		SetRect(&rect, 0, 0, m_size.x, m_size.y);

		m_pSprite->Draw(m_aTexture[m_buttonState], &rect, &m_pivot, &m_combinedPos,m_color);
	}
	IUIObject::Render();
}

void UIButton::SetTexture(string normal, string mouseOver, string selected)
{
	D3DXIMAGE_INFO info;
	m_aTexture[NORMAL] = g_pTextureManager->GetTexture(normal);
	m_aTexture[MOUSEOVER] = g_pTextureManager->GetTexture(mouseOver);
	m_aTexture[SELECTED] = g_pTextureManager->GetTexture(selected);

	//�ؽ��Ĵ� 3�� �޾ƿ���, ������ 1�� �޾ƿԴµ�, ������ ũ�⸦ ������ �Ŵϱ�, 3�� �ؽ����� ũ�Ⱑ ������
	//1���� �̿��ؼ� ���� �Ǵ°Ŵϱ�!
	D3DXGetImageInfoFromFileA(normal.c_str(), &info);

	m_size.x = info.Width;
	m_size.y = info.Height;
}

void UIButton::SetText(LPD3DXFONT font, LPCWSTR  text)
{
	UIText * pText = new UIText(font, m_pSprite);
	this->AddChild(pText);
	pText->m_text = text;
	pText->m_size = m_size;
}

