#pragma once

#define PARTICLE_NUM 40

class BloodParticle
{
private:
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	vector<Particle*>		m_vecAtt; //파티클들
	LPD3DXMESH				m_pMesh;

	//LPDIRECT3DTEXTURE9		m_pTex;
	//vector<BoundingSphere*>	m_vecpBoundary;

	float playTime;			//활성화 타임
	float endTime;			//활성화 종료 타임
	float Speed;			
	bool fire;				//활성화 중인지
	D3DXVECTOR3 firePos;	//외부에서 받아올 시작 위치
	D3DXVECTOR3 fireDir;	//외부에서 받아올 방향, Forward 반대로 튀기는

							//파티클 각자 확장도
	float Expands[PARTICLE_NUM] =
	{
		.5f, .8f, .5f, .9f, .7f, .8f, .7f, .6f, .7f, .5f,
		.5f, .6f, .5f, .7f, .5f, .7f, .5f, .6f, .8f, .6f,
		.5f, .8f, .5f, .9f, .7f, .8f, .7f, .6f, .7f, .5f,
		.5f, .6f, .5f, .7f, .5f, .7f, .5f, .6f, .8f, .6f
	};

	//파티클 각자 크기
	float Scales[PARTICLE_NUM] =
	{
		12.2f, 11.1f, 10.f, 10.f, 9.9f, 12.2f, 8.8f, 8.8f, 7.7f, 15.5f,
		10.f, 8.8f, 12.2f, 8.8f, 18.8f, 15.5f, 8.8f, 11.1f, 15.5f, 15.5f,
		12.2f, 11.1f, 10.f, 10.f, 9.9f, 12.2f, 8.8f, 8.8f, 7.7f, 15.5f,
		10.f, 8.8f, 12.2f, 8.8f, 18.8f, 15.5f, 8.8f, 11.1f, 15.5f, 15.5f
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
	void SetPos(D3DXVECTOR3 _firePos) { firePos = _firePos; }
	void SetDir(D3DXVECTOR3 _fireDir) { fireDir = _fireDir; }
};

