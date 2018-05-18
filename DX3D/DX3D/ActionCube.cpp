#include "stdafx.h"
#include "ActionCube.h"


ActionCube::ActionCube()
{
	m_pVB = NULL;
	m_pIB = NULL;
}


ActionCube::~ActionCube()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
}

void ActionCube::Init()
{
	InitVertex();
	//RunAction(new ActionMoveTo(0.7, D3DXVECTOR3(10, 0, 5)));

	/*
		무브투로 이동확인
		여섯번 쓰면 여섯개 지점 이동가능
		여섯개를 액션 시퀀스로 묶는다
		시퀀스가 리핏되게 반복
	*/
	//연속적으로 액션을 수행해줄 객체 생성
	auto seq = new ActionSequence();
	float radius = 8;
	for (int i = 0; i < 6; i++)
	{
		D3DXVECTOR2 pt(cos(D3DX_PI * i / 3.0f) * radius, sin(D3DX_PI* i / 3.0f)*radius);
		seq->AddAction(new ActionMoveTo( 0.7, D3DXVECTOR3(pt.x, 0, pt.y)));
	}
	this->RunAction(new ActionRepeat(seq));//seq, 2 -> 2 넣으면 2번 돌리고, 변수 안넣으면 무한 돌리기

	
}

void ActionCube::Update()
{
	D3DXMATRIXA16 matT, matR;

	UpdateAction();
	//내 정면의 대한 값을 여기다 넘겨달라
	LookForward(m_forward, matR);

	m_prevPos = m_pos;

	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

	m_matWorld = matR * matT;
}

void ActionCube::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetFVF(VERTEX_PC::FVF);

	//버텍스 인덱스 버퍼로 그리기
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PC));
	g_pDevice->SetIndices(m_pIB);
	//그릴 방법, 버텍스 사이즈만큼 뒤부터 읽겠다(시작부터니 0), 인덱스 사이즈만큼 뒤에서
	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0,
		m_VBDesc.Size, 0, m_IBDesc.Size / 3);
}

void ActionCube::InitVertex()
{
	vector<D3DXVECTOR3> vecPos;
	for (size_t i = 0; i < CUBE_VERTEX_SIZE; i++)
	{
		vecPos.push_back(g_aCubeVertex[i]);
	}

	SetVertex(m_vecVertex, m_vecIndex, vecPos);
	SetBuffer(m_pVB, m_pIB, m_vecVertex, m_vecIndex);

	m_pVB->GetDesc(&m_VBDesc);
	m_pIB->GetDesc(&m_IBDesc);
}

void ActionCube::SetVertex(vector<VERTEX_PC>& vecVertexOut,vector<WORD>& vecIndexOut, vector<D3DXVECTOR3> vecPos)
{
	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
	D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);
	D3DCOLOR yellow = D3DCOLOR_XRGB(255, 255, 0);

	vecVertexOut.push_back(VERTEX_PC(vecPos[0], blue));
	vecVertexOut.push_back(VERTEX_PC(vecPos[1], red));
	vecVertexOut.push_back(VERTEX_PC(vecPos[2], green));
	vecVertexOut.push_back(VERTEX_PC(vecPos[3], red));
	vecVertexOut.push_back(VERTEX_PC(vecPos[4], blue));
	vecVertexOut.push_back(VERTEX_PC(vecPos[5], red));
	vecVertexOut.push_back(VERTEX_PC(vecPos[6], green));
	vecVertexOut.push_back(VERTEX_PC(vecPos[7], red));

	for (size_t i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		vecIndexOut.push_back(g_aCubeIndex[i]);
	}
}

void ActionCube::SetBuffer(LPDIRECT3DVERTEXBUFFER9 & pVb,LPDIRECT3DINDEXBUFFER9 & pIb,vector<VERTEX_PC>& vecVertex, vector<WORD>& vecIndex)
{
	// 필요한 버퍼 공간 생성
	// 버퍼 공간 사이즈, 0, FVF, 메모리 풀 관리할지 안할지(여기서는관리), 버텍스 버퍼 변수, 안쓰는 변수 
	g_pDevice->CreateVertexBuffer(vecVertex.size() * sizeof(VERTEX_PC),
		0, VERTEX_PC::FVF, D3DPOOL_MANAGED, &pVb, NULL);

	//버퍼에 실제 접근하려면 포인터로 접근해야한다
	//락거는게 많아지면 화면 지연이 생김
	VERTEX_PC* pVertex;
	// 오프셋 시작 위치, 크기(0이면 다 가져다쓰겟다),플래그
	pVb->Lock(0, 0, (LPVOID*)&pVertex, 0);
	//이 포인터에다가 내가 생성한 정보를 넣어줘야함
	memcpy(pVertex, &vecVertex[0], vecVertex.size() * sizeof(VERTEX_PC));
	pVb->Unlock();
	vecVertex.clear();

	g_pDevice->CreateIndexBuffer(vecIndex.size() * sizeof(WORD),
		NULL, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIb, NULL);

	WORD* pIndex;
	pIb->Lock(0, 0, (LPVOID*)&pIndex, 0);
	memcpy(pIndex, &vecIndex[0], vecIndex.size() * sizeof(WORD));
	pIb->Unlock();
	vecIndex.clear();
}

void ActionCube::LookForward(D3DXVECTOR3 & outVec3, D3DXMATRIXA16 & outMat)
{
	//현재 - 이전 좌표
	D3DXVECTOR3 forward = m_pos - m_prevPos;

	//이동해서 방향이 바꼇으면 
	if (D3DXVec3LengthSq(&forward) > FLT_EPSILON)
	{
		m_forward = forward;
	}
	//뷰스페이스 : 카메라를 원점으로 옮기고 정면을 바라보게 하는 함수
	//보고있는 방향을 정면으로 바꿔준다.
	D3DXMatrixLookAtLH(&outMat, &D3DXVECTOR3(0, 0, 0), &m_forward,
		&D3DXVECTOR3(0, 1, 0));

	
	D3DXMatrixTranspose(&outMat, &outMat);

	

}
