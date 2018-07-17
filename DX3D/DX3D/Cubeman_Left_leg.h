#pragma once
#include "BaseObject.h"

class Cubeman_Left_leg : public BaseObject, public Cube
{
private:
	float m_rotY;

	float deltaZ;
	float m_moveSpeed;

	D3DXMATRIX mS;
	D3DXMATRIX mR;
	D3DXMATRIX mT;

	vector<VERTEX_PC> m_vecVertex;
	vector<int>		m_vecIndex;

	bool isJumpKeyHit;
	float m_basePosY;//Y의 기본적 최소값
	bool m_isJumping;//점프 중이냐
	float m_jumpPower;//Y축으로 갖는 힘
	float m_gravity;//중력 보정
	float m_currGravity;//현재 적용 중력값
	float m_moveSpeedRate;//점프 중일 때 이동 속도 보정값

public:
	Cubeman_Left_leg();
	~Cubeman_Left_leg();

	D3DXVECTOR3 m_vPosition;
	D3DXMATRIX m_matWorld;
	float RotY;
	float RotX;

	void Init();
	void Update();
	void Render();
};

