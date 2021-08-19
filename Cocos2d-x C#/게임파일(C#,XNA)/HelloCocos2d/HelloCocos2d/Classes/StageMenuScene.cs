using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using cocos2d;
using HelloCocos2d.GameObject;
using HelloCocos2d.Library;
using CocosDenshion;

namespace HelloCocos2d
{
    public class StageMenuScene : CCLayer
    {
        /// <summary>
        ///  Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
        /// </summary>
        /// 

        public struct stStageInfo
        {
            public float m_fTimeLimit;  //!< 제한시간
            public float m_fCraeteTime; //!< 생성시간
            public float m_fErosionSpeed; //!< 침식속도
            public int m_nErosionPlusSpeed; //!< 침식가속도
            public float m_fSeaLevelMax; //!< 최대 해수면 게이지

            public stStageInfo(float fTimeLimit, float fCraeteTime, float fErosionSpeed, int nErosionPlusSpeed, float fSeaLevelMax)
            {
                m_fTimeLimit = fTimeLimit;
                m_fCraeteTime = fCraeteTime;
                m_fErosionSpeed = fErosionSpeed;
                m_nErosionPlusSpeed = nErosionPlusSpeed;
                m_fSeaLevelMax = fSeaLevelMax;
            }
        };


        public CCSprite m_pSprite;

        public float m_fTouchTimer;

        public float m_fTimer;
        public float m_fUpDownTime;
        public float m_fUpDownSpeed;
        public float m_fUpDownPlusTime;
        public bool m_fUpDown;

        //! extern
        static public int g_nScore = 0;
        static public int g_nSelectStage = 0;
        static public stStageInfo[] g_StageInfo;


        public SimpleAudioEngine m_Sae;

        public bool m_bPopUp;
        CCMenuItemImage[] m_pPlayItem;
	    CCMenu[] m_pPlay;
        CNumber[] m_CNumber;



        CCMenuItemImage m_pBackItem;
        CCMenu m_pBack;

        //{
        //    {10.0f, 8.0f, 1.05f, (0.5f / 60.0f), 90.0f},  //!< 1Stage
        //    {40.0f, 7.9f, 1.08f, (0.5f / 60.0f), 120.0f}, //!< 2Stage
        //    {50.0f, 7.8f, 1.10f, (0.5f / 60.0f), 150.0f}, //!< 3Stage
        //    {60.0f, 7.7f, 1.10f, (0.52f / 60.0f), 150.0f}, //!< 4Stage
        //    {65.0f, 7.6f, 1.15f, (0.54f / 60.0f), 150.0f}, //!< 5Stage
        //    {70.0f, 7.5f, 1.20f, (0.56f / 60.0f), 150.0f}, //!< 6Stage
        //    {90.0f, 7.2f, 1.30f, (0.60f / 60.0f), 200.0f}, //!< 7Stage
        //    {90.0f, 7.0f, 1.35f, (0.62f / 60.0f), 195.0f}, //!< 8Stage
        //    {90.0f, 6.8f, 1.40f, (0.64f / 60.0f), 190.0f}, //!< 9Stage
        //    {90.0f, 6.6f, 1.45f, (0.66f / 60.0f), 185.0f}, //!< 10Stage
        //    {90.0f, 6.4f, 1.50f, (0.68f / 60.0f), 180.0f}, //!< 11Stage
        //    {90.0f, 6.2f, 1.55f, (0.70f / 60.0f), 175.0f}, //!< 12Stage
        //    {90.0f, 6.0f, 1.60f, (0.73f / 60.0f), 170.0f}, //!< 13Stage
        //    {90.0f, 5.8f, 1.65f, (0.76f / 60.0f), 165.0f}, //!< 14Stage
        //    {90.0f, 5.6f, 1.70f, (0.80f / 60.0f), 160.0f}, //!< 15Stage
        //    {90.0f, 5.4f, 1.75f, (0.83f / 60.0f), 155.0f}, //!< 16Stage
        //    {90.0f, 5.2f, 1.80f, (0.85f / 60.0f), 150.0f}, //!< 17Stage
        //    {90.0f, 5.0f, 1.85f, (0.88f / 60.0f), 145.0f}, //!< 18Stage
        //    {90.0f, 4.9f, 1.90f, (0.90f / 60.0f), 140.0f}, //!< 19Stage
        //    {90.0f, 4.8f, 1.95f, (0.95f / 60.0f), 140.0f}, //!< 20Stage
        //    {90.0f, 4.6f, 2.00f, (1.05f / 60.0f), 135.0f}, //!< 21Stage
        //};
        public override bool init()
        {
            CCDirector.sharedDirector().deviceOrientation = ccDeviceOrientation.CCDeviceOrientationPortrait;
            int nStageCount = 0;

            m_fUpDownTime = 0.0f;
            m_fUpDownSpeed = 0.017f;
            m_fUpDownPlusTime = 0.0f;
            m_fTimer = 0.0f;

            m_fTouchTimer = 0.0f;

            //m_pPlayItem = new CCMenuItemImage[Define.D_STAGE_MAX];
            //m_pPlay = new CCMenu[Define.D_STAGE_MAX];
            ////////////////////////////////////////////////////////////////////////////////////////
            //pGameStartItem = CCMenuItemImage.itemFromNormalImage(
            //                                    "Button_Start_1",
            //                                    "Button_Start_3",
            //                                    this,
            //                                    new SEL_MenuHandler(GameStartCallback));
            //pGameStartItem.position = new CCPoint(235, 400);

            //pGameStart = CCMenu.menuWithItems(pGameStartItem);
            //pGameStart.position = new CCPoint(0, 0);
            //this.addChild(pGameStart, 3);
            ////////////////////////////////////////////////////////////////////////////////////////


            //m_pPlayItem.

            //////////////////////////////
            // 1. super init first
            if (!base.init())
            {
                return false;
            }

            this.m_bIsTouchEnabled = false;


            m_Sae = new SimpleAudioEngine();

            m_Sae.preloadEffect("Button");
            m_Sae.preloadEffect("StageStart");

            m_Sae.preloadBackgroundMusic("Menu_BGM");
            if (MenuScene.g_bBGM_Sound == true)
                m_Sae.playBackgroundMusic("Menu_BGM", true);

            m_pBackItem = CCMenuItemImage.itemFromNormalImage(
                                                "Button_Back_1",
                                                "Button_Back_3",
                                                this,
                                                new SEL_MenuHandler(BackCallback));
            m_pBackItem.position = new CCPoint(50, 25);
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pBack = CCMenu.menuWithItems(m_pBackItem);
            m_pBack.position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            this.addChild(m_pBack, 3);


            m_pPlayItem = new CCMenuItemImage[Define.D_STAGE_MAX];
            m_pPlay = new CCMenu[Define.D_STAGE_MAX];
            m_CNumber = new CNumber[Define.D_STAGE_MAX];
            g_StageInfo = new stStageInfo[Define.D_STAGE_MAX];


            g_StageInfo[0] = new stStageInfo(10.0f, 8.0f, 1.05f, (int)(0.5f / 60.0f), 90.0f);
            g_StageInfo[1] = new stStageInfo(40.0f, 7.9f, 1.08f, (int)(0.5f / 60.0f), 120.0f);
            g_StageInfo[2] = new stStageInfo(50.0f, 7.8f, 1.10f, (int)(0.5f / 60.0f), 150.0f);
            g_StageInfo[3] = new stStageInfo(60.0f, 7.7f, 1.10f, (int)(0.52f / 60.0f), 150.0f);
            g_StageInfo[4] = new stStageInfo(65.0f, 7.6f, 1.15f, (int)(0.54f / 60.0f), 150.0f);
            g_StageInfo[5] = new stStageInfo(70.0f, 7.5f, 1.20f, (int)(0.56f / 60.0f), 150.0f);
            g_StageInfo[6] = new stStageInfo(90.0f, 7.2f, 1.30f, (int)(0.60f / 60.0f), 200.0f);
            g_StageInfo[7] = new stStageInfo(90.0f, 7.0f, 1.35f, (int)(0.62f / 60.0f), 195.0f);
            g_StageInfo[8] = new stStageInfo(90.0f, 6.8f, 1.40f, (int)(0.64f / 60.0f), 190.0f);
            g_StageInfo[9] = new stStageInfo(90.0f, 6.6f, 1.45f, (int)(0.66f / 60.0f), 185.0f);
            g_StageInfo[10] = new stStageInfo(90.0f, 6.4f, 1.50f, (int)(0.68f / 60.0f), 180.0f);
            g_StageInfo[11] = new stStageInfo(90.0f, 6.2f, 1.55f, (int)(0.70f / 60.0f), 175.0f);
            

            for (int i = 0; i < Define.D_STAGE_MAX; i++)
            {
                m_CNumber[i] = new CNumber();

            }
            /////////////////////////////////////////////////////////////////////////////////
            m_pPlayItem[nStageCount] = CCMenuItemImage.itemFromNormalImage(
										        "Button_SelectMenu_1",
										        "Button_SelectMenu_3",
										        this,
                                                new SEL_MenuHandler(StageCallback1));
            m_pPlayItem[nStageCount].position = new CCPoint(25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64, 800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)));
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pPlay[nStageCount] = CCMenu.menuWithItems(m_pPlayItem[nStageCount]);
	        m_pPlay[nStageCount].position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
	        this.addChild(m_pPlay[nStageCount], 3);

            m_CNumber[nStageCount].Init(this, new CCPoint(1.0f, 1.0f), nStageCount + 1, new CCPoint((25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64), (800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)))), 4);

            //m_pLock[nStageCount] = CCSprite::create("Lock.png");
            //m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);
	
            //this->addChild(m_pLock[nStageCount], 3);

            //for(int i=nStageCount; i<3; i++)
            //{
            //    m_pStar[nStageCount][i] = CCSprite::create("Star.png");
            //    m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
            //    this->addChild(m_pStar[nStageCount][i], 3);
            //}
            nStageCount++;
	        ///////////////////////////////////////////////////////////////////////////////

            /////////////////////////////////////////////////////////////////////////////////
            m_pPlayItem[nStageCount] = CCMenuItemImage.itemFromNormalImage(
                                                "Button_SelectMenu_1",
                                                "Button_SelectMenu_3",
                                                this,
                                                new SEL_MenuHandler(StageCallback2));
            m_pPlayItem[nStageCount].position = new CCPoint(25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64, 800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)));
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pPlay[nStageCount] = CCMenu.menuWithItems(m_pPlayItem[nStageCount]);
            m_pPlay[nStageCount].position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            this.addChild(m_pPlay[nStageCount], 3);

            m_CNumber[nStageCount].Init(this, new CCPoint(1.0f, 1.0f), nStageCount + 1, new CCPoint((25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64), (800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)))), 4);

            //m_pLock[nStageCount] = CCSprite::create("Lock.png");
            //m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

            //this->addChild(m_pLock[nStageCount], 3);

            //for(int i=nStageCount; i<3; i++)
            //{
            //    m_pStar[nStageCount][i] = CCSprite::create("Star.png");
            //    m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
            //    this->addChild(m_pStar[nStageCount][i], 3);
            //}
            nStageCount++;
            ///////////////////////////////////////////////////////////////////////////////

            /////////////////////////////////////////////////////////////////////////////////
            m_pPlayItem[nStageCount] = CCMenuItemImage.itemFromNormalImage(
                                                "Button_SelectMenu_1",
                                                "Button_SelectMenu_3",
                                                this,
                                                new SEL_MenuHandler(StageCallback3));
            m_pPlayItem[nStageCount].position = new CCPoint(25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64, 800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)));
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pPlay[nStageCount] = CCMenu.menuWithItems(m_pPlayItem[nStageCount]);
            m_pPlay[nStageCount].position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            this.addChild(m_pPlay[nStageCount], 3);

            m_CNumber[nStageCount].Init(this, new CCPoint(1.0f, 1.0f), nStageCount + 1, new CCPoint((25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64), (800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)))), 4);

            //m_pLock[nStageCount] = CCSprite::create("Lock.png");
            //m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

            //this->addChild(m_pLock[nStageCount], 3);

            //for(int i=nStageCount; i<3; i++)
            //{
            //    m_pStar[nStageCount][i] = CCSprite::create("Star.png");
            //    m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
            //    this->addChild(m_pStar[nStageCount][i], 3);
            //}
            nStageCount++;
            ///////////////////////////////////////////////////////////////////////////////

            /////////////////////////////////////////////////////////////////////////////////
            m_pPlayItem[nStageCount] = CCMenuItemImage.itemFromNormalImage(
                                                "Button_SelectMenu_1",
                                                "Button_SelectMenu_3",
                                                this,
                                                new SEL_MenuHandler(StageCallback4));
            m_pPlayItem[nStageCount].position = new CCPoint(25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64, 800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)));
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pPlay[nStageCount] = CCMenu.menuWithItems(m_pPlayItem[nStageCount]);
            m_pPlay[nStageCount].position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            this.addChild(m_pPlay[nStageCount], 3);

            m_CNumber[nStageCount].Init(this, new CCPoint(1.0f, 1.0f), nStageCount + 1, new CCPoint((25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64), (800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)))), 4);

            //m_pLock[nStageCount] = CCSprite::create("Lock.png");
            //m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

            //this->addChild(m_pLock[nStageCount], 3);

            //for(int i=nStageCount; i<3; i++)
            //{
            //    m_pStar[nStageCount][i] = CCSprite::create("Star.png");
            //    m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
            //    this->addChild(m_pStar[nStageCount][i], 3);
            //}
            nStageCount++;
            ///////////////////////////////////////////////////////////////////////////////

            /////////////////////////////////////////////////////////////////////////////////
            m_pPlayItem[nStageCount] = CCMenuItemImage.itemFromNormalImage(
                                                "Button_SelectMenu_1",
                                                "Button_SelectMenu_3",
                                                this,
                                                new SEL_MenuHandler(StageCallback5));
            m_pPlayItem[nStageCount].position = new CCPoint(25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64, 800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)));
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pPlay[nStageCount] = CCMenu.menuWithItems(m_pPlayItem[nStageCount]);
            m_pPlay[nStageCount].position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            this.addChild(m_pPlay[nStageCount], 3);

            m_CNumber[nStageCount].Init(this, new CCPoint(1.0f, 1.0f), nStageCount + 1, new CCPoint((25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64), (800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)))), 4);

            //m_pLock[nStageCount] = CCSprite::create("Lock.png");
            //m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

            //this->addChild(m_pLock[nStageCount], 3);

            //for(int i=nStageCount; i<3; i++)
            //{
            //    m_pStar[nStageCount][i] = CCSprite::create("Star.png");
            //    m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
            //    this->addChild(m_pStar[nStageCount][i], 3);
            //}
            nStageCount++;
            ///////////////////////////////////////////////////////////////////////////////

            /////////////////////////////////////////////////////////////////////////////////
            m_pPlayItem[nStageCount] = CCMenuItemImage.itemFromNormalImage(
                                                "Button_SelectMenu_1",
                                                "Button_SelectMenu_3",
                                                this,
                                                new SEL_MenuHandler(StageCallback6));
            m_pPlayItem[nStageCount].position = new CCPoint(25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64, 800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)));
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pPlay[nStageCount] = CCMenu.menuWithItems(m_pPlayItem[nStageCount]);
            m_pPlay[nStageCount].position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            this.addChild(m_pPlay[nStageCount], 3);

            m_CNumber[nStageCount].Init(this, new CCPoint(1.0f, 1.0f), nStageCount + 1, new CCPoint((25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64), (800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)))), 4);

            //m_pLock[nStageCount] = CCSprite::create("Lock.png");
            //m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

            //this->addChild(m_pLock[nStageCount], 3);

            //for(int i=nStageCount; i<3; i++)
            //{
            //    m_pStar[nStageCount][i] = CCSprite::create("Star.png");
            //    m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
            //    this->addChild(m_pStar[nStageCount][i], 3);
            //}
            nStageCount++;
            ///////////////////////////////////////////////////////////////////////////////

            /////////////////////////////////////////////////////////////////////////////////
            m_pPlayItem[nStageCount] = CCMenuItemImage.itemFromNormalImage(
                                                "Button_SelectMenu_1",
                                                "Button_SelectMenu_3",
                                                this,
                                                new SEL_MenuHandler(StageCallback7));
            m_pPlayItem[nStageCount].position = new CCPoint(25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64, 800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)));
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pPlay[nStageCount] = CCMenu.menuWithItems(m_pPlayItem[nStageCount]);
            m_pPlay[nStageCount].position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            this.addChild(m_pPlay[nStageCount], 3);

            m_CNumber[nStageCount].Init(this, new CCPoint(1.0f, 1.0f), nStageCount + 1, new CCPoint((25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64), (800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)))), 4);

            //m_pLock[nStageCount] = CCSprite::create("Lock.png");
            //m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

            //this->addChild(m_pLock[nStageCount], 3);

            //for(int i=nStageCount; i<3; i++)
            //{
            //    m_pStar[nStageCount][i] = CCSprite::create("Star.png");
            //    m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
            //    this->addChild(m_pStar[nStageCount][i], 3);
            //}
            nStageCount++;
            ///////////////////////////////////////////////////////////////////////////////

            /////////////////////////////////////////////////////////////////////////////////
            m_pPlayItem[nStageCount] = CCMenuItemImage.itemFromNormalImage(
                                                "Button_SelectMenu_1",
                                                "Button_SelectMenu_3",
                                                this,
                                                new SEL_MenuHandler(StageCallback8));
            m_pPlayItem[nStageCount].position = new CCPoint(25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64, 800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)));
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pPlay[nStageCount] = CCMenu.menuWithItems(m_pPlayItem[nStageCount]);
            m_pPlay[nStageCount].position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            this.addChild(m_pPlay[nStageCount], 3);

            m_CNumber[nStageCount].Init(this, new CCPoint(1.0f, 1.0f), nStageCount + 1, new CCPoint((25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64), (800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)))), 4);

            //m_pLock[nStageCount] = CCSprite::create("Lock.png");
            //m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

            //this->addChild(m_pLock[nStageCount], 3);

            //for(int i=nStageCount; i<3; i++)
            //{
            //    m_pStar[nStageCount][i] = CCSprite::create("Star.png");
            //    m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
            //    this->addChild(m_pStar[nStageCount][i], 3);
            //}
            nStageCount++;
            ///////////////////////////////////////////////////////////////////////////////

            /////////////////////////////////////////////////////////////////////////////////
            m_pPlayItem[nStageCount] = CCMenuItemImage.itemFromNormalImage(
                                                "Button_SelectMenu_1",
                                                "Button_SelectMenu_3",
                                                this,
                                                new SEL_MenuHandler(StageCallback9));
            m_pPlayItem[nStageCount].position = new CCPoint(25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64, 800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)));
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pPlay[nStageCount] = CCMenu.menuWithItems(m_pPlayItem[nStageCount]);
            m_pPlay[nStageCount].position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            this.addChild(m_pPlay[nStageCount], 3);

            m_CNumber[nStageCount].Init(this, new CCPoint(1.0f, 1.0f), nStageCount + 1, new CCPoint((25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64), (800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)))), 4);

            //m_pLock[nStageCount] = CCSprite::create("Lock.png");
            //m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

            //this->addChild(m_pLock[nStageCount], 3);

            //for(int i=nStageCount; i<3; i++)
            //{
            //    m_pStar[nStageCount][i] = CCSprite::create("Star.png");
            //    m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
            //    this->addChild(m_pStar[nStageCount][i], 3);
            //}
            nStageCount++;
            ///////////////////////////////////////////////////////////////////////////////

            /////////////////////////////////////////////////////////////////////////////////
            m_pPlayItem[nStageCount] = CCMenuItemImage.itemFromNormalImage(
                                                "Button_SelectMenu_1",
                                                "Button_SelectMenu_3",
                                                this,
                                                new SEL_MenuHandler(StageCallback10));
            m_pPlayItem[nStageCount].position = new CCPoint(25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64, 800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)));
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pPlay[nStageCount] = CCMenu.menuWithItems(m_pPlayItem[nStageCount]);
            m_pPlay[nStageCount].position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            this.addChild(m_pPlay[nStageCount], 3);

            m_CNumber[nStageCount].Init(this, new CCPoint(1.0f, 1.0f), nStageCount + 1, new CCPoint((25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64), (800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)))), 4);

            //m_pLock[nStageCount] = CCSprite::create("Lock.png");
            //m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

            //this->addChild(m_pLock[nStageCount], 3);

            //for(int i=nStageCount; i<3; i++)
            //{
            //    m_pStar[nStageCount][i] = CCSprite::create("Star.png");
            //    m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
            //    this->addChild(m_pStar[nStageCount][i], 3);
            //}
            nStageCount++;
            ///////////////////////////////////////////////////////////////////////////////

            /////////////////////////////////////////////////////////////////////////////////
            m_pPlayItem[nStageCount] = CCMenuItemImage.itemFromNormalImage(
                                                "Button_SelectMenu_1",
                                                "Button_SelectMenu_3",
                                                this,
                                                new SEL_MenuHandler(StageCallback11));
            m_pPlayItem[nStageCount].position = new CCPoint(25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64, 800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)));
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pPlay[nStageCount] = CCMenu.menuWithItems(m_pPlayItem[nStageCount]);
            m_pPlay[nStageCount].position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            this.addChild(m_pPlay[nStageCount], 3);

            m_CNumber[nStageCount].Init(this, new CCPoint(1.0f, 1.0f), nStageCount + 1, new CCPoint((25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64), (800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)))), 4);

            //m_pLock[nStageCount] = CCSprite::create("Lock.png");
            //m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

            //this->addChild(m_pLock[nStageCount], 3);

            //for(int i=nStageCount; i<3; i++)
            //{
            //    m_pStar[nStageCount][i] = CCSprite::create("Star.png");
            //    m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
            //    this->addChild(m_pStar[nStageCount][i], 3);
            //}
            nStageCount++;
            ///////////////////////////////////////////////////////////////////////////////

            /////////////////////////////////////////////////////////////////////////////////
            m_pPlayItem[nStageCount] = CCMenuItemImage.itemFromNormalImage(
                                                "Button_SelectMenu_1",
                                                "Button_SelectMenu_3",
                                                this,
                                                new SEL_MenuHandler(StageCallback12));
            m_pPlayItem[nStageCount].position = new CCPoint(25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64, 800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)));
            //m_pPlayItem[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            m_pPlay[nStageCount] = CCMenu.menuWithItems(m_pPlayItem[nStageCount]);
            m_pPlay[nStageCount].position = new CCPoint(0, 0);
            //m_pPlay[nStageCount].Color = new ccColor3B((byte)(255 - (nStageCount*3),(byte)(255 - (nStageCount*3)),(byte)(255 - (nStageCount*5)));
            this.addChild(m_pPlay[nStageCount], 3);

            m_CNumber[nStageCount].Init(this, new CCPoint(1.0f, 1.0f), nStageCount + 1, new CCPoint((25 + (Define.D_STAGEMENU_WIDTH * ((nStageCount % 3) + 1)) - 64), (800 - (Define.D_STAGEMENU_HEGIHT * ((nStageCount / 3) + 1)))), 4);

            //m_pLock[nStageCount] = CCSprite::create("Lock.png");
            //m_pLock[nStageCount]->setPosition( ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64) * D_SCALE_WIDTH , (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1))) * D_SCALE_HEIGHT) );m_pLock[nStageCount]->setScaleX(1.00f * D_SCALE_WIDTH);m_pLock[nStageCount]->setScaleY(1.00f * D_SCALE_HEIGHT);

            //this->addChild(m_pLock[nStageCount], 3);

            //for(int i=nStageCount; i<3; i++)
            //{
            //    m_pStar[nStageCount][i] = CCSprite::create("Star.png");
            //    m_pStar[nStageCount][i]->setPosition(ccp( (25 +  (D_STAGEMENU_WIDTH * ((nStageCount%3)+1)) -64 +(30*i) - 30) * D_SCALE_WIDTH, (800  - (D_STAGEMENU_HEGIHT * ((nStageCount/3)+1)) - 30) * D_SCALE_HEIGHT ));m_pStar[nStageCount][i]->setScaleX(0.50f * D_SCALE_WIDTH);m_pStar[nStageCount][i]->setScaleY(0.50f * D_SCALE_HEIGHT);
            //    this->addChild(m_pStar[nStageCount][i], 3);
            //}
            nStageCount++;
            ///////////////////////////////////////////////////////////////////////////////
            CCMenuItemImage pCloseItem = CCMenuItemImage.itemFromNormalImage(
                                                "CloseNormal",
                                                "CloseSelected",
                                                this,
                                                new SEL_MenuHandler(menuCloseCallback));
            pCloseItem.position = new CCPoint(CCDirector.sharedDirector().getWinSize().width - 20, 20);

            CCMenu pMenu = CCMenu.menuWithItems(pCloseItem);
            pMenu.position = new CCPoint(0, 0);
            this.addChild(pMenu, 3);




            ///////////////////////////////
            //// 3. add your codes below...

            //// add a label shows "Hello World"
            //// create and initialize a label
            //CCLabelTTF pLabel = CCLabelTTF.labelWithString("SwordArt Online", "Arial", 24);
            //// ask director the window size
            //CCSize size = CCDirector.sharedDirector().getWinSize();

            //// position the label on the center of the screen
            //pLabel.position = new CCPoint(size.width / 2, size.height - 50);

            //// add the label as a child to this layer
            //this.addChild(pLabel, 1);

            //////////////////////////////////////////////////////////////////////////////////////
            m_pSprite = CCSprite.spriteWithFile("StageMenu_Bg");
            m_pSprite.position = new CCPoint(240, 400);
            m_pSprite.scaleX = 1.05f;
            m_pSprite.scaleY = 1.05f;
            this.addChild(m_pSprite, 1);
            //////////////////////////////////////////////////////////////////////////////////////

            CCParticleSystem emitter;
            emitter = CCParticleSnow.node();
            emitter.Texture = CCTextureCache.sharedTextureCache().addImage("Snow1"); // emitter.setTexture(CCTextureCache::sharedTextureCache()->addImage("Snow1.png"));
            emitter.TotalParticles = 500; //emitter->setTotalParticles(500);
            emitter.IsAutoRemoveOnFinish = true; //emitter->setAutoRemoveOnFinish(true);
            emitter.Life = 6.0f; //emitter->setLife(6.0f);
            emitter.LifeVar = 1.0f; //emitter->setLifeVar(1.0f);
            emitter.position = new CCPoint(300, (850)); // emitter->setPosition(ccp(size.width - (size.width/4), (size.height) + 50));
            emitter.setGravity(new CCPoint(-100, -100)); // emitter->setGravity(ccp(-100,-100));
            emitter.setSpeedVar(200);

            //emitter->setRotatePerSecond(10.0f);
            //emitter->setRotatePerSecondVar(20.0f);

            emitter.scale = 1.0f;//emitter.setScale(1.0f);
            emitter.StartSize = 10.0f;//emitter.setStartSize(10.0f);
            emitter.EndSize = 10.0f;//emitter.setEndSize(10.0f);
            emitter.Duration = 60.0f;//emitter.setDuration(360.0f);

            emitter.setSpeed(200);
            //emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
            emitter.EmissionRate = 100.0f;
            //emitter->setEmissionRate(100.0f);
            //emitter->setAngle(0.0f);
            //emitter->setAngleVar(360.0f);
            addChild(emitter, 1);
            this.schedule(Update, 0.0f);

            return true;
        }
        /// <summary>
        /// there's no 'id' in cpp, so we recommand to return the exactly class pointer
        /// </summary>
        /// 
        public void Update(float dt)
        {
            m_fTimer += dt;

            if (m_fTouchTimer < 1.0f)
            {
                m_fTouchTimer += dt;
                if (m_fTouchTimer >= 1.0f)
                {
                    m_fTouchTimer = 1.0f;
                    CCApplication.m_bIsProcTocuh = true;
                }
            }
        }
        public static CCScene scene()
        {
            // 'scene' is an autorelease object
            CCScene scene = CCScene.node();

            // 'layer' is an autorelease object
            CCLayer layer = StageMenuScene.node();

            // add layer as a child to scene
            scene.addChild(layer);

            // return the scene
            return scene;
        }

        public static new CCLayer node()
        {
            StageMenuScene ret = new StageMenuScene();
            if (ret.init())
            {
                return ret;
            }
            else
            {
                ret = null;
            }

            return ret;
        }

        /// <summary>
        /// a selector callback
        /// </summary>
        /// <param name="pSender"></param>
        public virtual void menuCloseCallback(CCObject pSender)
        {
            CCDirector.sharedDirector().end();
            CCApplication.sharedApplication().Game.Exit();
        }

        public virtual void BackCallback(CCObject pSender)
        {
            if (m_bPopUp == false)
            {

                //m_pLoading.setVisible(true);
                CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, MenuScene.scene());

                CCDirector.sharedDirector().replaceScene(pScene);

                if (MenuScene.g_bEffect_Sound == true)
                    m_Sae.playEffect("StageStart");
            }
        }


        public virtual void CreditCallback(CCObject pSender)
        {
            // if(m_bPopUp == false)
            // {
            //  // CCDirector::sharedDirector()->end();
            //D_SCENE_CHANGE_EFFECT_L(CreditScene::scene());
            //
            ////CCScene *pScene = CCTransitionTurnOffTiles::transitionWithDuration(1,CreditScene::scene(),true);
            ////CCScene *pScene = CCTransitionCrossFade();
            //CCDirector::sharedDirector()->replaceScene(pScene);
            //if(g_bSound == true) { m_Sae->playEffect("StageStart.mp3"); }
            // }
    }



        public virtual void StageCallback1(CCObject pSender)
        {
            g_nSelectStage = 1;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }
        public virtual void StageCallback2(CCObject pSender)
        {
            g_nSelectStage = 2;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }
        public virtual void StageCallback3(CCObject pSender)
        {
            g_nSelectStage = 3;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }
        public virtual void StageCallback4(CCObject pSender)
        {
            g_nSelectStage = 4;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }
        public virtual void StageCallback5(CCObject pSender)
        {
            g_nSelectStage = 5;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }
        public virtual void StageCallback6(CCObject pSender)
        {
            g_nSelectStage = 6;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }
        public virtual void StageCallback7(CCObject pSender)
        {
            g_nSelectStage = 7;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }
        public virtual void StageCallback8(CCObject pSender)
        {
            g_nSelectStage = 8;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }
        public virtual void StageCallback9(CCObject pSender)
        {
            g_nSelectStage = 9;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }
        public virtual void StageCallback10(CCObject pSender)
        {
            g_nSelectStage = 10;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }
        public virtual void StageCallback11(CCObject pSender)
        {
            g_nSelectStage = 11;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }
        public virtual void StageCallback12(CCObject pSender)
        {
            g_nSelectStage = 12;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }
        public virtual void ExitCallback(CCObject pSender)
        {
            if (m_bPopUp == false)
            {
                CCDirector.sharedDirector().end();
                CCApplication.sharedApplication().Game.Exit();
            }
        }


        

        public virtual void OptionCallback(CCObject pSender)
        {
            //if(m_bPopUp == false)
            //{
            //    m_bPopUp = true;
            //}
        }
        public override void ccTouchesBegan(List<CCTouch> touches, CCEvent event_)
        {
            //CCSize s = CCDirector.sharedDirector().getWinSize();
            //CCActionInterval actionTo = CCMoveTo.actionWithDuration(3, new CCPoint(-s.width, -s.height));
            //pSprite.runAction(actionTo);
        }
    }
}
