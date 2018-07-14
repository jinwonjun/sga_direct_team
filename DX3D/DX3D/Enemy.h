#pragma once

#include "IUnitObject.h"
#include "BoundingBox.h"
#include "SampleUI.h"

#define MAX_SEE_HEAD 10
#define MAX_AVOID_FORCE 0.5
#define MOVE_STOP_DISTANCE 10

#define SCALE 10.00f
#define MOB_FULL_HP 100//몹의 전체 피통

class BoundingBox;
class SkinnedMesh;

class Enemy : public IUnitObject
{
private:
	friend class EnemyManager;

	int						testNum;				//F3누르면 모드 변경

	int						m_enemyNum;				//Enemy식별넘버

	CString					m_path;
	CString					m_filename;

	D3DXMATRIXA16			matS, matR, matT;

	BoundingBox*			m_pBox;

	BoundingSphere*			m_pBounidngSphere;
	LPD3DXMESH				m_pSphereMesh;
	LPD3DXMESH				m_pCollSphereMesh;

	SkinnedMesh*			m_pSkinnedMesh;

	int						m_HP;
	bool					m_ItemDrop;
	float					m_radius;				//피격 구체 반지름

	D3DXMATRIXA16			m_SphereMat;
	float					m_SphereHeight;

	//화면 좌표
	float ScreenX, ScreenY;

	//피격 구체 그려주기
	vector<BoundingSphere*> m_vecBoundary;


	//충돌 처리
	float					m_CollRadius;			//충돌체크 반경
	float					m_HeadRadius;			//헤드 크기(확인용), 연산X
	float					m_dynamicLength;		//유동적 방향벡터 비율

	D3DXVECTOR3				m_frontHead;			//먼 헤드
	D3DXVECTOR3				m_backHead;				//인접 헤드
	D3DXVECTOR3				m_avoid;				//밀어낼 벡터
	D3DXVECTOR3				velocity;				//연산 후 움직일 속도벡터

	LPD3DXMESH				m_pFrontSphereMesh;
	LPD3DXMESH				m_pBackSphereMesh;
	D3DXMATRIXA16			m_matFrontSphere;
	D3DXMATRIXA16			m_matBackSphere;

	//슛에서 맞은 놈 체크
	bool					isDamage;

	//HUD_Ui HP_Info;

	vector<HUD_Ui> HP_Info;
	LPD3DXSPRITE m_pSprite;
	D3DXMATRIXA16 matT_UI, matS_UI, matR_UI,matW_UI;

public:
	Enemy(D3DXVECTOR3& pos, CString path, CString fileName, int enemyNum);
	virtual ~Enemy();

	// IDisplayObject을(를) 통해 상속됨
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

	int GetHP() { return m_HP; }
	int GetMonsterX() { return ScreenX;	}
	int GetMonsterY() { return ScreenY; }

	void MinusHP() { m_HP -= g_pStatus->MyChara.EndAtk; }

	int GetEnemyNum() { return m_enemyNum; }

	D3DXMATRIXA16 ApplyMatWorld;//스킨매쉬에서 그리는 월드 행렬값을 여기서 가져오자.
	void AnimationModify();//X파일 위치 및 스케일 조정부분.

	BoundingBox*	GetBoundingBox() { return m_pBox; }
	BoundingSphere*	GetSphere() { return m_pBounidngSphere; }

	vector<BoundingSphere*> GetBossSphere() { return m_vecBoundary; }


	void WorldToVP();
	
	//void HpBar();

	void RenderUseShader_0();
	void RenderUseShader_1();
};

