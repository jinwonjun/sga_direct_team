#pragma once
#include "IDisplayObject.h"

#define PARTICLE_NUM 20

struct Attribute
{
	D3DXVECTOR3 _position;	//��ü ����
	D3DXCOLOR	_color;		//��ü ��
	float		_expand;	//Ȯ�嵵
	float		_angle;		//���� ��ġ ���� �ִ� ����
};

class BloodParticle : public IDisplayObject
{
private:
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	vector<Attribute*>		m_vecAtt; //��ƼŬ��
	LPD3DXMESH				m_pMesh;

	//LPDIRECT3DTEXTURE9		m_pTex;
	//vector<BoundingSphere*>	m_vecpBoundary;



	float t; //Ÿ�� ��


			 //��ƼŬ ���� Ȯ�嵵
	float Expands[PARTICLE_NUM] =
	{
		.3f, .8f, .7f, .9f, 1.f, .9f, .7f, .6f, .7f, .3f
		,.5f, .6f, .5f, .2f, .3f, .2f, .5f, .3f, .4f, .4f
	};

	//��ƼŬ ���� ũ��
	float Scales[PARTICLE_NUM] =
	{
		1.2f, 1.1f, 1.f, 1.f, .9f, 1.2f, .8f, .8f, .7f, 1.5f
		, 1.f, .8f, 1.2f, .8f, 1.8f, 1.5f, .8f, 1.1f, 1.5f, 1.5f
	};


public:

	BloodParticle();
	~BloodParticle();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

