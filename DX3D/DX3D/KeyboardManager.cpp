#include "stdafx.h"
#include "KeyboardManager.h"


KeyboardManager::KeyboardManager()
{
}


KeyboardManager::~KeyboardManager()
{
}

void KeyboardManager::Update()
{
	UpdateMoving();
}
/*
자신의 현재 pos rot 변수가 아닌 deltaPos deltaRot 변수 추가 후에 이 변수를 keyboardManager->setTarget 에 적용하기
delta 값이 0 이 아니면 이동 및 회전 적용하기

키매니저 설명 및 동작 원리
어플리케이션 인잇 부분에서 씬매니저 호출
어플리케이션 업뎃 부분에서 키보드 매니저 업데이트
씬에서 업데이트 하면
큐브맨에서 업데이트 들어옴
큐브맨 업데이트 포지션에서
키매니저 받아온(델타 류)변수들이
큐브맨 업데이트 포지션 함수 내에서 적용
*/

void KeyboardManager::UpdateMoving()
{
	if (m_pKeyState == NULL)
		return;

	//if (m_pTargetPos == NULL || m_pTargetRot == NULL)
	//   return;

	if (GetKeyState('A') & 0x8000)
	{
		m_pKeyState->deltaRot.y = -1;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		m_pKeyState->deltaRot.y = 1;
	}
	else
	{
		m_pKeyState->deltaRot.y = 0;
	}

	if (GetKeyState('W') & 0x8000)
	{
		m_pKeyState->deltaPos.z = 1;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		m_pKeyState->deltaPos.z = -1;
	}
	else
	{
		m_pKeyState->deltaPos.z = 0;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		m_pKeyState->bJump = true;
	}
	else
	{
		m_pKeyState->bJump = false;
	}
}

void KeyboardManager::SetMovingTarget(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pRot,bool* pIsJumping)
{
	m_pTargetPos = pPos;
	m_pTargetRot = pRot;
	m_pTargetIsJumping = pIsJumping;
}