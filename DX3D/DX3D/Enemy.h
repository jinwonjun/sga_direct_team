#pragma once

#include "IUnitObject.h"
#include "SampleUI.h"

#define MAX_SEE_HEAD 10
#define MAX_SEE_HEAD_BOSS 30
#define MAX_AVOID_FORCE 0.5
#define MOVE_STOP_DISTANCE 10
#define MOVE_STOP_DISTANCE_BOSS 50
#define MOB_SCALE 15.00f
#define MOB_FULL_HP 100//몹의 전체 피통
#define MOB_DAMAGE 5//몹이 주는 데미지
#define BOSS_MOB_DAMAGE 50//몹이 주는 데미지

class BoundingBox;
class SkinnedMesh;

class Enemy : public IUnitObject
{
private:
	friend class EnemyManager;

protected:
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

	//int					m_HP;
	bool					m_ItemDrop;
	float					m_radius;				//피격 구체 반지름

	D3DXMATRIXA16			m_SphereMat;
	float					m_SphereHeight;

	//화면 좌표
	float ScreenX, ScreenY;

	//피격 구체 그려주기
	vector<BoundingSphere*> m_vecBoundary;

	//어택 모션 타이머 및 체크
	float					AtkTimer;
	bool					AtkCheck;

	//사망 모션 타이머 및 체크
	float					DeathTimer;
	bool					DeathCheck;
	
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

	//체력바 UI 그리기 표시
	vector<HUD_Ui> HP_Info;
	LPD3DXSPRITE m_pSprite;
	D3DXMATRIXA16 matT_UI, matS_UI, matR_UI,matW_UI;

	int check;//구체 그리는거 체크용 함수
	bool SphereDrawRender;

	D3DXMATRIXA16 ApplyMatWorld;//스킨매쉬에서 그리는 월드 행렬값을 여기서 가져오자.


	//공격 애니메이션 초기화할 변수
	bool					m_isAniAttack;
	//공격 애니메이션 소리 낼 조건을 위한 변수
	bool					m_isAniSoundAttack;
public:
	Enemy(D3DXVECTOR3& pos, CString path, CString fileName, int enemyNum);
	virtual ~Enemy();

	// IDisplayObject을(를) 통해 상속됨
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

