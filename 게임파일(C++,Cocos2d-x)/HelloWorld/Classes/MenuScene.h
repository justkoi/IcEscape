#pragma once

#include "stdafx.h"
USING_NS_CC;

class MenuScene : public cocos2d::CCLayer
{
public:
	CocosDenshion::SimpleAudioEngine *m_Sae;

	CCSprite* m_pSprite;
	CCSprite* m_pTitle;
	CCSprite* m_pBlind;
	CCSprite* m_pPopUp;

	CCSprite* m_pPopUp_BGM;
	CCSprite* m_pPopUp_Effect;
	
	CCSprite* m_pGameLevel;
	float m_fGLTimer;

	bool m_bPopUp;

	CCParticleSnow* m_pSnow;

	
	float		m_fTimer;
	float		m_fUpDownTime;
	float		m_fUpDownSpeed;
	float		m_fUpDownPlusTime;
	bool		m_fUpDown;

	CCMenuItemImage* pCancelItem;
	CCMenu* pCancel;

	


	CCMenuItemImage* pGameStartItem;
	CCMenu* pGameStart;

	
	CCMenuItemImage* pCreditItem;
	CCMenu* pCreditStart;

	CCMenuItemImage* pOptionItem;
	CCMenu* pOption;

	CCMenuItemImage* pExitItem;
	CCMenu* pExit;


	CCMenuItemImage* pBGM_SoundOnItem;
	CCMenu* pBGM_SoundOn;

	
	CCMenuItemImage* pBGM_SoundOffItem;
	CCMenu* pBGM_SoundOff;
	
	CCMenuItemImage* pEFFECT_SoundOnItem;
	CCMenu* pEFFECT_SoundOn;

	
	CCMenuItemImage* pEFFECT_SoundOffItem;
	CCMenu* pEFFECT_SoundOff;
	


	CCSprite* m_pLoading;

	CCLabelTTF* m_pText;

	float m_fMenuTimer;
	float m_fMenuSpeed;
public:


public:
	void SaveOption();
	bool LoadOption();
	

	float ReturnWidth(float fValue);
	float ReturnHeight(float fValue);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void GameStartCallback(CCObject* pSender);
    void CreditCallback(CCObject* pSender);
    void ExitCallback(CCObject* pSender);
    void OptionCallback(CCObject* pSender);
    void CancelCallback(CCObject* pSender);
	
    void BGM_SoundOnCallback(CCObject* pSender);
    void BGM_SoundOffCallback(CCObject* pSender);

	
    void EFFECT_SoundOnCallback(CCObject* pSender);
    void EFFECT_SoundOffCallback(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(MenuScene);

    void Update(float dt);


};
