#include "stdafx.h"
#include "BoundingBox.h"
#include "PortalEffect.h"


PortalEffect::PortalEffect()
{
	m_pTex = NULL;
}


PortalEffect::~PortalEffect()
{
}

void PortalEffect::Release()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pTex);
	SAFE_RELEASE(m_pBox);
}

void PortalEffect::Init()
{
	m_pTex = g_pTextureManager->GetTexture("resources/images/ironMan_head.png");

	assert(m_pTex && "이미지 없음");

	size_t numParticle = 3000;
	m_vecParticle.resize(numParticle);

	DWORD c = D3DCOLOR_RGBA(0, 255, 0, 255);
	float radius = 4.f;

	for (size_t i = 0; i < numParticle; i++)
	{
		Particle * pt = new Particle();
		pt->_angle = 0.02f * i;
		pt->_position.x = radius * cosf(pt->_angle);
		pt->_position.z = radius * sinf(pt->_angle);
		pt->_position.y = 0.005f * i;
		pt->_color = c;
		m_vecParticle[i] = pt;
	}
	g_pDevice->CreateVertexBuffer(numParticle * sizeof(VERTEX_PC), D3DUSAGE_POINTS | D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, VERTEX_PC::FVF, D3DPOOL_DEFAULT, &m_pVB, 0);

	//생성 위치 조절
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, 0, 0, 10);

	D3DXVec3TransformCoord(&m_pos, &m_pos, &matT);

	m_matPortal = matT * m_matWorld;
	m_pBox = new BoundingBox(D3DXVECTOR3(radius, 10.0f, radius), m_pos); m_pBox->Init();
}

void PortalEffect::Update()
{
	for (size_t i = 0; i < m_vecParticle.size(); i++)
	{
		m_vecParticle[i]->_position.y += 0.1f;
	}

	for (auto p : m_vecParticle)
	{
		if (p->_position.y > 10.f)
		{
			p->_position.y = 0.f;
		}
	}

	VERTEX_PC *v;
	m_pVB->Lock(0, 0, (LPVOID *)&v, D3DLOCK_DISCARD);//기존 버퍼에 쓰여져있던 값들을 신경쓰지 않겠다.
	for (auto p : m_vecParticle)
	{
		v->p = p->_position;
		v->c = p->_color;
		v++;
	}

	SAFE_UPDATE(m_pBox);
}

void PortalEffect::Render()
{
	if (m_renderMode != RenderMode_Default) return;

	//SAFE_RENDER(m_pBox);

	//g_pDevice->SetTexture(0, NULL);
	//버퍼그릴때 z값을 그리지 않겠따.
	//g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);

	//점의 크기 조절을 할수 있게 하겠다.
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	g_pDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(0.4f));
	g_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.f));

	//거리에 따른 감쇄값
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.f));
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.f));
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.f));



	g_pDevice->SetTransform(D3DTS_WORLD, &(m_matPortal));
	g_pDevice->SetTexture(0, m_pTex);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
	g_pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_vecParticle.size());

	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
}
