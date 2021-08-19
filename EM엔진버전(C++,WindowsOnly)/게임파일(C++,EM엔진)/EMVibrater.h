#pragma once 

#include "stdafx.h"

typedef enum
{
	E_DERECTION_UP,
	E_DERECTION_DOWN,
}E_DERECTION_VIB;

typedef enum
{
	E_VIBACT_STATE_NONE,
	E_VIBACT_STATE_ACT,
	E_VIBACT_STATE_VIB,
	E_VIBACT_STATE_STOP,
}E_VIBACT_STATE;

typedef struct
{
	CEMPlane* m_pPlane;
	
	float	m_fSpeed;
	float	m_fPlusSpeed;
	float	m_fBasicLine;
	float   m_fLastBasicLine;
	float	m_fVibDistance;
	float	m_fNowVibDistance;
	bool   m_bTurn;				//���� ��� ǥ�� true�� ��� ���ư��� ������ �����Ͽ� ���� �������� ���δ�.
	E_VIBACT_STATE m_eState;
	E_DERECTION_VIB	m_eDerection;

}stEMVibrain;

class CEMVibrater
{
private:
	CRootScene* m_pThisScene; //!< Commit�� �ʿ��� CRootScene�� �����͸� ����
	list<stEMVibrain*> m_VibrainList; //!< ���׸� ���ڸ� ���� ����Ʈ ����

	float	m_fSpeed;				//!< �⺻ �ӵ�
	float	m_fPlusSpeed;			//!< ���ӵ�
	float	m_fBasicLine;			//!< ������ ���ؼ�
	float   m_fLastBasicLine;		//!< �������� ���� ���ؼ� (��Ȯ�� ���� ���� ��츦 ���)
	float	m_fVibDistance;			//!< ���� ��

	float	m_fVibDistanceScale;    //!< ���� �� ���̴� ���� (�����)
	float	m_fVibDistanceMinus;    //!< ���� �� ���̴� ���� (����)

	E_DERECTION m_eDerection;		//!< ����
	
	bool	m_bStart;				//!< �÷��� ��
	bool	m_bSkip; //!<Skip��
public:
	bool IsVibrating();
	bool IsEnd();

	void Init(CRootScene* pThisScene,float fSpeed,float fPlusSpeed,float fBasicLine, float fLastBasicLine,float fVibDistance,float fVibDistanceScale, float fVibDistanceMinus); //!< �ʱ�ȭ
	void Update(float dt);
	void Exit();

	void Input(CEMPlane* pPlane);
	void Input(CEMPlane* pPlane, float fSpeed,float fPlusSpeed,float fBasicLine, float fLastBasicLine,float fVibDistance, E_VIBACT_STATE eState);


	void Start();


	void Pause();
	void Stop();
	void Skip();

};