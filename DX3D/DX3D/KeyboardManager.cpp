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
�ڽ��� ���� pos rot ������ �ƴ� deltaPos deltaRot ���� �߰� �Ŀ� �� ������ keyboardManager->setTarget �� �����ϱ�
delta ���� 0 �� �ƴϸ� �̵� �� ȸ�� �����ϱ�

Ű�Ŵ��� ���� �� ���� ����
���ø����̼� ���� �κп��� ���Ŵ��� ȣ��
���ø����̼� ���� �κп��� Ű���� �Ŵ��� ������Ʈ
������ ������Ʈ �ϸ�
ť��ǿ��� ������Ʈ ����
ť��� ������Ʈ �����ǿ���
Ű�Ŵ��� �޾ƿ�(��Ÿ ��)��������
ť��� ������Ʈ ������ �Լ� ������ ����
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