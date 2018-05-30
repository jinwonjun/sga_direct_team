#pragma once
#include "BaseObject.h"

struct EDGE_INFO
{
	//각 노드가 갖고 있을 인접 노드에 대한 정보 표시
	//인접노드가 이놈들의 인덱스와 cost를 갖고 있는데, 노드의 벡터에서 인덱스를 참조해서 그때의 노드 F값을 가져오게함
	int index;//해당 노드의 인덱스
	float edgeCost;//이 변수가 G값이 됨, 원본노드에서 인접노드로 가는 비용을 나타냄
};

enum NODE_STATE
{
	STATE_NONE,//아직 아무것도 안함
	STATE_OPEN,//개방상태
	STATE_CLOSE,//닫힘상태
	STATE_USING,//내가 사용할 목록(길 표시 할때 써먹나봄)
	STATE_WALL //못가는 영역
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
	int m_via;//내 이전 노드의 인덱스가 뭔지를 저장해둠

	vector<EDGE_INFO * > m_vecEdgeInfo;
	vector<D3DXVECTOR3> m_vecLine;//노드와 노드 사이를 선으로 연결해주기 위한 보여주기용 변수
	AStarNode(D3DXVECTOR3 location, int index);

	virtual ~AStarNode();
	void SetValues(NODE_STATE _nodeState, float _g, float _h, float _f, int _via);
	void AddEdge(AStarNode * pNode);//edgeCost를 계산해서 벡터에 넣어주자.
	const D3DXVECTOR3 & GetLocation() { return m_location; }
	const vector<D3DXVECTOR3> & GetVecLines() { return m_vecLine; }
	const vector<EDGE_INFO * > & GetEdgeInfos() { return m_vecEdgeInfo; }
};

