#include "stdafx.h"
#include "ParticleTest.h"


ParticleTest::ParticleTest()
{
}


ParticleTest::~ParticleTest()
{
	SAFE_RELEASE(m_pVB);
}

void ParticleTest::Init()
{
	//이미지 파일 넣기
	m_pTex = g_pTextureManager->GetTexture("resources/images/snowflake.png");
	
	size_t numParticle = 5000;
	m_vecAtt.resize(numParticle);
	for (size_t i = 0; i < numParticle; i++)
	{
		//Att 생성 및 값을 조절하고, 버퍼에서 이걸 가져다 쓴다.
		Attribute * att = new Attribute();
		//_position으로 벡터의 위치값을 준다
		att->_position = D3DXVECTOR3(GetRandomFloat(-30, 30) + g_pCurrentMap->GetSize().x /2 , GetRandomFloat(-30, 30), GetRandomFloat(-30, 30) + g_pCurrentMap->GetSize().z / 2);
		//att->_color = 0xffffffff * GetRandomFloat(0, 1);
		att->_color = D3DXCOLOR(255, 255, 255,1);
		m_vecAtt[i] = att;//파티클의 속성 벡터에 저장하기
	}
	//다이나믹으로 설정하면 D3DPOOL_MANAGED 설정 못씀!!!
	g_pDevice->CreateVertexBuffer(numParticle * sizeof(VERTEX_PC), D3DUSAGE_POINTS | D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, VERTEX_PC::FVF, D3DPOOL_DEFAULT,&m_pVB,0);
	
}

void ParticleTest::Update()
{
	for (size_t i = 0; i < m_vecAtt.size(); i++)
	{
		m_vecAtt[i]->_position.x -= GetRandomFloat(-0.001f, 0.01f);
		m_vecAtt[i]->_position.y -= GetRandomFloat(0.01f, 0.03f);

		//알파값 조절하기
		m_vecAtt[i]->_color.a -= 0.005f;


	}

	VERTEX_PC * v;
	//버퍼에 락걸기
	m_pVB->Lock(0, 0, (LPVOID *)&v, D3DLOCK_DISCARD);//기존 버퍼에 쓰여져있던 값들을 신경쓰지 않겠다.
	for (auto p : m_vecAtt)
	{
		v->p = p->_position;
		v->c = p->_color;
		v++;
	}

	//다 떨어지면 재생성하기
	if (m_vecAtt[m_vecAtt.size() - 1]->_position.y < 0)
	{
		ParticleTest::Init();
	}

	
	("벡터 사이즈 %d ,마지막 높이 : %f\n", m_vecAtt.size(),m_vecAtt[m_vecAtt.size() - 1]->_position.y);
	//float angle = D3DX_PI/2;
	//angle -= GetRandomFloat(0.01f, 0.03f);
	//D3DXMatrixRotationY(&m_matWorld, angle);

}

void ParticleTest::Render()
{
	//버텍스의 컬러값을 쓰기때문에 조명은 꺼주자
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	//점의 크기를 조절해 줄수 있게 하겠다
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	g_pDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(0.4f));//사용할 점의 기본 크기
	g_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));//점 최소값은 0으로 하기

	g_pDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));//거리에 따른 감쇄값
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));//거리에 따른 감쇄값
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));//거리에 따른 감쇄값

	//g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);//알파값을 아규먼트1번에 대한 걸로 쓰겠다.
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);//알파값을 아규먼트1번에 대한 걸로 쓰겠다.
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);//아규먼트1번은 텍스쳐의 알파값을 쓰겠다.
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);//텍스쳐 알파값이랑 디퓨즈 알파값을 곱해서 쓰겠다.
	
	

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);//dest의 factor로 쓸거다.
	
	//파티클이 뭉쳐서 되있을때 중앙은 밝게, 주변은 점점 어둡게
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);//dest의 factor로 쓸거다.

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetTexture(0, m_pTex);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
	g_pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_vecAtt.size());

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
}
