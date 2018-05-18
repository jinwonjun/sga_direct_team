#pragma once
#include "BaseObject.h"

struct EDGE_INFO
{
	//�� ��尡 ���� ���� ���� ��忡 ���� ���� ǥ��
	//������尡 �̳���� �ε����� cost�� ���� �ִµ�, ����� ���Ϳ��� �ε����� �����ؼ� �׶��� ��� F���� ����������
	int index;//�ش� ����� �ε���
	float edgeCost;//�� ������ G���� ��, ������忡�� �������� ���� ����� ��Ÿ��
};

enum NODE_STATE
{
	STATE_NONE,//���� �ƹ��͵� ����
	STATE_OPEN,//�������
	STATE_CLOSE,//��������
	STATE_USING,//���� ����� ���(�� ǥ�� �Ҷ� ��Գ���)
	STATE_WALL //������ ����
};

class AStarNode  : public BaseObject
{
public:
	D3DXVECTOR3 m_location;
	int m_index;
	NODE_STATE m_nodeState;
	float m_g;
	float m_h;
	float m_f;
	int m_via;//�� ���� ����� �ε����� ������ �����ص�

	vector<EDGE_INFO * > m_vecEdgeInfo;
	vector<D3DXVECTOR3> m_vecLine;//���� ��� ���̸� ������ �������ֱ� ���� �����ֱ�� ����
	AStarNode(D3DXVECTOR3 location, int index);

	virtual ~AStarNode();
	void SetValues(NODE_STATE _nodeState, float _g, float _h, float _f, int _via);
	void AddEdge(AStarNode * pNode);//edgeCost�� ����ؼ� ���Ϳ� �־�����.
	const D3DXVECTOR3 & GetLocation() { return m_location; }
	const vector<D3DXVECTOR3> & GetVecLines() { return m_vecLine; }
	const vector<EDGE_INFO * > & GetEdgeInfos() { return m_vecEdgeInfo; }
};

