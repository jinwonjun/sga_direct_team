#include "stdafx.h"
#include "ActionMoveTo.h"
#include "IActionObject.h"

ActionMoveTo::ActionMoveTo(float _totalTime, D3DXVECTOR3 _to)
	:IAction(_totalTime)
{
	//ȣ���� ������ ������ ������ from�� �ȴ�!
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
	//from ���� to���� time rate �� ���� lerp (�����ϰ� �ð������� ���� �����ϴ� �۾�)�ؼ� �Ѱ���.
	//0�� ���� from��, 1�� ���� to��,�� �Ѱ���.(���������� ������ ���̴� �뵵�̴�.)
	D3DXVec3Lerp(&pos, &m_from, &m_to, GetTimeRate());
	m_pTarget->SetPosition(&pos);
}


