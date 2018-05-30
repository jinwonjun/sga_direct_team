#pragma once
#include "BaseObject.h"

class AStarNode;
class Heap;

class AStar :public BaseObject
{
private:
	vector<AStarNode * > m_vecNode;
	list<AStarNode * > m_pOpenNodeList;

	Heap * m_pOpenNodeHeap;//����Ʈ�� ������ ��ü�ϱ�

	LPD3DXMESH m_pSphere;//�����̼Ǹ��� ��ü �׷��ֱ�
	vector<D3DXVECTOR3> m_vecObstacle;//��ֹ� �׷��ֱ�� ������

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
	void Render();//���� ����ȭ�� �� �׷��ִ°� ���⼭ ����
	void InitNodes(IMap * pMap);//���� ȣ���ؼ�, ũ�⿡ �°� ��带 ����������
	const vector<AStarNode *> &GetNodes() { return m_vecNode; }
	void SetObstacle(const vector<D3DXVECTOR3> & vecObstacle)
	{
		m_vecObstacle = vecObstacle;
	}
	void FindPath(D3DXVECTOR3 startPos, D3DXVECTOR3 destPos, OUT vector<int> & vecIndex);//������ġ�� ������ġ �Ѱ��༭ ���󰡾ߵ� �ε����� ����� �־�����
	//���ε��н��� ���� �ε��� ã�� �޾ƿͼ� �ɽ�ŸŬ�̶� ���ؼ� ã�°�
	void MakeDirectPath(const D3DXVECTOR3 &startPos,const D3DXVECTOR3 &destPos, OUT vector<int> &vecIndex);
};

