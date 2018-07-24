#pragma once

#include "IUnitObject.h"
#include "BoundingBox.h"
#include "SampleUI.h"

#define MAX_SEE_HEAD 10
#define MAX_AVOID_FORCE 0.5
#define MOVE_STOP_DISTANCE 10

#define MOB_SCALE 15.00f
#define MOB_FULL_HP 100//���� ��ü ����

class BoundingBox;
class SkinnedMesh;

class Enemy : public IUnitObject
{
private:
	friend class EnemyManager;

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

	//int						m_HP;
	bool					m_ItemDrop;
	float					m_radius;				//�ǰ� ��ü ������

	D3DXMATRIXA16			m_SphereMat;
	float					m_SphereHeight;

	//ȭ�� ��ǥ
	float ScreenX, ScreenY;

	//�ǰ� ��ü �׷��ֱ�
	vector<BoundingSphere*> m_vecBoundary;

	//��� ��� Ÿ�̸� �� üũ
	float					timer;
	bool					checkTimer;

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

	//HUD_Ui HP_Info;

	vector<HUD_Ui> HP_Info;
	LPD3DXSPRITE m_pSprite;
	D3DXMATRIXA16 matT_UI, matS_UI, matR_UI,matW_UI;

	int check;//��ü �׸��°� üũ�� �Լ�
	bool SphereDrawRender;

public:
	Enemy(D3DXVECTOR3& pos, CString path, CString fileName, int enemyNum);
	virtual ~Enemy();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	/*
	void InitVertex();
	void SetVertex(vector<VERTEX_PC> &vecVertexOut, vector<WORD> &vecIndexOut, vector<D3DXVECTOR3> vecPos);
	void SetBuffer(LPDIRECT3DVERTEXBUFFER9 &pVb, LPDIRECT3DINDEXBUFFER9 &pIb, vector<VERTEX_PC> &vecVertex, vector<WORD> &vecIndex);
	*/
	void UpdatePosition();
	void SetDestPos(D3DXVECTOR3& pos) { m_destPos = pos; }
	void SetIsMove(bool isMove) { m_isMoving = isMove; }
	void SetDamage(bool Damage) { isDamage = Damage; }

	int GetHP() { return m_Hp; }
	int GetMonsterX() { return ScreenX;	}
	int GetMonsterY() { return ScreenY; }

	void MinusHP() { m_Hp -= g_pInventory->Equip[1].Atk; }

	int GetEnemyNum() { return m_enemyNum; }

	D3DXMATRIXA16 ApplyMatWorld;//��Ų�Ž����� �׸��� ���� ��İ��� ���⼭ ��������.
	void AnimationModify();//X���� ��ġ �� ������ �����κ�.

	BoundingBox*	GetBoundingBox() { return m_pBox; }
	BoundingSphere*	GetSphere() { return m_pBounidngSphere; }

	vector<BoundingSphere*> GetSphereVector() { return m_vecBoundary; }


	void WorldToVP();

	//����� �� �غ��� IUnitObject�� �� �־ ��ü�����ϴ°� �����Ű�����...
	//�ϴ� ����
	// ��ü �浹 �� ���� ���κ�
	void Hit_Mob();//�̸��� ���� ��
	void Hit_Boss();//������ ���� ��
	bool SphereCollideCheck(BoundingSphere player, BoundingSphere Monster);

	void RenderUseShader_0();
	void RenderUseShader_1();
};

