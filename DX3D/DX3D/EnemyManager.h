#pragma once
#include "IDisplayObject.h"

class Enemy;
class EnemyManager : public IDisplayObject
{
private:
	friend class Enemy;

	vector<Enemy*> m_vecEnemy;
public:
	EnemyManager();
	~EnemyManager();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	//이너미 추가
	void AddEnemy(D3DXVECTOR3 & pos, CString path, CString fileName, int enemyNum);
	//몬스터끼리 충돌 체크
	void CollisionCheck();
	//충돌하면 밀어낼 벡터 방향 대입
	void IntersectHead(const D3DXVECTOR3 fHead, const D3DXVECTOR3 bHead, const D3DXVECTOR3 center, const float radius, D3DXVECTOR3 &avoid);

	vector<Enemy*> GetVecEnemy() { return m_vecEnemy; }
};

