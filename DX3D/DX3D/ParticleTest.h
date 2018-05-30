#pragma once
#include "IDisplayObject.h"

struct Attribute
{
	//파티클 하나하나가 갖는 속성 만들어주기
	D3DXVECTOR3 _position;
	D3DXCOLOR _color;
};

class ParticleTest :public IDisplayObject
{
public:
	//버퍼에 있는 점들이 ATT에 있는 값을 참조해서 상태를 변화시킴
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DTEXTURE9 m_pTex;
	vector<Attribute *> m_vecAtt;

	

	ParticleTest();
	~ParticleTest();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

