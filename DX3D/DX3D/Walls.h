#pragma once
#include "IDisplayObject.h"
class Walls :
	public IDisplayObject
{
private:
	vector<VERTEX_PN> m_vecWall0;

public:
	Walls();
	~Walls();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

};

