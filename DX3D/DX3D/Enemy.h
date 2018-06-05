#pragma once

#include "IDisplayObject.h"
#include "BoundingBox.h"

class BoundingBox;
class Enemy : public IDisplayObject
{
private :
	friend class EnemyManager;

	vector<VERTEX_PC>		m_vecVertex;
	vector<WORD>			m_vecIndex;
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	D3DVERTEXBUFFER_DESC	m_VBDesc;
	D3DINDEXBUFFER_DESC		m_IBDesc;

	D3DXVECTOR3				m_forward;
	
	float					m_moveSpeed;
	float					m_rotationSpeed;
	float					m_maxStepHeight;

	D3DXVECTOR3				m_destPos;
	D3DXVECTOR3				m_finalDestPos;
	vector<int>				m_vecAStarIndex;

	bool					m_moving;

	BoundingBox*			m_pBox;

	BoundingSphere*			m_pBounidngSphere;
	LPD3DXMESH				m_pSphere;
public:
	Enemy(D3DXVECTOR3& pos);
	virtual ~Enemy();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void InitVertex();
	void SetVertex(vector<VERTEX_PC> &vecVertexOut,	vector<WORD> &vecIndexOut, vector<D3DXVECTOR3> vecPos);
	void SetBuffer(LPDIRECT3DVERTEXBUFFER9 &pVb, LPDIRECT3DINDEXBUFFER9 &pIb, vector<VERTEX_PC> &vecVertex, vector<WORD> &vecIndex);

	void UpdatePosition();
	void SetDestPos(D3DXVECTOR3& pos);
	void MoveStop();

	BoundingBox*	GetBoundingBox() { return m_pBox; }
	BoundingSphere*	GetSphere() { return m_pBounidngSphere; }
};

