#pragma once

class AStarNode;


class Heap
{
private :
	void Upheap(int targetIdx);//삽입 하면 가장 마지막에 들어가니까 하나하나  올려줌
	void DownHeap(int targetIdx);//자식이랑 비교해서 크면 내려보내기
	void Swap(int idx1, int idx2);//부모자식 교환할때 스왑시키기

public:

	vector<AStarNode * > m_vecNode;

	Heap();
	~Heap();
	
	void Insert(AStarNode * pNode);
	AStarNode* ExtractMin();//가장 작은 애를 추출해줌
	void Clear();//리스트 비우기
};
