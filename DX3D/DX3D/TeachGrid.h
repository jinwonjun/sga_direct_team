#pragma once
#include "BaseObject.h"
class TeachGrid :
	public BaseObject
{
public:

	vector<VERTEX_PC> m_vecVertex;


	TeachGrid();
	~TeachGrid();

	void Init();
	void Render();
};

