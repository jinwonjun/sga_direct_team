#pragma once
#include "IUnitObject.h"
class Ironman :
	public IUnitObject
{
public:
	Ironman();
	~Ironman();

	// IUnitObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

