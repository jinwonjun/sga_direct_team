#include "stdafx.h"
#include "IUnitObject.h"
#include "AStar.h" 
#include "AStarNode.h" 

IUnitObject::IUnitObject()
{
	m_isMoving = false;
	m_moveSpeed = 0.2f;
	m_currMoveSpeedRate = 1.0f;
	m_rotationSpeed = 0.1f;

	m_isJumping = false;
	m_jumpPower = 1.0f;
	m_gravity = 0.05f;
	m_currGravity = 0.0f;

	m_maxStepHeight = 2.0f;
}


IUnitObject::~IUnitObject()
{
}

void IUnitObject::SetDestination(const D3DXVECTOR3 & pos)
{
	//m_destPos = pos;

	m_vecAStarIndex.clear(); //���콺 Ŭ�������� ���� ����ؾ��ϴϱ�

	//IUnitObject::UpdateTargetPosition �Լ�
	//D3DXVec3LengthSq(&forward) > 0 �� �Ѿ���� ���ִ°�????
	m_destPos = m_pos;
	m_finalDestPos = pos;
	g_pCurrentMap->GetAstar()->FindPath(m_pos, pos, m_vecAStarIndex);
	g_pCurrentMap->GetAstar()->MakeDirectPath(m_pos, pos, m_vecAStarIndex);
}

void IUnitObject::UpdateKeyboardState()
{
	////������ false�϶��� ������ ����
	//if (m_isJumping == false) m_isJumping = m_keyState.bJump;
	//m_deltaPos.z = m_keyState.deltaPos.z;
	//m_deltaRot.y = m_keyState.deltaRot.y;

	////�̵��� ������ �׳� �����ֱ�
	//if (m_deltaPos.z == 0 && m_deltaRot.y == 0) return;

	//D3DXMATRIXA16 matRY;
	////��ȭ���� ���� ���� ȸ������ �� ȸ����Ű��
	//D3DXMatrixRotationY(&matRY, m_deltaRot.y * m_rotationSpeed);
	//D3DXVec3TransformNormal(&m_forward, &m_forward, &matRY);
	////��Ÿ ����� ������� Ȯ�� �뵵
	////�̵� ���� destPos�� �־��� ������ �ణ�� ���װ� ���� �� ����!
	//m_destPos = (D3DXVECTOR3(m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate));

	//m_finalDestPos = m_destPos;
	////�յڷ� ������ ���� ��ȭ����
	//m_vecAStarIndex.clear();
	if (m_isJumping == false) m_isJumping = m_keyState.bJump;
	m_deltaPos.z = m_keyState.deltaPos.z;
	m_deltaRot.y = m_keyState.deltaRot.y;
	m_deltaPos.x = m_keyState.deltaPos.x;

	//�̵��� ������ ������
	if (m_deltaPos.z == 0 && m_deltaRot.y == 0 && m_deltaPos.x == 0)return;

	//������ 
	D3DXMATRIXA16 matRY;
	D3DXMatrixRotationY(&matRY, m_deltaRot.y * m_rotationSpeed);
	D3DXVec3TransformNormal(&m_forward, &m_forward, &matRY);

	//������ ���� ����Ʈ
	D3DXMATRIXA16 matLeft;
	D3DXMatrixRotationY(&matLeft, D3DX_PI / 2);
	D3DXVec3TransformNormal(&m_left, &m_forward, &matLeft);

	m_destPos = (D3DXVECTOR3(m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate));
}

void IUnitObject::UpdatePositionToDestination()
{
	D3DXVECTOR3 targetPos = m_pos;
	UpdateTargetPosition(targetPos);
	ApplyTargetPosition(targetPos);

	D3DXMATRIXA16 m_matRotY;
	D3DXMatrixLookAtLH(&m_matRotY, &D3DXVECTOR3(0, 0, 0), &m_forward, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&m_matRotY, &m_matRotY);
	//ĳ���� ������ forward �������� ���ϰ� �ϴϱ�, baseRotation �߰��� ���� ������.
	D3DXMATRIXA16 matBaseR;
	D3DXMatrixRotationY(&matBaseR, m_baseRotY);

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = m_matRotY * matBaseR * matT;

	if (D3DXVec3LengthSq(&m_deltaPos) > 0 || D3DXVec3LengthSq(&m_deltaRot) > 0)
		m_isMoving = true;
	else
		m_isMoving = false;
}

void IUnitObject::UpdateTargetPosition(OUT D3DXVECTOR3 & targetPos)
{
	//���� �̵��� ����
	D3DXVECTOR3 forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
	D3DXVECTOR3 forwardNormalized = forward;
	
	//0���� ũ�� dest�� current�� �ٸ�����
	if (D3DXVec3LengthSq(&forward) > 0)
	{
		D3DXVec3Normalize(&forwardNormalized, &forwardNormalized);
		m_forward = forwardNormalized;
		//�����̵�
		if (m_deltaPos.z == 1)
		{
			//WŰ�� �̵��� ��
			m_currMoveSpeedRate = 1.0f;
		}
		//�ڷ� �̵�
		else if (m_deltaPos.z == -1)
		{
			//S Ű�� �̵��� ��
			m_currMoveSpeedRate = 0.5f;
			m_forward *= -1;
		}
		//���콺�� �Է½ÿ�
		else
		{
			m_currMoveSpeedRate = 1.0f;
			m_deltaPos.z = 1;

		}
		//�̵� �ӵ����� �Ÿ��� �� Ŭ �� 
		//D3DXVec3Length(&forward)-> �̰� �̵��� ��ŭ�� �Ÿ�!
		if (D3DXVec3Length(&forward) >= m_moveSpeed * m_currMoveSpeedRate)
		{
			targetPos = m_pos + forwardNormalized * m_moveSpeed * m_currMoveSpeedRate;
			//printf("Ŭ������ �� ��ġ : %f %f %f\n", targetPos.x, targetPos.y, targetPos.z);
		}
		//�Ÿ��� �� �̵��ӵ����� ���� ��
		else
		{
			targetPos.x = m_destPos.x;
			targetPos.z = m_destPos.z;
		}
	}
	//Astar�� �̵�
	else if (m_vecAStarIndex.empty() == false)
	{
		//������ ���� �� AStar ��尡 �������� �� ������ �缳��
		m_destPos = g_pCurrentMap->GetAstar()->GetNodes()[m_vecAStarIndex.back()]->GetLocation();

		m_vecAStarIndex.pop_back();
	}
	else
	{
		m_destPos = m_finalDestPos;
	}
}

void IUnitObject::ApplyTargetPosition(D3DXVECTOR3 & targetPos)
{
	bool	isIntersected = true;
	float	height = 0;

	if (m_isJumping == true)
	{
		m_currMoveSpeedRate = 0.7f;
		//targetPos = m_pos + m_forward * m_deltaPos.z* m_moveSpeed * m_currMoveSpeedRate;

		targetPos.y += m_jumpPower - m_currGravity;
		m_currGravity += m_gravity;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
		}

		if (isIntersected == false)
		{
			if (g_pCurrentMap != NULL)
			{
				isIntersected = g_pCurrentMap->GetHeight(height, m_pos);
			}
			m_pos.y = targetPos.y;
		}
		else
		{
			m_pos = targetPos;
		}

		if (m_pos.y <= height && m_jumpPower < m_currGravity)
		{
			m_pos.y = height;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}
		//m_pos = targetPos;
	}
	else //m_isJumping == false
	{
		//targetPos = m_pos + m_forward * m_deltaPos.z* m_moveSpeed * m_currMoveSpeedRate;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
			int tmp = 0;
			if (isIntersected == false || fabs(height - m_pos.y) > m_maxStepHeight)
			{

			}
			else
			{
				targetPos.y = height;
				m_pos = targetPos;
			}
		}
		else
		{
			m_pos = targetPos;
		}

		//m_pos = targetPos;
	}
}

void IUnitObject::UpdatePosition()
{
	//m_rot += m_deltaRot * m_rotationSpeed;
	if (!(g_pKeyboard->KeyPress('I')))
	{
		m_rot.x = g_pCamera->m_rotX;
		m_rot.y = g_pCamera->m_rotY;
	}
	else
		m_rot += m_deltaRot * m_rotationSpeed;
	//����� �˾Ҵ�!!!!
	//m_rot.y = g_pCamera->m_rotY;

	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matRotY, m_rot.y);
	D3DXVec3TransformNormal(&m_forward,&D3DXVECTOR3(0, 0, 1), &matRotY);

	D3DXVECTOR3 targetPos;
	float basePosY = 0;
	bool	isIntersected = true;
	float	height = 0;

	if (m_isJumping == true)
	{
		m_currMoveSpeedRate = 0.7f;
		//targetPos = m_pos + m_forward * m_deltaPos.z* m_moveSpeed * m_currMoveSpeedRate;

		targetPos = m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate+ m_left * m_deltaPos.x * m_moveSpeed * m_currMoveSpeedRate;

		targetPos.y += m_jumpPower - m_currGravity;
		m_currGravity += m_gravity;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
		}

		if (isIntersected == false)
		{
			if (g_pCurrentMap != NULL)
			{
				isIntersected = g_pCurrentMap->GetHeight(height, m_pos);
			}
			m_pos.y = targetPos.y;
		}
		else
		{
			m_pos = targetPos;
		}

		if (m_pos.y <= height && m_jumpPower < m_currGravity)
		{
			m_pos.y = height;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}
		//m_pos = targetPos;
	}
	else //m_isJumping == false
	{
		//targetPos = m_pos + m_forward * m_deltaPos.z* m_moveSpeed * m_currMoveSpeedRate;
		targetPos = m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate + m_left * m_deltaPos.x * m_moveSpeed * m_currMoveSpeedRate;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
			int tmp = 0;
			if (isIntersected == false || fabs(height - m_pos.y) > m_maxStepHeight)
			{

			}
			else
			{
				targetPos.y = height;
				m_pos = targetPos;
			}
		}
		else
		{
			m_pos = targetPos;
		}

		//m_pos = targetPos;
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixRotationY(&matRotY, m_rot.y + m_baseRotY);
	m_matWorld = matRotY * matT;

	if (D3DXVec3LengthSq(&m_deltaRot) > D3DX_16F_EPSILON ||D3DXVec3LengthSq(&m_deltaPos) > D3DX_16F_EPSILON)
		m_isMoving = true;
	else
		m_isMoving = false;
}
