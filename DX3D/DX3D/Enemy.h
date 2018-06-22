#pragma once

#include "IUnitObject.h"
#include "BoundingBox.h"

class BoundingBox;
class ObjLoader;
class DrawingGroup;

class Enemy : public IUnitObject
{
private :
	friend class EnemyManager;

	vector<VERTEX_PC>		m_vecVertex;
	vector<WORD>			m_vecIndex;
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	D3DVERTEXBUFFER_DESC	m_VBDesc;
	D3DINDEXBUFFER_DESC		m_IBDesc;

	BoundingBox*			m_pBox;

	BoundingSphere*			m_pBounidngSphere;
	LPD3DXMESH				m_pSphere;

	vector<DrawingGroup * > m_vecDrawingGroup;

	int					m_HP;
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
	void MinusHP() { m_HP--; }

	BoundingBox*	GetBoundingBox() { return m_pBox; }
	BoundingSphere*	GetSphere() { return m_pBounidngSphere; }
};

