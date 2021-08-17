#pragma once


#include "stdafx.h" 
using namespace std;

USING_NS_CC;

class CFish
{
private:
	CCLayer* m_pThisScene;			//!< 출력 대상 신
	float m_fMoveSpeedX;//!<
	float m_fMoveSpeedY;//!<
	CCPoint m_stPos;
	float m_fT;
	float m_fG;


public:
	CCAnimation* m_pFishAni;
	CCActionInterval * m_pFishAnt;
	CCSprite * m_pFish;

	void Init(CCLayer* pThisScene);
	void Update(float dt, CBlock * BlockList, CEffectManager* EffectManager,CocosDenshion::SimpleAudioEngine *Sae );
	void Exit();


public:
	
	bool HitTest(CCPoint stPos1, CCPoint stPixel1, CCPoint stPos2, CCPoint stPixel2);

};