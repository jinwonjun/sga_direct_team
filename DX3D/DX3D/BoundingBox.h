#pragma once
#include "IDisplayObject.h"
class BoundingBox : public IDisplayObject
{
private :
	//AABB
	vector<VERTEX_PC>		m_vecVertex;
	vector<WORD>			m_vecIndex;
	
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	D3DVERTEXBUFFER_DESC	m_VBDesc;
	D3DINDEXBUFFER_DESC		m_IBDesc;

	D3DXVECTOR3				m_minPos;
	D3DXVECTOR3				m_maxPos;
	D3DXVECTOR3				m_oriPos;	//updatePos

	D3DXVECTOR3				m_size;
public:
	BoundingBox(D3DXVECTOR3 size);
	~BoundingBox();

	D3DXVECTOR3	GetMinPos()
	{
		return D3DXVECTOR3(
			m_oriPos.x + m_minPos.x * m_size.x,
			m_oriPos.y + m_minPos.y * m_size.y,
			m_oriPos.z + m_minPos.z * m_size.z);
	}

	D3DXVECTOR3 GetMaxPos()
	{
		return D3DXVECTOR3(
			m_oriPos.x + m_maxPos.x * m_size.x,
			m_oriPos.y + m_maxPos.y * m_size.y,
			m_oriPos.z + m_maxPos.z * m_size.z);
	}

	bool IsIntersected(BoundingBox &box)
	{
		//최솟값이 최댓값보다 크거나, 최댓값이 최솟값보다 작으면 충돌하지않는 상태!
		if (GetMinPos().x > box.GetMaxPos().x ||
		GetMaxPos().x < box.GetMinPos().x) return false;
		if (GetMinPos().y > box.GetMaxPos().y ||
		GetMaxPos().y < box.GetMinPos().y) return false;
		if (GetMinPos().z > box.GetMaxPos().z ||
		GetMaxPos().z < box.GetMinPos().z) return false;

		return true;
	}
	
	void InitVertex();
	void SetVertex(vector<VERTEX_PC> &vecVertexOut, vector<WORD> &vecIndexOut, vector<D3DXVECTOR3> vecPos);
	//vertex 저장배열, index 저장배열, 사용할 posision 배열(정점8개좌표)
	void SetBuffer(LPDIRECT3DVERTEXBUFFER9 &pVb, LPDIRECT3DINDEXBUFFER9 &pIb,
		vector<VERTEX_PC> &vecVertex, vector<WORD> &vecIndex);

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

