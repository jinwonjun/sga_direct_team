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

	m_vecAStarIndex.clear(); //마우스 클릭떄마다 새로 계산해야하니까

	//IUnitObject::UpdateTargetPosition 함수
	//D3DXVec3LengthSq(&forward) > 0 을 넘어가도록 해주는거????
	m_destPos = m_pos;
	m_finalDestPos = pos;
	g_pCurrentMap->GetAstar()->FindPath(m_pos, pos, m_vecAStarIndex);
	g_pCurrentMap->GetAstar()->MakeDirectPath(m_pos, pos, m_vecAStarIndex);
}

void IUnitObject::UpdateKeyboardState()
{
	////점프가 false일때만 쓰도록 하자
	//if (m_isJumping == false) m_isJumping = m_keyState.bJump;
	//m_deltaPos.z = m_keyState.deltaPos.z;
	//m_deltaRot.y = m_keyState.deltaRot.y;

	////이동이 없으면 그냥 막아주기
	//if (m_deltaPos.z == 0 && m_deltaRot.y == 0) return;

	//D3DXMATRIXA16 matRY;
	////변화량이 있을 때만 회전값을 얻어서 회전시키기
	//D3DXMatrixRotationY(&matRY, m_deltaRot.y * m_rotationSpeed);
	//D3DXVec3TransformNormal(&m_forward, &m_forward, &matRY);
	////델타 포즈는 정면방향 확인 용도
	////이동 값을 destPos로 주었기 때문에 약간의 버그가 있을 수 있음!
	//m_destPos = (D3DXVECTOR3(m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate));

	//m_finalDestPos = m_destPos;
	////앞뒤로 누르면 값이 변화없음
	//m_vecAStarIndex.clear();
	if (m_isJumping == false) m_isJumping = m_keyState.bJump;
	m_deltaPos.z = m_keyState.deltaPos.z;
	m_deltaRot.y = m_keyState.deltaRot.y;
	m_deltaPos.x = m_keyState.deltaPos.x;

	//이동이 없으면 막아줌
	if (m_deltaPos.z == 0 && m_deltaRot.y == 0 && m_deltaPos.x == 0)return;

	//포워드 
	D3DXMATRIXA16 matRY;
	D3DXMatrixRotationY(&matRY, m_deltaRot.y * m_rotationSpeed);
	D3DXVec3TransformNormal(&m_forward, &m_forward, &matRY);

	//포워드 기준 레프트
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
	//캐릭터 정면이 forward 방향으로 향하게 하니까, baseRotation 추가로 적용 시켜줌.
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
	//내가 이동할 방향
	D3DXVECTOR3 forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
	D3DXVECTOR3 forwardNormalized = forward;
	
	//0보다 크면 dest랑 current랑 다른거임
	if (D3DXVec3LengthSq(&forward) > 0)
	{
		D3DXVec3Normalize(&forwardNormalized, &forwardNormalized);
		m_forward = forwardNormalized;
		//정면이동
		if (m_deltaPos.z == 1)
		{
			//W키로 이동할 때
			m_currMoveSpeedRate = 1.0f;
		}
		//뒤로 이동
		else if (m_deltaPos.z == -1)
		{
			//S 키로 이동할 때
			m_currMoveSpeedRate = 0.5f;
			m_forward *= -1;
		}
		//마우스로 입력시에
		else
		{
			m_currMoveSpeedRate = 1.0f;
			m_deltaPos.z = 1;

		}
		//이동 속도보다 거리가 더 클 때 
		//D3DXVec3Length(&forward)-> 이게 이동할 만큼의 거리!
		if (D3DXVec3Length(&forward) >= m_moveSpeed * m_currMoveSpeedRate)
		{
			targetPos = m_pos + forwardNormalized * m_moveSpeed * m_currMoveSpeedRate;
			//printf("클릭했을 때 위치 : %f %f %f\n", targetPos.x, targetPos.y, targetPos.z);
		}
		//거리가 내 이동속도보다 작을 때
		else
		{
			targetPos.x = m_destPos.x;
			targetPos.z = m_destPos.z;
		}
	}
	//Astar로 이동
	else if (m_vecAStarIndex.empty() == false)
	{
		//목적지 도달 후 AStar 노드가 남아있을 시 목적지 재설정
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
	//방식을 알았다!!!!
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
