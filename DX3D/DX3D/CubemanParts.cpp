#include "stdafx.h"
#include "CubemanParts.h"


CubemanParts::CubemanParts(int partNum, float rotXSpeed)
{
	m_partNum = partNum;
	m_rotXSpeed = rotXSpeed;
}

CubemanParts::~CubemanParts()
{
}

void CubemanParts::Init(D3DXMATRIXA16* pMat, vector<vector<int>> &vecUV)
{
	vector<D3DXVECTOR3> vecVertex;
	for (int i = 0; i < CUBE_VERTEX_SIZE; i++)
	{
		vecVertex.push_back(g_aCubeVertex[i]);
	}

	if (pMat)
	{
		for (int i = 0; i < vecVertex.size(); i++)
		{
			D3DXVec3TransformCoord(&vecVertex[i],&vecVertex[i], pMat);
		}
	}
	D3DXCreateTextureFromFile(g_pDevice, _T("resources/textures/ironman.png"), &tex);
	//SetPCVertex(m_vecPCVertex, vecVertex);
	SetPTVertex(m_vecPTVertex, vecVertex, vecUV);
}

void CubemanParts::Init()
{
}

void CubemanParts::Update()
{
	D3DXMATRIXA16 matR, matT;
	//키값을 눌렀을 때 그에 따른 변화 값을 주자
	if (m_isMoving) m_rotXAngle += m_rotXSpeed;

	//회전은 -45도에서 45도 까지만 작동하게
	if (m_rotXAngle < -D3DX_PI / 4.0f)
	{
		m_rotXSpeed *= -1;
		m_rotXAngle = -D3DX_PI / 4.0f;
	}
	if (m_rotXAngle > D3DX_PI / 4.0f)
	{
		m_rotXSpeed *= -1;
		m_rotXAngle = D3DX_PI / 4.0f;
	}
	if (m_rotXAngle > (-D3DX_PI / 4.0f) && m_rotXAngle < -D3DX_PI / 2.0f)
	{
		m_rotXAngle = 0.0f;
	}
	if (g_pMouse->ButtonPress(Mouse::INPUT_TYPE::LBUTTON))
	{
		if (m_partNum == 오른팔 || m_partNum == 무기)
		{
			m_rotXAngle = -D3DX_PI / 2.0f;
		}
	}
	else if (!(g_pMouse->ButtonPress(Mouse::INPUT_TYPE::LBUTTON)) && m_isMoving == false)
	{
		m_rotXAngle = 0.0f;
	}

	//행렬 연산 시작 부분
	D3DXMatrixRotationX(&matR, m_rotXAngle);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

	m_matWorld = matR * matT;

	//부모가 먼저 월드 업데이트 한 후에 자식이 업데이트 함수 호출하도록
	if (m_pParent)
	{
		m_matWorld = m_matWorld * m_pParent->GetWorldMatrix();
	}

	for (auto child : m_vecPChild)
	{
		child->Update();
	}
}
//큐브맨 파츠 렌더링
void CubemanParts::Render()
{
	/*
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pDevice->SetFVF(VERTEX_PT::FVF);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetTexture(0, tex);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,vecPTVertex.size() / 3, &vecPTVertex[0], sizeof(VERTEX_PT));
	g_pDevice->SetTexture(0, NULL);
	*/

	//g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//g_pDevice->SetFVF(VERTEX_PT::FVF);

	////추가부분
	//g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//g_pDevice->SetTexture(0, tex);
	////
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPCVertex.size() / 3, &m_vecPCVertex[0], sizeof(VERTEX_PT));

	//for (auto child : m_vecPChild)
	//{
	//	child->Render();
	//}

	////추가부분
	//g_pDevice->SetTexture(0, NULL);

	g_pDevice->SetTexture(0, tex);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetFVF(VERTEX_PT::FVF);
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecPTVertex.size() / 3,
		&m_vecPTVertex[0], sizeof(VERTEX_PT));

	for (auto child : m_vecPChild)
	{
		child->Render();
	}
}

//vector<VERTEX_PT>& vecOut <--이거 원래 VERTEX_PC 였음
void CubemanParts::SetPTVertex(vector<VERTEX_PT>& vecOut, vector<D3DXVECTOR3>& vecVertex ,vector<vector<int>>& uv)
{
	//D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	//D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
	//D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	//D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);
	//D3DCOLOR yellow = D3DCOLOR_XRGB(255, 255, 0);

	//버텍스들을 이용해서 8개의 버텍스들을 VERTEX_PC 자료형을 가진 vec에다 넣어주자.(이걸로 렌더링할건가보다)
	//왠지 이부분인 것 같다!!!

	//vector<VERTEX_PC> vec;
	//vector<VERTEX_PT> texture_test;
	/*vec.push_back(VERTEX_PC(vecVertex[0], white));
	vec.push_back(VERTEX_PC(vecVertex[1], yellow));
	vec.push_back(VERTEX_PC(vecVertex[2], green));
	vec.push_back(VERTEX_PC(vecVertex[3], blue));
	vec.push_back(VERTEX_PC(vecVertex[4], white));
	vec.push_back(VERTEX_PC(vecVertex[5], yellow));
	vec.push_back(VERTEX_PC(vecVertex[6], red));
	vec.push_back(VERTEX_PC(vecVertex[7], green));*/

	//일단 머리
	//texture_test.push_back(VERTEX_PT(vecVertex[0], D3DXVECTOR2(0, 1)));
	//texture_test.push_back(VERTEX_PT(vecVertex[1], D3DXVECTOR2(16/64,16/32)));
	//texture_test.push_back(VERTEX_PT(vecVertex[2], D3DXVECTOR2(1, 0)));
	//texture_test.push_back(VERTEX_PT(vecVertex[3], D3DXVECTOR2(6 / 64, 16 / 32)));
	//texture_test.push_back(VERTEX_PT(vecVertex[4], D3DXVECTOR2(16/64,16/32)));
	//texture_test.push_back(VERTEX_PT(vecVertex[5], D3DXVECTOR2(16/64,8/32)));
	//texture_test.push_back(VERTEX_PT(vecVertex[6], D3DXVECTOR2(8/64,8/32)));
	//texture_test.push_back(VERTEX_PT(vecVertex[7], D3DXVECTOR2(8/64,16/32)));
	
	////이미지 및 버텍스 , 2차 벡터 붙이기

	//D3DXCreateTextureFromFile(g_pDevice, _T("resources/textures/batman.png"), &tex);

	//for (int i = 0; i < CUBE_INDEX_SIZE; i++)
	//{
	//	//8개의 정점을 가진 행렬 놈을 다시 벡터에 넣기.(이해 안되면 global definition 참조) 인덱스 값 찾아서 큐브를 그려주는 놈이네
	//	//vecOut.push_back(vec[g_aCubeIndex[i]]);
	//	vecOut.push_back(texture_test[g_aCubeIndex[i]]);
	//}

	//쌤 코드
	vector<D3DXVECTOR2> vecUV4Vertex;
	MakeUVList(vecUV4Vertex, uv);

	for (int i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		vecOut.push_back(VERTEX_PT(vecVertex[g_aCubeIndex[i]], vecUV4Vertex[i]));
	}
}

void CubemanParts::SetMovingState(bool isMoving)
{
	//현재 상태랑 들어온 값이랑 같으면 신경 ㄴㄴ해
	if (m_isMoving == isMoving) return;

	m_isMoving = isMoving;
	if (m_isMoving == false)
	{
		m_rotXAngle = 0;
	}
	for (auto child : m_vecPChild)
	{
		//child는 디스플레이 오브젝트에 상속을 받아왔으니까, 차일드의 자료형은 디스플레이오브젝트인데, 
		//큐브맨 파츠 자료형으로 캐스팅해서 함수 사용함.
		static_cast <CubemanParts *> (child)->SetMovingState(m_isMoving);
	}
}

void CubemanParts::MakeUVList(vector<D3DXVECTOR2>& out,vector<vector<int>>& uv)
{
	for (size_t i = 0; i < uv.size(); i++)
	{
		out.push_back(D3DXVECTOR2(uv[i][0] / 64.0f, uv[i][1] / 32.0f));
		out.push_back(D3DXVECTOR2(uv[i][2] / 64.0f, uv[i][3] / 32.0f));
		out.push_back(D3DXVECTOR2(uv[i][4] / 64.0f, uv[i][5] / 32.0f));

		out.push_back(D3DXVECTOR2(uv[i][0] / 64.0f, uv[i][1] / 32.0f));
		out.push_back(D3DXVECTOR2(uv[i][4] / 64.0f, uv[i][5] / 32.0f));
		out.push_back(D3DXVECTOR2(uv[i][6] / 64.0f, uv[i][7] / 32.0f));
	}
}

