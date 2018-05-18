#pragma once
#include "IDisplayObject.h"
class CubemanParts :
	public IDisplayObject
{
private:
	//기존 버텍스 기준
	//vector<VERTEX_PC> m_vecPCVertex;

	vector <VERTEX_PT> m_vecPTVertex;
	
	//팔다리니까 X축만 관여하면 되겠지?
	bool m_isMoving;
	float m_rotXAngle;
	float m_rotXSpeed;

	LPDIRECT3DTEXTURE9 tex;//텍스쳐 한번 씌워보자

public:
	CubemanParts(float rotXSpeed = 0.0f);
	~CubemanParts();

	// IDisplayObject을(를) 통해 상속됨
	//구현만 하고 안쓸거임. 근데 왜 가상함수 했냐면 선언을 안해놓으면 아래 인잇을 써먹을 수가 없어서!
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	//void Init(D3DXMATRIXA16 * pMat);
	//기존 버텍스 돌리는용도
	//void SetPCVertex(vector<VERTEX_PC> & vecOut, vector<D3DXVECTOR3> & vecVertex);
	//수정 전
	//void SetPTVertex(vector<VERTEX_PT> & vecOut, vector<D3DXVECTOR3> & vecVertex);
	//void SetMovingState(bool isMoving);

	void Init(D3DXMATRIXA16* pMat, vector<vector<int>> &vecUV);
	//void SetPCVertex(vector<VERTEX_PC> &vecOut,vector<D3DXVECTOR3> &vecVertex);
	void SetPTVertex(vector<VERTEX_PT> &vecOut,vector<D3DXVECTOR3> &vecVertex, vector<vector<int>> &uv);
	void SetMovingState(bool isMoving);
	void MakeUVList(vector<D3DXVECTOR2> &out,vector<vector<int>> &uv);
};

