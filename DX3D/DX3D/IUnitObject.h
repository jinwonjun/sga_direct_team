#pragma once
#include "IDisplayObject.h"

class IUnitObject : public IDisplayObject
{
protected:
	D3DXVECTOR3		m_deltaPos;
	D3DXVECTOR3		m_deltaRot;
	D3DXVECTOR3		m_forward;
	KEYBOARD_STATE  m_keyState;

	D3DXVECTOR3		m_left;

	bool			m_isMoving;
	float			m_moveSpeed;
	float			m_currMoveSpeedRate;
	float			m_rotationSpeed;

	bool			m_isJumping;
	float			m_jumpPower;
	float			m_gravity;
	float			m_currGravity;

	float			m_maxStepHeight;
	float			m_baseRotY;

	D3DXVECTOR3		m_destPos;		//현재 이동할 노드
	D3DXVECTOR3		m_finalDestPos;	//최종 목적지 노드
	vector<int>		m_vecAStarIndex;

	//===============공통 객체 변수 정리===============
	bool			m_isDead;
	int				m_Atk;
	int				m_Dmg;
	int				m_Def;
	int				m_MaxHp;
	int				m_Hp;

	IUnitObject();

public:


	virtual ~IUnitObject();

	void SetDestination(const D3DXVECTOR3 &pos);
	void UpdateKeyboardState();
	void UpdatePositionToDestination();
	//타겟 포지션값을 조절해줄 함수
	void UpdateTargetPosition(OUT D3DXVECTOR3 & targetPos);
	//실제 위치 적용시켜줄 함수
	void ApplyTargetPosition(D3DXVECTOR3 & targetPos);
	void UpdatePosition();

	void DamageCalcul(int Atk);

	void AttackCalcultate(IUnitObject * DamagedUnit);
	

	D3DXVECTOR3 GetForward() { return m_forward; }
	bool GetMoveStatus() { return m_isMoving; }
	void SetMoveStatus(bool moving) { m_isMoving = moving; }
	int GetHp() { return m_Hp; }
	void SetHp(int hp) { m_Hp = hp; }
};

