#pragma once
#include "IDisplayObject.h"

class AStar;

class IMap : public IDisplayObject
{
protected:
	vector<D3DXVECTOR3>	m_vecVertex;
	size_t				m_numTile;
	size_t				m_dimension;
	D3DXVECTOR3			m_size;
	D3DXVECTOR3			m_scale;

	AStar * m_pAStar;

	//매쉬 포인터 변수랑 값 저장할 벡터
	LPD3DXMESH m_pMeshMap;
	vector<MTLTEX * > m_vecMtlTex;

	vector<D3DXVECTOR3>	m_surfaceVertices;

	CString			m_filepath;
	CString			m_mapFilename;
	CString			m_surfaceFilename;

	IMap() { m_pAStar = NULL; }

public:
	virtual ~IMap() {}
	virtual bool GetHeight(OUT float & height, const D3DXVECTOR3 & pos) = 0;
	virtual bool CalcPickedPosition(D3DXVECTOR3 &vOut,WORD screenX, WORD screenY) = 0;

	const vector<D3DXVECTOR3>& GetVertex() { return m_vecVertex; }
	void SetDimension(size_t dimension)
	{
		m_dimension = dimension; m_numTile = m_dimension - 1;
	}
	const D3DXVECTOR3& GetSize() { return m_size; }

	AStar * GetAstar() { return m_pAStar; }//맵에다가 노드를 먼저 깔아보자

	void SetFilename(LPCTSTR filepath, LPCTSTR mapFilename, LPCTSTR surfaceFilename) {
		m_filepath = filepath; m_mapFilename = mapFilename; m_surfaceFilename = surfaceFilename;
	}

};