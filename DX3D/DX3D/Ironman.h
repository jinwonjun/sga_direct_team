#pragma once
#include "IUnitObject.h"

class SkinnedMesh;
class BoundingBox;
class BloodEffect;

#define SCALE 0.1f

class Ironman :
	public IUnitObject
{

private:
	float	timer;
	float	deathTimer;
	bool	checkTimer;
	bool	checkDeathTimer;
	int		check;		//��ü �׸��°� üũ�� �Լ�

	//�ǰ� ��ü �׷��ֱ�
	vector<BoundingSphere*> m_vecBoundary;
	LPD3DXMESH				m_pSphereMesh;

	int AddAtk;		// ���� ���� �߰����ݷ�
	int AddMaxHp;	// ���� ���� �ƽ� HP
	int AddDef;		// ���� ���� �߰�����

	//���带 ���� ���� bool ����
	bool isRun;

	//�� �ݵ�
	bool	isShoot;	//���� ������
	int		shootTime;	//����� �ð� ����
	int		endTime;	//�ݵ� ���� �ð� : Ŭ���� õõ�� ����
	float	recoilPower;//�ݵ� �Ŀ�

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
	void Death();
	void Hit();
	void Status();
	bool SphereCollideCheck(BoundingSphere player, BoundingSphere Monster);
	vector<BoundingSphere*> GetVecBoundary() { return m_vecBoundary; }

	bool SphereDrawRender;

	//�ִϸ��̼� �׽�Ʈ�� ���� ���� ����
	bool keyPress;

	//damagefont�� ���� ����
	int DamageFontNum;


	void AnimationModify();//X���� ��ġ �� ������ �����κ�.
	void AnimationKeySetting();//Ű�Է¿� ���� �ִϸ��̼� ��¸����
	void SoundSetting();

	//���� ĳ������ ���� ���� ����� ��������
	D3DXMATRIXA16 matRotY, matRotX, matT, matR, matS, matTemp;


	void RenderUseShader_0();
	void RenderUseShader_1();

	bool GetCheckDeathTimer() { return checkDeathTimer; }
};
