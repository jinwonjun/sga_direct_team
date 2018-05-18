#pragma once

#include "BaseObject.h"

class IActionObject;

class IActionDelegate
{
public:
	virtual void OnFinishAction() = 0;
};

class IAction : public BaseObject
{
protected:
	IActionObject *		m_pTarget;
	//다음 액션 호출할 때 알려주려고 쓰이는 용도
	IActionDelegate*	m_pActionDelegate;
	bool				m_isFinish;
	float				m_currentTime;
	float				m_totalTime;

public:
	IAction(float _totalTime = 0);
	virtual ~IAction();

	virtual void Update();
	virtual void UpdateAction() {}
	virtual void Reset();
	virtual void SetTarget(IActionObject* pTarget) { m_pTarget = pTarget; }
	void SetDelegate(IActionDelegate* pActionDelegate) { m_pActionDelegate = pActionDelegate; }
	//진행도 = 전체시간/진행시간
	float GetTimeRate() { return m_currentTime / m_totalTime; }
};

#include "ActionMoveTo.h"
#include "ActionSequence.h"
#include "ActionRepeat.h"