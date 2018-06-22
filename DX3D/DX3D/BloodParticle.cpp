#include "stdafx.h"
#include "BloodParticle.h"

#include "SkinnedMesh.h"

BloodParticle::BloodParticle()
{
	m_pMesh = NULL;
}


BloodParticle::~BloodParticle()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pMesh);
	//SAFE_RELEASE(m_pTex);
}

void BloodParticle::Init()
{
	//m_pTex = g_pTextureManager->GetTexture("resources/images/ham2.png");

	//D3DXMatrixIdentity(&m_matWorld);


	m_vecAtt.resize(PARTICLE_NUM);

	//구체 반지름
	float radius = 0.02f;

	//각 파티클 각도마다 돌려가며 그릴 임시 변수
	float angle = 0;

	D3DXCreateSphere(g_pDevice, radius, 10, 10, &m_pMesh, NULL);

	for (size_t i = 0; i < PARTICLE_NUM; i++)
	{
		Attribute* att = new Attribute();
		att->_position = D3DXVECTOR3(0, 0, 0);
		att->_angle = angle;
		att->_color = 0xffff0000;
		att->_expand = Expands[i];
		m_vecAtt[i] = att;

		//파티클 갯수만큼 360도 돌게끔
		angle += 2 * D3DX_PI / PARTICLE_NUM;

		//BoundingSphere* s = new BoundingSphere(
		//	D3DXVECTOR3(GetRandomFloat(-30, 30), GetRandomFloat(-30, 30), GetRandomFloat(-30, 30)), radius);
		//m_vecpBoundary.push_back(s);

	}

	//D3DUSAGE_DYNAMIC : 값을 변경해줄때 속도감소 줄임
	//대신 D3DPOOL_MANAGED를 못씀
	g_pDevice->CreateVertexBuffer(PARTICLE_NUM * sizeof(VERTEX_PC),
		D3DUSAGE_POINTS | D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,
		VERTEX_PC::FVF, D3DPOOL_DEFAULT, &m_pVB, 0);

	t = 0.f;
}

void BloodParticle::Update()
{
	t += 0.01f;

	for (size_t i = 0; i < m_vecAtt.size(); i++)
	{
		//m_vecAtt[i]->_angle += 0.1f;
		//m_vecAtt[i]->_position.y += 0.1f;
		//m_vecAtt[i]->_position.x = m_vecAtt[i]->_position.y * 10.f * cosf(m_vecAtt[i]->_angle);
		//m_vecAtt[i]->_position.z = m_vecAtt[i]->_position.y * 10.f * sinf(m_vecAtt[i]->_angle);
		//m_vecAtt[i]->_color.a -= 0.001f;

		m_vecAtt[i]->_position.x = t * cosf(m_vecAtt[i]->_angle);
		//경사도 * time * (time - 확장도)
		m_vecAtt[i]->_position.y = -8.f * t * (t + m_vecAtt[i]->_expand);
		m_vecAtt[i]->_position.z = t * sinf(m_vecAtt[i]->_angle);
	}

	VERTEX_PC* v;
	//기존 버퍼에 쓰여져있던 값은 무시하겠따.
	m_pVB->Lock(0, 0, (LPVOID*)&v, D3DLOCK_DISCARD);
	for (auto p : m_vecAtt)
	{
		v->p = p->_position;
		v->c = p->_color;
		v++;
	}
	m_pVB->Unlock();

	//시간지났을떄 처리
	if (t > .5f)
	{
		t = 0.f;
	}
}

void BloodParticle::Render()
{
	//버퍼그릴때 z값을 그리지 않겠따.
	//g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetMaterial(&DXUtil::BLOOD_MTRL);

	int i = 0;
	for (auto p : m_vecAtt)
	{
		D3DXMATRIXA16 mat, matS, matT;
		D3DXMatrixScaling(&matS, Scales[i], Scales[i], Scales[i]);

		//끄적
		D3DXMatrixScaling(&matS, 5.0f, 5.0f, 5.0f);
		
		D3DXMatrixTranslation(&mat, p->_position.x, p->_position.y, p->_position.z);

		//끄적
		//p->_position = (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition();
		D3DXVECTOR3 TempPosByHit = static_cast <SkinnedMesh*> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->BloodCalPos;

		//Debug->AddText("생성 위치 : ");
		//Debug->AddText(TempPosByHit);
		//Debug->EndLine();
		//Debug->EndLine();
		//값 보정
		D3DXMatrixTranslation(&matT, TempPosByHit.x, TempPosByHit.y + 10.0f, TempPosByHit.z );

		//시작위치 이동
		//D3DXMatrixTranslation(&matT, 2, 5, 0);
		mat = matS * matT * mat;
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		m_pMesh->DrawSubset(0);
		i++;
	}
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);


	//for (auto p : m_vecpBoundary)
	//{

	//	D3DXMATRIXA16 mat;
	//	D3DXMatrixTranslation(&mat, p->center.x, p->center.y, p->center.z);
	//	g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	//	m_pMesh->DrawSubset(0);

	//}

	//g_pDevice->SetRenderState(D3DRS_LIGHTING, false);

	////포인트 하나에 스프라이트 하나를 입혀서 쓰겠따
	//g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	////점의 크기 조절을 할수 있게 하겠다.
	//g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	//g_pDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(0.1f));
	//g_pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.f));

	////거리에 따른 감쇄값
	//g_pDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.f));
	//g_pDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.f));
	//g_pDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.f));

	//g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	////ARG1번값은 뭐로 할거냐 -> 텍스쳐의 알파값을 쓰겠따.
	//g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	//g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	//g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//g_pDevice->SetTexture(0, m_pTex);

	//g_pDevice->SetFVF(VERTEX_PC::FVF);
	//g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
	//g_pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_vecAtt.size());


	//g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	//g_pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	//g_pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	//g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);


}
