
#pragma once

#include "stdafx.h"
//=====================================================

/**
	@file    : < CEMNeonSign >
	@author  : < 백노연 >
	@version : < 0.1 >
	@brief   : < 만든이 같은것을 보여줄때에 사용하는 네온사인 클래스입니다. >
 */

//=====================================================

typedef enum
{
	E_NEONSTATE_NONE,
	E_NEONSTATE_MOVE,


}E_NEONSTATE;
class CEMNeonSign
{
public:

	CRootScene* m_pThisScene;

	stEMVec2	m_Pos;
	stEMVec2	m_stSize;
	stEMVec2*	m_MoveSpeed;
	CEMPlane**  m_pTile;
	int			m_nMaxTile;
	int			m_nWidth;
	int			m_nHeight;
	int			m_nTemp;

	int			m_nStage;
	bool		m_bTrue;

	float		m_fTimer;
	int			m_nLevel;

	int			m_nSpeed; //작을수록 빠르다

	E_NEONSTATE m_eNeonState;

public:

	CEMNeonSign()
	{

	};
	~CEMNeonSign()
	{

	};

	void Init(float m_fX, float m_fY, int nSpeed, stEMVec2 stSize, CRootScene* pThisScene);
	void Update(float dt);
	void SetTile(int nStage);

};