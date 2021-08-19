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
	bool   m_bTurn;				//도는 경우 표시 true일 경우 돌아가는 것으로 간주하여 다음 진동폭을 줄인다.
	E_VIBACT_STATE m_eState;
	E_DERECTION_VIB	m_eDerection;

}stEMVibrain;

class CEMVibrater
{
private:
	CRootScene* m_pThisScene; //!< Commit에 필요한 CRootScene의 포인터를 보관
	list<stEMVibrain*> m_VibrainList; //!< 조그만 글자를 담을 리스트 생성

	float	m_fSpeed;				//!< 기본 속도
	float	m_fPlusSpeed;			//!< 가속도
	float	m_fBasicLine;			//!< 굴러들어갈 기준선
	float   m_fLastBasicLine;		//!< 구른후의 최종 기준선 (정확히 맞지 않을 경우를 대비)
	float	m_fVibDistance;			//!< 진동 폭

	float	m_fVibDistanceScale;    //!< 진독 폭 줄이는 비율 (백분율)
	float	m_fVibDistanceMinus;    //!< 진독 폭 줄이는 비율 (고정)

	E_DERECTION m_eDerection;		//!< 방향
	
	bool	m_bStart;				//!< 플레이 중
	bool	m_bSkip; //!<Skip중
public:
	bool IsVibrating();
	bool IsEnd();

	void Init(CRootScene* pThisScene,float fSpeed,float fPlusSpeed,float fBasicLine, float fLastBasicLine,float fVibDistance,float fVibDistanceScale, float fVibDistanceMinus); //!< 초기화
	void Update(float dt);
	void Exit();

	void Input(CEMPlane* pPlane);
	void Input(CEMPlane* pPlane, float fSpeed,float fPlusSpeed,float fBasicLine, float fLastBasicLine,float fVibDistance, E_VIBACT_STATE eState);


	void Start();


	void Pause();
	void Stop();
	void Skip();

};