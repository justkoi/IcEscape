using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using cocos2d;
using CocosDenshion;

namespace HelloCocos2d
{
    public class MenuScene : CCLayer
    {
        /// <summary>
        ///  Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
        /// </summary>
        /// 
        public CCSprite m_pSprite;
        public CCSprite m_pTitle;
        public CCSprite m_pBlind;

        public CCMenuItemImage pGameStartItem;
        public CCMenu pGameStart;

        public CCMenuItemImage pCreditItem;
        public CCMenu pCreditStart;

        public CCMenuItemImage pOptionItem;
        public CCMenu pOption;

        public CCMenuItemImage pExitItem;
        public CCMenu pExit;

        public float m_fTimer;
        public float m_fUpDownTime;
        public float m_fUpDownSpeed;
        public float m_fUpDownPlusTime;
        public bool m_fUpDown;

        public bool m_bPopUp;

        public SimpleAudioEngine m_Sae;

        static public bool g_bBGM_Sound = true;
        static public bool g_bEffect_Sound = true;

        public float m_fTouchTimer;

        public override bool init()
        {
            CCDirector.sharedDirector().deviceOrientation = ccDeviceOrientation.CCDeviceOrientationPortrait;

            m_fUpDownTime = 0.0f;
            m_fUpDownSpeed = 0.017f;
            m_fUpDownPlusTime = 0.0f;
            m_fTimer = 0.0f;
            m_fTouchTimer = 0.0f;

            //////////////////////////////
	        // 1. super init first
            if (!base.init())
            {
                return false;
            }

            m_Sae = new SimpleAudioEngine();

            m_Sae.preloadEffect("Button");
            m_Sae.preloadEffect("StageStart");

            m_Sae.preloadBackgroundMusic("Logo_BGM");
            if (MenuScene.g_bBGM_Sound == true)
                m_Sae.playBackgroundMusic("Logo_BGM", true);

            this.m_bIsTouchEnabled = true;
            CCApplication.m_bIsProcTocuh = true;

	        CCMenuItemImage pCloseItem = CCMenuItemImage.itemFromNormalImage(
										        "CloseNormal",
										        "CloseSelected",
										        this,
										        new SEL_MenuHandler(menuCloseCallback) );
	        pCloseItem.position = new CCPoint(CCDirector.sharedDirector().getWinSize().width - 20, 20);

	        CCMenu pMenu = CCMenu.menuWithItems(pCloseItem);
	        pMenu.position = new CCPoint(0, 0);
	        this.addChild(pMenu, 3);

            //////////////////////////////////////////////////////////////////////////////////////
            pGameStartItem = CCMenuItemImage.itemFromNormalImage(
										        "Button_Start_1",
										        "Button_Start_3",
										        this,
										        new SEL_MenuHandler(GameStartCallback) );
	        pGameStartItem.position = new CCPoint(230, 400);

	        pGameStart = CCMenu.menuWithItems(pGameStartItem);
	        pGameStart.position = new CCPoint(0, 0);
	        this.addChild(pGameStart, 3);
            //////////////////////////////////////////////////////////////////////////////////////
            pCreditItem = CCMenuItemImage.itemFromNormalImage(
										        "Button_Credit_1",
										        "Button_Credit_3",
										        this,
										        new SEL_MenuHandler(CreditCallback) );
	        pCreditItem.position = new CCPoint(235, 300);

	        pCreditStart = CCMenu.menuWithItems(pCreditItem);
	        pCreditStart.position = new CCPoint(0, 0);
	        this.addChild(pCreditStart, 3);
	        //////////////////////////////////////////////////////////////////////////////////////
            pOptionItem = CCMenuItemImage.itemFromNormalImage(
										        "Button_Option_1",
										        "Button_Option_3",
										        this,
										        new SEL_MenuHandler(OptionCallback) );
	        pOptionItem.position = new CCPoint(235, 200);

	        pOption = CCMenu.menuWithItems(pOptionItem);
	        pOption.position = new CCPoint(0, 0);
	        this.addChild(pOption, 3);
	        //////////////////////////////////////////////////////////////////////////////////////
            pExitItem = CCMenuItemImage.itemFromNormalImage(
										        "Button_Quit_1",
										        "Button_Quit_3",
										        this,
										        new SEL_MenuHandler(ExitCallback) );
	        pExitItem.position = new CCPoint(235, 100);

	        pExit = CCMenu.menuWithItems(pExitItem);
	        pExit.position = new CCPoint(0, 0);
	        this.addChild(pExit, 3);
	        //////////////////////////////////////////////////////////////////////////////////////
            

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
            m_pSprite = CCSprite.spriteWithFile("Menu");
            m_pSprite.position = new CCPoint(240, 400);
            m_pSprite.scaleX = 1.05f;
            m_pSprite.scaleY = 1.05f;
            this.addChild(m_pSprite, 1);
            //////////////////////////////////////////////////////////////////////////////////////
            m_pTitle = CCSprite.spriteWithFile("Title");
            m_pTitle.position = new CCPoint(240, 600);
            m_pTitle.scaleX = 1.6f;
            m_pTitle.scaleY = 1.6f;
            this.addChild(m_pTitle, 2);
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
            addChild(emitter,1);

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

            //m_pTitle.position.x += 50.0f;
            // m_pTitle.positionInPixels.x += 50.0f;


            // m_pTitle.update(dt);
            //  m_pTitle.runAction(new CCAction());
            // m_pSprite.setPosition(CCPoint(m_pSprite->getPositionX(), m_pSprite->getPositionY() - (m_fUpDownTime)));
            // m_pTitle.setPosition(CCPoint(m_pTitle->getPositionX(), m_pTitle->getPositionY() + (m_fUpDownTime)));

            m_pSprite.position = new CCPoint(m_pSprite.position.x, m_pSprite.position.y - m_fUpDownTime * dt * 60.0f);
            m_pTitle.position = new CCPoint(m_pTitle.position.x, m_pTitle.position.y + m_fUpDownTime * dt * 60.0f);

            //m_pSprite.position.y = m_pSprite.position.y - m_fUpDownTime;
            //m_pTitle.position.y = m_pTitle.position.y + m_fUpDownTime;

            ////m_pTitle->MoveY();
            m_fUpDownTime -= m_fUpDownSpeed * dt * 60.0f;
            m_fUpDownSpeed += m_fUpDownPlusTime * dt * 60.0f;
            if (m_fUpDownTime <= -0.5f)
            {
                m_fUpDownSpeed = -0.017f;
            }
            else if (m_fUpDownTime >= 0.5f)
            {
                m_fUpDownSpeed = 0.017f;
            }

        }
        public static CCScene scene()
        {
            // 'scene' is an autorelease object
            CCScene scene = CCScene.node();

            // 'layer' is an autorelease object
            CCLayer layer = MenuScene.node();

            // add layer as a child to scene
            scene.addChild(layer);

            // return the scene
            return scene;
        }

        public static new CCLayer node()
        {
            MenuScene ret = new MenuScene();
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
        
        public virtual void GameStartCallback(CCObject pSender)
        {
            if(m_bPopUp == false)
            {
	           
                //m_pLoading.setVisible(true);
                CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageMenuScene.scene());

                CCDirector.sharedDirector().replaceScene(pScene);
                CCApplication.m_bIsProcTocuh = false;

                if (g_bEffect_Sound == true)
                    m_Sae.playEffect("StageStart",false);
	        }
        }


        public virtual void CreditCallback(CCObject pSender)
        {
          if(m_bPopUp == false)
          {
              CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, CreditScene.scene());

              CCDirector.sharedDirector().replaceScene(pScene);
              CCApplication.m_bIsProcTocuh = false;

              if (g_bEffect_Sound == true)
                  m_Sae.playEffect("StageStart", false);
          }
        }

        public virtual void ExitCallback(CCObject pSender)
        {
	        if(m_bPopUp == false)
            {
                CCDirector.sharedDirector().end();
                CCApplication.sharedApplication().Game.Exit();

                if (g_bEffect_Sound == true)
                    m_Sae.playEffect("StageStart");
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
