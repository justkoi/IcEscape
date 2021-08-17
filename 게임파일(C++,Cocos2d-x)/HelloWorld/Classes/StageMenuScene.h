#pragma once

#include "stdafx.h"
USING_NS_CC;

typedef struct 
{
	float m_fTimeLimit;  //!< 제한시간
	float m_fCraeteTime; //!< 생성시간
	float m_fErosionSpeed; //!< 침식속도
	int m_nErosionPlusSpeed; //!< 침식가속도
	float m_fSeaLevelMax; //!< 최대 해수면 게이지
}stStageInfo;


class StageMenuScene : public cocos2d::CCLayer
{
public:
	CocosDenshion::SimpleAudioEngine *m_Sae;

	CCSprite* m_pBackGround;

	CCParticleSnow* m_pSnow;
	//CNumber m_pNumberSample;
	float m_fStarRot;

	CNumber m_CNumber[D_STAGE_MAX];
	//CCSprite* m_pNumber[D_STAGE_MAX];
	CCMenuItemImage* m_pPlayItem[D_STAGE_MAX];
	CCMenu* m_pPlay[D_STAGE_MAX];
	CCSprite* m_pLock[D_STAGE_MAX];
	CCSprite* m_pStar[D_STAGE_MAX][3];
	
	
	float		m_fTimer;


	
	CCMenuItemImage* pBackItem;
	CCMenu* pBack;
/*
	
	CCMenuItemImage* pResetItem;
	CCMenu* pReset;
	
	CCMenuItemImage* pNextItem;
	CCMenu* pNext;*/
	
	float m_fScroll_Y_Vector; //!< 스크롤변화량
	float m_fScroll_Y_All; //!< 총변화량
	float m_fScroll_Y_Smooth;
	float m_fStart_Y;
	//float m_fMove_Y;



	CCSprite* m_pLoading;
public:
	void SaveStage();
	void LoadStage();
	void ShowUpdateLock();
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 
	
	float ReturnWidth(float fValue);
	float ReturnHeight(float fValue);

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void BackCallback(CCObject* pSender);

    void ResetCallback(CCObject* pSender);
    void NextCallback(CCObject* pSender);

	
	void StageCallback1(CCObject* pSender);
	void StageCallback2(CCObject* pSender);
	void StageCallback3(CCObject* pSender);

	void StageCallback4(CCObject* pSender);
	void StageCallback5(CCObject* pSender);
	void StageCallback6(CCObject* pSender);

	
	void StageCallback7(CCObject* pSender);
	void StageCallback8(CCObject* pSender);
	void StageCallback9(CCObject* pSender);
	
	void StageCallback10(CCObject* pSender);
	void StageCallback11(CCObject* pSender);
	void StageCallback12(CCObject* pSender);
	
	void StageCallback13(CCObject* pSender);
	void StageCallback14(CCObject* pSender);
	void StageCallback15(CCObject* pSender);
	
	void StageCallback16(CCObject* pSender);
	void StageCallback17(CCObject* pSender);
	void StageCallback18(CCObject* pSender);
	
	void StageCallback19(CCObject* pSender);
	void StageCallback20(CCObject* pSender);
	void StageCallback21(CCObject* pSender);

	virtual void  registerWithTouchDispatcher();

	virtual bool  ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void  ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent); 
	virtual void  ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent);

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(StageMenuScene);

    void Update(float dt);


};

