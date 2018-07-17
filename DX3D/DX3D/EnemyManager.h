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

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	//�̳ʹ� �߰�
	void AddEnemy(D3DXVECTOR3 & pos, CString path, CString fileName, int enemyNum);
	//���ͳ��� �浹 üũ
	void CollisionCheck();
	//�浹�ϸ� �о ���� ���� ����
	void IntersectHead(const D3DXVECTOR3 fHead, const D3DXVECTOR3 bHead, const D3DXVECTOR3 center, const float radius, D3DXVECTOR3 &avoid);

	vector<Enemy*> GetVecEnemy() { return m_vecEnemy; }
};

