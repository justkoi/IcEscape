#pragma once

#include "stdafx.h"

USING_NS_CC;

class CreditScene : public cocos2d::CCLayer
{
public:
	CocosDenshion::SimpleAudioEngine *m_Sae;
	CCParticleSystem *emitter[3];
	CCSprite* m_pBg[2];
	CCSprite* m_pBlind;

	CCSprite* m_pProducer[4];

	int	  m_nStep;
	float m_fTimer;
	float m_fBlendTimer;

	float m_fSpeed;
	float m_fPlusSpeed;

	CCMenuItemImage* pBackItem;
	CCMenu* pBack;
	
	CCSprite* m_pLoading;
public:
	float ReturnWidth(float fValue);
	float ReturnHeight(float fValue);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void BackCallback(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(CreditScene);

    void Update(float dt);


};
