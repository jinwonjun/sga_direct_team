#pragma once
class Grid
{
	vector<VERTEX_PC> vecLine_X;
	vector<VERTEX_PC> vecLine_Y;

	D3DXMATRIX m_matWorld;
	vector<VERTEX_PC> m_vecVertex;//��׸���


public:
	Grid();
	~Grid();

	void Init();
	void Render();
};

