#pragma once
#include "IUnitObject.h"

class SkinnedMesh;
class BoundingBox;
class BloodEffect;

class Ironman :
	public IUnitObject
{

private:
	float timer;
	bool checkTimer;

	//�ǰ� ��ü �׷��ֱ�
	vector<BoundingSphere*> m_vecBoundary;
	LPD3DXMESH				m_pSphereMesh;


	int AddAtk; // ���� ���� �߰����ݷ�
	int AddMaxHp;// ���� ���� �ƽ� HP
	int AddDef;// ���� ���� �߰�����


public:
	Ironman();
	~Ironman();

	// IUnitObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;



	BoundingBox*	m_pBox;

	SkinnedMesh * m_pSkinnedMesh;

	BoundingBox* GetBoundingBox() { return m_pBox; }

	BloodEffect* m_pBlood;

	D3DXVECTOR3 BloodCalPos;

	D3DXMATRIXA16 RightHand;

	void Shoot();
	void Status();

	//�ִϸ��̼� �׽�Ʈ�� ���� ���� ����
	bool keyPress;

	//UI ������ �� ĳ���� �̵� ����
	bool OpenUI;

	//damagefont�� ���� ����
	int DamageFontNum;


	void AnimationModify();//X���� ��ġ �� ������ �����κ�.
	void AnimationKeySetting();//Ű�Է¿� ���� �ִϸ��̼� ��¸����


	//���� ĳ������ ���� ���� ����� ��������
	D3DXMATRIXA16 matRotY, matRotX, matT, matR, matS, matTemp;


	void RenderUseShader_0();
	void RenderUseShader_1();
};
