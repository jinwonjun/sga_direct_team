#pragma once

struct	CINDEX { WORD _0, _1, _2; };
struct	CINDEXLINE { WORD _0, _1; };

class SkyBox
{
public:
	SkyBox(WCHAR* top, WCHAR* bottom, WCHAR* left, WCHAR* right, WCHAR* front, WCHAR* back);
	~SkyBox();

	int  FrameMove(float et);
	void Render();

public:
	LPDIRECT3DVERTEXBUFFER9		mVtx[6];
	LPDIRECT3DINDEXBUFFER9		mIdx[6];
	LPDIRECT3DTEXTURE9			mTex[6];
	void	Set_Vtx3D_Tex(VERTEX_PNT &ct, D3DXVECTOR3 p, D3DXVECTOR3 n, float tu, float tv);
	void	Set_Idx(CINDEX &ci, WORD _0, WORD _1, WORD _2);
};

