#pragma once

#include "stdafx.h"
#define D_BASIC_CAM_OFFSET 0.0f
//=====================================================

/**
	@file    : < EMCamShakeManager >
	@author  : < ��뿬 >
	@version : < 0.1 >
	@brief   : < ī�޶��� ������ǥ�� ���ο� �����Ͽ� ���� Ŭ���� �Դϴ�. >
 */


//=====================================================

typedef enum
{
	E_DERECTION_UPDOWN,
	E_DERECTION_LEFTRIGHT,
}E_DERECTION;


class CEMCamShakeManager					//!< ī�޶� ���� Ŭ���� , �ش� ī�޶��� �����͸� ���ο� ������ �����Ӱ� ����
{
public:
	stEMVec3*	m_TargetCamPos;				//!< ��� ��ǥ ī�޶�

	int			m_nNowShakeNumber;			//!< ���� Ƚ��
	int			m_nMaxShakeNumber;			//!< ���� Ƚ��
	int			m_nNowRotNumber;			//!< ���� ���� Ƚ��
	int			m_nMaxRotNumber;			//!< ���� ���� Ƚ��


	float		m_fCamShakeSpeed;			//!< ���� �ӵ�
	float		m_fCamShakeSpeed_Basic;		//!< ���� �⺻ �ӵ� (�ʱ�ȭ �� �ʿ�)
	float		m_fCamPlusSpeed;			//!< ���� ���ӵ�
	float		m_fCamMaxShakeDistance;		//!< ���� �ִ�Ÿ�
	float		m_fCamAccrueShake;			//!< ������� ������ ���� �Ÿ�
	float		m_fMaxRot;					//!< �ִ� ���� ����
	float		m_fRotSpeed;				//!< ���� ���� �ӵ�
	float		m_fRotAccrue;				//!< ������� ������ ���� ����

	E_DERECTION m_eDerection;				//!< ���⼳��
public:

	CEMCamShakeManager()
	{

	};
	~CEMCamShakeManager()
	{

	};

	//=====================================================
	/**
		@brief     : �ʱ�ȭ (Ÿ�� ī�޶� ��ǥ ����)

		@param : Ÿ��ī�޶� ��ǥ
		@param : 
		@param : 
		@param : 
		@param : 

		@return : ����.
	*/
	//=====================================================
	void Init(stEMVec3*	TargetCamPos); // !< �ʱ�ȭ (Ÿ�� ī�޶� ��ǥ ����)

	//=====================================================
	/**
		@brief     : ������ǿ� �����Ұ�� �ǽð����� �������� ����� �ϸ� ����.

		@param : �ð������� �ʿ��� dt
		@param : 
		@param : 
		@param : 
		@param : 

		@return : ����.
	*/
	//=====================================================
	void Update(float dt); // !< ������ǿ� �����Ұ�� �ǽð����� ����
	//=====================================================
	/**
		@brief     : ���� ����� �����Ѵ�.
		
		@param : ���� ����.
		@param : ���Ʒ��� ���� Ƚ��.
		@param : ���Ʒ��� ���� �ӵ�.
		@param : ���Ʒ��� ���� ���ӵ�.
		@param : ���Ʒ��� ���� �ִ�Ÿ�.
		@param : �翷 ������ ���� �ִ�Ÿ�.
		@param : �翷 ������ ���� �ӵ�.
		@param : �翷 ������ ���� Ƚ��.


		@return : ����.
	*/
	//=====================================================
	// ex) E_DERECTION_UPDOWN,3,300,150,10,4,2,2
	//
	void Shake(E_DERECTION eDerection, int nNumber, float fCamShakeSpeed, float fCamPlusSpeed, float	fCamMaxShakeDistance, float fMaxRot, float fRotSpeed, int nRotNumber); // !< ���� ����� �����Ѵ�//=====================================================
	
	/**
		@brief     : ���� ���� ����� Ƚ���� ���Ѵ�. 0���� ���� �� ����.

		@param : �翷���� ���� Ƚ��.
		@param : �翷 ������ ���� �ӵ�.

		@return : ����.
	*/
	void Shake_AddNumber(int nNumber, int nRotNumber); // !< ���Ʒ��� ���� ���Ƚ���� �߰��Ѵ�.
	//=====================================================
	/**
		@brief     : ���� ���� ������ Ȯ���Ѵ�.

		@param : 

		@return : bool ���� ���̸� true. �ƴҰ�� false.
	*/
	//=====================================================
	bool IsShaking(); //!< ���� ���� ������ Ȯ���Ѵ�.

};