#pragma once

class AStarNode;


class Heap
{
private :
	void Upheap(int targetIdx);//���� �ϸ� ���� �������� ���ϱ� �ϳ��ϳ�  �÷���
	void DownHeap(int targetIdx);//�ڽ��̶� ���ؼ� ũ�� ����������
	void Swap(int idx1, int idx2);//�θ��ڽ� ��ȯ�Ҷ� ���ҽ�Ű��

public:

	vector<AStarNode * > m_vecNode;

	Heap();
	~Heap();
	
	void Insert(AStarNode * pNode);
	AStarNode* ExtractMin();//���� ���� �ָ� ��������
	void Clear();//����Ʈ ����
};
