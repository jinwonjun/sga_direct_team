#pragma once
#include "IDisplayObject.h"

#define PARTICLE_NUM 20

struct Attribute
{
	D3DXVECTOR3 _position;	//구체 중점
	D3DXCOLOR	_color;		//구체 색
	float		_expand;	//확장도
	float		_angle;		//시작 위치 영향 주는 각도
};

class BloodParticle : public IDisplayObject
{
private:
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	vector<Attribute*>		m_vecAtt; //파티클들
	LPD3DXMESH				m_pMesh;

	//LPDIRECT3DTEXTURE9		m_pTex;
	//vector<BoundingSphere*>	m_vecpBoundary;



	float t; //타임 값


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

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

