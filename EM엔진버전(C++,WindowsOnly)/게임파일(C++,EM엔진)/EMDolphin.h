#pragma once 

#include "stdafx.h"

typedef enum
{
	E_DOLPHIN_STATE_NONE,
	E_DOLPHIN_STATE_PLAY

}E_DOLPHIN_STATE;


class CEMDolphin
{
public:

	float	m_fCreateTime;
	float	m_fCreateTimer;
	CRootScene* m_pThisScene;

	CEMAnimation* m_pDolphin;
	stEMVec2 m_stPos;
	float	 m_fG;
	float	 m_fT;
	float    m_fJumpSpeed;
	float	 m_fJumpPower;

	float	 m_fMoveSpeed;
	E_DOLPHIN_STATE m_eState;


public:

	void Init(CRootScene* m_pThisScene, int Index,  float CreateTime);
	void Update(float dt, list<CEMBlock*> BlockList);
	void Exit();


};