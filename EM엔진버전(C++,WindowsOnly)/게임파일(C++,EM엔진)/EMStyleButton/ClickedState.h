#pragma once

#include "stdafx.h"

class CClickedState : public CButtonState
{
private:
	CClickedState(){};

public:
	static CClickedState* Instance();
	virtual ~CClickedState(){};

	virtual void Enter(void*);					//!< 상태변경시 한번만 호출됩니다
	virtual void Execute(void*, float fDt);		//!< 상태변경전까지 계속 호출됩니다
	virtual void Exit(void*);					//!< 다른 상태로 넘어가기전에 한번 호출됩니다

	
	virtual void Check_Down(void* pPt, stMouseInfo stPos, int nLayer);
	virtual void Check_Up(void* pPt, stMouseInfo stPos, int nLayer);
	virtual void Check_Move(void* pPt, stMouseInfo stPos, int nLayer);
};