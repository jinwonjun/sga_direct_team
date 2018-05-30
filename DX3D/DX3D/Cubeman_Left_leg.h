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
	float m_basePosY;//Y�� �⺻�� �ּҰ�
	bool m_isJumping;//���� ���̳�
	float m_jumpPower;//Y������ ���� ��
	float m_gravity;//�߷� ����
	float m_currGravity;//���� ���� �߷°�
	float m_moveSpeedRate;//���� ���� �� �̵� �ӵ� ������

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

