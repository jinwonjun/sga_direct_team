#include "stdafx.h"
#include "ActionMoveTo.h"
#include "IActionObject.h"

ActionMoveTo::ActionMoveTo(float _totalTime, D3DXVECTOR3 _to)
	:IAction(_totalTime)
{
	//호출이 됬을때 현재의 지점이 from이 된다!
	m_to = _to;
}


ActionMoveTo::~ActionMoveTo()
{
}

void ActionMoveTo::Reset()
{
	IAction::Reset();
	
	m_from = m_pTarget->GetPosition();
}

void ActionMoveTo::UpdateAction()
{
	D3DXVECTOR3 pos;
	//from 에서 to까지 time rate 의 값을 lerp (간단하게 시간비율에 따라 보간하는 작업)해서 넘겨줌.
	//0일 때는 from값, 1일 때는 to값,을 넘겨줌.(선형보간의 예제로 쓰이는 용도이다.)
	D3DXVec3Lerp(&pos, &m_from, &m_to, GetTimeRate());
	m_pTarget->SetPosition(&pos);
}


