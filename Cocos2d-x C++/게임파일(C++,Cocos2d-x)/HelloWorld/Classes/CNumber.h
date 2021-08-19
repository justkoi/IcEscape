#pragma once 
#include "stdafx.h"

class CNumber
{
private:
	vector<CCSprite*> m_pNumberList;//!< 보관될 넘버
	int m_nNumber;//!< 표시할 숫자
	int m_nTargetNumber;//!< 표시할 숫자
	CCLayer* m_pThisScene;
	int m_nLayer;
	bool m_bVisible;

public:
	CCPoint m_stPos;
	CCPoint m_stSize;

public:
	void Init(CCLayer* pThisScene, CCPoint stSize, int nNumber, CCPoint stPos, int nLayer);
	void Update(float dt);
	void Exit();

	void SetNumber(int nNumber);
	void SetSize(CCPoint stSize);
	void SetVisible(bool bVisible);
	void EffectNumber(int nNumber);
	void SetPositionY(float fPosY);
};