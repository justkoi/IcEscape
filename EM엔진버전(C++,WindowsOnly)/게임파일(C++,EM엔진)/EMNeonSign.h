
#pragma once

#include "stdafx.h"
//=====================================================

/**
	@file    : < CEMNeonSign >
	@author  : < ��뿬 >
	@version : < 0.1 >
	@brief   : < ������ �������� �����ٶ��� ����ϴ� �׿»��� Ŭ�����Դϴ�. >
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

	int			m_nSpeed; //�������� ������

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