#include "../stdafx.h"

CClickedState* CClickedState::Instance()
{
	static CClickedState pState;
	return &pState;
}

void CClickedState::Enter(void* pPt)
{
	CEMStyleButton* pButton = (CEMStyleButton*)pPt;
	pButton->m_bClicked = true;
	
}

void CClickedState::Execute(void* pPt, float fDt)
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

void CClickedState::Exit(void* pPt)
{
	CEMStyleButton* pButton = (CEMStyleButton*)pPt;
	pButton->m_bClicked = false;

}


void CClickedState::Check_Down(void* pPt, stMouseInfo stPos, int nLayer)
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
		if(i == E_BUTTON_STATE_MAX)
		{
			pButton->ChangeState(CNoneState::Instance());
		}
	}
	else if(pTemp == NULL)
	{
		pButton->ChangeState(CNoneState::Instance());
	}
}
void CClickedState::Check_Up(void* pPt, stMouseInfo stPos, int nLayer)
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
			if(pButton->IsClicked() == true)
				pButton->m_bAction = true;
			//pButton->ChangeState(COverState::Instance());
		}
		if(i == E_BUTTON_STATE_MAX)
		{
			pButton->ChangeState(CNoneState::Instance());
		}
	}
	else if(pTemp == NULL)
	{
		pButton->ChangeState(CNoneState::Instance());
	}

}
void CClickedState::Check_Move(void* pPt, stMouseInfo stPos, int nLayer)
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
		if(i == E_BUTTON_STATE_MAX)
		{
			pButton->ChangeState(CClickedState::Instance());
		}
	}
	else if(pTemp == NULL)
	{
		pButton->ChangeState(CClickedState::Instance());
	}
}