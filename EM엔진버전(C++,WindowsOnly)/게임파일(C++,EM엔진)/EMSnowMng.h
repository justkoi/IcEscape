#pragma once 

#include "stdafx.h"
typedef enum
{
	E_SNOW_OPTION_MENU,
	E_SNOW_OPTION_STAGE,
}E_SNOW_OPTION_SCENE;
typedef struct 
{
	CEMPlane* m_pSnow;
	stEMVec2 m_stPos;
	stEMVec2 m_stSize;
	float	 m_fRot;
	float	 m_fRotSpeed;
}stSnow;

class CEMSnowMng
{
private:
	CRootScene*	m_pThisScene;
	stSnow* m_stSnowList;
	int m_nMaxSnow;
	int m_fSpeed;
	E_SNOW_OPTION_SCENE m_eSnowOption;
	CEMColor m_SnowColor;

public:

	void Init(CRootScene* pScene, int nMaxSnow, E_SNOW_OPTION_SCENE eSnowOption, CEMColor SnowColor, float fSpeed);
	void Update(float dt);
	void Exit();

};