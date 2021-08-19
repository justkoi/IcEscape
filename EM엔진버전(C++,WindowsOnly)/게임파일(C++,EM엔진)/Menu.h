#pragma once

#include "stdafx.h"


/*
	1. 물리 안붙은 Plane
		- 물리가 붙이 않았으므로 충돌 계산을 사용자가 직접 해줘야합니다
*/
class CMenu : public CRootScene
{
public:

	CEMPlane*	m_pBlack[2];
	
	CEMStyleButton m_SoundButton;
	CEMPlane*	m_pSoundButtonImg[3];
	
	CEMStyleButton m_SoundButton2;
	CEMPlane*	m_pSoundButton2Img[3];


	//CEMStyleButton m_Skip;// !< Skip버튼
	//CEMPlane* m_pSkipImg[3];

	CEMStyleButton m_ButtonGameStart;
	CEMStyleButton m_ButtonExit;
	CEMStyleButton m_ButtonHowTo;
	CEMStyleButton m_ButtonCredit;
	CEMStyleButton m_ButtonOption;

	CEMPlane*	m_pButtonGameStartImg[3];
	CEMPlane*	m_pButtonExitImg[3];
	CEMPlane*	m_pButtonHowToImg[3];
	CEMPlane*	m_pButtonCreditImg[3];
	CEMPlane*	m_pButtonOptionImg[3];

	CEMPlane*	m_pTitle;
	CEMVibrater*	m_pVibrater;
	//CEMTextDisplay*	m_pTextBox;
	CEMSnowMng*	m_SnowMng;
public:

	CEMPlane*	m_pPlane;	//!< Plane 출력
	CEMPlane*	m_pHero;	//!< Plane 출력

	float		m_fTimer;
	float		m_fUpDownTime;
	float		m_fUpDownSpeed;
	float		m_fUpDownPlusTime;
	bool		m_fUpDown;
	
	//CEMPlane*	m_pVib[D_LOGOVIB_MAX];	//!< Plane 출력

	CEMPlane*	m_pButtonImg[3];	//!< Plane 출력

	CEMPlane*	m_pBg;	//!< Plane 출력

	stEMVec3	m_stCamPos;	//!< 카메라 위치 저장 벡터
	
	CEMPlane*	m_pBlind;
	float		m_pBlindTimer;
	float		m_pBlindSpeed;
	bool		m_bButtonAppear;

public:
	float		m_fRot;		
	float		m_fSize;	

public:
	CMenu(void)
	{	
		m_pPlane = NULL;
		//m_pVibrater = NULL;
		//m_pTextBox = NULL;
		//m_pHero = NULL;
		for(int i=0; i<D_LOGOVIB_MAX; i++)
		//	m_pVib[i] = NULL;
		for(int i=0; i<3; i++)
			m_pButtonImg[i] = NULL;
		m_pBg = NULL;
		m_pBlind = NULL;

		m_fRot = 0.0f;
		m_fSize = 3.0f;
		
		m_stCamPos = stEMVec3(0.0f, 3.0f,400.0f);
	};
	virtual ~CMenu(void)
	{
		
	};

public:
	virtual void Enter				(CSceneWork* pSceneWork);										//!< 진입(로딩)
	virtual void Update				(CSceneWork*, float dt);										//!< Update
	virtual void Render				(CSceneWork*);													//!< Render
	virtual void Exit				(CSceneWork* pSceneWork);										//!< 탈출(메모리 해제등)
	virtual void MouseDownEvent		(stMouseInfo stPos, enumMouseButton eButton);					//!< 마우스 다운 이벤트
	virtual void MouseUpEvent		(stMouseInfo stPos, enumMouseButton eButton);					//!< 마우스 업 이벤트
	virtual void MouseMoveEvent		(stMouseInfo stPos);											//!< 마우스 이동 이벤트
	virtual HRESULT WindowMessage	(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);			//!< 윈도우 이벤트

	//!=================================================================================================
	//! 물리 충돌 이벤트들 입니다.
	virtual void BeginContact		(b2Contact* contact); 											//!< 충돌시작  되면 자동 호출된다
	virtual void EndContact			(b2Contact* contact); 											//!< 충돌이 끝나고 떨어질때 자동 호출된다
	virtual void PreSolve			(b2Contact* contact, const b2Manifold* oldManifold);			//!< 물리량계산이 발생했을때(충격이 발생했을때처리^^(
	virtual void PostSolve			(const b2Contact* contact, const b2ContactImpulse* impulse);	//!< 물리량계산이 끝났을때


};