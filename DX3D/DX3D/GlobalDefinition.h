#pragma once

//extern CSring

#define CUBE_INDEX_SIZE 36
extern WORD g_aCubeIndex[];
#define CUBE_VERTEX_SIZE 8
extern D3DXVECTOR3 g_aCubeVertex[];

#define SINGLETON(class_name) private:\
	class_name();\
	~class_name();\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#define SAFE_WNDPROC(p) if(p) {(p)->WndProc(hWnd, message, wParam, lParam);}
#define SAFE_UPDATE(p) if(p) { (p)->Update();}
#define SAFE_RENDER(p) if(p) { (p)->Render();}
#define SAFE_RELEASE(p) if(p) { (p)->Release(); (p) = NULL;}
#define SAFE_DELETE(p) if(p) { delete (p); (p) = NULL;}
#define SAFE_DELETE_ARRAY(p) if(p) {delete [] (p); (p) = NULL;}

#define SCREEN_POINT(lParam) LOWORD(lParam), HIWORD(lParam)

#define METHOD_WNDPROC(method) void method(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

#define WINSIZEX 1760
#define WINSIZEY 990

enum SCENE_INDEX {
	SCENE_GRID,
	SCENE_OBJMAP,
	SCENE_HEIGHTMAP,
	SCENE_UI
};

enum TAG_DISPLAYOBJECT {
	TAG_PLAYER,
	TAG_ENEMY1,
	TAG_ENEMY,
	TAG_INVEN,
	TAG_PARTICLE
};

struct KEYBOARD_STATE
{
	D3DXVECTOR3 deltaPos;
	D3DXVECTOR3	deltaRot;
	bool bJump;
};

//	1. Position 정점의 좌표 x,y,z(float)				: D3DFVF_XYZ
// 	2. RHW (float)                                  : D3DFVF_XYZRHW (D3DFVF_XYZ 또는 D3DFVF_NORMAL과 같이 사용불가)
// 	3. Blending Weight Data 결합 가중치 (float)		: D3DFVF_XYZB1 ~ D3DFVF_XYZB5
// 	4. Vertex Normal 정점의 법선 벡터 x,y,z(float)	: D3DFVF_NORMAL
// 	5. Vertex Point Size 정점의 점 크기 (float)		: D3DFVF_PSIZE
// 	6. Diffuse Color (DWORD)						: D3DFVF_DIFFUSE
// 	7. Specular Color (DWORD)						: D3DFVF_SPECULAR
// 	8. Texture Coordinate Set 1 (float)             : D3DFVF_TEX0 - D3DFVF_TEX8

struct VERTEX_PC
{
	D3DXVECTOR3 p;
	D3DCOLOR c;

	VERTEX_PC() {}
	VERTEX_PC(D3DXVECTOR3 _p, D3DCOLOR _c) :p(_p), c(_c) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct VERTEX_PT
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	VERTEX_PT() {}
	VERTEX_PT(D3DXVECTOR3 _p, D3DXVECTOR2 _t) :p(_p), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct VERTEX_PN
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;

	VERTEX_PN() {}
	VERTEX_PN(D3DXVECTOR3 _p, D3DXVECTOR3 _n) :p(_p), n(_n) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

struct VERTEX_PNT
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	VERTEX_PNT() {}
	VERTEX_PNT(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t)
		:p(_p), n(_n), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct VERTEX_BLENDING
{
	D3DXVECTOR3 p;
	float weight[3];
	DWORD index;
	D3DXVECTOR2 t;

	VERTEX_BLENDING() {}
	VERTEX_BLENDING(D3DXVECTOR3 _p, float* _weights, DWORD _i,
		D3DXVECTOR2 _t) : p(_p), index(_i), t(_t)
	{
		weight[0] = _weights[0];
		weight[1] = _weights[1];
		weight[2] = _weights[2];
	}

	enum { FVF = D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_TEX1 };

};


struct MTLTEX : public BaseObject
{
	D3DMATERIAL9		material;
	LPDIRECT3DTEXTURE9	pTexture;
	int					id;

	MTLTEX() {
		ZeroMemory(&material, sizeof(D3DMATERIAL9));
		pTexture = NULL;
	}

	void SetMaterial(const D3DMATERIAL9 &_material)
	{
		material = _material;
	}
	D3DMATERIAL9 GetMaterial() { return material; }
	void SetTexture(LPDIRECT3DTEXTURE9 _pTexture)
	{
		pTexture = _pTexture;
	}
	LPDIRECT3DTEXTURE9 GetTexture() { return pTexture; }
};

struct ASE_POS_SAMPLE
{
	int			tick;
	D3DXVECTOR3 position;
};

struct ASE_ROT_SAMPLE
{
	int				tick;
	D3DXQUATERNION	quaternion;
};

struct ASE_SCENE
{
	int numFirstFrame;
	int numLastFrame;
	int frameSpeed;
	int ticksPerFrame;
};

struct BoundingSphere
{
	D3DXVECTOR3 center;
	float		radius;
	bool		isPicked;

	BoundingSphere() :isPicked(false) {}
	BoundingSphere(D3DXVECTOR3 _center, float _radius) :center(_center),
		radius(_radius), isPicked(false) {}
};
//RHW의 역수라는 의미랜다 W값에 의해서 같은 차원이냐 아니냐를 구분하는데 행렬 계산 할때 w 1주고서 계산한다

struct Particle
{
	D3DXVECTOR3 _position;	//구체 중점
	float		_expand;	//확장도
	float		_angle;		//시작 위치 영향 주는 각도
};

struct VERTEX_RHWC
{
	D3DXVECTOR4 p;
	//D3DXVECTOR3 n;
	//D3DXVECTOR2 t;
	D3DCOLOR c;

	VERTEX_RHWC() {}
	VERTEX_RHWC(D3DXVECTOR4 _p, D3DCOLOR _c)
		:p(_p), c(_c){}

	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE};
};

DWORD FtoDw(float f);
//랜덤 함수 만들기
float GetRandomFloat(float lowBound, float highBound);


inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width, y + height };
	return rc;
}
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2),y - (height / 2), x + (width / 2), y + (height / 2) };


	return rc;
}