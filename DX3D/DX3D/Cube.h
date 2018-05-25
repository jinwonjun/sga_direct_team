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
	float m_basePosY;//Y의 기본적 최소값
	bool m_isJumping;//점프 중이냐
	float m_jumpPower;//Y축으로 갖는 힘
	float m_gravity;//중력 보정
	float m_currGravity;//현재 적용 중력값
	float m_moveSpeedRate;//점프 중일 때 이동 속도 보정값

	//머리 부분 동적 선언
	Cubeman_Head * m_pCube_Head;
	//다리 부분
	Cubeman_Left_leg * m_pCube_Left_leg;
	Cubeman_Right_leg * m_pCube_Right_leg;
	//팔부분
	Cubeman_Left_arm * m_pCube_Left_arm;
	Cubeman_Right_arm * m_pCube_Right_arm;




public:
	Cube();
	~Cube();
	D3DXVECTOR3 m_vPosition;//큐브 몸통 중심점 좌표
	D3DXMATRIX m_matWorld;//큐브 중심 월드 행렬
	float RotY; //회전 크기
	float RotX; //
	bool			go_Left;
	bool			go_Right;


	void Init();
	void Update();
	void Render();
	//Vector3* GetPosition() { return &m_vPosition; }
};

