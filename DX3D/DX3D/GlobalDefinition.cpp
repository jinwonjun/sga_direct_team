#include "stdafx.h"
#include "GlobalDefinition.h"

WORD g_aCubeIndex[36] = {
	0, 1, 2, 0, 2, 3,	// ��
	7, 6, 5, 7, 5, 4,	// ��
	4, 5, 1, 4, 1, 0,	// ��
	3, 2, 6, 3, 6, 7,	// ��
	1, 5, 6, 1, 6, 2,	// ��
	4, 0, 3, 4, 3, 7	// ��
};

D3DXVECTOR3 g_aCubeVertex[8] = {
	D3DXVECTOR3(-1.0f, -1.0f, -1.0f),//0
	D3DXVECTOR3(-1.0f,  1.0f, -1.0f),//1
	D3DXVECTOR3(1.0f,  1.0f, -1.0f),//2
	D3DXVECTOR3(1.0f, -1.0f, -1.0f),//3
	D3DXVECTOR3(-1.0f, -1.0f,  1.0f),//4
	D3DXVECTOR3(-1.0f,  1.0f,  1.0f),//5
	D3DXVECTOR3(1.0f,  1.0f,  1.0f),//6
	D3DXVECTOR3(1.0f, -1.0f,  1.0f)//7
};

DWORD FtoDw(float f)
{
	return *((DWORD*)&f);
}

float GetRandomFloat(float lowBound, float highBound)
{
	//0~1 ���� Ŭ����(�߶��ֱ�)�ϴ� �۾�
	float f = (rand() % 10000) * 0.0001f;

	return (f*(highBound - lowBound)) + lowBound;
}