#pragma once

#define PARTICLE_NUM 40

class BloodParticle
{
private:
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	vector<Particle*>		m_vecAtt; //��ƼŬ��
	LPD3DXMESH				m_pMesh;

	//LPDIRECT3DTEXTURE9		m_pTex;
	//vector<BoundingSphere*>	m_vecpBoundary;

	float playTime;			//Ȱ��ȭ Ÿ��
	bool fire;				//Ȱ��ȭ ������
	D3DXVECTOR3 firePos;	//�ܺο��� �޾ƿ� ���� ��ġ
	D3DXVECTOR3 fireDir;	//�ܺο��� �޾ƿ� ����, Forward �ݴ�� Ƣ���

							//��ƼŬ ���� Ȯ�嵵
	float Expands[PARTICLE_NUM] =
	{
		.5f, .8f, .5f, .9f, 7.f, .8f, .7f, .6f, .7f, .5f,
		.5f, .6f, .5f, .7f, .5f, .7f, .5f, .6f, .8f, .6f,
		.5f, .8f, .5f, .9f, 7.f, .8f, .7f, .6f, .7f, .5f,
		.5f, .6f, .5f, .7f, .5f, .7f, .5f, .6f, .8f, .6f
	};

	//��ƼŬ ���� ũ��
	float Scales[PARTICLE_NUM] =
	{
		1.2f, 1.1f, 1.f, 1.f, .9f, 1.2f, .8f, .8f, .7f, 1.5f,
		1.f, .8f, 1.2f, .8f, 1.8f, 1.5f, .8f, 1.1f, 1.5f, 1.5f,
		1.2f, 1.1f, 1.f, 1.f, .9f, 1.2f, .8f, .8f, .7f, 1.5f,
		1.f, .8f, 1.2f, .8f, 1.8f, 1.5f, .8f, 1.1f, 1.5f, 1.5f
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

