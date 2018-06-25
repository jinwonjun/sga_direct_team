#pragma once
#include "IUnitObject.h"
class Ironman :
	public IUnitObject
{
public:
	Ironman();
	~Ironman();

	// IUnitObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

