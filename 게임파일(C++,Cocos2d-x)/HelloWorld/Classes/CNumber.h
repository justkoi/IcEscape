#pragma once 
#include "stdafx.h"

class CNumber
{
private:
	vector<CCSprite*> m_pNumberList;//!< ������ �ѹ�
	int m_nNumber;//!< ǥ���� ����
	int m_nTargetNumber;//!< ǥ���� ����
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