#pragma once

class CButtonState
{
public:
	CButtonState(){};
	virtual ~CButtonState(){};
	
public:
	virtual void Enter(void*) = 0;					//!< 상태변경시 한번만 호출됩니다
	virtual void Execute(void*, float fDt) = 0;		//!< 상태변경전까지 계속 호출됩니다
	virtual void Exit(void*) = 0;					//!< 다른 상태로 넘어가기전에 한번 호출됩니다

	virtual void Check_Down(void* pPt, stMouseInfo stPos, int nLayer) = 0;
	virtual void Check_Up(void* pPt, stMouseInfo stPos, int nLayer) = 0;
	virtual void Check_Move(void* pPt, stMouseInfo stPos, int nLayer) = 0;
};