#include "stdafx.h"
#include "IUIObject.h"


IUIObject::IUIObject(LPD3DXSPRITE pSprite, int uiTag) 
	: m_bDrawBorder(false), m_pSprite(pSprite),m_uiTag(uiTag),m_color(D3DXCOLOR(1,1,1,1))
{//스프라이트 하나가지고서, 맨위에가 공유해주면 그거가지고 계속 사용하기(-1이면 태그 필요없는 놈)
}


IUIObject::~IUIObject()
{
}

void IUIObject::Init()
{
}

void IUIObject::Update()
{
	UpdatecombinedPosition();

	for (auto p : m_vecPChild)
	{
		p->Update();
	}
}

void IUIObject::Render()
{
	if (m_bDrawBorder) DrawBorder();
	
	for (auto p : m_vecPChild)
	{
		p->Render();
	}
}

void IUIObject::DrawBorder()
{
	RECT r;
	GetFinalRect(&r);
	//최종점 위치 가져와서 경계선 그리기
	vector<VERTEX_RHWC> vecVertex;
	vecVertex.reserve(5);
	D3DCOLOR c = WHITE;
	vecVertex.push_back(VERTEX_RHWC(D3DXVECTOR4(r.left, r.top, 0, 1), c));//좌상을 찍었다고 한다
	vecVertex.push_back(VERTEX_RHWC(D3DXVECTOR4(r.right, r.top, 0, 1), c));//돌려
	vecVertex.push_back(VERTEX_RHWC(D3DXVECTOR4(r.right, r.bottom, 0, 1), c));//돌려
	vecVertex.push_back(VERTEX_RHWC(D3DXVECTOR4(r.left, r.bottom, 0, 1), c));//돌려
	vecVertex.push_back(VERTEX_RHWC(D3DXVECTOR4(r.left, r.top, 0, 1), c));//제자리로 돌아갔다고 한다

	g_pDevice->SetFVF(VERTEX_RHWC::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, vecVertex.size() - 1, &vecVertex[0], sizeof(VERTEX_RHWC));
}

void IUIObject::UpdatecombinedPosition()
{
	m_combinedPos = m_pos;

	if (m_pParent)
	{
		m_combinedPos += static_cast <IUIObject *>(m_pParent)->GetCombinedPosition();
	}
}

IUIObject * IUIObject::FindChildByUITag(int uiTag)
{
	if (m_uiTag == uiTag) return this;
	
	for (auto p : m_vecPChild)
	{
		IUIObject * pChild = ((IUIObject*)p)->FindChildByUITag(uiTag);
		//자기 자신이 아닌데, 차일드 중에서 찾았는데 널이 아니면, 
		if (pChild) return pChild;
	}
	return NULL;
}

void IUIObject::GetFinalRect(RECT * rect)
{
	D3DXMATRIXA16 mat;
	m_pSprite->GetTransform(&mat);

	int left = mat._41 + m_combinedPos.x * mat._11;
	int top = mat._42 + m_combinedPos.y * mat._22;
	int right = left + m_size.x * mat._11;
	int bottom = top + m_size.y * mat._22;

	SetRect(rect, left, top, right, bottom);
}

/*
화면에 스프라이트 들이 묶여있는데, 좌하를 기준으로 0,0 잡고, 암튼 그려 !
//mat._41 = UI배경이미지 기준점 x
//mat._42 = UI배경이미지 기준점 y
//m_combinedPos = 내부 UI의 기준점
*/