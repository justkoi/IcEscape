#include "../stdafx.h"

COverState* COverState::Instance()
{
	static COverState pState;
	return &pState;
}

void COverState::Enter(void* pPt)
{
	CEMStyleButton* pButton = (CEMStyleButton*)pPt;
}

void COverState::Execute(void* pPt, float fDt)
{
	CEMStyleButton* pButton = (CEMStyleButton*)pPt;
	if(pButton->IsBlending() == true)
	{
		if(pButton->m_fBlendTimer < pButton->m_fBlendMaxTime)
		{
			pButton->m_fBlendTimer += fDt;
		}
		if(pButton->m_fBlendTimer >= pButton->m_fBlendMaxTime)
		{
			pButton->m_fBlendTimer = pButton->m_fBlendMaxTime;
			pButton->m_bBlendAppear = false;
		}
	}
}

void COverState::Exit(void* pPt)
{
	CEMStyleButton* pButton = (CEMStyleButton*)pPt;

}


void COverState::Check_Down(void* pPt, stMouseInfo stPos, int nLayer)
{
	CEMStyleButton* pButton = (CEMStyleButton*)pPt;

	int i=0;
	CEMPlane* pTemp = pButton->m_pThisScene->AABBvsRay(stPos.m_nX,stPos.m_nY,nLayer);
	
	if(pTemp)
	{
		for(i=0; i<E_BUTTON_STATE_MAX; i++)
		{
			if(pTemp == pButton->m_pButton[i])
				break;
		}
		if(i < E_BUTTON_STATE_MAX)
		{
			pButton->ChangeState(CClickedState::Instance());
		}
		else if(i == E_BUTTON_STATE_MAX)
		{
			pButton->ChangeState(CNoneState::Instance());
		}
	}
	else if(pTemp == NULL)
	{
		pButton->ChangeState(CNoneState::Instance());
	}
}
void COverState::Check_Up(void* pPt, stMouseInfo stPos, int nLayer)
{
	CEMStyleButton* pButton = (CEMStyleButton*)pPt;

	int i=0;
	CEMPlane* pTemp = pButton->m_pThisScene->AABBvsRay(stPos.m_nX,stPos.m_nY,nLayer);
	
	if(pTemp)
	{
		for(i=0; i<E_BUTTON_STATE_MAX; i++)
		{
			if(pTemp == pButton->m_pButton[i])
				break;
		}
		if(i < E_BUTTON_STATE_MAX)
		{
			pButton->ChangeState(COverState::Instance());
		}
		else if(i == E_BUTTON_STATE_MAX)
		{
			pButton->ChangeState(CNoneState::Instance());
		}
	}
	else if(pTemp == NULL)
	{
		pButton->ChangeState(CNoneState::Instance());
	}
}
void COverState::Check_Move(void* pPt, stMouseInfo stPos, int nLayer)
{
	CEMStyleButton* pButton = (CEMStyleButton*)pPt;

	int i=0;
	CEMPlane* pTemp = pButton->m_pThisScene->AABBvsRay(stPos.m_nX,stPos.m_nY,nLayer);
	
	if(pTemp)
	{
		for(i=0; i<E_BUTTON_STATE_MAX; i++)
		{
			if(pTemp == pButton->m_pButton[i])
				break;
		}
		if(i < E_BUTTON_STATE_MAX)
		{
			pButton->ChangeState(COverState::Instance());
		}
		else if(i == E_BUTTON_STATE_MAX)
		{
			pButton->ChangeState(CNoneState::Instance());
		}
		
	}
	else if(pTemp == NULL)
	{
		pButton->ChangeState(CNoneState::Instance());
	}
}