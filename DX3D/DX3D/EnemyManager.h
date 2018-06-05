#pragma once
#include "IDisplayObject.h";

class Enemy;
class EnemyManager : public IDisplayObject
{
private:
	friend class Enemy;

	list<Enemy*> m_listEnemy;
public:
	EnemyManager();
	~EnemyManager();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void AddEnemy(D3DXVECTOR3& pos);

	list<Enemy*> GetEnemyList() { return m_listEnemy; }

	void RemoveEnemy(Enemy* enemy) { m_listEnemy.remove(enemy); }
};

