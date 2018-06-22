#pragma once

#define PARTICLE_NUM 20

class BloodParticle
{
private:
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	vector<Particle*>		m_vecAtt; //파티클들
	LPD3DXMESH				m_pMesh;

	//LPDIRECT3DTEXTURE9		m_pTex;
	//vector<BoundingSphere*>	m_vecpBoundary;

	float playTime;			//활성화 타임
	bool fire;				//활성화 중인지
	D3DXVECTOR3 tempPos;	//외부에서 받아올 시작 위치

							//파티클 각자 확장도
	float Expands[PARTICLE_NUM] =
	{
		.3f, .8f, .7f, .9f, 1.f, .9f, .7f, .6f, .7f, .3f
		,.5f, .6f, .5f, .2f, .3f, .2f, .5f, .3f, .4f, .4f
	};

	//파티클 각자 크기
	float Scales[PARTICLE_NUM] =
	{
		1.2f, 1.1f, 1.f, 1.f, .9f, 1.2f, .8f, .8f, .7f, 1.5f
		, 1.f, .8f, 1.2f, .8f, 1.8f, 1.5f, .8f, 1.1f, 1.5f, 1.5f
	};


public:

	BloodParticle();
	~BloodParticle();

	void Init();
	void Update();
	void Render();
	void Release();

	bool GetFire() { return fire; }
	void SetFire(bool _fire) { fire = _fire; }
	void SetPos(D3DXVECTOR3 _tempPos) { tempPos = _tempPos; }
};

