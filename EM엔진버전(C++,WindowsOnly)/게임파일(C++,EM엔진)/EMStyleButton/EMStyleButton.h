#pragma once
#include "../stdafx.h"

typedef enum
{
	E_BUTTON_STATE_NONE,
	E_BUTTON_STATE_OVER,
	E_BUTTON_STATE_CLICKED,
	E_BUTTON_STATE_MAX,
};

class CEMStyleButton
{
private:
	

public:
	bool			m_bClicked;
	bool			m_bAction;
	bool			m_bInited;
	bool			m_bVisible;


	stEMVec2		m_stPos;

	CEMPlane*		m_pButton[E_BUTTON_STATE_MAX];

	CButtonState*			m_pStates[E_BUTTON_STATE_MAX];
	CButtonState*			m_pCurrentState;		//!< 주인공의 현재 상태


	CRootScene*		m_pThisScene;

	bool			m_bBlendAppear;
	float			m_fBlendTimer;
	float			m_fBlendMaxTime;

	CEMStyleButton()
	{
	for(int i=0; i<E_BUTTON_STATE_MAX; i++)
		m_pButton[i] = NULL;

	for(int i=0; i<E_BUTTON_STATE_MAX; i++)
		m_pStates[i] = NULL;

	m_bClicked = false;
	m_bAction = false;
	m_bInited = false;
	m_bVisible = false;
	
	}
	~CEMStyleButton()
	{
		
	}

	CButtonState* GetState()				{return m_pCurrentState;}	//!< 현재 상태 얻어오기

	bool IsClicked() { return m_bClicked; };
	bool IsAction() { return m_bAction; };
	bool IsBlending() { return m_bBlendAppear; };

	void Init(CRootScene* pScene, CEMPlane* pButton_None, CEMPlane* pButton_Over, CEMPlane* pButton_Clicked, stEMVec2 stPos, bool bVisible);
	void Update(CRootScene* pScene, float fDt);		
	void Exit(CRootScene* pScene);

	void BlendAppear(float fBlendMaxTime);//자연스러운 등장

	/**
	@brief 상태들의 포인터를 넣어둡니다
		   상태가 늘어나면 이곳도 추가 시켜주세요
	@param 
	@return 없음
	*/


	void InitStates();			

	void StateUpdate();

	void ShowUpdate();

	void PosUpdate();

	void Check_Down(stMouseInfo stPos, int nLayer);
	void Check_Up(stMouseInfo stPos, int nLayer);
	void Check_Move(stMouseInfo stPos, int nLayer);

	void ChangeState(CButtonState* pNewState);

};