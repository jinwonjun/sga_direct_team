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

	D3DXVECTOR3		m_destPos;		//���� �̵��� ���
	D3DXVECTOR3		m_finalDestPos;	//���� ������ ���
	vector<int>		m_vecAStarIndex;

	//===============���� ��ü ���� ����===============
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
	//Ÿ�� �����ǰ��� �������� �Լ�
	void UpdateTargetPosition(OUT D3DXVECTOR3 & targetPos);
	//���� ��ġ ��������� �Լ�
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

