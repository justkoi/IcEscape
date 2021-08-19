#pragma once

#include "stdafx.h"
#define D_BASIC_CAM_OFFSET 0.0f
//=====================================================

/**
	@file    : < EMCamShakeManager >
	@author  : < 백노연 >
	@version : < 0.1 >
	@brief   : < 카메라의 설정좌표를 내부에 저장하여 흔드는 클래스 입니다. >
 */


//=====================================================

typedef enum
{
	E_DERECTION_UPDOWN,
	E_DERECTION_LEFTRIGHT,
}E_DERECTION;


class CEMCamShakeManager					//!< 카메라 흔드는 클래스 , 해당 카메라의 포인터를 내부에 가지고 자유롭게 변경
{
public:
	stEMVec3*	m_TargetCamPos;				//!< 흔들 목표 카메라

	int			m_nNowShakeNumber;			//!< 흔드는 횟수
	int			m_nMaxShakeNumber;			//!< 흔드는 횟수
	int			m_nNowRotNumber;			//!< 각도 흔드는 횟수
	int			m_nMaxRotNumber;			//!< 각도 흔드는 횟수


	float		m_fCamShakeSpeed;			//!< 흔드는 속도
	float		m_fCamShakeSpeed_Basic;		//!< 흔드는 기본 속도 (초기화 시 필요)
	float		m_fCamPlusSpeed;			//!< 흔드는 가속도
	float		m_fCamMaxShakeDistance;		//!< 흔드는 최대거리
	float		m_fCamAccrueShake;			//!< 현재까지 도달한 누적 거리
	float		m_fMaxRot;					//!< 최대 도달 각도
	float		m_fRotSpeed;				//!< 각도 흔드는 속도
	float		m_fRotAccrue;				//!< 현재까지 도달한 누적 각도

	E_DERECTION m_eDerection;				//!< 방향설정
public:

	CEMCamShakeManager()
	{

	};
	~CEMCamShakeManager()
	{

	};

	//=====================================================
	/**
		@brief     : 초기화 (타겟 카메라 좌표 보관)

		@param : 타겟카메라 좌표
		@param : 
		@param : 
		@param : 
		@param : 

		@return : 없음.
	*/
	//=====================================================
	void Init(stEMVec3*	TargetCamPos); // !< 초기화 (타겟 카메라 좌표 보관)

	//=====================================================
	/**
		@brief     : 명령조건에 만족할경우 실시간으로 여러가지 계산을 하며 흔든다.

		@param : 시간누적에 필요한 dt
		@param : 
		@param : 
		@param : 
		@param : 

		@return : 없음.
	*/
	//=====================================================
	void Update(float dt); // !< 명령조건에 만족할경우 실시간으로 흔든다
	//=====================================================
	/**
		@brief     : 흔드는 명령을 갱신한다.
		
		@param : 흔드는 방향.
		@param : 위아래로 흔드는 횟수.
		@param : 위아래로 흔드는 속도.
		@param : 위아래로 흔드는 가속도.
		@param : 위아래로 흔드는 최대거리.
		@param : 양옆 각도로 흔드는 최대거리.
		@param : 양옆 각도로 흔드는 속도.
		@param : 양옆 각도로 흔드는 횟수.


		@return : 없음.
	*/
	//=====================================================
	// ex) E_DERECTION_UPDOWN,3,300,150,10,4,2,2
	//
	void Shake(E_DERECTION eDerection, int nNumber, float fCamShakeSpeed, float fCamPlusSpeed, float	fCamMaxShakeDistance, float fMaxRot, float fRotSpeed, int nRotNumber); // !< 흔드는 명령을 갱신한다//=====================================================
	
	/**
		@brief     : 현재 흔드는 명령의 횟수를 더한다. 0보다 작을 수 없다.

		@param : 양옆으로 흔드는 횟수.
		@param : 양옆 각도로 흔드는 속도.

		@return : 없음.
	*/
	void Shake_AddNumber(int nNumber, int nRotNumber); // !< 위아래로 흔드는 명령횟수를 추가한다.
	//=====================================================
	/**
		@brief     : 현재 흔드는 중인지 확인한다.

		@param : 

		@return : bool 흔드는 중이면 true. 아닐경우 false.
	*/
	//=====================================================
	bool IsShaking(); //!< 현재 흔드는 중인지 확인한다.

};