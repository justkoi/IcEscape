#include "stdafx.h"

USING_NS_CC;

int g_nSelectStage = 0;
//
//void (*pStageCallback[D_STAGE_MAX])(CCObject*) = 
//{
//	  
//	&StageCallback1,
//	&StageCallback2,
//	&StageCallback3
//
//} 2.0 = 50% = 0.5 
// 0.1 = 0.4
stStageInfo g_StageInfo[D_STAGE_MAX] = 
{
	{10.0f, 8.0f, 1.05f, (0.5f / 60.0f), 90.0f},  //!< 1Stage
	{40.0f, 7.9f, 1.08f, (0.5f / 60.0f), 120.0f}, //!< 2Stage
	{50.0f, 7.8f, 1.10f, (0.5f / 60.0f), 150.0f}, //!< 3Stage
	{60.0f, 7.7f, 1.10f, (0.52f / 60.0f), 150.0f}, //!< 4Stage
	{65.0f, 7.6f, 1.15f, (0.54f / 60.0f), 150.0f}, //!< 5Stage
	{70.0f, 7.5f, 1.20f, (0.56f / 60.0f), 150.0f}, //!< 6Stage
	{90.0f, 7.2f, 1.30f, (0.60f / 60.0f), 200.0f}, //!< 7Stage
	{90.0f, 7.0f, 1.35f, (0.62f / 60.0f), 195.0f}, //!< 8Stage
	{90.0f, 6.8f, 1.40f, (0.64f / 60.0f), 190.0f}, //!< 9Stage
	{90.0f, 6.6f, 1.45f, (0.66f / 60.0f), 185.0f}, //!< 10Stage
	{90.0f, 6.4f, 1.50f, (0.68f / 60.0f), 180.0f}, //!< 11Stage
	{90.0f, 6.2f, 1.55f, (0.70f / 60.0f), 175.0f}, //!< 12Stage
	{90.0f, 6.0f, 1.60f, (0.73f / 60.0f), 170.0f}, //!< 13Stage
	{90.0f, 5.8f, 1.65f, (0.76f / 60.0f), 165.0f}, //!< 14Stage
	{90.0f, 5.6f, 1.70f, (0.80f / 60.0f), 160.0f}, //!< 15Stage
	{90.0f, 5.4f, 1.75f, (0.83f / 60.0f), 155.0f}, //!< 16Stage
	{90.0f, 5.2f, 1.80f, (0.85f / 60.0f), 150.0f}, //!< 17Stage
	{90.0f, 5.0f, 1.85f, (0.88f / 60.0f), 145.0f}, //!< 18Stage
	{90.0f, 4.9f, 1.90f, (0.90f / 60.0f), 140.0f}, //!< 19Stage
	{90.0f, 4.8f, 1.95f, (0.95f / 60.0f), 140.0f}, //!< 20Stage
	{90.0f, 4.6f, 2.00f, (1.05f / 60.0f), 135.0f}, //!< 21Stage
};
bool		g_bStageLock[D_STAGE_MAX];
//int g_nHighScore[D_STAGE_MAX];//최고점수 Save
int g_nScoreLevel[D_STAGE_MAX];//판정레벨 0, 1, 2, 3 Save
int g_nJudgment[D_STAGE_MAX][3];

float StageMenuScene::ReturnWidth(float fValue)
{
	fValue = fValue - 240;
	return (g_PhoneSize.width/2) + fValue;
}
float StageMenuScene::ReturnHeight(float fValue)
{
	fValue = fValue - 400;
	return (g_PhoneSize.height/2) + fValue;
}



void StageMenuScene::SaveStage()
{
	CCFileUtils FileUitil;
	TCHAR path[MAX_PATH + 1] = "";
	DWORD len = GetCurrentDirectory(MAX_PATH, path);
	string strTemp = path;
	strTemp.append("stagelock.sav");
	string strTemp2 = path;
	strTemp2.append("stagejudgment.sav");

	FILE* fpw = fopen(strTemp.c_str(),"wb");
	FILE* fpw2 = fopen(strTemp2.c_str(),"wb");
	
	
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		fwrite(&g_bStageLock[i],sizeof(bool),1,fpw);
	}
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		fwrite(&g_nScoreLevel[i],sizeof(int),1,fpw2);
	}

	fclose(fpw);
	fclose(fpw2);
}
void StageMenuScene::LoadStage()
{
	CCFileUtils FileUitil;
	string strTemp = "";// FileUitil.sharedFileUtils()->getWriteablePath();
	strTemp.append("stagelock.sav");
	string strTemp2 = "";// FileUitil.sharedFileUtils()->getWriteablePath();
	strTemp2.append("stagejudgment.sav");

	FILE* fpr = fopen(strTemp.c_str(),"rb");
	FILE* fpr2 = fopen(strTemp2.c_str(),"rb");
	
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		fread(&g_bStageLock[i],sizeof(bool),1,fpr);
	}
	
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		fread(&g_nScoreLevel[i],sizeof(int),1,fpr2);
	}
	fclose(fpr);
	fclose(fpr2);
}


CCScene* StageMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StageMenuScene *layer = StageMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageMenuScene::init()
{

  
    //////////////////////////////
    // 1. super init first

	
    if ( !CCLayer::init() )
    {
        return false;
    }


	this->setTouchEnabled(true);

	int nStageCount = 0;
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		for(int j=0; j<3; j++)
		{
			g_nJudgment[i][j] = 80 + (i * 50) + (j*80);
			if(i > 10)
			{
				g_nJudgment[i][j] = 650 + (j*80);
			}
		}
	}
	
	m_fScroll_Y_Vector = 0.0f;
	m_fScroll_Y_All = 0.0f;
	m_fScroll_Y_Smooth = 0.0f;
	m_fStart_Y = 0.0f;

	CCFileUtils FileUitil;

	string strTemp = "";// FileUitil.sharedFileUtils()->getWriteablePath();
	strTemp.append("stagelock.sav");
	string strTemp2 = "";// FileUitil.sharedFileUtils()->getWriteablePath();
	strTemp2.append("stagejudgment.sav");

	FILE* fpr = fopen(strTemp.c_str(),"rb");
	FILE* fpr2 = fopen(strTemp2.c_str(),"rb");
	
	g_nSelectStage = 0;

	if(fpr == NULL)
	{
		for(int i=0; i<D_STAGE_MAX; i++)
		{
			g_bStageLock[i] = false;
		}
		g_bStageLock[0] = true;
		SaveStage();
	}
	if(fpr2 == NULL)
	{
		for(int i=0; i<D_STAGE_MAX; i++)
		{
			g_nScoreLevel[i] = 0;
		}
		SaveStage();
	}
	
	LoadStage();

	CCSize size = CCDirector::sharedDirector()->getWinSize();


	
	m_Sae->preloadEffect("Button.wav");
	m_Sae->preloadEffect("StageStart.mp3");

	m_fTimer = 0.0f;
	m_fStarRot = 0.0f;

	//m_pNumberSample.Init(this,13,ccp(200,200),2);

	//CCLabelTTF* m_pText = CCLabelTTF::create("Hello World", "굴림체", 40);
	//m_pText->setPosition(ccp( (240), 450));
	////m_pText->setOpacity(255 * 0.6f);
	////m_pText->setColor(ccc3(255,255,255));
	//this->addChild(m_pText,40);
	//
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
   


	// add a "close" icon to exit the progress. it's an autorelease object
    pBackItem = CCMenuItemImage::create(
                                        "Button_Back_1.png",
                                        "Button_Back_3.png",
                                        this,
                                        menu_selector(StageMenuScene::BackCallback) );
    pBackItem->setPosition( ccp( ReturnWidth(50), ReturnHeight(25)) );
    pBack = CCMenu::create(pBackItem, NULL);

	pBack->setPosition( CCPointZero );
	pBack->setScaleX(1.00f * D_SCALE_WIDTH);
	pBack->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(pBack, 1);

	//!< 치트키
	////////////////////////////////////////////////////////////////////////
	// add a "close" icon to exit the progress. it's an autorelease object
 //   pResetItem = CCMenuItemImage::create(
 //                                       "Reset_1.png",
 //                                       "Reset_3.png",
 //                                       this,
 //                                       menu_selector(StageMenuScene::ResetCallback) );
 //   pResetItem->setPosition( ccp( ReturnWidth(35), ReturnHeight(730)) );
 //   pReset = CCMenu::create(pResetItem, NULL);

	//
	//pReset->setPosition( CCPointZero );
	//pReset->setScaleX(1.00f * D_SCALE_WIDTH);
	//pReset->setScaleY(1.00f * D_SCALE_HEIGHT);
 //   this->addChild(pReset, 1);

	//// add a "close" icon to exit the progress. it's an autorelease object
 //   pNextItem = CCMenuItemImage::create(
 //                                       "Next_1.png",
 //                                       "Next_3.png",
 //                                       this,
 //                                       menu_selector(StageMenuScene::NextCallback) );
 //   pNextItem->setPosition( ccp( ReturnWidth(445),  ReturnHeight(730)) );
 //   pNext = CCMenu::create(pNextItem, NULL);
	//pNext->setColor(ccc3(255 * 0.5f,255 * 0.9f,255 * 0.9f));
	//
	//pNext->setPosition( CCPointZero );
	//pNext->setScaleX(1.00f * D_SCALE_WIDTH);
	//pNext->setScaleY(1.00f * D_SCALE_HEIGHT);

 //   this->addChild(pNext, 1);
	////////////////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback1 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );
	m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

	m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
	this->addChild(m_pPlay[nStageCount], 1);

	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
	this->addChild(m_pLock[nStageCount], 3);

	for(int i=nStageCount; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	













	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback2 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	









	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback3 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback4 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback5 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
	this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback6 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback7 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback8 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback9 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback10 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback11 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback12 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback13 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback14 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback15 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback16 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback17 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback18 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback19 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback20 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	m_pPlayItem[nStageCount] = CCMenuItemImage::create(
									"Button_SelectMenu_1.png",
									"Button_SelectMenu_3.png",
									this,
									menu_selector( StageMenuScene::StageCallback21 )
									);
	m_pPlayItem[nStageCount]->setPosition( ccp( ReturnWidth(25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) , ReturnHeight(800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)))) );
    m_pPlay[nStageCount] = CCMenu::create(m_pPlayItem[nStageCount], NULL);
    m_pPlay[nStageCount]->setPosition( CCPointZero );m_pPlay[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pPlay[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);m_pPlay[nStageCount]->setColor(ccc3(255 - (nStageCount*1),255 - (nStageCount*3),255 - (nStageCount*5)));
    this->addChild(m_pPlay[nStageCount], 1);
	m_CNumber[nStageCount].Init(this,ccp(1.0f* D_SCALE_WIDTH,1.0f* D_SCALE_HEIGHT),nStageCount+1,ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT ),2);
	m_pLock[nStageCount] = CCSprite::create("Lock.png");
    m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
    this->addChild(m_pLock[nStageCount], 3);
	for(int i=0; i<3; i++)
	{
		m_pStar[nStageCount][i] = CCSprite::create("Star.png");
		m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
		 
		this->addChild(m_pStar[nStageCount][i], 3);
	}
	nStageCount++;
	///////////////////////////////////////////////////////////////////////////////


    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    // ask director the window size

    // position the label on the center of the screen
    //pLabel->setPosition( ccp(size.width / 2, size.height - 50) );

    // add the label as a child to this layer
    //this->addChild(pLabel, 1);i

    // add "HelloWorld" splash screen"
    m_pBackGround = CCSprite::create("StageMenu_Bg.png");
	
	m_pBackGround->setPosition( ccp(240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pBackGround->setScaleX(1.05f * D_SCALE_WIDTH);
	m_pBackGround->setScaleY(1.05f * D_SCALE_HEIGHT);

    this->addChild(m_pBackGround, 0);
    
	m_Sae = CocosDenshion::SimpleAudioEngine::sharedEngine();
	m_Sae->preloadBackgroundMusic("Menu_BGM.mp3");
	if(g_bBGM_Sound == true)
	m_Sae->playBackgroundMusic( "Menu_BGM.mp3", true);
	
	
    m_pLoading = CCSprite::create("Loading.png");
	
	m_pLoading->setPosition( ccp(240 * D_SCALE_WIDTH, 400  * D_SCALE_HEIGHT) );
	m_pLoading->setScaleX(1.05f * D_SCALE_WIDTH);
	m_pLoading->setScaleY(1.05f * D_SCALE_HEIGHT);

	m_pLoading->setVisible(false);
    this->addChild(m_pLoading, 99);
	
	this->schedule(schedule_selector(StageMenuScene::Update), 0.0);

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

    return true;
}

void StageMenuScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void StageMenuScene::BackCallback(CCObject* pSender)
{
   // CCDirector::sharedDirector()->end();
	//CCScene *pScene = CCTransitionEaseScene::transitionWithDuration(1,GameScene::scene());
	D_SCENE_CHANGE_EFFECT_R(MenuScene::scene());
	//CCScene *pScene = CCTransitionCrossFade();
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}

void StageMenuScene::ResetCallback(CCObject* pSender)
{
   for(int i=0; i<D_STAGE_MAX; i++)
	{
		g_bStageLock[i] = false;
		g_nScoreLevel[i] = 0;
	}
	g_bStageLock[0] = true;
	SaveStage();
}

void StageMenuScene::NextCallback(CCObject* pSender)
{
	int nNextStage = -1;
    for(int i=0; i<D_STAGE_MAX; i++)
	{
		if(g_bStageLock[i] == false)
		{
			nNextStage = i;
			break;
		}
	}
	if(nNextStage == -1)
		return;
	g_bStageLock[nNextStage] = true;
	SaveStage();
}

void StageMenuScene::StageCallback1(CCObject* pSender)
{
	g_nSelectStage = 1;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback2(CCObject* pSender)
{
	g_nSelectStage = 2;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true)
	m_Sae->playEffect("StageStart.mp3");
}
void StageMenuScene::StageCallback3(CCObject* pSender)
{
	g_nSelectStage = 3;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback4(CCObject* pSender)
{
	g_nSelectStage = 4;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback5(CCObject* pSender)
{
	g_nSelectStage = 5;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback6(CCObject* pSender)
{
	g_nSelectStage = 6;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback7(CCObject* pSender)
{
	g_nSelectStage = 7;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback8(CCObject* pSender)
{
	g_nSelectStage = 8;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback9(CCObject* pSender)
{
	g_nSelectStage = 9;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback10(CCObject* pSender)
{
	g_nSelectStage = 10;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback11(CCObject* pSender)
{
	g_nSelectStage = 11;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback12(CCObject* pSender)
{
	g_nSelectStage = 12;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback13(CCObject* pSender)
{
	g_nSelectStage = 13;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback14(CCObject* pSender)
{
	g_nSelectStage = 14;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback15(CCObject* pSender)
{
	g_nSelectStage = 15;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}

void StageMenuScene::StageCallback16(CCObject* pSender)
{
	g_nSelectStage = 16;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback17(CCObject* pSender)
{
	g_nSelectStage = 17;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}

void StageMenuScene::StageCallback18(CCObject* pSender)
{
	g_nSelectStage = 18;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback19(CCObject* pSender)
{
	g_nSelectStage = 19;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback20(CCObject* pSender)
{
	g_nSelectStage = 20;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::StageCallback21(CCObject* pSender)
{
	g_nSelectStage = 21;

	D_SCENE_CHANGE_EFFECT_R(GameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
	if(g_bEFFECT_Sound == true) { m_Sae->playEffect("StageStart.mp3"); }
}
void StageMenuScene::Update(float dt)
{
	m_fStarRot += dt;
	if(m_fStarRot >= 3.0f)
	{
		m_fStarRot = 0.0f;
	}
	m_fTimer += dt;
	ShowUpdateLock();
	
	m_fScroll_Y_Smooth += m_fScroll_Y_Vector/30;
	m_fScroll_Y_Vector -= m_fScroll_Y_Smooth;

	m_fScroll_Y_All += m_fScroll_Y_Smooth;
	if(m_fScroll_Y_All >= 0.0f && m_fScroll_Y_All <= (D_STAGEMENU_HEGIHT * ((int)(D_STAGE_MAX/3) - 4)))
	{
		//m_fScroll_Y_Vector = -(m_fScroll_Y_Vector - m_fScroll_Y_All);
		for(int i=0; i<D_STAGE_MAX; i++)
		{
			for(int j=0; j<3; j++)
			{
				m_pStar[i][j]->setPositionY(m_pStar[i][j]->getPositionY() + m_fScroll_Y_Smooth);
			}
			m_CNumber[i].SetPositionY(m_CNumber[i].m_stPos.y + m_fScroll_Y_Smooth);
		
			m_pLock[i]->setPositionY(m_pLock[i]->getPositionY() + m_fScroll_Y_Smooth);
			m_pPlay[i]->setPositionY(m_pPlay[i]->getPositionY() + m_fScroll_Y_Smooth);
		}
		m_fScroll_Y_Smooth = 0.0f;
	}
	/*else if( m_fScroll_Y_All >= (D_STAGEMENU_HEGIHT * 2))
	{
		m_fScroll_Y_Smooth = 0.0f;
		m_fScroll_Y_Vector = 0.0f;
	}*/
	else if(m_fScroll_Y_All < 0.0f)
	{
		m_fScroll_Y_All = 0.0f;
		m_fScroll_Y_Smooth = 0.0f;
		m_fScroll_Y_Vector = 0.0f;
	}
	else if(m_fScroll_Y_All > (D_STAGEMENU_HEGIHT * ((int)(D_STAGE_MAX/3) - 4)))
	{
		m_fScroll_Y_All = (D_STAGEMENU_HEGIHT * ((int)(D_STAGE_MAX/3) - 4));
		m_fScroll_Y_Smooth = 0.0f;
		m_fScroll_Y_Vector = 0.0f;
	}

	for(int i=0; i<D_STAGE_MAX; i++)
	{
		for(int j=0; j<3; j++)
		{
			m_pStar[i][j]->setVisible(false);
		}

	}
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		if( g_bStageLock[i] == true )
		{
			for(int j=0; j<g_nScoreLevel[i]; j++)
			{
				m_pStar[i][j]->setVisible(true);
				
				if(m_fStarRot <= 1.0f)
				{
					float fTemp = (m_fStarRot/1.0f) * 450.0f - (j*30);
					if(fTemp >= 360.0f)
						fTemp = 360.0f;

					m_pStar[i][j]->setRotation( fTemp );
				}
			}
		}
	}
	
	
} 

void StageMenuScene::ShowUpdateLock()
{
	for(int i=0; i<D_STAGE_MAX; i++)
	{
		if(g_bStageLock[i] == true)
		{
			m_pPlayItem[i]->setVisible(true);
			m_pPlay[i]->setVisible(true);
			m_pLock[i]->setVisible(false);
		}
		else if(g_bStageLock[i] == false)
		{
			m_pPlayItem[i]->setVisible(false);
			m_pPlay[i]->setVisible(false);
			m_pLock[i]->setVisible(true);
		}
	}
}

void StageMenuScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool StageMenuScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	m_fStart_Y = stPos.y;

	return true;
}
void   StageMenuScene::ccTouchMoved (CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
	m_fScroll_Y_Vector += -(m_fStart_Y - stPos.y) * 1.1f;
	m_fStart_Y = stPos.y;
}

void  StageMenuScene::ccTouchEnded (CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint stPos = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());

}