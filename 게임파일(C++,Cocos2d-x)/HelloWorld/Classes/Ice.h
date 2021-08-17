#pragma once

#include "stdafx.h"

USING_NS_CC;

class CIce
{
private:
	CCPoint m_stPos;
	CCPoint m_stTargetPos;

	CCPoint m_stMoveSpeed;

	//float m_fSpitTimer; //!<  Ƣ��� �ð�
	//float m_fSpitDistance; //!< Ƣ��� Y�� �̵��� ����

	bool m_bHited;
	float m_fAlphaTimer;
	float m_fG;
	float m_fT;

public:
	
	CCSprite* m_pPlane;

	void Init(CCLayer* pThisScene, CCPoint stPos);
	void Update(float dt);
	void Exit();

public:
	bool Hited();
	bool Finished();
};