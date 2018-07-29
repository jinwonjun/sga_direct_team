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

	// Enemy을(를) 통해 상속됨
	virtual void Hit() override;

	D3DXMATRIXA16 ApplyMatWorld;//스킨매쉬에서 그리는 월드 행렬값을 여기서 가져오자.

	void UpdatePosition();
	void AnimationModify();//X파일 위치 및 스케일 조정부분.

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

