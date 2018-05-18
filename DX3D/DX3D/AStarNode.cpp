#include "stdafx.h"
#include "AStarNode.h"

AStarNode::AStarNode(D3DXVECTOR3 location, int index)
{
	m_location = location;
	m_index = index;

	SetValues(STATE_NONE, 0, 0, 0, 0);
}

AStarNode::~AStarNode()
{

}

void AStarNode::SetValues(NODE_STATE _nodeState, float _g, float _h, float _f, int _via)
{
	m_nodeState = _nodeState;
	m_g = _g;
	m_h = _h;
	m_f = _f;
	m_via = _via;
}

void AStarNode::AddEdge(AStarNode * pNode)
{
	EDGE_INFO * edgeInfo = new EDGE_INFO;
	edgeInfo->index = pNode->m_index;
	edgeInfo->edgeCost = D3DXVec3Length(&(m_location - pNode->m_location));//해당 노드와 pNode의 코스트 삽입
	
	m_vecEdgeInfo.push_back(edgeInfo);//노드를 넣어주면 자신의 벡터라고 인접정보를 갖고 있는 상태가 되겠지?
	
	m_vecLine.push_back(this->m_location);
	m_vecLine.push_back(pNode->m_location);
}
