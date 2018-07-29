#pragma once
#include "Enemy.h"

class SubMonster :
	public Enemy
{
public:
	SubMonster(D3DXVECTOR3& pos, CString path, CString fileName, int enemyNum);
	~SubMonster();


	void Init();
	void Update();
	void Render();

	// Enemy��(��) ���� ��ӵ�
	virtual void Hit() override;

	D3DXMATRIXA16 ApplyMatWorld;//��Ų�Ž����� �׸��� ���� ��İ��� ���⼭ ��������.

	void UpdatePosition();
	void AnimationModify();//X���� ��ġ �� ������ �����κ�.

	void WorldToVP();

	void UpdateFrameMatrix();

	bool SphereCollideCheck(BoundingSphere player, BoundingSphere Monster);

	void DrawRenderSphere();
	void DrawRenderMobHp();
	void MonsterCollideCheckRender();

	void RenderUseShader_0();
	void RenderUseShader_1();

	void SetDestPos(D3DXVECTOR3& pos) { m_destPos = pos; }
	void SetIsMove(bool isMove) { m_isMoving = isMove; }
	void SetDamage(bool Damage) { isDamage = Damage; }
	void MinusHP() { m_Hp -= g_pInventory->Equip[1].Atk; }

	int GetHP() { return m_Hp; }
	int GetMonsterX() { return ScreenX; }
	int GetMonsterY() { return ScreenY; }
	BoundingBox*	GetBoundingBox() { return m_pBox; }
	BoundingSphere*	GetSphere() { return m_pBounidngSphere; }
	vector<BoundingSphere*> GetSphereVector() { return m_vecBoundary; }
	int GetEnemyNum() { return m_enemyNum; }

	void EnemyAttackSound();
};

