#pragma once

#include "stdafx.h"




		/*



	1. ���� �Ⱥ��� Plane
		- ������ ���� �ʾ����Ƿ� �浹 ����� ����ڰ� ���� ������մϴ�



		*/





typedef struct stStageInfo
{
	float m_fTimeLimit; 
	float m_fCraeteTime;
	float m_fErosionSpeed;
	int m_nErosionPlusSpeed;
	int m_nMaxSnow;
};


class CStageMenu : public CRootScene
{
public:
	
	CEMPlane*	m_pBlack[2];
	//CEMVibrater*	m_pVibrater;
	//CEMTextDisplay*	m_pTextBox;

	
	CEMStyleButton	m_Back;
	CEMPlane*		m_BackButton[3];

	CEMStyleButton*		m_Button;
	CEMPlane***			m_pButtonImg;
	CEMNumber**			m_NumberButton;

	CEMPlane***		m_pStar;
public:

	CEMPlane*	m_pHero;	//!< Plane ���
	

	float		m_fStarRot;
	CEMPlane*	m_pBg;	//!< Plane ���

	stEMVec3	m_stCamPos;	//!< ī�޶� ��ġ ���� ����
	
	//CEMPlane*	m_pBlind;
	//float		m_pBlindTimer;
	//float		m_pBlindSpeed;
	//bool		m_bButtonAppear;

public:
	float		m_fRot;		
	float		m_fSize;


public:
	CStageMenu(void)
	{	
		
		m_pBg = NULL;

		m_fRot = 0.0f;
		m_fSize = 3.0f;
		
		m_stCamPos = stEMVec3(0.0f, 3.0f,400.0f);
	};
	virtual ~CStageMenu(void)
	{
		
	};
	void LoadStage();
	void SaveStage();

	
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