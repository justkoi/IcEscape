#pragma once

#include "EM2DEngine.h"


/*
	1. ���� �Ⱥ��� Plane
		- ������ ���� �ʾ����Ƿ� �浹 ����� ����ڰ� ���� ������մϴ�
*/
class CLogo : public CRootScene
{
public:
	
	CEMPlane*	m_pBlack[2];
public:
	CEMPlane* m_pSkipImg[3];
	CEMStyleButton m_Skip;// !< Skip��ư
	CEMPlane*	m_pPlane;	//!< Plane ���

	stEMVec3	m_stCamPos;	//!< ī�޶� ��ġ ���� ����

	float		m_fTimer;
	bool m_fChange;

public:
	float		m_fRot;		
	float		m_fSize;	

public:
	CLogo(void)
	{	
		m_pPlane = NULL;
		m_fRot = 0.0f;
		m_fSize = 3.0f;
		
		m_stCamPos = stEMVec3(0.0f, 3.0f,400.0f);
	};
	virtual ~CLogo(void)
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