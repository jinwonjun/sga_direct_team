#include "stdafx.h"
#include "SkyBox.h"

SkyBox::SkyBox(WCHAR* top, WCHAR* bottom, WCHAR* left, WCHAR* right, WCHAR* front, WCHAR* back)
{
	//상자 만들기
	// - texture UV까지 생각해보면 정점 24개가 필요하다.

	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, top, &mTex[0])))	mTex[0] = NULL;
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, bottom, &mTex[1])))	mTex[1] = NULL;
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, left, &mTex[2])))	mTex[2] = NULL;
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, right, &mTex[3])))	mTex[3] = NULL;
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, front, &mTex[4])))	mTex[4] = NULL;
	if (FAILED(D3DXCreateTextureFromFile(g_pDevice, back, &mTex[5])))	mTex[5] = NULL;

	VERTEX_PNT* pv;

	for (int i = 0; i<6; i++)
	{
		if (FAILED(g_pDevice->CreateVertexBuffer(sizeof(VERTEX_PNT) * 4, 0, VERTEX_PNT::FVF, D3DPOOL_DEFAULT, &mVtx[i], NULL))) return;
	}
	//top
	if (FAILED(mVtx[0]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	mVtx[0]->Unlock();
	//bottom
	if (FAILED(mVtx[1]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[1]->Unlock();
	//left
	if (FAILED(mVtx[2]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[2]->Unlock();
	//right
	if (FAILED(mVtx[3]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[3]->Unlock();
	//front
	if (FAILED(mVtx[4]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[4]->Unlock();
	//back
	if (FAILED(mVtx[5]->Lock(0, 0, (void**)&pv, 0))) return;
	Set_Vtx3D_Tex(pv[0], D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 0);
	Set_Vtx3D_Tex(pv[1], D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 0);
	Set_Vtx3D_Tex(pv[2], D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 0, 1);
	Set_Vtx3D_Tex(pv[3], D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR3(1, 1, 1), 1, 1);
	mVtx[5]->Unlock();
	for (int i = 0; i<6; i++)
	{
		//인덱스 버퍼
		if (FAILED(g_pDevice->CreateIndexBuffer(sizeof(CINDEX) * 12, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &mIdx[i], NULL))) return;
	}
	//인덱스 버퍼 초기화
	CINDEX* iv;
	for (int i = 0; i<6; i++)
	{
		if (FAILED(mIdx[i]->Lock(0, 0, (void**)&iv, 0))) return;
		Set_Idx(iv[0], 0, 1, 2);
		Set_Idx(iv[1], 2, 1, 3);
		mIdx[i]->Unlock();
	}
	return;
}

SkyBox::~SkyBox()
{
	for (int i = 0; i<6; i++)
	{
		SAFE_RELEASE(mTex[i]);
		SAFE_RELEASE(mVtx[i]);
		SAFE_RELEASE(mIdx[i]);
	}
}

int SkyBox::FrameMove(float et)
{
	return 0;
}

void SkyBox::Render()
{
	if (!mVtx || !mIdx) return;

	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//컬링은 양면
	g_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);			//Z버퍼 끄기
	g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);			//조명 끄기

	//스카이 박스 이동.
	//D3DXVECTOR3 vPos = *GCam()->GetEyePt();
	D3DXVECTOR3 vPos = g_pCamera->m_lookAt;
	
	D3DXMATRIX matWrd, matS, matT;
	D3DXMatrixIdentity(&matWrd);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, 100.0f, 100.0f,100.0f);
	D3DXMatrixTranslation(&matT, vPos.x, vPos.y, vPos.z);

	matWrd = matS * matT;

	//D3DXMatrixTranslation(&matWrd, vPos.x, vPos.y, vPos.z);
	g_pDevice->SetTransform(D3DTS_WORLD, &matWrd);

	//텍스쳐 UV Address를 설정.
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	//스카이박스 드로우.
	for (int i = 0; i<6; i++)
	{
		g_pDevice->SetTexture(0, (mTex[i]) ? mTex[i] : NULL);
		g_pDevice->SetStreamSource(0, mVtx[i], 0, sizeof(VERTEX_PNT));
		g_pDevice->SetFVF(VERTEX_PNT::FVF);
		g_pDevice->SetIndices(mIdx[i]);
		g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	}

	//행렬 초기화.
	D3DXMatrixIdentity(&matWrd);
	g_pDevice->SetTransform(D3DTS_WORLD, &matWrd);

	g_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);			//Z버퍼 켜기
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);			//조명 켜기
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//컬링 반시계방향
}

void SkyBox::Set_Vtx3D_Tex(VERTEX_PNT & ct, D3DXVECTOR3 p, D3DXVECTOR3 n, float tu, float tv)
{
	//ct.pos = p; ct.normal = n;	ct.tu = tu;	ct.tv = tv;
	ct.p = p;
	ct.n = n;
	ct.t = D3DXVECTOR2(tu, tv);
}

void SkyBox::Set_Idx(CINDEX & ci, WORD _0, WORD _1, WORD _2)
{
	ci._0 = _0; ci._1 = _1;	ci._2 = _2;
}
