#pragma once
#include "IDisplayObject.h";

class Enemy;
class EnemyManager : public IDisplayObject
{
private:
	friend class Enemy;

	vector<Enemy*> m_vecEnemy;
public:
	EnemyManager();
	~EnemyManager();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void AddEnemy(D3DXVECTOR3 & pos, CString path, CString fileName, int enemyNum);

	vector<Enemy*> GetVecEnemy() { return m_vecEnemy; }

	void WorldToVP();
};

