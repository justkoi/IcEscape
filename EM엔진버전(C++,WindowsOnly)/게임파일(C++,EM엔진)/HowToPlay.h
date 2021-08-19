#pragma once

#include "stdafx.h"


class CHowToPlay : public CRootScene
{
public:

	
	CEMPlane*	m_pBlack[2];
public:

	CEMStyleButton	m_Back;
	CEMPlane*		m_BackButton[3];

	
	CEMStyleButton	m_Stage;
	CEMPlane*		m_StageButton[3];
	CEMPlane*	m_pBg;	//!< Plane 출력

	CEMPlane*	m_Maker;
	

	stEMVec3	m_stCamPos;	//!< 카메라 위치 저장 벡터
	
	CEMPlane*	m_pBlind;

public:
	float		m_fRot;		
	float		m_fSize;	

public:
	CHowToPlay(void)
	{	

		m_fRot = 0.0f;
		m_fSize = 3.0f;

	};
	virtual ~CHowToPlay(void)
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