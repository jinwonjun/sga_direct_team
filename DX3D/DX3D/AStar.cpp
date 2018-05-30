#include "stdafx.h"
#include "AStar.h"
#include "AStarNode.h"
#include "Ray.h"
#include "Heap.h"

AStar::AStar()
{
}

AStar::~AStar()
{
	SAFE_DELETE(m_pOpenNodeHeap);
	SAFE_RELEASE(m_pSphere);

	for (auto p : m_vecNode)
		SAFE_RELEASE(p);
}

void AStar::Init()
{
	D3DXCreateSphere(g_pDevice, 0.2f, 10, 10, &m_pSphere, NULL);
	m_pOpenNodeHeap = new Heap;
}

void AStar::Render()
{
	D3DXMATRIXA16 mat;

	g_pDevice->SetTexture(0, NULL);

	for (auto p : m_vecNode)
	{
		switch (p->m_nodeState)
		{
		case STATE_NONE:
			g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
			break;
		case STATE_OPEN:
			g_pDevice->SetMaterial(&DXUtil::GREEN_MTRL);
			break;
		case STATE_CLOSE:
			g_pDevice->SetMaterial(&DXUtil::RED_MTRL);
			break;
		case STATE_USING:
			g_pDevice->SetMaterial(&DXUtil::YELLOW_MTRL);
			break;
		case STATE_WALL:
			g_pDevice->SetMaterial(&DXUtil::BLUE_MTRL);
			break;
		}

		D3DXMatrixTranslation(&mat, p->GetLocation().x, p->GetLocation().y,
			p->GetLocation().z);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		m_pSphere->DrawSubset(0);

		D3DXMatrixIdentity(&mat);
		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST,
			p->GetVecLines().size() / 2, p->GetVecLines()[0], sizeof(D3DXVECTOR3));
	}
}

void AStar::InitNodes(IMap * pMap)
{
	int nodeDim = 30;
	float interval = pMap->GetSize().x / (float)(nodeDim - 0.99);

	for (int posZ = 0; posZ < nodeDim; posZ++)
	{
		for (int posX = 0; posX < nodeDim; posX++)
		{
			D3DXVECTOR3 location(posX * interval, 0, posZ * interval);
			pMap->GetHeight(location.y, location);

			AStarNode* pNode = new AStarNode(location, m_vecNode.size());
			m_vecNode.push_back(pNode);

			//장애물
			if (posX == 5 && posZ < 5)
			{
				pNode->m_nodeState = STATE_WALL;
			}
		}
	}

	for (size_t i = 0; i < m_vecNode.size(); i++)
	{
		//제일 우측 열을 제외하고 자신의 우측 노드와 서로 Edge 등록
		if (i % nodeDim != nodeDim - 1)
		{
			m_vecNode[i]->AddEdge(m_vecNode[i + 1]);
			m_vecNode[i + 1]->AddEdge(m_vecNode[i]);
		}
		//제일 윗 횡을 제외하고 자신의 윗 노드와 서로 Edge 등록
		if (i < m_vecNode.size() - nodeDim)
		{
			m_vecNode[i]->AddEdge(m_vecNode[i + nodeDim]);
			m_vecNode[i + nodeDim]->AddEdge(m_vecNode[i]);
		}
	}
}

void AStar::FindPath(D3DXVECTOR3 startPos, D3DXVECTOR3 destPos, OUT vector<int>& vecIndex)
{
	RestNode();

	int startNodeIdx = FindClosestNode(startPos);
	int destNodeIdx = FindClosestNode(destPos);

	//노드가 없으면 종료
	if (startNodeIdx == -1 || destNodeIdx == -1)
		return;

	//출발 노드 초기화 하고 오픈 상태로 만듬
	float g = 0.f;
	float h = GetManHattanDistance(startNodeIdx, destNodeIdx);
	float f = g + h;

	m_vecNode[startNodeIdx]->SetValues(STATE_OPEN, g, h, f, startNodeIdx);
	//m_pOpenNodeList.push_back(m_vecNode[startNodeIdx]);

	m_pOpenNodeHeap->Insert(m_vecNode[startNodeIdx]);

	//목적지 노드가 클로즈 될때까지 확장, 확장 완료한 노드는 닫힘
	while (m_vecNode[destNodeIdx]->m_nodeState != STATE_CLOSE)
	{
		int currIndex = GetMinFNodeIndex();
		if (currIndex == -1) return;
		Extend(currIndex, destNodeIdx);
		m_vecNode[currIndex]->m_nodeState = STATE_CLOSE;
	}

	//목적지 노드부터 출발지 노드 이전까지 경유 노드들의 인덱스를 Path목록에 추가
	//목록에 추가한 노드들은 사용 상태로 만든다.
	int currIndex = destNodeIdx;
	while (currIndex != startNodeIdx)
	{
		m_vecNode[currIndex]->m_nodeState = STATE_USING;
		vecIndex.push_back(currIndex);
		//m_via는 자기 이전노드의 인덱스
		currIndex = m_vecNode[currIndex]->m_via;
	}
	//출발지 노드의 인덱스도 Path목록에 추가하고 사용상태로
	m_vecNode[currIndex]->m_nodeState = STATE_USING;
	vecIndex.push_back(currIndex);

	//목적지->경유지...->출발지 인덱스 목록 완성
	//m_pOpenNodeList.clear();
	m_pOpenNodeHeap->Clear();
}

void AStar::RestNode()
{
	for (int i = 0; i < m_vecNode.size(); i++)
	{
		if (m_vecNode[i]->m_nodeState != STATE_WALL)
			m_vecNode[i]->m_nodeState = STATE_NONE;
	}
}

int AStar::FindClosestNode(const D3DXVECTOR3 & pos)
{
	//노드 돌면서 현재 포지션이랑 가장 가까운 노드 찾는거
	float minDist = FLT_MAX;
	//못찾으면 -1리턴
	int closestNodeIndex = -1;

	for (int i = 0; i < m_vecNode.size(); i++)
	{
		if (m_vecNode[i]->m_nodeState == STATE_WALL)
			continue;

		D3DXVECTOR3 subtract = pos - m_vecNode[i]->GetLocation();

		float dist = D3DXVec3Length(&subtract);
		if (dist < minDist)
		{
			minDist = dist;
			closestNodeIndex = i;
		}
	}

	return closestNodeIndex;
}

float AStar::GetManHattanDistance(int from, int to)
{
	float offsetX = fabs(m_vecNode[from]->GetLocation().x - m_vecNode[to]->GetLocation().x);
	float offsetZ = fabs(m_vecNode[from]->GetLocation().z - m_vecNode[to]->GetLocation().z);

	return offsetX + offsetZ;
}

int AStar::GetMinFNodeIndex()
{
	//오픈 노드중 f값이 가장 작은거 찾을

	AStarNode* node = NULL;
	float minValue = FLT_MAX;

	//for (auto p : m_pOpenNodeList)
	//{
	//	if (p->m_f < minValue)
	//	{
	//		minValue = p->m_f;
	//		node = p;
	//	}
	//}
	//if (node == NULL) return -1;
	//m_pOpenNodeList.remove(node);

	node = m_pOpenNodeHeap->ExtractMin();
	if (node == NULL) return -1;



	return node->m_index;
}

void AStar::Extend(int targetIdx, int destIdx)
{
	//targetIdx이 시작지점 
	vector<EDGE_INFO*> vecEdge = m_vecNode[targetIdx]->GetEdgeInfos();

	for (int i = 0; i < vecEdge.size(); i++)
	{
		int index = vecEdge[i]->index;
		//엣지노드에서 받아서 처음 참조하는 노드가 어떤앤지??
		AStarNode* currNode = m_vecNode[index];

		//같은 노드이거나 장애물일시 추가X
		if (currNode->m_nodeState == STATE_CLOSE) continue;
		if (currNode->m_nodeState == STATE_WALL) continue;

		//시작점에서 현재 노드까지 필요한 비용
		float G = m_vecNode[targetIdx]->m_g + vecEdge[i]->edgeCost;
		//현재부터 목적지 까지 필요한 비용의 추정값
		float H = GetManHattanDistance(index, destIdx);

		float F = G + H;

		if (currNode->m_nodeState == STATE_OPEN &&
			G >= currNode->m_g) continue;

		currNode->SetValues(STATE_OPEN, G, H, F, targetIdx);
		//m_pOpenNodeList.push_back(currNode);
		m_pOpenNodeHeap->Insert(currNode);
	}
}

void AStar::MakeDirectPath(const D3DXVECTOR3 & startPos, const D3DXVECTOR3 & destPos, OUT vector<int>& vecIndex)
{
	if (m_vecObstacle.empty())
	{
		//장애물 없으면 직선이동
		vecIndex.clear();
	}
	else
	{
		int numNodeToErase = 0;
		//시작지점부터 장애물 교차 이전 지점까지 노드 삭제
		CalcEraseCount(startPos, vecIndex, true, numNodeToErase);

		if (numNodeToErase > 0)
			vecIndex.erase(vecIndex.end() - numNodeToErase, vecIndex.end());

		//마지막지점부터 장애물 교차 이전 지점까지 노드 삭제
		CalcEraseCount(destPos, vecIndex, false, numNodeToErase);
		if (numNodeToErase == vecIndex.size()) numNodeToErase--;
		if (numNodeToErase > 0)
			vecIndex.erase(vecIndex.begin(), vecIndex.begin() + numNodeToErase);
	}
}

void AStar::CalcEraseCount(const D3DXVECTOR3 & pos, const vector<int>& vecIndex, bool bByStartPos, OUT int & numEraseNode)
{
	numEraseNode = 0;

	Ray ray;
	ray.m_pos = pos;
	ray.m_pos.y += 0.3f; //너무 바닥이라 안될수도있으니 띄우기

	for (size_t index = 0; index < vecIndex.size(); index++)
	{
		if (bByStartPos = true)
		{
			//마지막 위치에서 내 위치 빼줌
			ray.m_dir = m_vecNode[vecIndex[vecIndex.size() - 1 - index]]
				->GetLocation() - pos;
		}
		else
		{
			ray.m_dir = m_vecNode[vecIndex[index]]->GetLocation() - pos;
		}

		//현재 위치에서 노드의 위치 까지의 거리
		float nodeDist = D3DXVec3Length(&ray.m_dir);
		D3DXVec3Normalize(&ray.m_dir, &ray.m_dir);

		float intersectionDist;
		bool isIntersected = false;

		for (size_t i = 0; i < m_vecObstacle.size(); i += 3)
		{
			if (ray.CalcIntersectTri(&m_vecObstacle[i], &intersectionDist))
			{
				//충돌한 거리가 현재 노드까지의 거리보다 짧을때
				if (intersectionDist < nodeDist)
				{
					isIntersected = true;
					break;
				}
			}
		}//for

		if (isIntersected == true)
		{
			numEraseNode--;
			break;
		}
		else
		{
			numEraseNode++;
		}
	}

}
