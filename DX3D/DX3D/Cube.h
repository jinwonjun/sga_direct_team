#pragma once
#include "BaseObject.h"

class Cubeman_Head;
class Cubeman_Left_leg;
class Cubeman_Right_leg;
class Cubeman_Left_arm;
class Cubeman_Right_arm;

class Cube :
	public BaseObject
{
private:
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

	//�Ӹ� �κ� ���� ����
	Cubeman_Head * m_pCube_Head;
	//�ٸ� �κ�
	Cubeman_Left_leg * m_pCube_Left_leg;
	Cubeman_Right_leg * m_pCube_Right_leg;
	//�Ⱥκ�
	Cubeman_Left_arm * m_pCube_Left_arm;
	Cubeman_Right_arm * m_pCube_Right_arm;




public:
	Cube();
	~Cube();
	D3DXVECTOR3 m_vPosition;//ť�� ���� �߽��� ��ǥ
	D3DXMATRIX m_matWorld;//ť�� �߽� ���� ���
	float RotY; //ȸ�� ũ��
	float RotX; //
	bool			go_Left;
	bool			go_Right;


	void Init();
	void Update();
	void Render();
	//Vector3* GetPosition() { return &m_vPosition; }
};

