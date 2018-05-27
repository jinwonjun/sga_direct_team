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
	//�̹��� ���� �ֱ�
	m_pTex = g_pTextureManager->GetTexture("resources/images/snowflake.png");
	
	size_t numParticle = 5000;
	m_vecAtt.resize(numParticle);
	for (size_t i = 0; i < numParticle; i++)
	{
		//Att ���� �� ���� �����ϰ�, ���ۿ��� �̰� ������ ����.
		Attribute * att = new Attribute();
		//_position���� ������ ��ġ���� �ش�
		att->_position = D3DXVECTOR3(GetRandomFloat(-30, 30) + g_pCurrentMap->GetSize().x /2 , GetRandomFloat(-30, 30), GetRandomFloat(-30, 30) + g_pCurrentMap->GetSize().z / 2);
		//att->_color = 0xffffffff * GetRandomFloat(0, 1);
		att->_color = D3DXCOLOR(255, 255, 255,1);
		m_vecAtt[i] = att;//��ƼŬ�� �Ӽ� ���Ϳ� �����ϱ�
	}
	//���̳������� �����ϸ� D3DPOOL_MANAGED ���� ����!!!
	g_pDevice->CreateVertexBuffer(numParticle * sizeof(VERTEX_PC), D3DUSAGE_POINTS | D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, VERTEX_PC::FVF, D3DPOOL_DEFAULT,&m_pVB,0);
	
}

void ParticleTest::Update()
{
	for (size_t i = 0; i < m_vecAtt.size(); i++)
	{
		m_vecAtt[i]->_position.x -= GetRandomFloat(-0.001f, 0.01f);
		m_vecAtt[i]->_position.y -= GetRandomFloat(0.01f, 0.03f);

		//���İ� �����ϱ�
		m_vecAtt[i]->_color.a -= 0.005f;


	}

	VERTEX_PC * v;
	//���ۿ� ���ɱ�
	m_pVB->Lock(0, 0, (LPVOID *)&v, D3DLOCK_DISCARD);//���� ���ۿ� �������ִ� ������ �Ű澲�� �ʰڴ�.
	for (auto p : m_vecAtt)
	{
		v->p = p->_position;
		v->c = p->_color;
		v++;
	}

	//�� �������� ������ϱ�
	if (m_vecAtt[m_vecAtt.size() - 1]->_position.y < 0)
	{
		ParticleTest::Init();
	}

	
	("���� ������ %d ,������ ���� : %f\n", m_vecAtt.size(),m_vecAtt[m_vecAtt.size() - 1]->_position.y);
	//float angle = D3DX_PI/2;
	//angle -= GetRandomFloat(0.01f, 0.03f);
	//D3DXMatrixRotationY(&m_matWorld, angle);

}

void ParticleTest::Render()
{
	//���ؽ��� �÷����� ���⶧���� ������ ������
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	//���� ũ�⸦ ������ �ټ� �ְ� �ϰڴ�
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	g_pDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(0.4f));//����� ���� �⺻ ũ��
	g_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));//�� �ּҰ��� 0���� �ϱ�

	g_pDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));//�Ÿ��� ���� ���Ⱚ
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));//�Ÿ��� ���� ���Ⱚ
	g_pDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));//�Ÿ��� ���� ���Ⱚ

	//g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);//���İ��� �ƱԸ�Ʈ1���� ���� �ɷ� ���ڴ�.
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);//���İ��� �ƱԸ�Ʈ1���� ���� �ɷ� ���ڴ�.
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);//�ƱԸ�Ʈ1���� �ؽ����� ���İ��� ���ڴ�.
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);//�ؽ��� ���İ��̶� ��ǻ�� ���İ��� ���ؼ� ���ڴ�.
	
	

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);//dest�� factor�� ���Ŵ�.
	
	//��ƼŬ�� ���ļ� �������� �߾��� ���, �ֺ��� ���� ��Ӱ�
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);//dest�� factor�� ���Ŵ�.

	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetTexture(0, m_pTex);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
	g_pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_vecAtt.size());

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
}
