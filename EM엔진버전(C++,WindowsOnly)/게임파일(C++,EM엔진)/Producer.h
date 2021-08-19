#pragma once

#include "stdafx.h"


class CProducer : public CRootScene
{
public:
	
	CEMPlane*	m_pBlack[2];
	CEMStyleButton	m_Button;
	//CEMSnowMng*	m_SnowMng;
	CEMNeonSign	m_NeonSign;

	CEMStyleButton	m_Back;
	CEMPlane*		m_BackButton[3];

public:

	CEMPlane*	m_pPlane;	//!< Plane ���
	

	CEMPlane*	m_pBg;	//!< Plane ���

	CEMPlane*	m_Maker;
	CEMPlane*	m_Maker2;
	CEMPlane*	m_Maker3;
	

	stEMVec3	m_stCamPos;	//!< ī�޶� ��ġ ���� ����
	
	CEMPlane*	m_pBlind;
	float		m_pBlindTimer;
	float		m_pBlindSpeed;
	bool		m_bButtonAppear;

	float		m_Speed;
	float		m_Speed1;
	float		m_Speed2;

	bool		m_Maker1EndCheck;
	bool		m_Maker2EndCheck;
	bool		m_Maker3EndCheck;
	
	float		m_fBlendTimer;

public:
	float		m_fRot;		
	float		m_fSize;	

public:
	CProducer(void)
	{	
		m_pPlane = NULL;

		m_pBg = NULL;
		m_pBlind = NULL;

		m_fRot = 0.0f;
		m_fSize = 3.0f;
		
		m_Speed = 190.0f;
		m_Speed1 = 190.0f;
		m_Speed2 = 190.0f;

		m_Maker1EndCheck = false;
		m_Maker2EndCheck = false;
		m_Maker3EndCheck = false;

		m_stCamPos = stEMVec3(0.0f, 3.0f,400.0f);
	};
	virtual ~CProducer(void)
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