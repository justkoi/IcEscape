#include "../stdafx.h"

void CEMStyleButton::Init(CRootScene* pScene, CEMPlane* pButton_None, CEMPlane* pButton_Over, CEMPlane* pButton_Clicked, stEMVec2 stPos, bool bVisible)
{
	m_bInited = true;
	m_bClicked = false;
	m_bAction = false;
	m_bVisible = bVisible;

	m_bBlendAppear = false;
	if(m_bVisible == false)
	{
		m_fBlendTimer = 0.0f;
		m_fBlendMaxTime = 3.0f;
	}
	else if(m_bVisible == true)
	{
		m_fBlendTimer = 3.0f;
		m_fBlendMaxTime = 3.0f;
	}

	m_pThisScene = pScene;

	m_stPos = stPos;

	m_pButton[E_BUTTON_STATE_NONE] = pButton_None;
	m_pButton[E_BUTTON_STATE_OVER] = pButton_Over;
	m_pButton[E_BUTTON_STATE_CLICKED] = pButton_Clicked;

	InitStates();

	m_pCurrentState = m_pStates[E_BUTTON_STATE_NONE];
}
void CEMStyleButton::Update(CRootScene* pScene, float fDt)
{
	PosUpdate();
	ShowUpdate();
	StateUpdate();
	GetState()->Execute((void*)this, fDt);
}

void CEMStyleButton::InitStates()
{
	m_pStates[E_BUTTON_STATE_NONE] = CNoneState::Instance();
	m_pStates[E_BUTTON_STATE_OVER] = COverState::Instance();
	m_pStates[E_BUTTON_STATE_CLICKED] = CClickedState::Instance();
}
void CEMStyleButton::PosUpdate()
{
	for(int i=0; i<E_BUTTON_STATE_MAX; i++)
		m_pButton[i]->SetPos(m_stPos);

}
void CEMStyleButton::ShowUpdate()
{
	for(int i=0; i<E_BUTTON_STATE_MAX; i++)
		m_pButton[i]->SetShow(false);
	for(int i=0; i<E_BUTTON_STATE_MAX; i++)
		m_pButton[i]->SetColor(1.0f,1.0f,1.0f,m_fBlendTimer/m_fBlendMaxTime);

	if(m_bVisible == true)
	{
		if(m_pCurrentState == CNoneState::Instance())
			m_pButton[E_BUTTON_STATE_NONE]->SetShow(true);
		if(m_pCurrentState == COverState::Instance())
			m_pButton[E_BUTTON_STATE_OVER]->SetShow(true);
		if(m_pCurrentState == CClickedState::Instance())
			m_pButton[E_BUTTON_STATE_CLICKED]->SetShow(true);
	}
	
}

void CEMStyleButton::StateUpdate()
{

}


void CEMStyleButton::ChangeState(CButtonState* pNewState)
{
	if(pNewState)
	{
		if(pNewState == m_pCurrentState)
			return;

		if(m_pCurrentState == NULL)
		{
			m_pCurrentState = pNewState;
			m_pCurrentState->Enter((void*)this);
		}
		else
		{
			// 기존상태의 exit를 호출합니다
			m_pCurrentState->Exit((void*)this);
			m_pCurrentState = pNewState;
			m_pCurrentState->Enter((void*)this);
		}
	}
}


void CEMStyleButton::Check_Down(stMouseInfo stPos, int nLayer)
{
	if(m_bInited == true)
		GetState()->Check_Down(this,stPos, nLayer);
}
void CEMStyleButton::Check_Up(stMouseInfo stPos, int nLayer)
{
	if(m_bInited == true)
		GetState()->Check_Up(this,stPos, nLayer);
}
void CEMStyleButton::Check_Move(stMouseInfo stPos, int nLayer)
{
	if(m_bInited == true)
		GetState()->Check_Move(this,stPos, nLayer);
}
void CEMStyleButton::BlendAppear(float fBlendMaxTime)
{
	m_bVisible = true;
	m_bBlendAppear = true;
	m_fBlendTimer = 0.0f;
	m_fBlendMaxTime = fBlendMaxTime;
}
//void StateUpdate();