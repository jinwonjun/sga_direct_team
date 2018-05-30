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
	//업데이트 에서 마우스 포인터 위치를 찾아서 반환하게 해보자.
	RECT rect;
	GetFinalRect(&rect);

	POINT mousePoint;
	//윈도우 기준이 아닌, 스크린기준으로 되어있엉
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);
	//마우스 포인터가 버튼 영역 안에 있을 때
	if (PtInRect(&rect, mousePoint))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			//영역안에 있는데, 눌렸으면 클릭이 된거겠지?
			if (m_buttonState == MOUSEOVER)
			{
				m_buttonState = SELECTED;
			}
		}
		else
		{
			//눌렀다가 땐 상태
			if (m_buttonState == SELECTED)
			{
				//내 자신이 클릭이 되었다고 알려주기
				if (m_pDelegate) m_pDelegate->OnClick(this);
			}
			m_buttonState = MOUSEOVER;
		}
	}
	//selected 상태를 풀어줘야지 안그럼 계속 값 들어오니까
	//마우스 포인터가 버튼 영역 밖에 있을 때
	else
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{

		}
		//버튼을 누른상태에서 밖으로 끌어땡기면 변경 안되게 해주자
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

	//텍스쳐는 3개 받아오고, 인포는 1개 받아왔는데, 목적은 크기를 얻어오는 거니까, 3개 텍스쳐의 크기가 같으면
	//1개만 이용해서 쓰면 되는거니까!
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

