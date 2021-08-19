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
	CEMPlane*	m_pBg;	//!< Plane ���

	CEMPlane*	m_Maker;
	

	stEMVec3	m_stCamPos;	//!< ī�޶� ��ġ ���� ����
	
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
	virtual void Enter				(CSceneWork* pSceneWork);										//!< ����(�ε�)
	virtual void Update				(CSceneWork*, float dt);										//!< Update
	virtual void Render				(CSceneWork*);													//!< Render
	virtual void Exit				(CSceneWork* pSceneWork);										//!< Ż��(�޸� ������)
	virtual void MouseDownEvent		(stMouseInfo stPos, enumMouseButton eButton);					//!< ���콺 �ٿ� �̺�Ʈ
	virtual void MouseUpEvent		(stMouseInfo stPos, enumMouseButton eButton);					//!< ���콺 �� �̺�Ʈ
	virtual void MouseMoveEvent		(stMouseInfo stPos);											//!< ���콺 �̵� �̺�Ʈ
	virtual HRESULT WindowMessage	(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);			//!< ������ �̺�Ʈ

	//!=================================================================================================
	//! ���� �浹 �̺�Ʈ�� �Դϴ�.
	virtual void BeginContact		(b2Contact* contact); 											//!< �浹����  �Ǹ� �ڵ� ȣ��ȴ�
	virtual void EndContact			(b2Contact* contact); 											//!< �浹�� ������ �������� �ڵ� ȣ��ȴ�
	virtual void PreSolve			(b2Contact* contact, const b2Manifold* oldManifold);			//!< ����������� �߻�������(����� �߻�������ó��^^(
	virtual void PostSolve			(const b2Contact* contact, const b2ContactImpulse* impulse);	//!< ����������� ��������


};