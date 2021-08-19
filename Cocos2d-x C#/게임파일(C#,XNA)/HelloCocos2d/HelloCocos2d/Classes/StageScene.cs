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
    public class StageScene : CCLayer
    {
        /// <summary>
        ///  Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
        /// </summary>
        /// 

        public enum E_BLOCKACT
        {
	        E_BLOCKACT_NONE,
	        E_BLOCKACT_MOVE,
	        E_BLOCKACT_DRAG,
	        E_BLOCKACT_NOT
        };
        public enum E_GAMERESULT
        {
	        E_GAMERESULT_NONE,
	        E_GAMERESULT_VICTORY,
	        E_GAMERESULT_DEFEAT,

        };
        public enum E_GAMESTEP
        {
	        E_GAMESTEP_READY,
	        E_GAMESTEP_PLAY,
	        E_GAMESTEP_END,

        };
        static public bool g_bPause;

        public CCSprite m_pBlind;
        public CCSprite[] m_pBackGround;


        public CCSprite m_pPauseBlind;

        public CCMenuItemImage m_pSetItem;
        public CCMenu m_pSet;

        public CCMenuItemImage m_pResumeItem;
        public CCMenu m_pResume;

        public CCMenuItemImage m_pPauseItem;
        public CCMenu m_pPause;


        public float m_fTimer;
        public float m_fUpDownTime;
        public float m_fUpDownSpeed;
        public float m_fUpDownPlusTime;
        public bool m_fUpDown;


        public bool m_bFreeMove;

        public bool m_bPopUp;

        public float m_fErosionSpeed; //!< 갈수록 빨라지는 침식속도
        public int m_nErosionPlusSpeed;//!< 침식가속도

        public int m_nTtLevel; //!< 튜토리얼 레벨

        public CBlock[] m_BlockList;

        public E_GAMERESULT m_eGameResult;
        public E_GAMESTEP m_eGameStep;


        public float m_fCreateTimer;
        public float m_fCreateTime;

        public float m_fTimeLimit;

        public int m_nBlockMax;

        public CMap m_Map;
        public Random r;

        public CCSprite m_pGameOver;
        public CCSprite m_pGameClear;

        public CCPoint m_stMoveBlockPos;

        public CNumber m_pNumberTimeLimit;
        public CNumber m_pNumberStage;
        public CNumber m_pNumberScore;
        public CNumber m_pNumberLastScore;


        public CSeaLevel m_CSeaLevel;
        public List<CBlock> m_MouseList;
        public List<CIceChunk> m_IceChunkList;


        public bool m_bMouseDown;
        public bool m_bBlockAct;

        public float m_fBlindTimer;

        public E_BLOCKACT m_eBlockAct;

        public int m_nStage;
        public bool m_bSaved;

        public float m_fTouchTimer;

        public float m_fPopUpTimer;
        public float m_fSeaLevelMax;


        public SimpleAudioEngine m_Sae;

        public void CreateBlock(int nX, int nY)
        {
	        for(int i=0; i<m_nBlockMax; i++)
	        {
		        if(m_BlockList[i].m_bLive == true)
			        continue;

                m_BlockList[i].Create(new stVec2i(nX, nY), r);
		        m_Map.m_nBlockMap[nY,nX] = 1;
		        break;
	        }
        }

        //void CreateBlockIt(int nX, int nY, E_BLOCKNUMBER eBlockNumber)
        //{
        //    for(int i=0; i<m_nBlockMax; i++)
        //    {
        //        if(m_BlockList[i].m_bLive == true)
        //            continue;

        //        m_BlockList[i].CreateIt(stVec2i(nX,nY),eBlockNumber);
        //        m_Map->m_nBlockMap[nY][nX] = 1;
        //        break;
        //    }
        //}
        public void CreateLine()
        {
	        for(int i=0; i<Define.D_BLOCKMAP_WIDTH; i++)
	        {
		        CreateBlock(i,0);
	        }
        }

        public override bool init()
        {
            CCDirector.sharedDirector().deviceOrientation = ccDeviceOrientation.CCDeviceOrientationPortrait;


            //////////////////////////////
	        // 1. super init first
            if (!base.init())
            {
                return false;
            }
            StageMenuScene.g_nScore = 0;

            g_bPause = false;

            m_bSaved = false;
            m_fPopUpTimer = 0.0f;

            m_fTouchTimer = 0.0f;

            m_Sae = new SimpleAudioEngine();

            m_Sae.preloadEffect("Ice");
            m_Sae.preloadEffect("Button");
            m_Sae.preloadEffect("StageStart");
            m_Sae.preloadEffect("WIN");
            m_Sae.preloadEffect("LOSE");
            m_Sae.preloadEffect("Warning2");
            m_Sae.preloadEffect("Erosion");


            m_Sae.preloadBackgroundMusic("Game_BGM1");
            if (MenuScene.g_bBGM_Sound == true)
                m_Sae.playBackgroundMusic("Game_BGM1", true);



            m_nStage = StageMenuScene.g_nSelectStage;


            m_fTimeLimit = StageMenuScene.g_StageInfo[StageMenuScene.g_nSelectStage - 1].m_fTimeLimit;
            m_fCreateTime = StageMenuScene.g_StageInfo[StageMenuScene.g_nSelectStage - 1].m_fCraeteTime;
            m_fErosionSpeed = StageMenuScene.g_StageInfo[StageMenuScene.g_nSelectStage - 1].m_fErosionSpeed;
            m_nErosionPlusSpeed = StageMenuScene.g_StageInfo[StageMenuScene.g_nSelectStage - 1].m_nErosionPlusSpeed;
            m_fSeaLevelMax = StageMenuScene.g_StageInfo[StageMenuScene.g_nSelectStage - 1].m_fSeaLevelMax;


            m_pNumberTimeLimit = new CNumber();
            m_pNumberStage = new CNumber();
            m_pNumberScore = new CNumber();
            m_pNumberLastScore = new CNumber();
            

            m_pNumberTimeLimit.Init(this, new CCPoint(1.1f, 1.1f), (int)m_fTimeLimit, new CCPoint(242, 705), 40);
            m_pNumberStage.Init(this, new CCPoint(1.0f, 1.0f), m_nStage, new CCPoint(400, 750), 40);
            m_pNumberScore.Init(this, new CCPoint(1.0f, 1.0f), StageMenuScene.g_nSelectStage, new CCPoint(73, 750), 40);
            m_pNumberLastScore.Init(this, new CCPoint(1.5f, 1.5f), 0, new CCPoint(238, 495), 106);
            m_pNumberLastScore.SetVisible(false);


            m_pPauseItem = CCMenuItemImage.itemFromNormalImage(
                                                "Button_Pause_1",
                                                "Button_Pause_3",
                                                this,
                                                new SEL_MenuHandler(PauseCallback));
            m_pPauseItem.position = new CCPoint(480 - 38, 800 - 100);
            m_pPause = CCMenu.menuWithItems(m_pPauseItem);
            m_pPause.position = new CCPoint(0, 0);
            this.addChild(m_pPause, 100);


            m_pSetItem = CCMenuItemImage.itemFromNormalImage(
                                                "Button_SMenu_1",
                                                "Button_SMenu_3",
                                                this,
                                                new SEL_MenuHandler(BackCallback));
            m_pSetItem.position = new CCPoint(240 - 70, 400);
            m_pSet = CCMenu.menuWithItems(m_pSetItem);
            m_pSet.position = new CCPoint(0, 0);
            this.addChild(m_pSet, 100);

            m_pResumeItem = CCMenuItemImage.itemFromNormalImage(
                                                "Button_Set_1",
                                                "Button_Set_3",
                                                this,
                                                new SEL_MenuHandler(ResumeCallback));
            m_pResumeItem.position = new CCPoint(330, 400);
            m_pResume = CCMenu.menuWithItems(m_pResumeItem);
            m_pResume.position = new CCPoint(0, 0);
            this.addChild(m_pResume, 100);

            m_pPauseBlind = CCSprite.spriteWithFile("Pause");
            m_pPauseBlind.position = new CCPoint(240, 400);
            m_pPauseBlind.visible = false;
            this.addChild(m_pPauseBlind, 103);



            m_pGameOver = CCSprite.spriteWithFile("GameOver");
            m_pGameOver.position = new CCPoint(240, 400);
            m_pGameOver.visible = false;
            m_pGameOver.scaleX = 0.1f;
            m_pGameOver.scaleY = 0.1f;
            this.addChild(m_pGameOver, 105);

            m_pGameClear = CCSprite.spriteWithFile("GameClear");
            m_pGameClear.position = new CCPoint(240, 400);
            m_pGameClear.visible = false;
            m_pGameClear.scaleX = 0.1f;
            m_pGameClear.scaleY = 0.1f;
            this.addChild(m_pGameClear, 105);

            m_pBlind = CCSprite.spriteWithFile("Blind");
            m_pBlind.position = new CCPoint(240, 400);
            m_pBlind.Opacity = (byte)(255 * 0.7f);
            m_pBlind.visible = false;
            this.addChild(m_pBlind, 98);


            m_MouseList = new List<CBlock>();
            m_IceChunkList = new List<CIceChunk>();

            m_stMoveBlockPos = new CCPoint(0, 0);

            m_bFreeMove = false;

            this.m_bIsTouchEnabled = true;


            m_eBlockAct = E_BLOCKACT.E_BLOCKACT_NONE;

            m_bMouseDown = false;

            g_bPause = false;
            m_bBlockAct = false;


            m_fBlindTimer = 0.0f;

            m_CSeaLevel = new CSeaLevel();
            m_CSeaLevel.Init(this);

            m_CSeaLevel.m_fSeaLevelMax = m_fSeaLevelMax;

            r = new Random();


            m_fCreateTimer = 0.0f;
            //m_fCreateTime = 5.0f;

            m_Map = new CMap();
            m_Map.Init();

            m_eGameStep = E_GAMESTEP.E_GAMESTEP_PLAY;
            m_eGameResult = E_GAMERESULT.E_GAMERESULT_NONE;


            m_nBlockMax = Define.D_BLOCKMAP_WIDTH * Define.D_BLOCKMAP_HEIGHT;


            m_BlockList = new CBlock[m_nBlockMax];
            for (int i = 0; i < m_BlockList.Length; i++)
            {
                m_BlockList[i] = new CBlock();
                m_BlockList[i].Init(this, i);
            }

            CreateLine();


            m_fUpDownTime = 0.0f;
            m_fUpDownSpeed = 0.017f;
            m_fUpDownPlusTime = 0.0f;
            m_fTimer = 0.0f;

	        CCMenuItemImage pCloseItem = CCMenuItemImage.itemFromNormalImage(
										        "CloseNormal",
										        "CloseSelected",
										        this,
										        new SEL_MenuHandler(menuCloseCallback) );
	        pCloseItem.position = new CCPoint(CCDirector.sharedDirector().getWinSize().width - 20, 20);

	        CCMenu pMenu = CCMenu.menuWithItems(pCloseItem);
	        pMenu.position = new CCPoint(0, 0);
	        this.addChild(pMenu, 1);

            m_pBackGround = new CCSprite[5];

            //m_fErosionSpeed = 1.05f;
            //m_nErosionPlusSpeed = (int)(0.5f / 60.0f);

            for(int i=0; i<5; i++)
	        {

                m_pBackGround[i] = CCSprite.spriteWithFile("Stage_"+i.ToString());
                m_pBackGround[i].position = new CCPoint(240, 400);
                m_pBackGround[i].scaleX = 1.00f;
                m_pBackGround[i].scaleY = 1.00f;

		        if(i >= 2)
		        {
			        this.addChild(m_pBackGround[i], 30);
		        }
		        else
		        {
			        this.addChild(m_pBackGround[i], 0);
		        }


	        }
            m_pBackGround[2].Opacity = (byte)255.0f * (byte)0.0f;









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
            emitter.Duration = 360.0f;//emitter.setDuration(360.0f);
            
            emitter.setSpeed(200);
	        //emitter->setEmissionRate(emitter->getTotalParticles()/emitter->getLife());
            emitter.EmissionRate = 100.0f;
	        //emitter->setEmissionRate(100.0f);
	        //emitter->setAngle(0.0f);
	        //emitter->setAngleVar(360.0f);
            addChild(emitter);


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

            m_pPauseBlind.visible = g_bPause;
            m_pSet.visible = g_bPause;
            m_pResume.visible = g_bPause;

            if (m_fTouchTimer < 1.0f)
            {
                m_fTouchTimer += dt;
                if (m_fTouchTimer >= 1.0f)
                {
                    m_fTouchTimer = 1.0f;
                    CCApplication.m_bIsProcTocuh = true;
                }
            }
            //m_CBlock.Update(dt, Define.D_EROSIONTIME);

            if (g_bPause == false)
            {
                if (m_eGameStep == E_GAMESTEP.E_GAMESTEP_PLAY)
                {
                    m_pNumberTimeLimit.Update(dt);
                    m_pNumberStage.Update(dt);
                    m_pNumberScore.Update(dt);
                    m_pNumberLastScore.Update(dt);

                    m_pNumberTimeLimit.SetNumber((int)m_fTimeLimit);
                    m_pNumberScore.EffectNumber((int)StageMenuScene.g_nScore);
                    m_pNumberScore.Update(dt);

                    //(int)StageMenuScene.g_nScore++;
                    //m_pNumberTimeLimit.SetNumber((int)m_fTimeLimit);

                    m_pBackGround[1].position = new CCPoint(m_pBackGround[1].position.x, m_pBackGround[1].position.y + m_fUpDownTime * dt * 60.0f);
                    //m_pTitle->MoveY();
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

                    m_CSeaLevel.Update(dt);

                    m_fCreateTimer += dt;
                    if (m_fCreateTimer >= m_fCreateTime)
                    {
                        m_fCreateTimer = 0.0f;
                        CreateLine();
                    }

                    m_fTimeLimit -= dt;

                    for (int i = 0; i < m_nBlockMax; i++)
                    {
                        m_BlockList[i].Update(dt, m_fErosionSpeed);
                    }
                    m_fErosionSpeed += (m_nErosionPlusSpeed * dt);

                    int nBlock;

                    for (nBlock = 0; nBlock < m_nBlockMax; nBlock++)
                    {
                        if (m_BlockList[nBlock].m_bLive == false)
                            continue;
                        //if(g_nSelectStage == 1 && m_nTtLevel < 3)
                        //{
                        //	m_BlockList[nBlock].m_fErosionTime = m_BlockList[nBlock].m_fErosionMaxTime;
                        //}
                        if (m_BlockList[nBlock].IsErosoined() == true)
                        {
                            //if(m_nStage == 1 && m_nTtLevel == 0)
                            //{
                            //	m_bSetText = false;
                            //	m_nTtLevel++;
                            //	//D_SOUND->Play(m_SoundEffectTtFp,1.5f);
                            //}

                            m_Map.m_nBlockMap[m_BlockList[nBlock].m_stIndex.m_nY, m_BlockList[nBlock].m_stIndex.m_nX] = 0;
                            m_BlockList[nBlock].Die();
                            m_CSeaLevel.m_fSeaLevel_Target += Define.D_SEA_LEVEL_POINT;

                            //if(m_bNeedDelete == true)
                            //{
                            //    if(m_stNeedIndex.m_nX == m_BlockList[nBlock].m_stIndex.m_nX &&
                            //            m_stNeedIndex.m_nY == m_BlockList[nBlock].m_stIndex.m_nY)
                            //    {
                            //        m_bNeedDelete = false;
                            //        this->removeChild(m_pGhost,true);
                            //    }
                            //}

                            if (m_MouseList.Count >= 1)
                            {
                                int nM;
                                for (nM = 0; nM < m_MouseList.Count; nM++)
                                {
                                    if (m_BlockList[nBlock].m_stIndex.m_nX == m_MouseList[nM].m_stIndex.m_nX && m_BlockList[nBlock].m_stIndex.m_nY == m_MouseList[nM].m_stIndex.m_nY)
                                    {
                                        m_MouseList.Remove(m_MouseList[nM]);

                                        break;
                                    }
                                }
                            }

                            //delete (*it);
                            //it = m_BlockList.erase(it);
                            StageMenuScene.g_nScore += Define.D_SCORE_EROSIONBLOCK;
                            if (MenuScene.g_bEffect_Sound == true)
                                m_Sae.playEffect("Erosion", false);


                        }
                    }

                    for (nBlock = 0; nBlock < m_nBlockMax; nBlock++)
                    {
                        if (m_BlockList[nBlock].m_bLive == false)
                            continue;
                        if (m_BlockList[nBlock].m_eBlockState == E_BLOCKSTATE.E_BLOCKSTATE_FALLING)
                            continue;
                        if (m_BlockList[nBlock].m_bDraged == true)
                            continue;
                        if (m_BlockList[nBlock].m_stIndex.m_nY != Define.D_BLOCKMAP_HEIGHT - 1)
                        {
                            if (m_Map.m_nBlockMap[m_BlockList[nBlock].m_stIndex.m_nY + 1, m_BlockList[nBlock].m_stIndex.m_nX] == 0)
                            {
                                m_Map.m_nBlockMap[m_BlockList[nBlock].m_stIndex.m_nY, m_BlockList[nBlock].m_stIndex.m_nX] = 0;
                                m_Map.m_nBlockMap[m_BlockList[nBlock].m_stIndex.m_nY + 1, m_BlockList[nBlock].m_stIndex.m_nX] = 1;


                                m_BlockList[nBlock].m_eBlockState = E_BLOCKSTATE.E_BLOCKSTATE_FALLING;
                                m_BlockList[nBlock].m_fStartY = m_BlockList[nBlock].m_stPos.y;
                                m_BlockList[nBlock].m_fDistance = m_BlockList[nBlock].m_fNextDistance;
                                m_BlockList[nBlock].m_fNextDistance = 64.0f;
                                m_BlockList[nBlock].m_stIndex.m_nY += 1;
                            }
                        }
                    }


                    int nIceCount = 0;
                    for (nIceCount = 0; nIceCount < m_IceChunkList.Count; nIceCount++)
                    {
                        m_IceChunkList[nIceCount].Update(dt);
                        if (m_IceChunkList[nIceCount].ReadyToBomb() == true)
                        {
                            if (m_IceChunkList[nIceCount].m_eBombOption == E_BOMB_OPTION.E_BOMB_OPTION_ONE)
                            {
                                for (int i = 0; i < 2; i++)
                                {
                                    CIceChunk pTempIce = new CIceChunk();
                                    pTempIce.Init(this, new CCPoint(m_IceChunkList[nIceCount].m_stPos.x, m_IceChunkList[nIceCount].m_stPos.y), E_BOMB_OPTION.E_BOMB_OPTION_ONE, m_IceChunkList[nIceCount].m_nTickNumber - 1, r);
                                    m_IceChunkList.Add(pTempIce);
                                }
                            }
                            else if (m_IceChunkList[nIceCount].m_eBombOption == E_BOMB_OPTION.E_BOMB_OPTION_TWO)
                            {
                                for (int i = 0; i < 3; i++)
                                {
                                    CIceChunk pTempIce = new CIceChunk();
                                    pTempIce.Init(this, new CCPoint(m_IceChunkList[nIceCount].m_stPos.x, m_IceChunkList[nIceCount].m_stPos.y), E_BOMB_OPTION.E_BOMB_OPTION_ONE, m_IceChunkList[nIceCount].m_nTickNumber - 1, r);
                                    pTempIce.m_stMoveSpeed.x *= 1.6f;
                                    pTempIce.m_stMoveSpeed.y *= 2.2f;
                                    m_IceChunkList.Add(pTempIce);
                                }
                            }
                            this.removeChild(m_IceChunkList[nIceCount].m_pPlane, true);
                            m_IceChunkList.RemoveAt(nIceCount);
                        }

                        if (m_IceChunkList[nIceCount].Finished() == true)
                        {

                            m_CSeaLevel.m_fSeaLevel_Target -= Define.D_SEA_LEVEL_RESTORATION;
                            m_CSeaLevel.Check();
                            removeChild(m_IceChunkList[nIceCount].m_pPlane, true);

                            m_IceChunkList.RemoveAt(nIceCount);
                        }
                    }
                    //list<CIceChunk*>::iterator it;
                    //for(it = m_IceChunkList.begin(); it != m_IceChunkList.end();)
                    //{
                    //    (*it)->Update(dt);

                    //    if((*it)->ReadyToBomb() == true)
                    //    {
                    //        if((*it)->m_eBombOption == E_BOMB_OPTION_ONE)
                    //        {
                    //            for(int i=0; i<2; i++)
                    //            {
                    //                CIceChunk* pTempIce = new CIceChunk();
                    //                pTempIce->Init(this,ccp((*it)->m_stPos.x,(*it)->m_stPos.y),E_BOMB_OPTION_ONE,(*it)->m_nTickNumber - 1);
                    //                m_IceChunkList.push_back(pTempIce);
                    //            }
                    //        }
                    //        else if((*it)->m_eBombOption == E_BOMB_OPTION_TWO)
                    //        {
                    //            for(int i=0; i<3; i++)
                    //            {
                    //                CIceChunk* pTempIce = new CIceChunk();
                    //                pTempIce->Init(this,ccp((*it)->m_stPos.x,(*it)->m_stPos.y),E_BOMB_OPTION_TWO,(*it)->m_nTickNumber - 1);
                    //                pTempIce->m_stMoveSpeed.x *= 1.6f;
                    //                pTempIce->m_stMoveSpeed.y *= 2.2f;
                    //                m_IceChunkList.push_back(pTempIce);
                    //           
                    //             }
                    //        }
                    //        this->removeChild((*it)->m_pPlane,true);
                    //        delete (*it)->m_pBlock;
                    //        delete (*it)->m_pBlockAni;
                    //        delete (*it);
                    //        it = m_IceChunkList.erase(it);
                    //    }
                    //    if((*it)->Finished() == true)
                    //    {

                    //        m_CSeaLevel.m_fSeaLevel_Target -= D_SEA_LEVEL_RESTORATION;
                    //        m_CSeaLevel.Check();
                    //        this->removeChild((*it)->m_pPlane,true);
                    //        delete (*it)->m_pBlock;
                    //        delete (*it)->m_pBlockAni;
                    //        delete (*it);
                    //        it = m_IceChunkList.erase(it);
                    //    }
                    //    else
                    //    {
                    //        it++;
                    //    }
                    //}

                    if (m_fTimeLimit <= 0)
                    {
                        // if (m_nStage == 1)
                        // {
                        //if (m_nTtLevel >= 5)
                        //{
                        //m_eGameResult = E_GAMERESULT.E_GAMERESULT_VICTORY;

                        ////if (g_bEFFECT_Sound == true)
                        ////   m_Sae->playEffect("WIN.mp3");

                        //m_fPopUpTimer = 0.1f;
                        //m_eGameStep = E_GAMESTEP.E_GAMESTEP_END;
                        //m_pBlind.visible = true; // setVisible(true);
                        //m_pGameClear.visible = true;
                        ////m_pGameClear->setVisible(true);
                        //for (int i = 0; i < m_nBlockMax; i++)
                        //{
                        //    m_BlockList[i].ShowUpdate();
                        //}
                        // }
                        // }
                        // else
                        //  {
                        m_eGameResult = E_GAMERESULT.E_GAMERESULT_VICTORY;

                        if (MenuScene.g_bEffect_Sound == true)
                            m_Sae.playEffect("WIN", false);

                        m_fPopUpTimer = 0.1f;
                        m_eGameStep = E_GAMESTEP.E_GAMESTEP_END;
                        m_pBlind.visible = true; // setVisible(true);
                        m_pGameClear.visible = true;
                        m_pNumberLastScore.SetVisible(true);
                        for (int i = 0; i < m_nBlockMax; i++)
                        {
                            m_BlockList[i].ShowUpdate();
                        }
                        //}
                        /*if(g_SoundOnOff == true)
                        {
                            D_SOUND->Play(m_SoundWinFp,1.5f);
                        }*/
                    }
                    else
                    {

                        if (m_CSeaLevel.m_fSeaLevel >= m_CSeaLevel.m_fSeaLevelMax)
                        {
                            m_eGameResult = E_GAMERESULT.E_GAMERESULT_DEFEAT;

                            if (MenuScene.g_bEffect_Sound == true)
                                m_Sae.playEffect("LOSE", false);

                            m_fPopUpTimer = 0.05f;
                            m_eGameStep = E_GAMESTEP.E_GAMESTEP_END;
                            m_pBlind.visible = true; // setVisible(true);
                            m_pGameOver.visible = true;
                            m_pNumberLastScore.SetVisible(true);
                            for (int i = 0; i < m_nBlockMax; i++)
                            {
                                m_BlockList[i].ShowUpdate();
                            }
                        }

                        //int nLiveBlockNum = 0;
                        //for(int i=0; i<m_nBlockMax; i++)
                        //{
                        //	if(m_BlockList[i].m_bLive == true)
                        //		nLiveBlockNum++;
                        //}

                        //if(nLiveBlockNum == 0)
                        //{
                        //	m_eGameResult = E_GAMERESULT_DEFEAT;
                        //	m_eGameStep = E_GAMESTEP_END;
                        //	m_pGameOver->setVisible(true);
                        //	for(int i=0; i<m_nBlockMax; i++)
                        //	{
                        //		m_BlockList[i].ShowUpdate();
                        //	}
                        //	/*if(g_SoundOnOff == true)
                        //	{
                        //		D_SOUND->Play(m_SoundLoseFp,1.5f);
                        //	}*/
                        //}
                        //else
                        //{
                        //	if(m_eBlockAct == E_BLOCKACT_MOVE)
                        //	{
                        //		if(m_CSeaLevel.m_fSeaLevel >= m_CSeaLevel.m_fSeaLevelMax)
                        //		{
                        //			m_eGameResult = E_GAMERESULT_DEFEAT;
                        //			m_eGameStep = E_GAMESTEP_END;	
                        //			m_pGameOver->setVisible(true);
                        //			for(int i=0; i<m_nBlockMax; i++)
                        //			{
                        //				m_BlockList[i].ShowUpdate();
                        //			}
                        //		}
                        //		//if(nLiveBlockNum - m_MouseList.size() <= 0)
                        //		//{
                        //			
                        //		//}
                        //	}
                        //}
                    }
                }
                if (m_eGameStep == E_GAMESTEP.E_GAMESTEP_END)
                {
                    m_pSet.visible = false;
                    m_pResume.visible = false;
                    m_pPause.visible = false;

                    m_pNumberLastScore.SetNumber((int)StageMenuScene.g_nScore);
                    m_pNumberLastScore.SetSize(new CCPoint((m_fPopUpTimer / Define.D_GAME_END_BLIND_TIME) * 1.5f, (m_fPopUpTimer / Define.D_GAME_END_BLIND_TIME) * 1.5f));
                    if (m_fPopUpTimer < Define.D_GAME_END_BLIND_TIME)
                    {
                        //!< m_fBlindTimer += dt;
                        //m_fPopUpTimer += dt;
                        m_fPopUpTimer *= 1.23f;
                        if (m_fPopUpTimer >= Define.D_GAME_END_BLIND_TIME)
                        {
                            m_fPopUpTimer = Define.D_GAME_END_BLIND_TIME;
                        }
                    }
                    else if (m_fPopUpTimer >= Define.D_GAME_END_BLIND_TIME && m_fBlindTimer < Define.D_GAME_END_STAR_TIME)
                    {
                        m_fBlindTimer += dt;
                        if (m_fBlindTimer >= Define.D_GAME_END_STAR_TIME)
                        {
                            m_fBlindTimer = Define.D_GAME_END_STAR_TIME;
                        }
                    }

                    if (m_eGameResult == E_GAMERESULT.E_GAMERESULT_DEFEAT)
                    {
                        m_pNumberLastScore.SetVisible(true);
                        m_pNumberLastScore.m_stPos = new CCPoint(400, 290);
                        m_pGameOver.scaleX = (m_fPopUpTimer / Define.D_GAME_END_BLIND_TIME);
                        m_pGameOver.scaleY = (m_fPopUpTimer / Define.D_GAME_END_BLIND_TIME);

                        //m_pGameOver->setScaleX((m_fPopUpTimer / D_GAME_END_BLIND_TIME) * D_SCALE_WIDTH);
                        // m_pGameOver->setScaleY((m_fPopUpTimer / D_GAME_END_BLIND_TIME) * D_SCALE_HEIGHT);

                    }
                    else if (m_eGameResult == E_GAMERESULT.E_GAMERESULT_VICTORY)
                    {
                        m_pNumberLastScore.SetVisible(true);
                        m_pNumberLastScore.m_stPos = new CCPoint(238, 495);
                        if (m_bSaved == false)
                        {
                            m_bSaved = true;

                            //!< 스테이지 저장
                            //if (StageMenuScene.g_nScore >= g_nJudgment[m_nStage - 1][2])
                            //{
                            //    if (g_nScoreLevel[m_nStage - 1] < 4)
                            //        g_nScoreLevel[m_nStage - 1] = 3;
                            //}
                            //else if (StageMenuScene.g_nScore >= g_nJudgment[m_nStage - 1][1])
                            //{
                            //    if (g_nScoreLevel[m_nStage - 1] < 3)
                            //        g_nScoreLevel[m_nStage - 1] = 2;
                            //}
                            //else if (StageMenuScene.g_nScore >= g_nJudgment[m_nStage - 1][0])
                            //{
                            //    if (g_nScoreLevel[m_nStage - 1] < 2)
                            //        g_nScoreLevel[m_nStage - 1] = 1;
                            //}
                            //g_bStageLock[m_nStage] = true;
                            //SaveStage();
                        }
                        //if (StageMenuScene.g_nScore >= g_nJudgment[m_nStage - 1][2])
                        //{
                        //    for (int i = 0; i < 3; i++)
                        //    {
                        //        m_pStar[i]->setVisible(true);
                        //        m_pStar[i]->setOpacity((255 * m_fBlindTimer) / D_GAME_END_STAR_TIME);
                        //        m_pStar[i]->setScaleX((0.5f + ((m_fBlindTimer / D_GAME_END_STAR_TIME) * 0.5f)) * D_SCALE_WIDTH);
                        //        m_pStar[i]->setScaleY((0.5f + ((m_fBlindTimer / D_GAME_END_STAR_TIME) * 0.5f)) * D_SCALE_HEIGHT);
                        //        m_pStar[i]->setRotation((m_fBlindTimer / D_GAME_END_STAR_TIME) * 360.0f);
                        //    }
                        //}
                        //else if (StageMenuScene.g_nScore >= g_nJudgment[m_nStage - 1][1])
                        //{
                        //    for (int i = 0; i < 2; i++)
                        //    {
                        //        m_pStar[i]->setVisible(true);
                        //        m_pStar[i]->setOpacity((255 * m_fBlindTimer) / D_GAME_END_STAR_TIME);
                        //        m_pStar[i]->setScaleX((0.5f + ((m_fBlindTimer / D_GAME_END_STAR_TIME) * 0.5f)) * D_SCALE_WIDTH);
                        //        m_pStar[i]->setScaleY((0.5f + ((m_fBlindTimer / D_GAME_END_STAR_TIME) * 0.5f)) * D_SCALE_HEIGHT);
                        //        m_pStar[i]->setRotation((m_fBlindTimer / D_GAME_END_STAR_TIME) * 360.0f);
                        //    }
                        //}
                        //else if (StageMenuScene.g_nScore >= g_nJudgment[m_nStage - 1][0])
                        //{
                        //    for (int i = 0; i < 1; i++)
                        //    {
                        //        m_pStar[i]->setVisible(true);
                        //        m_pStar[i]->setOpacity(m_fBlindTimer / D_GAME_END_STAR_TIME);
                        //        m_pStar[i]->setScaleX((0.5f + ((m_fBlindTimer / D_GAME_END_STAR_TIME) * 0.5f)) * D_SCALE_WIDTH);
                        //        m_pStar[i]->setScaleY((0.5f + ((m_fBlindTimer / D_GAME_END_STAR_TIME) * 0.5f)) * D_SCALE_HEIGHT);
                        //        m_pStar[i]->setRotation((m_fBlindTimer / D_GAME_END_STAR_TIME) * 360.0f);
                        //    }
                        //}
                        m_pGameClear.scaleX = (m_fPopUpTimer / Define.D_GAME_END_BLIND_TIME);
                        m_pGameClear.scaleY = (m_fPopUpTimer / Define.D_GAME_END_BLIND_TIME);
                        //m_pGameClear->setScaleX((m_fPopUpTimer / D_GAME_END_BLIND_TIME) * D_SCALE_WIDTH);
                        //m_pGameClear->setScaleY((m_fPopUpTimer / D_GAME_END_BLIND_TIME) * D_SCALE_HEIGHT);
                    }
                }
            }


        }
        public static CCScene scene()
        {
            // 'scene' is an autorelease object
            CCScene scene = CCScene.node();

            // 'layer' is an autorelease object
            CCLayer layer = StageScene.node();

            // add layer as a child to scene
            scene.addChild(layer);

            // return the scene
            return scene;
        }

        public static new CCLayer node()
        {
            StageScene ret = new StageScene();
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

        public override void registerWithTouchDispatcher()
        {
            //CCDirector.sharedDirector().Touch.addTargetedDelegate(this, 0, true);
            //CCTouchDispatcher.sharedDispatcher().addStandardDelegate(this, 0);
            CCTouchDispatcher.sharedDispatcher().addTargetedDelegate(this, 0, true);
        }

        //public override void ccTouchesBegan(List<CCTouch> touches, CCEvent event_)
        //{
        //    //CCSize s = CCDirector.sharedDirector().getWinSize();
        //    //CCActionInterval actionTo = CCMoveTo.actionWithDuration(3, new CCPoint(-s.width, -s.height));
        //    //pSprite.runAction(actionTo);
        //}
        public override bool ccTouchBegan(CCTouch touch, CCEvent event_)
        {
            // Debug.Assert(false, "Layer#ccTouchBegan override me");
            if(g_bPause == false)
            {
                if(m_eGameStep == E_GAMESTEP.E_GAMESTEP_PLAY)
                {
                    if(m_bMouseDown == false)
                    {
                        // 손가락이 화면에 닿을 때 실행 되는 부분
                        CCPoint stPos = CCDirector.sharedDirector().convertToGL(touch.locationInView(0));
                        m_bMouseDown = true;

                        //m_lfLastTouchX = stPos.x;
                        //m_lfLastTouchY = stPos.y;

                        //m_lfNewTouchX = stPos.x;
                        //m_lfNewTouchY = stPos.y;

                        //stEMVec2 stTemp = CEMMath::ScreenToWorld((int)stPos.m_nX,(int)stPos.m_nY);
                        //if(D_WORLD->GetWinInfo().m_stRt.bottom > D_WORLD->GetWinInfo().m_stRt.right)
                        //{
                        //	stTemp.m_fX = (stTemp.m_fX/180) * 100;
                        //	stTemp.m_fY = (stTemp.m_fY/180) * 100;
                        //}
                        //stTemp.m_fX = (stTemp.m_fX/205) * 100;
                        //stTemp.m_fY = (stTemp.m_fY/205) * 100;
                        //m_pText->SetOutPutString("마우스 좌표 (" + IntToEMString((int)stTemp.m_fX) + "," + IntToEMString((int)stTemp.m_fY) + ")");

                        //CEMPlane* pTemp = AABBvsRay(stPos.m_nX,stPos.m_nY,-2);
                        int nTemp = 0;
                        for(nTemp = 0; nTemp < m_nBlockMax; nTemp++)
                        {
                            if(m_BlockList[nTemp].HitTest(stPos.x, stPos.y) == true)
                            {
                                int nBlock = nTemp;

                                if( m_BlockList[nBlock].m_eBlockState != E_BLOCKSTATE.E_BLOCKSTATE_FALLING )
                                {
                                    if( m_BlockList[nBlock].m_bFreezed == false )
                                    {
                                        //m_MouseList.push_back(&m_BlockList[nBlock]);
                                        m_MouseList.Add(m_BlockList[nBlock]);

                                        m_BlockList[nBlock].m_pSelect.visible = true; //setVisible(true);
                                        m_bBlockAct = true;

                                        if (MenuScene.g_bEffect_Sound == true)
                                            m_Sae.playEffect("Button", false);

                                    }
                                }
                                break;
                            }
                        }
                        if(nTemp == m_nBlockMax)
                        {
                            m_bBlockAct = false;
                        }

                        return true;
                    }
                }
                else if(m_eGameStep == E_GAMESTEP.E_GAMESTEP_END && m_fBlindTimer >= Define.D_GAME_END_STAR_TIME)
                {
                    CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageMenuScene.scene());
                    CCDirector.sharedDirector().replaceScene(pScene);
                    CCApplication.m_bIsProcTocuh = false;
                }
            }
            return true;
        }

        public override void ccTouchMoved(CCTouch touch, CCEvent event_)
        {
            if(g_bPause == false)
	        {
		        if(m_eGameStep == E_GAMESTEP.E_GAMESTEP_PLAY)
		        {
						        // 손가락이 드래그 될 때 실행 되는 부분
						        CCPoint stPos = CCDirector.sharedDirector().convertToGL(touch.locationInView(0));

			
                                //m_lfNewTouchX = stPos.x;
                                //m_lfNewTouchY = stPos.y;

						        //m_lfLastTouchX = stPos.x;
						        //m_lfLastTouchY = stPos.y;

						        //!< 이미 들어있는 놈은 검사하여 break;
						        //

						        if(m_bMouseDown == false)
							        return;

						        int nLastBlock = 0; //!< 가장 마지막 블록

						        List<CBlock>.Enumerator itMouseList;//!< MouseList의 iterator

						        int nBlock = 0;//!< BlockList의 iterator

					        /*	stEMVec2 stTemp = CEMMath::ScreenToWorld((int)stPos.m_nX,(int)stPos.m_nY);
						        if(D_WORLD->GetWinInfo().m_stRt.bottom > D_WORLD->GetWinInfo().m_stRt.right)
						        {
							        stTemp.m_fX = (stTemp.m_fX/180) * 100;
							        stTemp.m_fY = (stTemp.m_fY/180) * 100;
						        }
			        */


						        //CEMPlane* pTemp = AABBvsRay(stPos.m_nX,stPos.m_nY,-2);
			

						        int i = 0;
						        List<CBlock>.Enumerator itLastBlock;//!< MouseList의 iterator
						        if(m_bMouseDown == true  && m_MouseList.Count >= 1 && m_bBlockAct == true)
						        {
							        nLastBlock = m_MouseList.ElementAt(m_MouseList.Count-1).m_nId;
							        //nLastBlock = (*itLastBlock)->m_nId;
						        }


						        bool bFirstBlock = false; //!< 처음 블록과 일치


						        bool bMouseBlock = false; //!< 이미 마우스블록에 들어있던 블록과 일치

						        for(nBlock = 0; nBlock < m_nBlockMax; nBlock++)
						        {
							        if(m_BlockList[nBlock].HitTest(stPos.x, stPos.y) == true)
							        {
								        break;
							        }
						        }

						        if(m_MouseList.Count >= 1)
						        {
							        if(m_eBlockAct == E_BLOCKACT.E_BLOCKACT_NONE)
							        {
								        if( nBlock == nLastBlock) //!< 움직이는데 처음 클릭한 블록이면 빠져나감
								        {
									        bFirstBlock = true;
									        return;
								        }
								        else
								        {

						
									        if(nBlock < m_nBlockMax)
									        {
										        //for(itBlockList = m_BlockList.begin(); itBlockList != m_BlockList.end(); itBlockList++)
										        //{
										        //	if( pTemp == m_BlockList[nBlock].m_pBlock) //!< 처음 클릭한 블록이 아니고 인접한 블록 중 하나이면 Drag판정을 내림
										        //	{
												        if(m_BlockList[nBlock].m_eBlockState != E_BLOCKSTATE.E_BLOCKSTATE_FALLING)
												        {
													        int m_nLR = m_BlockList[nLastBlock].m_stIndex.m_nX - m_BlockList[nBlock].m_stIndex.m_nX;
													        int m_nUD = m_BlockList[nLastBlock].m_stIndex.m_nY - m_BlockList[nBlock].m_stIndex.m_nY;
													        //!< 블록이 인접한 것인지 Check
													        if( 
														        (m_nUD == 0 && m_nLR == 1) ||	//좌
														        (m_nUD == 0 && m_nLR == -1) ||	//우
														        (m_nUD == 1 && m_nLR == 0) ||	//상
														        (m_nUD == -1 && m_nLR == 0)	//하
														        )
													        {
														        if(m_bFreeMove == true)
														        {
															        m_eBlockAct = E_BLOCKACT.E_BLOCKACT_NOT;
														        }
														        if(m_BlockList[nLastBlock].m_eBlockNumber == m_BlockList[nBlock].m_eBlockNumber)//!< 같은 종류인지 Check
														        {
															        if(m_BlockList[nBlock].m_bFreezed == false)//!< 얼어있는 녀석인지
															        {
																        m_BlockList[nBlock].m_pSelect.visible = true;
																
                                                                        m_MouseList.Add( m_BlockList[nBlock] ); //m_MouseList.push_back(&m_BlockList[nBlock]);
																        
																        //m_pTextNowBlock->SetOutPutString(m_BlockList[nBlock]->m_pBlock->GetName());
																        m_eBlockAct = E_BLOCKACT.E_BLOCKACT_DRAG;
                                                                        if (MenuScene.g_bEffect_Sound == true)
                                                                            m_Sae.playEffect("Button", false);
																        //m_SoundButton = D_SOUND->Play(m_SoundButtonFp,1.0f,false);
																        //break;
															        }
														        }
													        }
												        }
											        //}
										        }
										        if(nBlock >= m_nBlockMax && m_eBlockAct != E_BLOCKACT.E_BLOCKACT_NOT) //!< 인접한 블록이 아닐경우 Move판정
										        {
											
                                                    //!< 유령
                                                    /////////////////////////////////////////////////////////////////////////////////////
                                                    //char frameName[256];
                                                    //sprintf(frameName, "Block_%d_1.png",(int)m_BlockList[nLastBlock].m_eBlockNumber+1);
                                                    //m_pGhost = CCSprite::create(frameName);
                                                    //m_pGhost->setPosition( ccp( (m_BlockList[nLastBlock].m_stPos.x - 6.4f) * D_SCALE_WIDTH, (m_BlockList[nLastBlock].m_stPos.y - 6.4f)* D_SCALE_HEIGHT) );
                                                    //m_pGhost->setAnchorPoint(ccp(0.0,0.0));
                                                    //m_pGhost->setScaleX(1.2f * D_SCALE_WIDTH);
                                                    //m_pGhost->setScaleY(1.2f * D_SCALE_HEIGHT);
                                                    //m_pGhost->setOpacity(255 * 0.5f);
                                                    //m_pGhost->setVisible(true);
                                                    //this->addChild(m_pGhost, 26);
											        //m_bNeedDelete = true;
                                                    //m_stNeedIndex = m_BlockList[nLastBlock].m_stIndex;
                                                    /////////////////////////////////////////////////////////////////////////////////////

											        

											        //if(m_BlockList[nBlock].m_eBlockState != E_BLOCKSTATE_FALLING)
											        //{
											        m_BlockList[nLastBlock].m_pSelect.visible = true;
											        //m_MouseList.push_back((*itLastBlock));
											        m_BlockList[nLastBlock].m_bDraged = true;
                                                    m_stMoveBlockPos = new CCPoint(m_BlockList[nLastBlock].m_stPos.x, m_BlockList[nLastBlock].m_stPos.y);
											        m_eBlockAct = E_BLOCKACT.E_BLOCKACT_MOVE;
											

											        //}
										        }
									        }
							        }	
						
							        else if(m_eBlockAct == E_BLOCKACT.E_BLOCKACT_DRAG)
							        {
							        /*	for(nBlock = 0; nBlock < m_nBlockMax; nBlock++)
								        {
									        if(m_BlockList[nBlock].HitTest(stPos.x, stPos.y) == true)
									        {
										        break;
									        }
								        }*/

                                        //for(itMouseList = m_MouseList.begin(); itMouseList != m_MouseList.end(); itMouseList++)
                                        //{
                                        //    if(nBlock == (*itMouseList)->m_nId)
                                        //    {
                                        //        bMouseBlock = true;
                                        //        return;
                                        //    }
                                        //}
                                        int nMouseList;
                                        if (nBlock >= m_nBlockMax)
                                            return;
                                        for (nMouseList = 0; nMouseList < m_MouseList.Count; nMouseList++)
                                        {
                                            if (nBlock == m_MouseList[nMouseList].m_nId)
                                            {
                                                bMouseBlock = true;
                                                return;
                                            }
                                        }

								        if(bMouseBlock == false) //!< 이미 들어있는 블록이 아닐경우
								        {
									        //for(itBlockList = m_BlockList.begin(); itBlockList != m_BlockList.end(); itBlockList++)
									        //{
										        //if( pTemp == m_BlockList[nBlock].m_pBlock) //!< 처음 클릭한 블록이 아니고 인접한 블록 중 하나이면 Drag판정을 내림
										        //{
											        int m_nLR = m_BlockList[nLastBlock].m_stIndex.m_nX - m_BlockList[nBlock].m_stIndex.m_nX;
											        int m_nUD = m_BlockList[nLastBlock].m_stIndex.m_nY - m_BlockList[nBlock].m_stIndex.m_nY;
											        //!< 블록이 인접한 것인지 Check
											        if(
												        (m_nUD == 0 && m_nLR == 1) ||	//좌
												        (m_nUD == 0 && m_nLR == -1) ||	//우
												        (m_nUD == 1 && m_nLR == 0) ||	//상
												        (m_nUD == -1 && m_nLR == 0)	//하
												        )
											        {
												        if(m_BlockList[nLastBlock].m_eBlockNumber == m_BlockList[nBlock].m_eBlockNumber)//!< 같은 종류인지 Check
												        {
													        if(m_BlockList[nBlock].m_bFreezed == false)//!< 얼어있는 녀석인지
													        {
														        m_BlockList[nBlock].m_pSelect.visible = true;
														        m_MouseList.Add(m_BlockList[nBlock]);//m_MouseList.push_back(&m_BlockList[nBlock]);
                                                                if (MenuScene.g_bEffect_Sound == true)
                                                                    m_Sae.playEffect("Button", false);
														        //m_pTextNowBlock->SetOutPutString(m_BlockList[nBlock].m_pBlock->GetName());
														        //m_SoundButton = D_SOUND->Play(m_SoundButtonFp,1.0f,false);
													        }
												        }
											        }
										        //}
									        //}
								        }
							        }
							        else if(m_eBlockAct == E_BLOCKACT.E_BLOCKACT_MOVE)
							        {
								        //stEMVec2 stLastBlockPos;

								        //int nIndex_X = ((stPos.x - D_LINE_START_X)/D_BLOCK_WIDTH);
								        //int nIndex_Y = ((D_LINE_START_Y - stPos.y)/D_BLOCK_HEIGHT);

								        //stLastBlockPos = m_BlockList[nLastBlock].m_stPos;
                                        CBlock itr = m_MouseList.First();

                                        itr.m_stPos.x = (stPos.x ) - (Define.D_BLOCK_WIDTH / 2);
                                        itr.m_stPos.y = (stPos.y ) - (Define.D_BLOCK_HEIGHT / 2);

								        //list<CEMBlock*>::iterator itBlockList;
								        //for(itBlockList = m_BlockList.begin(); itBlockList != m_BlockList.end(); itBlockList++)
								        //{
								        //	if((*itLastBlock) == (*itBlockList))
								        //		continue;

									        /*if( 
									        CEMMath::Abs<float>(m_BlockList[nLastBlock].m_stPos.m_fX - m_BlockList[nBlock].m_stPos.m_fX) <= D_BLOCK_WIDTH &&
									        CEMMath::Abs<float>(m_BlockList[nLastBlock].m_stPos.m_fY - m_BlockList[nBlock].m_stPos.m_fY) <= D_BLOCK_HEIGHT )
									        {
										        if(stTemp.m_fY < m_BlockList[nBlock].m_stPos.m_fY)
										        {
											        m_BlockList[nLastBlock].m_stPos.m_fY = stLastBlockPos.m_fY;
										        }
										        break;
									        }*/

								        //}



								        //if( m_Map->m_nBlockMap[nIndex_Y][nIndex_X] == 0)
								        //{
								        //	m_Map->m_nBlockMap[m_BlockList[nLastBlock].m_stIndex.m_fY][m_BlockList[nLastBlock].m_stIndex.m_fX] = 0;
								        //	m_Map->m_nBlockMap[nIndex_Y][nIndex_X] = 1;
								        //	m_BlockList[nLastBlock].m_stIndex.m_fX = nIndex_X;
								        //	m_BlockList[nLastBlock].m_stIndex.m_fY = nIndex_Y;




								        // (*itLastBlock)->m_stPos.m_fX = D_LINE_START_X + (nIndex_X * D_BLOCK_WIDTH);
								        // (*itLastBlock)->m_stPos.m_fY = D_LINE_START_Y - (nIndex_Y * D_BLOCK_HEIGHT);
								        //}
							        }
						        }

			        }
	        }
        }
        
        
        public override void  ccTouchEnded(CCTouch touch, CCEvent event_)
        {
	
		        if(g_bPause == false)
		        {
			        if(m_eGameStep == E_GAMESTEP.E_GAMESTEP_PLAY)
				        {

				        if(m_bMouseDown == true)
				        {
                            //for(int i=0; i<D_SLIDE_NUM_MAX; i++)
                            //{
                            //    m_lfSlideNumX[i] = 0;
                            //    m_lfSlideNumY[i] = 0;
                            //}
                            //m_lfLastTouchX = 0;
                            //m_lfNewTouchX = 0;
                            //m_lfLastTouchY = 0;
                            //m_lfNewTouchY = 0;

					        // 손가락이 화면 밖에 나가거나 , 떨때 실행되는 부분
                            CCPoint stPos = CCDirector.sharedDirector().convertToGL(touch.locationInView(0));

						    /*int nBlock = 0;

						    for(nBlock = 0; nBlock < m_nBlockMax; nBlock++)
						    {
							    m_BlockList[nBlock].m_pSelect->setVisible(false);
						    }*/


								        m_bMouseDown = false;
								        m_bBlockAct = false;
								        //m_nTurnStep = 0;
								        //m_bTurnAble = true;
								        //m_bBlockAct = false;
								        //m_eBlockDragDerection = E_BLOCKDRAG_DEFECTION_LEFT;
								        //m_nTurnSkipBlock = 0;

							        /*	stEMVec2 stTemp = CEMMath::ScreenToWorld((int)stPos.m_nX,(int)stPos.m_nY);
								        if(D_WORLD->GetWinInfo().m_stRt.bottom > D_WORLD->GetWinInfo().m_stRt.right)
								        {
									        stTemp.m_fX = (stTemp.m_fX/180) * 100;
									        stTemp.m_fY = (stTemp.m_fY/180) * 100;
								        }*/
								        int itMouseList;
								        int nCount = 0;
								        if(m_eBlockAct == E_BLOCKACT.E_BLOCKACT_DRAG)
								        {
									        if(m_MouseList.Count >= 5)
									        {
										        CCPoint stTargetPos;
                                                for (itMouseList = 0; itMouseList < m_MouseList.Count; itMouseList++)
										        {
											        nCount++;
											        /*if((*itMouseList)->m_eBlockItem == E_BLOCKITEM_SLED)
											        {
												        (*itMouseList)->m_eBlockItem = E_BLOCKITEM_NONE;
												        (*itMouseList)->m_pItem_Sled->SetShow(false);
												        bSled = true;
											        }*/

                                                    m_MouseList[itMouseList].m_bFreezed = true;
                                                    m_MouseList[itMouseList].m_fErosionMaxTime += Define.D_FREEZETIME;
                                                    m_MouseList[itMouseList].m_fErosionTime += Define.D_FREEZETIME;

                                                    m_MouseList[itMouseList].m_pSelect.visible = false; // setVisible(false);
                                                    m_MouseList[itMouseList].m_bDraged = false;
                                                    StageMenuScene.g_nScore += (Define.D_SCORE_ICEBLOCK * m_MouseList.Count);


                                                    


											        //for(int i=0; i<D_SOUND_ICE_CHANNEL; i++)
											        //{
											        //	//if(D_SOUND->IsPlaying(m_SoundIce[i]) == false)
											        //	//{
											        //	m_SoundIce[i] = D_SOUND->Play(m_SoundIceFp,1.0f,false);
											        //	break;
											        //	//}
											        //}
								
									

											 

											        // !< 이펙트매니저
                                                    //m_EffectManager.Insert(1,((*itMouseList)->m_stPos.x -( D_BLOCK_WIDTH/2)) * D_SCALE_WIDTH,((*itMouseList)->m_stPos.y-( D_BLOCK_HEIGHT/2)) * D_SCALE_HEIGHT);
											
											
											        //if(nCount >= m_MouseList.size())
												        //m_EffectMng->Insert(4,(*itMouseList)->m_stPos.m_fX + 70, (*itMouseList)->m_stPos.m_fY + 0);

											        //m_EffectMng->Insert(1,(*itMouseList)->m_stPos.m_fX,(*itMouseList)->m_stPos.m_fY);
											        //m_fComboTimer = D_COMBOTIME;


                                                    stTargetPos = m_MouseList[itMouseList].m_stPos;

                                                    if (m_MouseList[itMouseList].m_eBlockItem != E_BLOCKITEM.E_BLOCKITEM_NONE)
											        {

                                                        //!< 아이템 사용 부분
                                                        //if (m_MouseList[itMouseList].m_eBlockItem == E_BLOCKITEM.E_BLOCKITEM_SLED)
                                                        //{
                                                        //    CSled * pSled = new CSled();
                                                        //    pSled->Init(this);
                                                        //    m_SledList.push_back(pSled);
                                                        //}
                                                        //else if (m_MouseList[itMouseList].m_eBlockItem == E_BLOCKITEM.E_BLOCKITEM_ICE)
                                                        //{
                                                        //    CIce * pIce = new CIce();
                                                        //    pIce->Init(this, ccp((*itMouseList)->m_stPos.x +( D_BLOCK_WIDTH/2),(*itMouseList)->m_stPos.y+( D_BLOCK_HEIGHT/2)));
                                                        //    m_IceList.push_back(pIce);
                                                        //}
                                                        //m_MouseList[itMouseList].UseItem();
											        }
										        }

                                                //!< 얼음조각
                                                //CIceChunk* pTempIce = new CIceChunk();
                                                //pTempIce->Init(this,ccp(stTargetPos.x +( D_BLOCK_WIDTH/2),stTargetPos.y+( D_BLOCK_HEIGHT/2)),E_BOMB_OPTION_TWO,3);
                                                //pTempIce->m_stMoveSpeed.x *= 1.7f;
                                                //pTempIce->m_stMoveSpeed.y *= 2.7f;
                                                //m_IceChunkList.push_back(pTempIce);


                                                CIceChunk pTempIce = new CIceChunk();

                                                pTempIce.Init(this, new CCPoint(m_MouseList[itMouseList - 1].m_stPos.x + (Define.D_BLOCK_WIDTH / 2), m_MouseList[itMouseList - 1].m_stPos.y + (Define.D_BLOCK_HEIGHT / 2)), E_BOMB_OPTION.E_BOMB_OPTION_TWO, 0, r);
                                                pTempIce.m_stMoveSpeed.x *= 1.7f;
                                                pTempIce.m_stMoveSpeed.y *= 2.7f;
                                                m_IceChunkList.Add(pTempIce);
                                                
									
					        /*
										        if(m_nStage == 1 && m_nTtLevel == 2)
										        {
											        m_bSetText = false;
											        m_nTtLevel++;
											        D_SOUND->Play(m_SoundEffectTtFp,1.5f);
										        }*/
					        /*
										        if(bSled == true)
										        {
						
											        if(m_Sled->m_bOnOff == false)
												        m_Sled->Sleding();
											        else if(m_Sled->m_bOnOff == true)
												        m_Sled->m_fHp = m_Sled->m_fMaxHp;

											        if(m_nStage == 1 && m_nTtLevel == 3)
											        {
												        m_bSetText = false;
												        m_nTtLevel++;
												        D_SOUND->Play(m_SoundEffectTtFp,1.5f);
											        }

										        }*/
                                                if (MenuScene.g_bEffect_Sound == true)
                                                    m_Sae.playEffect("Ice", false);
									        }
									        else if(m_MouseList.Count >= 4)
									        {
                                                for (itMouseList = 0; itMouseList < m_MouseList.Count; itMouseList++)
										        {
											        nCount++;
											        /*if((*itMouseList)->m_eBlockItem == E_BLOCKITEM_SLED)
											        {
												        (*itMouseList)->m_eBlockItem = E_BLOCKITEM_NONE;
												        (*itMouseList)->m_pItem_Sled->SetShow(false);
												        bSled = true;
											        }*/

                                                    m_MouseList[itMouseList].m_bFreezed = true;
                                                    m_MouseList[itMouseList].m_fErosionMaxTime += Define.D_FREEZETIME;
                                                    m_MouseList[itMouseList].m_fErosionTime += Define.D_FREEZETIME;

                                                    m_MouseList[itMouseList].m_pSelect.visible = false; // setVisible(false);
                                                    m_MouseList[itMouseList].m_bDraged = false;
                                                    StageMenuScene.g_nScore += (Define.D_SCORE_ICEBLOCK * m_MouseList.Count);

                                                   
											        //for(int i=0; i<D_SOUND_ICE_CHANNEL; i++)
											        //{
											        //	//if(D_SOUND->IsPlaying(m_SoundIce[i]) == false)
											        //	//{
											        //	m_SoundIce[i] = D_SOUND->Play(m_SoundIceFp,1.0f,false);
											        //	break;
											        //	//}
											        //}
								
                                                    //!< 얼음조각
                                                    for (int i = 0; i < 2; i++)
                                                    {
                                                        CIceChunk pTempIce = new CIceChunk();

                                                        pTempIce.Init(this, new CCPoint(m_MouseList[itMouseList].m_stPos.x + (Define.D_BLOCK_WIDTH / 2), m_MouseList[itMouseList].m_stPos.y + (Define.D_BLOCK_HEIGHT / 2)), E_BOMB_OPTION.E_BOMB_OPTION_ONE, 0, r);
                                                        m_IceChunkList.Add(pTempIce);
                                                    }

											 

                                                    //!< 이펙트매니저
											        //m_EffectManager.Insert(1,((*itMouseList)->m_stPos.x -( D_BLOCK_WIDTH/2)) * D_SCALE_WIDTH,((*itMouseList)->m_stPos.y-( D_BLOCK_HEIGHT/2)) * D_SCALE_HEIGHT);
											        
                                                    
                                                    //if(nCount >= m_MouseList.size())
												        //m_EffectMng->Insert(4,(*itMouseList)->m_stPos.m_fX + 70, (*itMouseList)->m_stPos.m_fY + 0);

											        //m_EffectMng->Insert(1,(*itMouseList)->m_stPos.m_fX,(*itMouseList)->m_stPos.m_fY);
											        //m_fComboTimer = D_COMBOTIME;
                                                    if (m_MouseList[itMouseList].m_eBlockItem != E_BLOCKITEM.E_BLOCKITEM_NONE)
											        {
                                                        //!< 아이템 사용 부분
                                                        //if (m_MouseList[itMouseList].m_eBlockItem == E_BLOCKITEM.E_BLOCKITEM_SLED)
                                                        //{
                                                        //    CSled * pSled = new CSled();
                                                        //    pSled->Init(this);
                                                        //    m_SledList.push_back(pSled);
                                                        //}
                                                        //else if (m_MouseList[itMouseList].m_eBlockItem == E_BLOCKITEM.E_BLOCKITEM_ICE)
                                                        //{
                                                        //    CIce * pIce = new CIce();
                                                        //    pIce->Init(this, ccp((*itMouseList)->m_stPos.x +( D_BLOCK_WIDTH/2),(*itMouseList)->m_stPos.y+( D_BLOCK_HEIGHT/2)));
                                                        //    m_IceList.push_back(pIce);
                                                        //}
                                                        //m_MouseList[itMouseList].UseItem();
											        }
										        }
                                                if (MenuScene.g_bEffect_Sound == true)
                                                    m_Sae.playEffect("Ice", false);

					        /* if (MenuScene.g_bEffect_Sound == true)
                                                        m_Sae.playEffect("Ice", false);

										        if(m_nStage == 1 && m_nTtLevel == 2)
										        {
											        m_bSetText = false;
											        m_nTtLevel++;
											        D_SOUND->Play(m_SoundEffectTtFp,1.5f);
										        }*/
					        /*
										        if(bSled == true)
										        {
						
											        if(m_Sled->m_bOnOff == false)
												        m_Sled->Sleding();
											        else if(m_Sled->m_bOnOff == true)
												        m_Sled->m_fHp = m_Sled->m_fMaxHp;

											        if(m_nStage == 1 && m_nTtLevel == 3)
											        {
												        m_bSetText = false;
												        m_nTtLevel++;
												        D_SOUND->Play(m_SoundEffectTtFp,1.5f);
											        }

										        }*/

									        }
									        else if(m_MouseList.Count >= 3)
									        {
                                                for (itMouseList = 0; itMouseList < m_MouseList.Count; itMouseList++)
										        {
											        nCount++;
											        /*if((*itMouseList)->m_eBlockItem == E_BLOCKITEM_SLED)
											        {
												        (*itMouseList)->m_eBlockItem = E_BLOCKITEM_NONE;
												        (*itMouseList)->m_pItem_Sled->SetShow(false);
												        bSled = true;
											        }*/

                                                    m_MouseList[itMouseList].m_bFreezed = true;
                                                    m_MouseList[itMouseList].m_fErosionMaxTime += Define.D_FREEZETIME;
                                                    m_MouseList[itMouseList].m_fErosionTime += Define.D_FREEZETIME;

                                                    m_MouseList[itMouseList].m_pSelect.visible = false; // (false);
                                                    m_MouseList[itMouseList].m_bDraged = false;
                                                    StageMenuScene.g_nScore += (Define.D_SCORE_ICEBLOCK * m_MouseList.Count);

                                                    
											        //for(int i=0; i<D_SOUND_ICE_CHANNEL; i++)
											        //{
											        //	//if(D_SOUND->IsPlaying(m_SoundIce[i]) == false)
											        //	//{
											        //	m_SoundIce[i] = D_SOUND->Play(m_SoundIceFp,1.0f,false);
											        //	break;
											        //	//}
											        //}
								
									
                                                    //!< 얼음조각
                                                    for (int i = 0; i < 2; i++)
                                                    {
                                                        CIceChunk pTempIce = new CIceChunk();

                                                        pTempIce.Init(this, new CCPoint(m_MouseList[itMouseList].m_stPos.x + (Define.D_BLOCK_WIDTH / 2), m_MouseList[itMouseList].m_stPos.y + (Define.D_BLOCK_HEIGHT / 2)), E_BOMB_OPTION.E_BOMB_OPTION_NO, 0, r);
                                                        m_IceChunkList.Add(pTempIce);
                                                    }

											 
                                                    //!< 이펙트매니저
											        //m_EffectManager.Insert(1,((*itMouseList)->m_stPos.x -( D_BLOCK_WIDTH/2)) * D_SCALE_WIDTH,((*itMouseList)->m_stPos.y-( D_BLOCK_HEIGHT/2)) * D_SCALE_HEIGHT);
											
											        //if(nCount >= m_MouseList.size())
												        //m_EffectMng->Insert(4,(*itMouseList)->m_stPos.m_fX + 70, (*itMouseList)->m_stPos.m_fY + 0);

											        //m_EffectMng->Insert(1,(*itMouseList)->m_stPos.m_fX,(*itMouseList)->m_stPos.m_fY);
											        //m_fComboTimer = D_COMBOTIME;
                                                    if (m_MouseList[itMouseList].m_eBlockItem != E_BLOCKITEM.E_BLOCKITEM_NONE)
											        {
                                                        //!< 아이템 사용 부분
                                                        //if (m_MouseList[itMouseList].m_eBlockItem == E_BLOCKITEM.E_BLOCKITEM_SLED)
                                                        //{
                                                        //    CSled * pSled = new CSled();
                                                        //    pSled->Init(this);
                                                        //    m_SledList.push_back(pSled);
                                                        //}
                                                        //else if (m_MouseList[itMouseList].m_eBlockItem == E_BLOCKITEM.E_BLOCKITEM_ICE)
                                                        //{
                                                        //    CIce * pIce = new CIce();
                                                        //    pIce->Init(this, ccp((*itMouseList)->m_stPos.x +( D_BLOCK_WIDTH/2),(*itMouseList)->m_stPos.y+( D_BLOCK_HEIGHT/2)));
                                                        //    m_IceList.push_back(pIce);
                                                        //}
                                                        //m_MouseList[itMouseList].UseItem();
											        }
											        if(m_nStage == 1 && m_nTtLevel == 2)
											        {
												        m_nTtLevel++;
												        for(int i = 0; i < m_nBlockMax; i++)
												        {
													        if(m_BlockList[i].m_bLive == false)
														        continue;

													        m_BlockList[i].m_fErosionTime = m_BlockList[i].m_fErosionMaxTime;
												        }

											        }
										        }
                                                if (MenuScene.g_bEffect_Sound == true)
                                                    m_Sae.playEffect("Ice", false);
					        /*if (MenuScene.g_bEffect_Sound == true)
                                                        m_Sae.playEffect("Ice", false);
										        if(m_nStage == 1 && m_nTtLevel == 2)
										        {
											        m_bSetText = false;
											        m_nTtLevel++;
											        D_SOUND->Play(m_SoundEffectTtFp,1.5f);
										        }*/
					        /*
										        if(bSled == true)
										        {
						
											        if(m_Sled->m_bOnOff == false)
												        m_Sled->Sleding();
											        else if(m_Sled->m_bOnOff == true)
												        m_Sled->m_fHp = m_Sled->m_fMaxHp;

											        if(m_nStage == 1 && m_nTtLevel == 3)
											        {
												        m_bSetText = false;
												        m_nTtLevel++;
												        D_SOUND->Play(m_SoundEffectTtFp,1.5f);
											        }

										        }*/

									        }
									        else
									        {
                                                for (itMouseList = 0; itMouseList < m_MouseList.Count; itMouseList++)
										        {
                                                    m_MouseList[itMouseList].m_pSelect.visible = false; //->setVisible(false);
                                                    m_MouseList[itMouseList].m_bDraged = false;
										        }
									        }

								        }
								        else if(m_eBlockAct == E_BLOCKACT.E_BLOCKACT_MOVE) //!< 옮김
								        {

				
									        if(m_MouseList.Count == 1)
									        {

                                                int nIndex_X = (int)((((stPos.x) - Define.D_LINE_START_X)) / Define.D_BLOCK_WIDTH);
                                                int nIndex_Y = (int)(((Define.D_LINE_START_Y - (stPos.y) + Define.D_BLOCK_HEIGHT)) / Define.D_BLOCK_HEIGHT);

										        if(nIndex_X < 0)
											        nIndex_X = 0;
                                                if (nIndex_X >= Define.D_BLOCKMAP_WIDTH)
                                                    nIndex_X = Define.D_BLOCKMAP_WIDTH - 1;

										        if(nIndex_Y < 0)
											        nIndex_Y = 0;
                                                if (nIndex_Y >= Define.D_BLOCKMAP_HEIGHT - 1)
                                                    nIndex_Y = Define.D_BLOCKMAP_HEIGHT - 1;


                                                itMouseList = m_MouseList.First().m_nId;

                                                m_BlockList[itMouseList].m_pSelect.visible = false; // setVisible(false);
                                                m_BlockList[itMouseList].m_bDraged = false;

										        if( m_Map.m_nBlockMap[nIndex_Y,nIndex_X] == 0)
										        {
                                                    m_Map.m_nBlockMap[m_BlockList[itMouseList].m_stIndex.m_nY, m_BlockList[itMouseList].m_stIndex.m_nX] = 0;
											        m_Map.m_nBlockMap[nIndex_Y,nIndex_X] = 1;

                                                    m_BlockList[itMouseList].m_stIndex.m_nX = nIndex_X;
                                                    m_BlockList[itMouseList].m_stIndex.m_nY = nIndex_Y;

                                                    m_BlockList[itMouseList].m_eBlockState = E_BLOCKSTATE.E_BLOCKSTATE_NONE;


                                                    m_BlockList[itMouseList].m_stPos.x = Define.D_LINE_START_X + (m_BlockList[itMouseList].m_stIndex.m_nX * Define.D_BLOCK_WIDTH);
                                                    m_BlockList[itMouseList].m_stPos.y = Define.D_LINE_START_Y - (m_BlockList[itMouseList].m_stIndex.m_nY * Define.D_BLOCK_HEIGHT);

                                                    if (m_nStage == 1 && m_nTtLevel == 0)
											        {
												        m_nTtLevel++;
											        }
											
										        }
										        else
										        {
                                                    m_BlockList[itMouseList].m_stPos = m_stMoveBlockPos;
										        }
										        /*if(m_nStage == 1 && m_nTtLevel == 1)
										        {
											        m_nTtLevel++;
											        m_SoundEffectTt = D_SOUND->Play(m_SoundButtonFp, 1.5f);
										        }*/
								
										        //(*itMouseList)->m_fNextDistance = D_BLOCK_HEIGHT - ((D_LINE_START_Y - ((*itMouseList)->m_stIndex.m_nY * D_BLOCK_HEIGHT) + D_BLOCK_HEIGHT) - (stPos.y + (D_BLOCK_HEIGHT/2)));
										        // 
										
                                                //!< 유령 삭제
                                                //if(m_bNeedDelete == true)
                                                //{
                                                //    m_bNeedDelete = false;
                                                //    this->removeChild(m_pGhost,true);
                                                //}
									        }
				
								        }
                                        else if (m_eBlockAct == E_BLOCKACT.E_BLOCKACT_NONE || m_eBlockAct == E_BLOCKACT.E_BLOCKACT_NOT)
								        {
                                            for (itMouseList = 0; itMouseList < m_MouseList.Count; itMouseList++)
									        {
                                                m_MouseList[itMouseList].m_pSelect.visible = false;
                                                m_MouseList[itMouseList].m_bDraged = false;
									        }
								        }


                                        m_eBlockAct = E_BLOCKACT.E_BLOCKACT_NONE;

                                        m_MouseList.Clear();
		
						        /*
						        list<CBlock*>::iterator itMouseBlock;
						        for(itMouseBlock = m_MouseList.begin(); itMouseBlock != m_MouseList.end(); itMouseBlock++)
						        {
							        (*itMouseBlock)->m_pSelect->setVisible(false);
						        }*/
				        }
			        }
		        }
	
        }
        //bool ccTouchBegan(CCTouch pTouch, CCEvent pEvent)
        //{
        
        //}
        
        void BackCallback(CCObject pSender)
        {
	        m_fCreateTimer = 0.0f;
            CCScene pScene = CCTransitionFade.transitionWithDuration(1.0f, StageMenuScene.scene());
            CCDirector.sharedDirector().replaceScene(pScene);
            CCApplication.m_bIsProcTocuh = false;


            if (MenuScene.g_bEffect_Sound == true)
                m_Sae.playEffect("StageStart");
        }

        void PauseCallback(CCObject pSender)
        {
	        if(g_bPause == false)
	        {
                g_bPause = true;

                if (MenuScene.g_bEffect_Sound == true)
                    m_Sae.playEffect("StageStart");
	        }
        }
        void ResumeCallback(CCObject pSender)
        {
	        if(g_bPause == true)
	        {
                g_bPause = false;

                if (MenuScene.g_bEffect_Sound == true)
                    m_Sae.playEffect("StageStart");
	        }
        }

    }
}
