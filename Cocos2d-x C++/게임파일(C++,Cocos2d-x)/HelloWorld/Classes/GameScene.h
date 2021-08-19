#pragma once

#include "stdafx.h" 
#include <vector>
#include <list>
using namespace std;

USING_NS_CC;

typedef enum
{
	E_BLOCKACT_NONE,
	E_BLOCKACT_MOVE,
	E_BLOCKACT_DRAG,
	E_BLOCKACT_NOT
}E_BLOCKACT;
typedef enum
{
	E_GAMERESULT_NONE,
	E_GAMERESULT_VICTORY,
	E_GAMERESULT_DEFEAT,

}E_GAMERESULT;
typedef enum
{
	E_GAMESTEP_READY,
	E_GAMESTEP_PLAY,
	E_GAMESTEP_END,

}E_GAMESTEP;

class GameScene : public cocos2d::CCLayer
{
public:

	list<CSled*> m_SledList;
	list<CIce*> m_IceList;
	
	CFish m_Fish;


	CocosDenshion::SimpleAudioEngine *m_Sae;
	CEffectManager m_EffectManager;
	float		m_fTimer;
	float		m_fIceTime; //!< 얼음조각에 의해 증가하는 타이머
	CMap* m_Map;

	CSeaLevel m_CSeaLevel;

	bool m_bFreeMove;
	float fTtTiemr;

	float		m_fUpDownTime;
	float		m_fUpDownSpeed;
	float		m_fUpDownPlusTime;
	bool		m_fUpDown;

	//list

	int m_nStage;

	CCPoint m_stMoveBlockPos;
	
	double		m_lfUpDownNumX;
	double		m_lfUpDownNumY;

	double		m_lfNewTouchX;
	double		m_lfNewTouchY;

	double		m_lfLastTouchX;
	double		m_lfLastTouchY;

	double		m_lfSlideNumX[D_SLIDE_NUM_MAX];
	double		m_lfSlideNumY[D_SLIDE_NUM_MAX];
	
	CCLabelTTF* m_pSensNumX;
	CCLabelTTF* m_pSensNumY;

	CNumber m_pNumberTimeLimit;
	CNumber m_pNumberStage;
	CNumber m_pNumberScore;
	CNumber m_pNumberLastScore;


	float		m_fCreateTimer;
	float		m_fCraeteTime;

	float		m_fTimeLimit;

	bool		m_nStageStepToNext;

	float m_fSensNumX;
	float m_fSensNumY;

	float m_fWarningTimer;
	
	E_GAMERESULT m_eGameResult;
	E_GAMESTEP m_eGameStep;

	CCSprite* m_pBackGround[5];
	
	CCSprite* m_pWarning;
	
	CCSprite* m_pCreateBar;
	
	CCSprite* m_pStar[3];
	
	CCSprite* m_pGameOver;
	CCSprite* m_pGameClear;

	CCSprite* m_pSeaLevel;
	
	CCSprite* m_pBlind;
	CCSprite* m_pGhost;

	CCSprite* m_pTtMsg[D_MAX_TTMSG];

	CCSprite* m_pDisplay_Ready;
	CCSprite* m_pDisplay_Go;

	CCPoint	 m_stPos;

	float	m_fReadySpeed;
	int		m_nReadyFlag;


	
	bool m_bNeedDelete;
	stVec2i m_stNeedIndex;
	
	float		m_fErosionSpeed; //!< 갈수록 빨라지는 침식속도
	int			m_nErosionPlusSpeed;//!< 침식가속도

	float m_fBlindTimer;
	float m_fPopUpTimer;


	
	


	
	CCSprite* m_pPause;

	CCMenuItemImage* pSetItem;
	CCMenu* pSet;

	CCMenuItemImage* pResumeItem;
	CCMenu* pResume;

	CCMenuItemImage* pPauseItem;
	CCMenu* pPause;



	list<CBlock*> m_MouseList;
	list<CBlock*> m_PopList;

	CBlock* m_MoveBlock;
	list<CIceChunk*> m_IceChunkList;

	E_BLOCKACT	m_eBlockAct;
	CBlock * m_BlockList;

	int m_nBlockMax;
	bool m_bMouseDown;
	bool m_bBlockAct;
	
	bool m_bSaved;

	//CCDictionary
	
	//list<CBlock*> m_BlockList;
	//list<CBlock*> m_MouseList;
	float _shipPointsPerSecY;
	
	CCSprite* m_pLoading;

	int m_nTtLevel; //!< 튜토리얼 레벨

	float m_fReadyTimer; //!< 타이머


public:
	
	float ReturnWidth(float fValue);
	float ReturnHeight(float fValue);

	void SaveStage();
	void LoadStage();




	void		CreateBlock();
	
	void		CreateBlock(int nY);
	void		CreateBlockIt(int nX, int nY, E_BLOCKNUMBER eBlockNumber);
	
	void		CreateBlock(int nX, int nY);
	void		CreateLine();
	
	void		ReadMap(int nStage);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void GameStartCallback(CCObject* pSender);
    void BackCallback(CCObject* pSender);

    void PauseCallback(CCObject* pSender);
    void ResumeCallback(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(GameScene);
	
	void onEnter();
	void onExit();

	void IceExplosion(float fX, float fY);

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);

	virtual void  registerWithTouchDispatcher();
	//ccTouchBegan
	virtual bool  ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void  ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent); 
	virtual void  ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent) ;
	//virtual void  ccTouchesCancelled (cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) ;

    void Update(float dt);


};

