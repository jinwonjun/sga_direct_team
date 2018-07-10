#pragma once

#include "IUnitObject.h"
#include "BoundingBox.h"
#include "SampleUI.h"

class BoundingBox;
class SkinnedMesh;

class Enemy : public IUnitObject
{
private:
	friend class EnemyManager;

	int						m_enemyNum;			//Enemy식별넘버

	CString					m_path;
	CString					m_filename;

	D3DXMATRIXA16			matT, matS, matR;

	BoundingBox*			m_pBox;

	BoundingSphere*			m_pBounidngSphere;
	LPD3DXMESH				m_pSphereMesh;

	SkinnedMesh*			m_pSkinnedMesh;

	int						m_HP;
	bool					m_ItemDrop;
	float					m_radius;

	D3DXMATRIXA16			m_SphereMat;
	float					m_SphereHeight;

	//화면 좌표
	float ScreenX, ScreenY;

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
	void SetDestPos(D3DXVECTOR3& pos);
	void MoveStop();
	int  GetHP() { return m_HP; }
	int GetMonsterX() { return ScreenX;	}
	int GetMonsterY() { return ScreenY; }
	void MinusHP() { m_HP-= g_pInventory->Equip[1].Atk;}


	int GetEnemyNum() { return m_enemyNum; }

	D3DXMATRIXA16 ApplyMatWorld;//스킨매쉬에서 그리는 월드 행렬값을 여기서 가져오자.
	void AnimationModify();//X파일 위치 및 스케일 조정부분.

	BoundingBox*	GetBoundingBox() { return m_pBox; }
	BoundingSphere*	GetSphere() { return m_pBounidngSphere; }


	void WorldToVP();
	void HpBar();

	void RenderUseShader_0();
	void RenderUseShader_1();
};

