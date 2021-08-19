#pragma once

#include "stdafx.h"


/*
	1. ���� �Ⱥ��� Plane
		- ������ ���� �ʾ����Ƿ� �浹 ����� ����ڰ� ���� ������մϴ�
*/
class CMenu : public CRootScene
{
public:

	CEMPlane*	m_pBlack[2];
	
	CEMStyleButton m_SoundButton;
	CEMPlane*	m_pSoundButtonImg[3];
	
	CEMStyleButton m_SoundButton2;
	CEMPlane*	m_pSoundButton2Img[3];


	//CEMStyleButton m_Skip;// !< Skip��ư
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

	CEMPlane*	m_pPlane;	//!< Plane ���
	CEMPlane*	m_pHero;	//!< Plane ���

	float		m_fTimer;
	float		m_fUpDownTime;
	float		m_fUpDownSpeed;
	float		m_fUpDownPlusTime;
	bool		m_fUpDown;
	
	//CEMPlane*	m_pVib[D_LOGOVIB_MAX];	//!< Plane ���

	CEMPlane*	m_pButtonImg[3];	//!< Plane ���

	CEMPlane*	m_pBg;	//!< Plane ���

	stEMVec3	m_stCamPos;	//!< ī�޶� ��ġ ���� ����
	
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