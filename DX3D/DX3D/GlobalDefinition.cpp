#include "stdafx.h"
#include "GlobalDefinition.h"

WORD g_aCubeIndex[36] = {
	0, 1, 2, 0, 2, 3,	// 후
	7, 6, 5, 7, 5, 4,	// 전
	4, 5, 1, 4, 1, 0,	// 좌
	3, 2, 6, 3, 6, 7,	// 우
	1, 5, 6, 1, 6, 2,	// 상
	4, 0, 3, 4, 3, 7	// 하
};

D3DXVECTOR3 g_aCubeVertex[8] = {
	D3DXVECTOR3(-1.0f, -1.0f, -1.0f),
	D3DXVECTOR3(-1.0f,  1.0f, -1.0f),
	D3DXVECTOR3(1.0f,  1.0f, -1.0f),
	D3DXVECTOR3(1.0f, -1.0f, -1.0f),
	D3DXVECTOR3(-1.0f, -1.0f,  1.0f),
	D3DXVECTOR3(-1.0f,  1.0f,  1.0f),
	D3DXVECTOR3(1.0f,  1.0f,  1.0f),
	D3DXVECTOR3(1.0f, -1.0f,  1.0f)
};

DWORD FtoDw(float f)
{
	return *((DWORD*)&f);
}

float GetRandomFloat(float lowBound, float highBound)
{
	//0~1 까지 클램프(잘라주기)하는 작업
	float f = (rand() % 10000) * 0.0001f;

	return (f*(highBound - lowBound)) + lowBound;
}

int GetRandomInt(int maxNum)
{
	int a;
	
	a = (rand() % maxNum);
	

	return a+1;

}