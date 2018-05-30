#pragma once
#include "IDisplayObject.h"
#include "IUnitObject.h"

#include "ObjMap.h"

class CubemanParts;

class Cubeman :public IUnitObject
{
private :
	CubemanParts* m_pRootParts;

	//���� �ޱ� ����
	//���� ����ġ �뵵
	bool m_isTurnedOnLight;

	//D3DXVECTOR3		m_deltaPos;
	//D3DXVECTOR3		m_deltaRot;
	//D3DXVECTOR3		m_forward;

	//ť��� Ŭ������ ��ü�� �����̸� �׾ȿ� ����� �� ������ ���� �����̰� ����.
	bool			m_isMoving;
	float			m_moveSpeed;
	float			m_currMoveSpeedRate;
	float			m_rotationSpeed;

	bool			m_isJumping;
	float			m_jumpPower;
	float			m_gravity;
	float			m_currGravity;

	float			m_maxStepHeight;//���� �ٴҶ� �������� ũ�� �Ǹ� ������ �����ִ� ����


public:
	Cubeman();
	~Cubeman();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;


	bool CalcPickedPosition(D3DXVECTOR3 &vOut, WORD screenX, WORD screenY);
	void UpdatePosition();
	void CreateAllParts();
	void CreateParts(CubemanParts* &pParts, IDisplayObject* pParent,D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 trans,vector<vector<int>> &vecUV);

	vector<vector<int>> uvBody = {
		{ 32, 32, 32, 20, 40, 20, 40, 32 },	// ��
		{ 20, 32, 20, 20, 28, 20, 28, 32 },	// ��
		{ 28, 32, 28, 20, 32, 20, 32, 32 },	// ��
		{ 16, 32, 16, 20, 20, 20, 20, 32 },	// ��
		{ 20, 20, 20, 16, 28, 16, 28, 20 },	// ��
		{ 28, 16, 28, 20, 36, 20, 36, 16 }	// ��
	};

	vector<vector<int>> uvHead = {
		//{ 24, 16, 24, 8, 32, 8, 32, 16 },	// ��
		//{ 8, 16, 8, 8, 16, 8, 16, 16 },		// ��
		//{ 16, 16, 16, 8, 24, 8, 24, 16 },	// ��
		//{ 0, 16, 0, 8, 8, 8, 8, 16 },		// ��
		//{ 8, 8, 8, 0, 16, 0, 16, 8 },		// ��
		//{ 16, 0, 16, 8, 24, 8, 24, 0 }		// ��

	//���̾�� �뵵
	{ 24+32, 16 + 32, 24 + 32, 8 + 32, 32 + 32, 8 + 32, 32 + 32, 16 + 32 },	// ��
	{ 8 + 32, 16 + 32, 8 + 32, 8 + 32, 16 + 32, 8 + 32, 16 + 32, 16 + 32 },	// ��
	{ 16 + 32, 16 + 32, 16 + 32, 8 + 32, 24 + 32, 8 + 32, 24 + 32, 16 + 32 },// ��
	{ 0 + 32, 16 + 32, 0 + 32, 8 + 32, 8 + 32, 8 + 32, 8 + 32, 16 + 32 },	// ��
	{ 8 + 32, 8 + 32, 8 + 32, 0 + 32, 16 + 32, 0 + 32, 16 + 32, 8 + 32 },	// ��
	{ 16 + 32, 0 + 32, 16 + 32, 8 + 32, 24 + 32, 8 + 32, 24 + 32, 0 + 32 }	// ��
	};

	vector<vector<int>> uvLArm = {
		{ 44, 32, 44, 20, 48, 20, 48, 32 },	// ��
		{ 52, 32, 52, 20, 56, 20, 56, 32 },	// ��
		{ 40, 32, 40, 20, 44, 20, 44, 32 },	// ��
		{ 48, 32, 48, 20, 52, 20, 52, 32 },	// ��
		{ 44, 20, 44, 16, 48, 16, 48, 20 },	// ��
		{ 48, 16, 48, 20, 52, 20, 52, 16 }	// ��
	};

	vector<vector<int>> uvRArm = {
		{ 48, 32, 48, 20, 44, 20, 44, 32 },	// ��
		{ 56, 32, 56, 20, 52, 20, 52, 32 },	// ��
		{ 48, 32, 48, 20, 52, 20, 52, 32 },	// ��
		{ 40, 32, 40, 20, 44, 20, 44, 32 },	// ��
		{ 48, 20, 48, 16, 44, 16, 44, 20 },	// ��
		{ 52, 16, 52, 20, 48, 20, 48, 16 }	// ��
	};

	vector<vector<int>> uvLLeg = {
		{ 12, 32, 12, 20, 16, 20, 16, 32 },	// ��
		{ 4, 32, 4, 20, 8, 20, 8, 32 },		// ��
		{ 8, 32, 8, 20, 12, 20, 12, 32 },	// ��
		{ 0, 32, 0, 20, 4, 20, 4, 32 },		// ��
		{ 4, 20, 4, 16, 8, 16, 8, 20 },		// ��
		{ 8, 16, 8, 20, 12, 20, 12, 16 }	// ��
	};

	vector<vector<int>> uvRLeg = {
		{ 16, 32, 16, 20, 12, 20, 12, 32 },	// ��
		{ 8, 32, 8, 20, 4, 20, 4, 32 },		// ��
		{ 4, 32, 4, 20, 0, 20, 0, 32 },		// ��
		{ 12, 32, 12, 20, 8, 20, 8, 32 },	// ��
		{ 8, 20, 8, 16, 4, 16, 4, 20 },		// ��
		{ 12, 16, 12, 20, 8, 20, 8, 16 }	// ��
	};
};

