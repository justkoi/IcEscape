using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using cocos2d;
using CocosDenshion;

namespace HelloCocos2d
{
    public class CreditScene : CCLayer
    {
        /// <summary>
        ///  Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
        /// </summary>
        /// 

        public CCSprite m_pBlind;

        public CCSprite[] m_pBg;
        public CCSprite[] m_pProducer;

        public SimpleAudioEngine m_Sae;

        public float m_fTouchTimer;

        public int m_nStep;
        public float m_fTimer;
        public float m_fBlendTimer;

        public CCMenuItemImage m_pBackItem;
        public CCMenu m_pBack;
        public CCParticleSystem[] emitter;
        public override bool init()
        {
            CCDirector.sharedDirector().deviceOrientation = ccDeviceOrientation.CCDeviceOrientationPortrait;

            m_fTouchTimer = 0.0f;

            //////////////////////////////
	        // 1. super init first
            if (!base.init())
            {
                return false;
            }

            m_pBg = new CCSprite[2];
            m_pProducer = new CCSprite[4];
            emitter = new CCParticleSystem[3];

            m_Sae = new SimpleAudioEngine();

            m_Sae.preloadEffect("Button");
            m_Sae.preloadEffect("StageStart");

            m_Sae.preloadBackgroundMusic("Producer_BGM");
            if (MenuScene.g_bBGM_Sound == true)
                m_Sae.playBackgroundMusic("Producer_BGM", true);

            this.m_bIsTouchEnabled = true;
            CCApplication.m_bIsProcTocuh = true;

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
            m_pBg[0] = CCSprite.spriteWithFile("Credit_Bg1");
            m_pBg[0].position = new CCPoint(240, 400);
            m_pBg[0].scaleX = 1.00f;
            m_pBg[0].scaleY = 1.00f;
            this.addChild(m_pBg[0], 0);
            //////////////////////////////////////////////////////////////////////////////////////

            //////////////////////////////////////////////////////////////////////////////////////
            m_pBg[1] = CCSprite.spriteWithFile("Credit_Bg2");
            m_pBg[1].position = new CCPoint(240, 400);
            m_pBg[1].scaleX = 1.00f;
            m_pBg[1].scaleY = 1.00f;
            this.addChild(m_pBg[1], 1);
            //////////////////////////////////////////////////////////////////////////////////////

            //////////////////////////////////////////////////////////////////////////////////////
            m_pBlind = CCSprite.spriteWithFile("Blind");
            m_pBlind.position = new CCPoint(240, 400);
            m_pBlind.scaleX = 1.00f;
            m_pBlind.scaleY = 1.00f;
            m_pBlind.Opacity = (byte)(255 * 0.7f);
            this.addChild(m_pBlind, 2);
            //////////////////////////////////////////////////////////////////////////////////////

            //////////////////////////////////////////////////////////////////////////////////////
            m_pProducer[0] = CCSprite.spriteWithFile("Maker1");
            m_pProducer[0].position = new CCPoint(240, 480);
            this.addChild(m_pProducer[0], 4);
            //////////////////////////////////////////////////////////////////////////////////////


            //////////////////////////////////////////////////////////////////////////////////////
            m_pProducer[1] = CCSprite.spriteWithFile("Maker2");
            m_pProducer[1].position = new CCPoint(240, 680);
            this.addChild(m_pProducer[1], 4);
            //////////////////////////////////////////////////////////////////////////////////////

            //////////////////////////////////////////////////////////////////////////////////////
            m_pProducer[2] = CCSprite.spriteWithFile("Maker3");
            m_pProducer[2].position = new CCPoint(240, 300);
            this.addChild(m_pProducer[2], 4);
            //////////////////////////////////////////////////////////////////////////////////////


            //////////////////////////////////////////////////////////////////////////////////////
            m_pProducer[3] = CCSprite.spriteWithFile("Maker4");
            m_pProducer[3].position = new CCPoint(240, 150);
            m_pProducer[3].scale = 0.6f;
            this.addChild(m_pProducer[3], 4);
            //////////////////////////////////////////////////////////////////////////////////////

            this.schedule(Update, 0.0f);

            emitter[0] = CCParticleFlower.node();
            emitter[0].Texture = CCTextureCache.sharedTextureCache().addImage("Snow1"); // emitter.setTexture(CCTextureCache::sharedTextureCache()->addImage("Snow1.png"));
            emitter[0].TotalParticles = 200; //emitter->setTotalParticles(500);
            emitter[0].IsAutoRemoveOnFinish = true; //emitter->setAutoRemoveOnFinish(true);
            emitter[0].Life = 6.0f; //emitter->setLife(6.0f);
            emitter[0].LifeVar = 1.0f; //emitter->setLifeVar(1.0f);
            emitter[0].position = new CCPoint((480/4), (800) - (800/5)); // emitter->setPosition(ccp(size.width - (size.width/4), (size.height) + 50));
            //emitter[0].setGravity(new CCPoint(-100, -100)); // emitter->setGravity(ccp(-100,-100));
            emitter[0].setSpeedVar(200);

            //emitter->setRotatePerSecond(10.0f);
            //emitter->setRotatePerSecondVar(20.0f);

            emitter[0].scale = 1.0f;//emitter.setScale(1.0f);
            emitter[0].StartSize = 10.0f;//emitter.setStartSize(10.0f);
            emitter[0].EndSize = 10.0f;//emitter.setEndSize(10.0f);
            emitter[0].Duration = 60.0f;//emitter.setDuration(360.0f);

            emitter[0].setSpeed(200);
            //emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
            emitter[0].EmissionRate = 100.0f;
            //emitter->setEmissionRate(100.0f);
            //emitter->setAngle(0.0f);
            //emitter->setAngleVar(360.0f);
            //addChild(emitter[0], 1);



            emitter[1] = CCParticleFlower.node();
            emitter[1].Texture = CCTextureCache.sharedTextureCache().addImage("Snow1"); // emitter.setTexture(CCTextureCache::sharedTextureCache()->addImage("Snow1.png"));
            emitter[1].TotalParticles = 200; //emitter->setTotalParticles(500);
            emitter[1].IsAutoRemoveOnFinish = true; //emitter->setAutoRemoveOnFinish(true);
            emitter[1].Life = 6.0f; //emitter->setLife(6.0f);
            emitter[1].LifeVar = 1.0f; //emitter->setLifeVar(1.0f);
            emitter[1].position = new CCPoint((480*3/ 4), (800) - (800*3/ 5)); // emitter->setPosition(ccp(size.width - (size.width/4), (size.height) + 50));
            //emitter[1].setGravity(new CCPoint(-100, -100)); // emitter->setGravity(ccp(-100,-100));
            emitter[1].setSpeedVar(200);

            //emitter->setRotatePerSecond(10.0f);
            //emitter->setRotatePerSecondVar(20.0f);

            emitter[1].scale = 1.0f;//emitter.setScale(1.0f);
            emitter[1].StartSize = 10.0f;//emitter.setStartSize(10.0f);
            emitter[1].EndSize = 10.0f;//emitter.setEndSize(10.0f);
            emitter[1].Duration = 60.0f;//emitter.setDuration(360.0f);

            emitter[1].setSpeed(200);
            //emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
            emitter[1].EmissionRate = 100.0f;
            //emitter->setEmissionRate(100.0f);
            //emitter->setAngle(0.0f);
            //emitter->setAngleVar(360.0f);
            //addChild(emitter[0], 1);

            emitter[2] = CCParticleFlower.node();
            emitter[2].Texture = CCTextureCache.sharedTextureCache().addImage("Snow1"); // emitter.setTexture(CCTextureCache::sharedTextureCache()->addImage("Snow1.png"));
            emitter[2].TotalParticles = 200; //emitter->setTotalParticles(500);
            emitter[2].IsAutoRemoveOnFinish = true; //emitter->setAutoRemoveOnFinish(true);
            emitter[2].Life = 6.0f; //emitter->setLife(6.0f);
            emitter[2].LifeVar = 1.0f; //emitter->setLifeVar(1.0f);
            emitter[2].position = new CCPoint((480 / 4), (800) - (800 * 4 / 5)); // emitter->setPosition(ccp(size.width - (size.width/4), (size.height) + 50));
            //emitter[2].setGravity(new CCPoint(-100, -100)); // emitter->setGravity(ccp(-100,-100));
            emitter[2].setSpeedVar(200);

            //emitter->setRotatePerSecond(10.0f);
            //emitter->setRotatePerSecondVar(20.0f);

            emitter[2].scale = 1.0f;//emitter.setScale(1.0f);
            emitter[2].StartSize = 10.0f;//emitter.setStartSize(10.0f);
            emitter[2].EndSize = 10.0f;//emitter.setEndSize(10.0f);
            emitter[2].Duration = 60.0f;//emitter.setDuration(360.0f);

            emitter[2].setSpeed(200);
            //emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
            emitter[2].EmissionRate = 100.0f;
            //emitter->setEmissionRate(100.0f);
            //emitter->setAngle(0.0f);
            //emitter->setAngleVar(360.0f);
            //addChild(emitter[0], 1);

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

            if (m_fTimer >= 1.0 && m_nStep < 1)
            {
                addChild(emitter[m_nStep], 3);
                m_nStep++;
            }
            else if (m_fTimer >= 3.0 && m_nStep < 2)
            {
                addChild(emitter[m_nStep], 3);
                m_nStep++;
            }
            else if (m_fTimer >= 5.0 && m_nStep < 3)
            {
                addChild(emitter[m_nStep], 3);
                m_nStep++;
            }

        }
        public static CCScene scene()
        {
            // 'scene' is an autorelease object
            CCScene scene = CCScene.node();

            // 'layer' is an autorelease object
            CCLayer layer = CreditScene.node();

            // add layer as a child to scene
            scene.addChild(layer);

            // return the scene
            return scene;
        }

        public static new CCLayer node()
        {
            CreditScene ret = new CreditScene();
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

                //m_pLoading.setVisible(true);
                CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, MenuScene.scene());

                CCDirector.sharedDirector().replaceScene(pScene);

                if (MenuScene.g_bEffect_Sound == true)
                    m_Sae.playEffect("StageStart");
            
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
