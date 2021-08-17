#include "stdafx.h"

USING_NS_CC;

CCScene* CreditScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    CreditScene *layer = CreditScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

float CreditScene::ReturnWidth(float fValue)
{
	fValue = fValue - 240;
	return (g_PhoneSize.width/2) + fValue;
}
float CreditScene::ReturnHeight(float fValue)
{
	fValue = fValue - 400;
	return (g_PhoneSize.height/2) + fValue;
}
// on "init" you need to initialize your instance
bool CreditScene::init()
{

    CCSize size = CCDirector::sharedDirector()->getWinSize();
	

	m_fTimer = 0.0f;



    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	
	m_Sae->preloadEffect("StageStart.mp3");
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    pBackItem = CCMenuItemImage::create(
                                        "Button_Back_1.png",
                                        "Button_Back_3.png",
                                        this,
										menu_selector(CreditScene::BackCallback) );
    pBackItem->setPosition( ccp( ReturnWidth(50), ReturnHeight(25)) );
    pBack = CCMenu::create(pBackItem, NULL);

	pBack->setPosition( CCPointZero );
	pBack->setScaleX(1.00f * D_SCALE_WIDTH);
	pBack->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(pBack, 30);


	// add a "close" icon to exit the progress. it's an autorelease object
   

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    // ask director the window size

    // position the label on the center of the screen
    //pLabel->setPosition( ccp(size.width / 2, size.height - 50) );

    // add the label as a child to this layer
    //this->addChild(pLabel, 1);i


	// 스프라이트 등록 ////////////////////////////
    m_pBg[0] = CCSprite::create("Credit_Bg1.png");
	m_pBg[0]->setPosition( ccp(240 * D_SCALE_WIDTH, 400 * D_SCALE_HEIGHT));
	m_pBg[0]->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pBg[0]->setScaleY(1.0f * D_SCALE_HEIGHT);
    this->addChild(m_pBg[0], 0);

	m_pBg[1] = CCSprite::create("Credit_Bg2.png");
	m_pBg[1]->setPosition( ccp(240 * D_SCALE_WIDTH, 400 * D_SCALE_HEIGHT));
	m_pBg[1]->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pBg[1]->setScaleY(1.0f * D_SCALE_HEIGHT);
    this->addChild(m_pBg[1], 1);

	/////////////////////////////////////////////////
    // 스프라이트 등록 ////////////////////////////
    m_pBlind = CCSprite::create("Blind.png");
	m_pBlind->setPosition( ccp(240 * D_SCALE_WIDTH, 400 * D_SCALE_HEIGHT));
	m_pBlind->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pBlind->setScaleY(1.0f * D_SCALE_HEIGHT);
	m_pBlind->setOpacity(255 * 0.7);
    this->addChild(m_pBlind, 2);
	/////////////////////////////////////////////////
	
	// 스프라이트 등록 ////////////////////////////
    m_pProducer[2] = CCSprite::create("Maker3.png");
    m_pProducer[2]->setPosition( ccp(240 * D_SCALE_WIDTH, 300 * D_SCALE_HEIGHT)  );
    
	m_pProducer[2]->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pProducer[2]->setScaleY(1.0f * D_SCALE_HEIGHT);
	this->addChild(m_pProducer[2], 4);
	/////////////////////////////////////////////////

	// 스프라이트 등록 ////////////////////////////
    m_pProducer[0] = CCSprite::create("Maker1.png");
    m_pProducer[0]->setPosition( ccp(240  * D_SCALE_WIDTH, 480 * D_SCALE_HEIGHT) );
	m_pProducer[0]->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pProducer[0]->setScaleY(1.0f * D_SCALE_HEIGHT);
	this->addChild(m_pProducer[0], 4);
	/////////////////////////////////////////////////

	// 스프라이트 등록 ////////////////////////////
    m_pProducer[1] = CCSprite::create("Maker2.png");
    m_pProducer[1]->setPosition( ccp(240 * D_SCALE_WIDTH, 680 * D_SCALE_HEIGHT) );
	m_pProducer[1]->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pProducer[1]->setScaleY(1.0f * D_SCALE_HEIGHT);
    this->addChild(m_pProducer[1], 4);
	/////////////////////////////////////////////////


	// 스프라이트 등록 ////////////////////////////
    m_pProducer[3] = CCSprite::create("Maker4.png");
    m_pProducer[3]->setPosition( ccp(240 * D_SCALE_WIDTH, 150 * D_SCALE_HEIGHT)  );
    
	m_pProducer[3]->setScaleX(0.6f * D_SCALE_WIDTH);
	m_pProducer[3]->setScaleY(0.6f * D_SCALE_HEIGHT);
	this->addChild(m_pProducer[3], 4);
	/////////////////////////////////////////////////


	m_Sae = CocosDenshion::SimpleAudioEngine::sharedEngine();
	m_Sae->preloadBackgroundMusic("Producer_BGM.mp3");
	if(g_bBGM_Sound == true)
	m_Sae->playBackgroundMusic( "Producer_BGM.mp3", true);

	
	this->schedule(schedule_selector(CreditScene::Update), 0.0);
	
    m_pLoading = CCSprite::create("Loading.png");
	m_pLoading->setPosition( ccp(240 * D_SCALE_WIDTH, 400 * D_SCALE_HEIGHT));
	m_pLoading->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pLoading->setScaleY(1.0f * D_SCALE_HEIGHT);
	m_pLoading->setVisible(false);
    this->addChild(m_pLoading, 99);
	//CCParticleSystem *emitter;
 //   emitter = CCParticleSnow::node();
 //   emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("Snow1.png"));
	//emitter->setTotalParticles(500);
 //   emitter->setAutoRemoveOnFinish(true);
	//emitter->setLife(6.0f);
	//emitter->setLifeVar(1.0f);
 //   emitter->setPosition(ccp(size.width - (size.width/4), (size.height) + 50));
	//emitter->setGravity(ccp(-100,-100));
 //   emitter->setSpeedVar(200);
	////emitter->setRotatePerSecond(10.0f);
	////emitter->setRotatePerSecondVar(20.0f);
	//emitter->setScale(1.0f);
 //   emitter->setStartSize(10.0f);
 //   emitter->setEndSize(10.0f);
 //   emitter->setDuration(60.0f);
 //   emitter->setSpeed(200);
	////emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	//emitter->setEmissionRate(100.0f);
	////emitter->setAngle(0.0f);
	////emitter->setAngleVar(360.0f);
 //   this->addChild(emitter, 3);


    emitter[0] = CCParticleFlower::node();
    emitter[0]->setTexture(CCTextureCache::sharedTextureCache()->addImage("Snow1.png"));
	emitter[0]->setTotalParticles(200);
    emitter[0]->setAutoRemoveOnFinish(true);
	emitter[0]->setLife(6.0f);
	emitter[0]->setLifeVar(1.0f);
    emitter[0]->setPosition( ccp((size.width /4), size.height - (size.height/5) ));
	//emitter2->setGravity(ccp(-100,-100));
    emitter[0]->setSpeedVar(200);
	//emitter->setRotatePerSecond(10.0f);
	//emitter->setRotatePerSecondVar(20.0f);
	emitter[0]->setScale(1.0f);
    emitter[0]->setStartSize(10.0f);
    emitter[0]->setEndSize(10.0f);
    emitter[0]->setDuration(600.0f);
    emitter[0]->setSpeed(200);
	//emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	emitter[0]->setEmissionRate(100.0f);
	//emitter->setAngle(0.0f);
	//emitter->setAngleVar(360.0f);
////////////////////////////////////////////////////////
	emitter[1] = CCParticleFlower::node();
    emitter[1]->setTexture(CCTextureCache::sharedTextureCache()->addImage("Snow1.png"));
	emitter[1]->setTotalParticles(200);
    emitter[1]->setAutoRemoveOnFinish(true);
	emitter[1]->setLife(6.0f);
	emitter[1]->setLifeVar(1.0f);
    emitter[1]->setPosition( ccp((size.width*3/4),size.height-(size.height*3/5) ));
	//emitter2->setGravity(ccp(-100,-100));
    emitter[1]->setSpeedVar(200);
	//emitter->setRotatePerSecond(10.0f);
	//emitter->setRotatePerSecondVar(20.0f);
	emitter[1]->setScale(1.0f);
    emitter[1]->setStartSize(10.0f);
    emitter[1]->setEndSize(10.0f);
    emitter[1]->setDuration(600.0f);
    emitter[1]->setSpeed(200);
	//emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	emitter[1]->setEmissionRate(100.0f);
	//emitter->setAngle(0.0f);
	//emitter->setAngleVar(360.0f);
////////////////////////////////////////////////////////////
	emitter[2] = CCParticleFlower::node();
    emitter[2]->setTexture(CCTextureCache::sharedTextureCache()->addImage("Snow1.png"));
	emitter[2]->setTotalParticles(200);
    emitter[2]->setAutoRemoveOnFinish(true);
	emitter[2]->setLife(6.0f);
	emitter[2]->setLifeVar(1.0f);
    emitter[2]->setPosition(ccp((size.width /4), size.height-(size.height*4/5) ));
	//emitter2->setGravity(ccp(-100,-100));
    emitter[2]->setSpeedVar(200);
	//emitter->setRotatePerSecond(10.0f);
	//emitter->setRotatePerSecondVar(20.0f);
	emitter[2]->setScale(1.0f);
    emitter[2]->setStartSize(10.0f);
    emitter[2]->setEndSize(10.0f);
    emitter[2]->setDuration(600.0f);
    emitter[2]->setSpeed(200);
	//emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	emitter[2]->setEmissionRate(100.0f);
	//emitter->setAngle(0.0f);
	//emitter->setAngleVar(360.0f);
	m_nStep = 0;
/*
	CCParticleSystem *pc;
    pc= CCParticleSnow::node(                          );
    CCTexture2D * chcheImage2D =  CCTextureCache::sharedTextureCache()->addImage("Snow1.png");
    pc->setTexture(chcheImage2D );
	pc->setScale(1.0f);
	pc->setPosition(ccp(0,0));
	this->addChild(pc, 2);*/

	m_fSpeed = 250.0f;
	m_fPlusSpeed = 200.0f;

	m_fBlendTimer = 0.0f;

    return true;
}

void CreditScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void CreditScene::BackCallback(CCObject* pSender)
{
   // CCDirector::sharedDirector()->end();
	D_SCENE_CHANGE_EFFECT_R(MenuScene::scene());
	//CCScene *pScene = CCTransitionPageTurn::transitionWithDuration(1,MenuScene::scene(),true);
	//CCScene *pScene = CCTransitionCrossFade();
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true)
	m_Sae->playEffect("StageStart.mp3");
}
void CreditScene::Update(float dt)
{
	m_fTimer += dt;

	if(m_fTimer >= 1.0 && m_nStep < 1)
	{
		this->addChild(emitter[m_nStep], 3);
		m_nStep++;
	}
	else if(m_fTimer >= 3.0 && m_nStep < 2)
	{
		this->addChild(emitter[m_nStep], 3);
		m_nStep++;
	}
	else if(m_fTimer >= 5.0 && m_nStep < 3)
	{
		this->addChild(emitter[m_nStep], 3);
		m_nStep++;
	}
	
}