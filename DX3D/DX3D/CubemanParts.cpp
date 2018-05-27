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
	//Ű���� ������ �� �׿� ���� ��ȭ ���� ����
	if (m_isMoving) m_rotXAngle += m_rotXSpeed;

	//ȸ���� -45������ 45�� ������ �۵��ϰ�
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
		if (m_partNum == ������ || m_partNum == ����)
		{
			m_rotXAngle = -D3DX_PI / 2.0f;
		}
	}
	else if (!(g_pMouse->ButtonPress(Mouse::INPUT_TYPE::LBUTTON)) && m_isMoving == false)
	{
		m_rotXAngle = 0.0f;
	}

	//��� ���� ���� �κ�
	D3DXMatrixRotationX(&matR, m_rotXAngle);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

	m_matWorld = matR * matT;

	//�θ� ���� ���� ������Ʈ �� �Ŀ� �ڽ��� ������Ʈ �Լ� ȣ���ϵ���
	if (m_pParent)
	{
		m_matWorld = m_matWorld * m_pParent->GetWorldMatrix();
	}

	for (auto child : m_vecPChild)
	{
		child->Update();
	}
}
//ť��� ���� ������
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

	////�߰��κ�
	//g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//g_pDevice->SetTexture(0, tex);
	////
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPCVertex.size() / 3, &m_vecPCVertex[0], sizeof(VERTEX_PT));

	//for (auto child : m_vecPChild)
	//{
	//	child->Render();
	//}

	////�߰��κ�
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

//vector<VERTEX_PT>& vecOut <--�̰� ���� VERTEX_PC ����
void CubemanParts::SetPTVertex(vector<VERTEX_PT>& vecOut, vector<D3DXVECTOR3>& vecVertex ,vector<vector<int>>& uv)
{
	//D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	//D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
	//D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
	//D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);
	//D3DCOLOR yellow = D3DCOLOR_XRGB(255, 255, 0);

	//���ؽ����� �̿��ؼ� 8���� ���ؽ����� VERTEX_PC �ڷ����� ���� vec���� �־�����.(�̰ɷ� �������Ұǰ�����)
	//���� �̺κ��� �� ����!!!

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

	//�ϴ� �Ӹ�
	//texture_test.push_back(VERTEX_PT(vecVertex[0], D3DXVECTOR2(0, 1)));
	//texture_test.push_back(VERTEX_PT(vecVertex[1], D3DXVECTOR2(16/64,16/32)));
	//texture_test.push_back(VERTEX_PT(vecVertex[2], D3DXVECTOR2(1, 0)));
	//texture_test.push_back(VERTEX_PT(vecVertex[3], D3DXVECTOR2(6 / 64, 16 / 32)));
	//texture_test.push_back(VERTEX_PT(vecVertex[4], D3DXVECTOR2(16/64,16/32)));
	//texture_test.push_back(VERTEX_PT(vecVertex[5], D3DXVECTOR2(16/64,8/32)));
	//texture_test.push_back(VERTEX_PT(vecVertex[6], D3DXVECTOR2(8/64,8/32)));
	//texture_test.push_back(VERTEX_PT(vecVertex[7], D3DXVECTOR2(8/64,16/32)));
	
	////�̹��� �� ���ؽ� , 2�� ���� ���̱�

	//D3DXCreateTextureFromFile(g_pDevice, _T("resources/textures/batman.png"), &tex);

	//for (int i = 0; i < CUBE_INDEX_SIZE; i++)
	//{
	//	//8���� ������ ���� ��� ���� �ٽ� ���Ϳ� �ֱ�.(���� �ȵǸ� global definition ����) �ε��� �� ã�Ƽ� ť�긦 �׷��ִ� ���̳�
	//	//vecOut.push_back(vec[g_aCubeIndex[i]]);
	//	vecOut.push_back(texture_test[g_aCubeIndex[i]]);
	//}

	//�� �ڵ�
	vector<D3DXVECTOR2> vecUV4Vertex;
	MakeUVList(vecUV4Vertex, uv);

	for (int i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		vecOut.push_back(VERTEX_PT(vecVertex[g_aCubeIndex[i]], vecUV4Vertex[i]));
	}
}

void CubemanParts::SetMovingState(bool isMoving)
{
	//���� ���¶� ���� ���̶� ������ �Ű� ������
	if (m_isMoving == isMoving) return;

	m_isMoving = isMoving;
	if (m_isMoving == false)
	{
		m_rotXAngle = 0;
	}
	for (auto child : m_vecPChild)
	{
		//child�� ���÷��� ������Ʈ�� ����� �޾ƿ����ϱ�, ���ϵ��� �ڷ����� ���÷��̿�����Ʈ�ε�, 
		//ť��� ���� �ڷ������� ĳ�����ؼ� �Լ� �����.
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

