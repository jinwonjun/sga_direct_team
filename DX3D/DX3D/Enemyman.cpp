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
	//키값을 눌렀을 때 그에 따른 변화 값을 주자
	//if (m_isMoving)

	m_rotXAngle += m_rotXSpeed;

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

	D3DXMatrixRotationX(&matR, m_rotXAngle);

	if (m_pos.z > m_CharPos.z) m_pos.z -= 0.1f;
	else m_pos.z += 0.1f;
	if (m_pos.x > m_CharPos.x) m_pos.x -= 0.1f;
	else m_pos.x += 0.1f;

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

//vector<VERTEX_PT>& vecOut <--이거 원래 VERTEX_PC 였음
void Enemyman::SetPTVertex(vector<VERTEX_PT>& vecOut, vector<D3DXVECTOR3>& vecVertex, vector<vector<int>>& uv)
{
	//쌤 코드
	vector<D3DXVECTOR2> vecUV4Vertex;
	MakeUVList(vecUV4Vertex, uv);

	for (int i = 0; i < CUBE_INDEX_SIZE; i++)
	{
		vecOut.push_back(VERTEX_PT(vecVertex[g_aCubeIndex[i]], vecUV4Vertex[i]));
	}
}
//적이 나를 향해 걸어오게 해보자
void Enemyman::SetMovingState(bool isMoving)
{
	//현재 상태랑 들어온 값이랑 같으면 신경 ㄴㄴ해
	
	if (m_isMoving == isMoving) return;
	m_isMoving = isMoving;
	m_rotXAngle = 0;
	for (auto child : m_vecPChild)
	{
		//child는 디스플레이 오브젝트에 상속을 받아왔으니까, 차일드의 자료형은 디스플레이오브젝트인데, 
		//큐브맨 파츠 자료형으로 캐스팅해서 함수 사용함.
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