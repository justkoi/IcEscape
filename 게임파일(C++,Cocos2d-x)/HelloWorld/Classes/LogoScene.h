#pragma once

#include "stdafx.h"
USING_NS_CC;

class LogoScene : public cocos2d::CCLayer
{
public:
	CocosDenshion::SimpleAudioEngine *m_Sae;

	CCSprite* m_pLogo;
	float		m_fTimer;

public:


public:
	float ReturnWidth(float fValue);
	float ReturnHeight(float fValue);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(LogoScene);

    void Update(float dt);


};
