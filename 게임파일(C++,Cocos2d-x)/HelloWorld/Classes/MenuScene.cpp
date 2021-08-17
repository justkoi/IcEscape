#include "stdafx.h"

USING_NS_CC;
CCSize g_PhoneSize;
CCScene* MenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MenuScene *layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}
float MenuScene::ReturnWidth(float fValue)
{
	fValue = fValue - 240;
	return (g_PhoneSize.width/2) + fValue;
}
float MenuScene::ReturnHeight(float fValue)
{
	fValue = fValue - 400;
	return (g_PhoneSize.height/2) + fValue;
}

void MenuScene::SaveOption()
{

	CCFileUtils FileUitil;
	TCHAR path[MAX_PATH + 1] = "";
	DWORD len = GetCurrentDirectory(MAX_PATH, path);
	string strTemp = "";// FileUitil.sharedFileUtils()->getWriteablePath();;
	strTemp.append("option.sav");
	
	FILE* fpw = fopen(strTemp.c_str(),"wb");
	
	fwrite(&g_bBGM_Sound,sizeof(bool),1,fpw);
	fwrite(&g_bEFFECT_Sound,sizeof(bool),1,fpw);


	fclose(fpw);
}
bool MenuScene::LoadOption()
{
	CCFileUtils FileUitil;
	TCHAR path[MAX_PATH + 1] = "";
	DWORD len = GetCurrentDirectory(MAX_PATH, path);
	string strTemp = "";// FileUitil.sharedFileUtils()->getWriteablePath();;
	strTemp.append("option.sav");

	FILE* fpr = fopen(strTemp.c_str(),"rb");

	if(fpr == nullptr)
		return false;
	
	fread(&g_bBGM_Sound,sizeof(bool),1,fpr);
	fread(&g_bEFFECT_Sound,sizeof(bool),1,fpr);

	fclose(fpr);

	return true;
}
// on "init" you need to initialize your instance
bool MenuScene::init()
{

    


    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	g_PhoneSize = CCDirector::sharedDirector()->getWinSize();
	
	bool bLoadResult = true;

	bLoadResult = LoadOption();

	if(bLoadResult == false)
	{
		SaveOption();
	}
	
	m_pBlind = CCSprite::create("Blind.png");
	m_pBlind->setPosition( ccp(240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBlind->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pBlind->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pBlind->setVisible(false);
	m_pBlind->setOpacity(255 * 0.7f);
    this->addChild(m_pBlind, 2);
    

	m_Sae->preloadEffect("Button.wav");
	m_fUpDownTime = 0.0f;
	m_fUpDownSpeed = 0.017f;
	m_fUpDownPlusTime = 0.0f;
	m_fTimer = 0.0f;

/*
	CCLabelTTF* m_pText = CCLabelTTF::labelWithString("Hi~ Lee Mj1", "µ¸¿òÃ¼", 32);
	this->addChild(m_pText,9999);
	m_pText->setPosition(ccp(size.width/2, size.height/2));
	m_pText->setAnchorPoint(ccp(0, 1));
*/
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    pGameStartItem = CCMenuItemImage::create(
                                        "Button_Start_1.png",
                                        "Button_Start_3.png",
                                        this,
                                        menu_selector(MenuScene::GameStartCallback) );
	pGameStartItem->setPosition( ccp((g_PhoneSize.width/2) - 5, (g_PhoneSize.height/2) ) );

    // create menu, it's an autorelease object
    pGameStart = CCMenu::create(pGameStartItem, NULL);
	float fSDFSDF = (g_PhoneSize.height/D_BASIC_PHONE_HEIGHT);
	pGameStart->setPosition( CCPointZero );
	pGameStart->setScaleX(1.00f * D_SCALE_WIDTH);
	pGameStart->setScaleY(1.00f * D_SCALE_HEIGHT);
	pGameStart->setAnchorPoint(ccp(0.5f,0.5f));

    this->addChild(pGameStart, 1);
	// add a "close" icon to exit the progress. it's an autorelease object
    pCreditItem = CCMenuItemImage::create(
                                        "Button_Credit_1.png",
                                        "Button_Credit_3.png",
                                        this,
                                        menu_selector(MenuScene::CreditCallback) );
	pCreditItem->setPosition( ccp( (g_PhoneSize.width/2), (g_PhoneSize.height/2) - 100 ) );
    pCreditStart = CCMenu::create(pCreditItem, NULL);
	pCreditStart->setPosition( CCPointZero );
	pCreditStart->setScaleX(1.00f * D_SCALE_WIDTH);
	pCreditStart->setScaleY(1.00f * D_SCALE_HEIGHT);
	pCreditStart->setAnchorPoint(ccp(0.5f,0.5f));
    this->addChild(pCreditStart, 1);

	/////////////////////////////
    pOptionItem = CCMenuItemImage::create(
                                        "Button_Option_1.png",
                                        "Button_Option_3.png",
                                        this,
                                        menu_selector(MenuScene::OptionCallback) );
    pOptionItem->setPosition( ccp( (g_PhoneSize.width/2), (g_PhoneSize.height/2) - 200 ) );
    pOption = CCMenu::create(pOptionItem, NULL);
	pOption->setPosition( CCPointZero );
	pOption->setScaleX(1.00f * D_SCALE_WIDTH);
	pOption->setScaleY(1.00f * D_SCALE_HEIGHT);
	pOption->setAnchorPoint(ccp(0.5f,0.5f));
	
    this->addChild(pOption, 1);

    /////////////////////////////
	pExitItem = CCMenuItemImage::create(
										"Button_Quit_1.png",
										"Button_Quit_3.png",
										this,
										menu_selector(MenuScene::ExitCallback) );
	pExitItem->setPosition(ccp( (g_PhoneSize.width/2), (g_PhoneSize.height/2) - 300 ) );
	pExit = CCMenu::create(pExitItem, NULL);
	pExit->setPosition( CCPointZero );
	pExit->setScaleX(1.00f * D_SCALE_WIDTH);
	pExit->setScaleY(1.00f * D_SCALE_HEIGHT);
	pExit->setAnchorPoint(ccp(0.5f,0.5f));
	this->addChild(pExit, 1);
    /////////////////////////////

	


    /////////////////////////////
    pBGM_SoundOnItem = CCMenuItemImage::create(
                                        "Speak_None_1.png",
                                        "Speak_None_3.png",
                                        this,
                                        menu_selector(MenuScene::BGM_SoundOnCallback) );
    pBGM_SoundOnItem->setPosition( ccp( ReturnWidth(150), ReturnHeight(400) ));
    pBGM_SoundOn = CCMenu::create(pBGM_SoundOnItem, NULL);
	pBGM_SoundOn->setPosition( CCPointZero );
	pBGM_SoundOn->setScaleX(0.60f * D_SCALE_WIDTH);
	pBGM_SoundOn->setScaleY(0.60f * D_SCALE_HEIGHT);
	pBGM_SoundOn->setVisible(false);
    this->addChild(pBGM_SoundOn, 4);

    /////////////////////////////

	m_bPopUp = false;

    /////////////////////////////
    pBGM_SoundOffItem = CCMenuItemImage::create(
                                        "Speak_Off_1.png",
                                        "Speak_Off_3.png",
                                        this,
                                        menu_selector(MenuScene::BGM_SoundOffCallback) );
    pBGM_SoundOffItem->setPosition( ccp( ReturnWidth(120.0f), ReturnHeight(392.0f)) );
    pBGM_SoundOff = CCMenu::create(pBGM_SoundOffItem, NULL);
	pBGM_SoundOff->setPosition( CCPointZero );
	pBGM_SoundOff->setScaleX(0.60f * D_SCALE_WIDTH);
	pBGM_SoundOff->setScaleY(0.60f * D_SCALE_HEIGHT);
	pBGM_SoundOff->setVisible(false);
    this->addChild(pBGM_SoundOff, 4);

    /////////////////////////////
	/////////////////////////////
    pEFFECT_SoundOnItem = CCMenuItemImage::create(
                                        "Speak_None_1.png",
                                        "Speak_None_3.png",
                                        this,
                                        menu_selector(MenuScene::EFFECT_SoundOnCallback) );
    pEFFECT_SoundOnItem->setPosition( ccp( ReturnWidth(360), ReturnHeight(400) ));
    pEFFECT_SoundOn = CCMenu::create(pEFFECT_SoundOnItem, NULL);
	pEFFECT_SoundOn->setPosition( CCPointZero );
	pEFFECT_SoundOn->setScaleX(0.60f * D_SCALE_WIDTH);
	pEFFECT_SoundOn->setScaleY(0.60f * D_SCALE_HEIGHT);
	pEFFECT_SoundOn->setVisible(false);
    this->addChild(pEFFECT_SoundOn, 4);

    /////////////////////////////

	m_bPopUp = false;

    /////////////////////////////
    pEFFECT_SoundOffItem = CCMenuItemImage::create(
                                        "Speak_Off_1.png",
                                        "Speak_Off_3.png",
                                        this,
                                        menu_selector(MenuScene::EFFECT_SoundOffCallback) );
    pEFFECT_SoundOffItem->setPosition( ccp( ReturnWidth(330.0f), ReturnHeight(392.0f)) );
    pEFFECT_SoundOff = CCMenu::create(pEFFECT_SoundOffItem, NULL);
	pEFFECT_SoundOff->setPosition( CCPointZero );
	pEFFECT_SoundOff->setScaleX(0.60f * D_SCALE_WIDTH);
	pEFFECT_SoundOff->setScaleY(0.60f * D_SCALE_HEIGHT);
	pEFFECT_SoundOff->setVisible(false);
    this->addChild(pEFFECT_SoundOff, 4);

    /////////////////////////////
	/////////////////////////////
    pCancelItem = CCMenuItemImage::create(
                                        "Button_Cancel_1.png",
                                        "Button_Cancel_3.png",
                                        this,
                                        menu_selector(MenuScene::CancelCallback) );
    pCancelItem->setPosition( ccp( ReturnWidth(366), ReturnHeight(484) ));
    pCancel = CCMenu::create(pCancelItem, NULL);
	pCancel->setPosition( CCPointZero );
	pCancel->setScaleX(1.00f * D_SCALE_WIDTH);
	pCancel->setScaleY(1.00f * D_SCALE_HEIGHT);
	pCancel->setVisible(false);
    this->addChild(pCancel, 5);

    /////////////////////////////
	// add a "close" icon to exit the progress. it's an autorelease object
	
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    // ask director the window size

    // position the label on the center of the screen
    //pLabel->setPosition( ccp(size.width / 2, size.height - 50) );

    // add the label as a child to this layer
    //this->addChild(pLabel, 1);i

	m_fGLTimer = 0.0f;
    // add "HelloWorld" splash screen"
    m_pSprite = CCSprite::create("Menu.png");

    // position the sprite on the center of the screen

	m_pSprite->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pSprite->setScaleX(1.05f * D_SCALE_WIDTH);
	m_pSprite->setScaleY(1.05f * D_SCALE_HEIGHT);
    // add the sprite as a child to this layer
    this->addChild(m_pSprite, 0);
    
	m_Sae = CocosDenshion::SimpleAudioEngine::sharedEngine();
	m_Sae->preloadBackgroundMusic("Logo_BGM.mp3");
	if(g_bBGM_Sound == true)
		m_Sae->playBackgroundMusic( "Logo_BGM.mp3", true);

    m_pTitle = CCSprite::create("Title.png");
	m_pTitle->setPosition( ccp( 240 * D_SCALE_WIDTH, 600  * D_SCALE_HEIGHT) );
	m_pTitle->setScaleX(1.6f * D_SCALE_WIDTH);
	m_pTitle->setScaleY(1.6f * D_SCALE_HEIGHT);
    this->addChild(m_pTitle, 1);
	
    m_pGameLevel = CCSprite::create("GameLevel.png");
	m_pGameLevel->setPosition( ccp( (480) * D_SCALE_WIDTH, 800  * D_SCALE_HEIGHT) );
	m_pGameLevel->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pGameLevel->setScaleY(1.0f * D_SCALE_HEIGHT);
	m_pGameLevel->setAnchorPoint(ccp(1,1));
    this->addChild(m_pGameLevel, 1);
	
    m_pLoading = CCSprite::create("Loading.png");
	m_pLoading->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pLoading->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pLoading->setScaleY(1.0f * D_SCALE_HEIGHT);

	m_pLoading->setVisible(false);
    this->addChild(m_pLoading, 99);
	
	this->schedule(schedule_selector(MenuScene::Update), 0.0);

	CCParticleSystem *emitter;
    emitter = CCParticleSnow::node();
    emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("Snow1.png"));
	emitter->setTotalParticles(500);
    emitter->setAutoRemoveOnFinish(true);
	emitter->setLife(6.0f);
	emitter->setLifeVar(1.0f);
    emitter->setPosition(ccp(size.width - (size.width/4), (size.height) + 50));
	emitter->setGravity(ccp(-100,-100));
    emitter->setSpeedVar(200);
	//emitter->setRotatePerSecond(10.0f);
	//emitter->setRotatePerSecondVar(20.0f);
	emitter->setScale(1.0f);
    emitter->setStartSize(10.0f);
    emitter->setEndSize(10.0f);
    emitter->setDuration(60.0f);
    emitter->setSpeed(200);
	//emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
	emitter->setEmissionRate(100.0f);
	//emitter->setAngle(0.0f);
	//emitter->setAngleVar(360.0f);
    this->addChild(emitter);
/*
	CCParticleSystem *pc;
    pc= CCParticleSnow::node();
    CCTexture2D * chcheImage2D =  CCTextureCache::sharedTextureCache()->addImage("Snow1.png");
    pc->setTexture(chcheImage2D );
	pc->setScale(1.0f);
	pc->setPosition(ccp(0,0));
	this->addChild(pc, 2);*/

	m_pPopUp = CCSprite::create("PopUp_Option.png");

	
	m_pPopUp->setPosition( ccp( 240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pPopUp->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pPopUp->setScaleY(1.0f * D_SCALE_HEIGHT);

	m_pPopUp->setVisible(false);
    this->addChild(m_pPopUp, 3);

	
	m_pPopUp_BGM = CCSprite::create("BGM.png");

	
	m_pPopUp_BGM->setPosition( ccp( 170 * D_SCALE_WIDTH, 440  * D_SCALE_HEIGHT) );
	m_pPopUp_BGM->setScaleX(1.2f * D_SCALE_WIDTH);
	m_pPopUp_BGM->setScaleY(1.2f * D_SCALE_HEIGHT);

	m_pPopUp_BGM->setVisible(false);
    this->addChild(m_pPopUp_BGM, 4);

	
	m_pPopUp_Effect = CCSprite::create("Effect.png");

	
	m_pPopUp_Effect->setPosition( ccp( 300 * D_SCALE_WIDTH, 440  * D_SCALE_HEIGHT) );
	m_pPopUp_Effect->setScaleX(1.2f * D_SCALE_WIDTH);
	m_pPopUp_Effect->setScaleY(1.2f * D_SCALE_HEIGHT);

	m_pPopUp_Effect->setVisible(false);
    this->addChild(m_pPopUp_Effect, 4);

	m_fMenuSpeed = 100.0f;


    return true;
}

void MenuScene::Update(float dt)
{
	m_fTimer += dt;
	if(m_fGLTimer < 4.0f)
	{
		m_fGLTimer += dt;
		if(m_fGLTimer >= 4.0f)
		{
			m_fGLTimer = 4.0f;
		}
		if(m_fGLTimer >= 3.0f)
		{
			m_pGameLevel->setOpacity(255 * (4.0f - m_fGLTimer));
		}
	}

	if(m_bPopUp == true)
	{
		m_pBlind->setVisible(true);
		m_pPopUp->setVisible(true);
		m_pPopUp_BGM->setVisible(true);
		m_pPopUp_Effect->setVisible(true);
		pCancel->setVisible(true);
		if(g_bBGM_Sound == true)
		{
			pBGM_SoundOn->setVisible(true);
			pBGM_SoundOff->setVisible(false);
		}
		else if(g_bBGM_Sound == false)
		{
			pBGM_SoundOn->setVisible(false);
			pBGM_SoundOff->setVisible(true);
		}

		if(g_bEFFECT_Sound == true)
		{
			pEFFECT_SoundOn->setVisible(true);
			pEFFECT_SoundOff->setVisible(false);
		}
		else if(g_bEFFECT_Sound == false)
		{
			pEFFECT_SoundOn->setVisible(false);
			pEFFECT_SoundOff->setVisible(true);
		}
	}
	else
	{
		m_pBlind->setVisible(false);
		m_pPopUp->setVisible(false);
		m_pPopUp_BGM->setVisible(false);
		m_pPopUp_Effect->setVisible(false);
		//pSoundOn->setVisible(false);
		//pSoundOff->setVisible(false);
		pBGM_SoundOn->setVisible(false);
		pBGM_SoundOff->setVisible(false);
		pEFFECT_SoundOn->setVisible(false);
		pEFFECT_SoundOff->setVisible(false);
		pCancel->setVisible(false);
	}
	
	if(m_bPopUp == false)
	{
		
		m_pSprite->setPosition(CCPoint(m_pSprite->getPositionX(),m_pSprite->getPositionY()-(m_fUpDownTime)));
		m_pTitle->setPosition(CCPoint(m_pTitle->getPositionX(),m_pTitle->getPositionY()+(m_fUpDownTime)));
		//m_pTitle->MoveY();
		m_fUpDownTime -= m_fUpDownSpeed;
		m_fUpDownSpeed += m_fUpDownPlusTime;
		if(m_fUpDownTime <= -0.5f)
		{
			m_fUpDownSpeed = -0.017f;
		}
		else if(m_fUpDownTime >= 0.5f)
		{
			m_fUpDownSpeed = 0.017f;
		}
	}
}

void MenuScene::menuCloseCallback(CCObject* pSender)
{

    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MenuScene::GameStartCallback(CCObject* pSender)
{
    if(m_bPopUp == false)
    {
	   // CCDirector::sharedDirector()->end();
		//CCScene *pScene = CCTransitionEaseScene::transitionWithDuration(1,GameScene::scene());
		D_SCENE_CHANGE_EFFECT_R(StageMenuScene::scene());
		//CCScene *pScene = CCTransitionCrossFade();
		CCDirector::sharedDirector()->replaceScene(pScene);
	
		if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
	}
}


void MenuScene::CreditCallback(CCObject* pSender)
{
  if(m_bPopUp == false)
  {
   // CCDirector::sharedDirector()->end();
	D_SCENE_CHANGE_EFFECT_L(CreditScene::scene());
	
	//CCScene *pScene = CCTransitionTurnOffTiles::transitionWithDuration(1,CreditScene::scene(),true);
	//CCScene *pScene = CCTransitionCrossFade();
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
  }
}

void MenuScene::ExitCallback(CCObject* pSender)
{
	if(m_bPopUp == false)
    {
	
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
	}
}

void MenuScene::OptionCallback(CCObject* pSender)
{
  if(m_bPopUp == false)
  {
	  m_bPopUp = true;
  }
}
void MenuScene::CancelCallback(CCObject* pSender)
{
  if(m_bPopUp == true)
  {
	  m_bPopUp = false;
  }
}

void MenuScene::BGM_SoundOnCallback(CCObject* pSender)
{
	if(m_bPopUp == true)
	{
		m_Sae->stopBackgroundMusic();
		g_bBGM_Sound = false;
		SaveOption();
	}
}
void MenuScene::BGM_SoundOffCallback(CCObject* pSender)
{
	if(m_bPopUp == true)
	{
		m_Sae->playBackgroundMusic("Logo_BGM.mp3",true);
		g_bBGM_Sound = true;
		SaveOption();
	}
}
void MenuScene::EFFECT_SoundOnCallback(CCObject* pSender)
{
	if(m_bPopUp == true)
	{
		g_bEFFECT_Sound = false;
		SaveOption();
	}
}
void MenuScene::EFFECT_SoundOffCallback(CCObject* pSender)
{
	if(m_bPopUp == true)
	{
		g_bEFFECT_Sound = true;
		SaveOption();
	}
}