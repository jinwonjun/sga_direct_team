#include "stdafx.h"
#include "Heap.h"
#include "AStarNode.h"

Heap::Heap()
{
}

Heap::~Heap()
{
}

void Heap::Insert(AStarNode * pNode)
{
	//마지막에 새 노드 추가
	//부모와 비교해가며 작을 때 스왑하기
	m_vecNode.push_back(pNode);
	Upheap(m_vecNode.size()-1);
	
}

AStarNode * Heap::ExtractMin()
{
	//루트를 추출, 제일 마지막 노드를 루트 자리로 올린 후에 자식 보다 큰 값이면 스왑
	if (m_vecNode.empty())return NULL;//비어있으면 null값 리턴
	AStarNode * minFNode = m_vecNode.front();
	Swap(0, m_vecNode.size() - 1);

	m_vecNode.pop_back();
	DownHeap(0);



	return minFNode;
}

void Heap::Clear()
{
	m_vecNode.clear();
}

void Heap::Upheap(int targetIdx)
{
	if (targetIdx == 0)return;//루트면 진행 못함
	int parentIdx = (targetIdx - 1) / 2;

	if (m_vecNode[parentIdx]->m_f > m_vecNode[targetIdx]->m_f)
	{
		Swap(targetIdx, parentIdx);//마지막에 있던에가 부모 인덱스 갖고 있을 거니까
		Upheap(parentIdx);//부모보다 크거나 0이 될때까지 비교돌리기, 재귀 호출하기 전에 빠져나가는 부분이 있어야함.
	}

}

void Heap::DownHeap(int targetIdx)
{
	int LChildIdx = targetIdx * 2 + 1;
	if (LChildIdx >= m_vecNode.size()) return;
	
	int minChildIdx = LChildIdx;
	int RChildIdx = LChildIdx + 1;

	//2개의 child중 더 작은 쪽을 찾는다.
	if (RChildIdx < m_vecNode.size())
	{
		if (m_vecNode[RChildIdx]->m_f < m_vecNode[LChildIdx]->m_f)
		{
			minChildIdx = RChildIdx;
		}
	}
	//target값이 더 크면 해당 child와 swap하기
	if (m_vecNode[targetIdx]->m_f > m_vecNode[minChildIdx]->m_f)
	{
		Swap(targetIdx, minChildIdx);
		DownHeap(minChildIdx);
	}
}

void Heap::Swap(int idx1, int idx2)
{
	AStarNode * pTemp = m_vecNode[idx2];
	m_vecNode[idx2] = m_vecNode[idx1];
	m_vecNode[idx1] = pTemp;
}