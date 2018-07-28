#pragma once

#include "IUnitObject.h"
#include "SampleUI.h"

#define MAX_SEE_HEAD 10
#define MAX_SEE_HEAD_BOSS 30
#define MAX_AVOID_FORCE 0.5
#define MOVE_STOP_DISTANCE 10
#define MOVE_STOP_DISTANCE_BOSS 50
#define MOB_SCALE 15.00f
#define MOB_FULL_HP 100//���� ��ü ����
#define MOB_DAMAGE 5//���� �ִ� ������
#define BOSS_MOB_DAMAGE 50//���� �ִ� ������

class BoundingBox;
class SkinnedMesh;

class Enemy : public IUnitObject
{
private:
	friend class EnemyManager;

protected:
	int						testNum;				//F3������ ��� ����
	int						m_enemyNum;				//Enemy�ĺ��ѹ�

	CString					m_path;
	CString					m_filename;

	D3DXMATRIXA16			matS, matR, matT;

	BoundingBox*			m_pBox;
	BoundingSphere*			m_pBounidngSphere;
	LPD3DXMESH				m_pSphereMesh;
	LPD3DXMESH				m_pCollSphereMesh;


	SkinnedMesh*			m_pSkinnedMesh;

	//int					m_HP;
	bool					m_ItemDrop;
	float					m_radius;				//�ǰ� ��ü ������

	D3DXMATRIXA16			m_SphereMat;
	float					m_SphereHeight;

	//ȭ�� ��ǥ
	float ScreenX, ScreenY;

	//�ǰ� ��ü �׷��ֱ�
	vector<BoundingSphere*> m_vecBoundary;

	//���� ��� Ÿ�̸� �� üũ
	float					AtkTimer;
	bool					AtkCheck;

	//��� ��� Ÿ�̸� �� üũ
	float					DeathTimer;
	bool					DeathCheck;
	
	//�浹 ó��
	float					m_CollRadius;			//�浹üũ �ݰ�
	float					m_HeadRadius;			//��� ũ��(Ȯ�ο�), ����X
	float					m_dynamicLength;		//������ ���⺤�� ����
	D3DXVECTOR3				m_frontHead;			//�� ���
	D3DXVECTOR3				m_backHead;				//���� ���
	D3DXVECTOR3				m_avoid;				//�о ����
	D3DXVECTOR3				velocity;				//���� �� ������ �ӵ�����
	LPD3DXMESH				m_pFrontSphereMesh;
	LPD3DXMESH				m_pBackSphereMesh;
	D3DXMATRIXA16			m_matFrontSphere;
	D3DXMATRIXA16			m_matBackSphere;


	//������ ���� �� üũ
	bool					isDamage;

	//ü�¹� UI �׸��� ǥ��
	vector<HUD_Ui> HP_Info;
	LPD3DXSPRITE m_pSprite;
	D3DXMATRIXA16 matT_UI, matS_UI, matR_UI,matW_UI;

	int check;//��ü �׸��°� üũ�� �Լ�
	bool SphereDrawRender;

	D3DXMATRIXA16 ApplyMatWorld;//��Ų�Ž����� �׸��� ���� ��İ��� ���⼭ ��������.


	//���� �ִϸ��̼� �ʱ�ȭ�� ����
	bool					m_isAniAttack;
	//���� �ִϸ��̼� �Ҹ� �� ������ ���� ����
	bool					m_isAniSoundAttack;
public:
	Enemy(D3DXVECTOR3& pos, CString path, CString fileName, int enemyNum);
	virtual ~Enemy();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void Hit() = 0;

	virtual void UpdatePosition();
	virtual void AnimationModify();
	virtual void WorldToVP();
	virtual void UpdateFrameMatrix();
	virtual bool SphereCollideCheck();
	virtual	void DrawRenderSphere();
	virtual	void DrawRenderMobHp();
	virtual	void MonsterCollideCheckRender();
	virtual	void RenderUseShader_0();
	virtual	void RenderUseShader_1();
	virtual void SetDestPos(D3DXVECTOR3& pos) { m_destPos = pos; }
	virtual void SetIsMove(bool isMove) { m_isMoving = isMove; }
	virtual void SetDamage(bool Damage) { isDamage = Damage; }
	virtual	void MinusHP();
	virtual	int GetHP();
	virtual	int GetMonsterX() ;
	virtual	int GetMonsterY() ;
	virtual	BoundingBox*	GetBoundingBox();
	virtual	BoundingSphere*	GetSphere();
	virtual	vector<BoundingSphere*> GetSphereVector();
	virtual	int GetEnemyNum();
};

