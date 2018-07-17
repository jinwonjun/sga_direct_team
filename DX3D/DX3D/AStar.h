#pragma once
#include "BaseObject.h"

class AStarNode;
class Heap;

class AStar :public BaseObject
{
private:
	vector<AStarNode * > m_vecNode;
	list<AStarNode * > m_pOpenNodeList;

	Heap * m_pOpenNodeHeap;//리스트를 힙으로 교체하기

	LPD3DXMESH m_pSphere;//로케이션마다 구체 그려주기
	vector<D3DXVECTOR3> m_vecObstacle;//장애물 그려주기용 포지션

	void RestNode();
	int FindClosestNode(const D3DXVECTOR3 & pos);
	float GetManHattanDistance(int from, int to);
	int GetMinFNodeIndex();
	void Extend(int targetIdx, int destIdx);
	void CalcEraseCount(const D3DXVECTOR3& pos,const vector<int>&vecIndex, bool bByStartPos,OUT int &numEraseNode);
public:
	AStar();
	virtual ~AStar();

	void Init();
	void Render();//노드들 색변화와 선 그려주는걸 여기서 하자
	void InitNodes(IMap * pMap);//맵을 호출해서, 크기에 맞게 노드를 세팅해주자
	const vector<AStarNode *> &GetNodes() { return m_vecNode; }
	void SetObstacle(const vector<D3DXVECTOR3> & vecObstacle)
	{
		m_vecObstacle = vecObstacle;
	}
	void FindPath(D3DXVECTOR3 startPos, D3DXVECTOR3 destPos, OUT vector<int> & vecIndex);//시작위치와 목적위치 넘겨줘서 따라가야될 인덱스의 목록을 넣어주자
	//파인드패스로 받은 인덱스 찾고 받아와서 옵스타클이랑 비교해서 찾는거
	void MakeDirectPath(const D3DXVECTOR3 &startPos,const D3DXVECTOR3 &destPos, OUT vector<int> &vecIndex);
};

