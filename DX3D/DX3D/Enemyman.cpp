#include "stdafx.h"
#include "Enemyman.h"


Enemyman::Enemyman(float rotXSpeed)
{
	m_rotXSpeed = rotXSpeed;
}

Enemyman::~Enemyman()
{
}

void Enemyman::Init(D3DXMATRIXA16* pMat, vector<vector<int>> &vecUV)
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
			D3DXVec3TransformCoord(&vecVertex[i],
				&vecVertex[i], pMat);
		}
	}
	D3DXCreateTextureFromFile(g_pDevice, _T("resources/textures/spiderman.png"), &tex);
	SetPTVertex(m_vecPTVertex, vecVertex, vecUV);
}

void Enemyman::Init()
{
}

void Enemyman::Update()
{
	D3DXMATRIXA16 matR, matT;
	//Ű���� ������ �� �׿� ���� ��ȭ ���� ����
	//if (m_isMoving)

	m_rotXAngle += m_rotXSpeed;

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

	D3DXMatrixRotationX(&matR, m_rotXAngle);

	if (m_pos.z > m_CharPos.z) m_pos.z -= 0.1f;
	else m_pos.z += 0.1f;
	if (m_pos.x > m_CharPos.x) m_pos.x -= 0.1f;
	else m_pos.x += 0.1f;

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
void Enemyman::Render()
{
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
void Enemyman::SetPTVertex(vector<VERTEX_PT>& vecOut, vector<D3DXVECTOR3>& vecVertex, vector<vector<int>>& uv)
{
	//�� �ڵ�
	vector<D3DXVECTOR2> vecUV4Vertex;
	MakeUVList(vecUV4Vertex, uv);

	for (int i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		vecOut.push_back(VERTEX_PT(vecVertex[g_aCubeIndex[i]], vecUV4Vertex[i]));
	}
}
//���� ���� ���� �ɾ���� �غ���
void Enemyman::SetMovingState(bool isMoving)
{
	//���� ���¶� ���� ���̶� ������ �Ű� ������
	
	if (m_isMoving == isMoving) return;
	m_isMoving = isMoving;
	m_rotXAngle = 0;
	for (auto child : m_vecPChild)
	{
		//child�� ���÷��� ������Ʈ�� ����� �޾ƿ����ϱ�, ���ϵ��� �ڷ����� ���÷��̿�����Ʈ�ε�, 
		//ť��� ���� �ڷ������� ĳ�����ؼ� �Լ� �����.
		static_cast <Enemyman *> (child)->SetMovingState(m_isMoving);
	}
}

void Enemyman::MakeUVList(vector<D3DXVECTOR2>& out, vector<vector<int>>& uv)
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