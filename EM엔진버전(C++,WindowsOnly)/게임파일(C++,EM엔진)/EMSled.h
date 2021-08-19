#pragma once 

#include "stdafx.h"

class CEMSled
{
public:

	float	m_fMoveSpeed;
	float	m_fHp;
	float	m_fMaxHp;


	CEMPlane* m_pSled;
	CEMPlane* m_pSled_IceLoad;

	stEMVec2 m_stPos;
	
	bool m_bOnOff;
	bool m_bSledMoved;


public:

	void Init(CRootScene* m_pThisScene);
	void Update(float dt);
	void Exit();

	void Sleding();

};