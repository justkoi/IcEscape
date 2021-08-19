using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using cocos2d;


namespace HelloCocos2d.GameObject
{
    public enum E_BLOCKNUMBER
    {
        E_BLOCKNUMBER_POLARBEAR,
        E_BLOCKNUMBER_SEAL,
        E_BLOCKNUMBER_PENGUIN,
        E_BLOCKNUMBER_BREA,
        E_BLOCKNUMBER_MAX,

    };
    
    public enum E_BLOCKSTATE
    {

	    E_BLOCKSTATE_NONE,
	    E_BLOCKSTATE_FALLING,
    };

    public enum E_BLOCKITEM
    {
	    E_BLOCKITEM_NONE,
	    E_BLOCKITEM_SLED,
	    E_BLOCKITEM_ICE,
    };
    
    public struct stVec2i
    {
	     public int m_nX;
	     public int m_nY;

         //public stVec2i()
         //{
         //    m_nX = 0;
         //    m_nY = 0;
         //}
	     public stVec2i(int nX, int nY)
	     {
		     m_nX = nX;
		     m_nY = nY;
	     }
	     

    };
    
    public class CBlock
    {

        public int Random;


	    //CEMPlane*	m_pPlane;
	    public CCSprite m_pBlock;//[E_BLOCKNUMBER_MAX];
        public CCActionInterval m_pBlockAnt;//[E_BLOCKNUMBER_MAX];
        public CCAnimation m_pBlockAni;//[E_BLOCKNUMBER_MAX];

        public CCSprite m_pBlock_Pause;
        public CCSprite m_pBlock_Freeze;
        public CCSprite m_pBlock_Angry;

        public float m_fEyeContact;

	    //[E_BLOCKNUMBER_MAX];
        public CCSprite m_pSelect;
	    //!< CCSprite*	m_pErosoin;
	    //!< CCSprite*	m_pErosoin_Border;
        public CCSprite m_pFreeze;
	    //CCSprite*	m_pItem_Sled;
        public CCSprite m_pItem;


        public float m_fEye;
        public bool m_bEye;


        public int m_nGT;
        public int m_nGC;

        public int m_nId;

        public E_BLOCKNUMBER m_eBlockNumber;

        public E_BLOCKITEM m_eBlockItem;

        public double m_fStartY;
        public double m_fSpeed;
        public double m_fPlusSpeed;
        public double m_fNowDistance;
        public double m_fDistance;
        public double m_fNextDistance;

        public float m_fErosionTime;
        public float m_fErosionMaxTime;
        public float m_fErosionOffsetY;

        public bool m_bFreezed;
        public bool m_bDraged;
        public bool m_bDolphinHited;

        public bool m_bLive;
        public CCLayer m_pThisScene;
        public CCPoint m_stPos;
        public CCPoint m_stOffsetPos;
        public stVec2i m_stIndex;
        public E_BLOCKSTATE m_eBlockState;





        public CBlock() { }
        ~CBlock() { }

        public void Init(CCLayer pThisScene, int nId)
        {
            m_pThisScene = pThisScene;
	        m_bLive = false;

	        m_nId = nId;
	        m_fNextDistance = 64.0f;
	        m_stOffsetPos = new CCPoint(0,0);

	        m_stIndex.m_nX = 0;
	        m_stIndex.m_nY = 0;
	        m_fEyeContact = 0.0f;

            m_stPos = new CCPoint(0, 0);
	        m_stPos.x = Define.D_LINE_START_X + (m_stIndex.m_nX * 64);
	        m_stPos.y = Define.D_LINE_START_Y - (m_stIndex.m_nY * 64);

            Random r = new Random();
	        Random = r.Next(0,(int)E_BLOCKNUMBER.E_BLOCKNUMBER_MAX);

	        m_eBlockNumber = (E_BLOCKNUMBER)Random;

	
            //////////////////////////////////////////////////////////////////////////////////////
            m_pSelect = CCSprite.spriteWithFile("Block_Select");
            m_pSelect.position = m_stPos;
            m_pSelect.scaleX = 1.00f;
            m_pSelect.scaleY = 1.00f;
            //m_pSelect.Opacity = (byte)(255.0f * 0.6f);
            m_pSelect.anchorPoint = new CCPoint(0.0f,0.0f);
            m_pSelect.visible = false;
            m_pThisScene.addChild(m_pSelect, 28);
            //////////////////////////////////////////////////////////////////////////////////////
            m_pFreeze = CCSprite.spriteWithFile("Block_Freeze");
            m_pFreeze.position = m_stPos;
            m_pFreeze.scaleX = 1.00f;
            m_pFreeze.scaleY = 1.00f;
            //m_pFreeze.Opacity = (byte)(255.0f * 0.6f);
            m_pFreeze.anchorPoint = new CCPoint(0.25f,0.25f);
            m_pThisScene.addChild(m_pFreeze, 27);
            //////////////////////////////////////////////////////////////////////////////////////


        /*
	        m_pItem_Sled = new CEMPlane();					
	        m_pItem_Sled->SetSize(1.0f, 1.0f);					
	        m_pItem_Sled->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	        m_pItem_Sled->SetLocalVec(0.0f, 0.0f);				
	        m_pItem_Sled->SetOffset(0.0f, 0.0f);
	        m_pItem_Sled->SetTexture(pThisScene, "Data/Image/Block/Block_Item_Sled.png");	
	        m_pItem_Sled->SetFrustumCulling(true);				
	        m_pItem_Sled->SetBoundingBoxCalc(true);				
	        m_pItem_Sled->SetBlend(true);				
	        m_pItem_Sled->SetShow(false);
	        m_pItem_Sled->SetBackFaceCulling(false);
	        m_pItem_Sled->SetColor(1.0f,1.0f,1.0f,1.0f);
	        pThisScene->Commit(-4,nCreateBlockNumber, "Item_Sled", m_pItem_Sled);
        */


	        m_fStartY			= m_stPos.y;
	        m_fSpeed			= Define.D_BLOCK_SPEED;
            m_fPlusSpeed        = Define.D_BLOCK_PLUSSPEED;
	        m_fNowDistance		= 0.0f;
	        m_fDistance			= 0.0f;

	        m_fEye = 0.0f;

	        m_eBlockState		= E_BLOCKSTATE.E_BLOCKSTATE_NONE;

            m_fErosionMaxTime = Define.D_EROSIONTIME;
	        m_fErosionTime = m_fErosionMaxTime;
	        m_fErosionOffsetY = 0.0f;

	        m_bFreezed = false;
	        m_bDraged = false;
	        m_bDolphinHited = false;


	        m_bEye = false;

	        //int nBlockItemRandom = CEMMath::RandomIntInRange(0,10000);

	        //if(nBlockItemRandom >= 0 && nBlockItemRandom <= 500)
	        //{
	        //	m_eBlockItem = E_BLOCKITEM_SLED;
	        //	m_pItem_Sled->SetShow(true);
	        //}
	        //else
	        //{
	        //	m_eBlockItem = E_BLOCKITEM_NONE;
	        //	m_pItem_Sled->SetShow(false);
	        //}
        }
        public void Create(stVec2i stIndex, Random r)
        {
            
	        m_bLive = true;
	        m_stIndex = stIndex;
	        m_fNextDistance = 64.0f;
	        m_stOffsetPos = new CCPoint(0,0);

	        m_stPos.x = Define.D_LINE_START_X + (stIndex.m_nX * 64);
	        m_stPos.y = Define.D_LINE_START_Y - (stIndex.m_nY * 64);

	        //m_stPos.x = 240;
	        //m_stPos.y = 400;
	
	
            
	        Random = r.Next(0,(int)E_BLOCKNUMBER.E_BLOCKNUMBER_MAX);

	        m_eBlockNumber = (E_BLOCKNUMBER)Random;
	
	
	        //m_pThisScene->removeChild(m_pBlock, true);
	        //m_pThisScene->removeChild(m_pBlock_Pause, true);


	        //
	        //CCAnimation* CAniTemp = CCAnimation::animation();
	        //for(int i=0; i<3; i++) {
	        //	 sprintf(frameName, "Block_%d_%d.png",(int)m_eBlockNumber+1,i+1);
	        //	 CAniTemp->addSpriteFrameWithFileName(frameName);
	        //}

	        //CAniTemp->setDelayPerUnit(0.15f);
	        //m_pBlockAnt = CCAnimate::create(CAniTemp);

	        //m_pBlock = CCSprite::spriteWithFile("Block_Select.png");
	        //m_pBlock->setPosition( ccp(m_stPos.x, m_stPos.y));
	        ////m_pThisScene->addChild(m_pBlock, 25);

	        ////m_pBlock->runAction(m_pBlockAnt);
	        //m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
	        //m_pBlock->setAnchorPoint(ccp(0.0,0.0));

	        //CCAnimationCache* animationcache = new  CCAnimationCache;
	        //animationcache->addAnimation(CAniTemp,"Block");
	        //m_pBlock->setDisplayFrameWithAnimationName("Block",0);
	        ////CCSequence::a
	

	        //m_pThisScene->addChild(m_pBlock_Pause, 25);

        /*
	        m_pItem_Sled = new CEMPlane();					
	        m_pItem_Sled->SetSize(1.0f, 1.0f);					
	        m_pItem_Sled->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	        m_pItem_Sled->SetLocalVec(0.0f, 0.0f);				
	        m_pItem_Sled->SetOffset(0.0f, 0.0f);
	        m_pItem_Sled->SetTexture(pThisScene, "Data/Image/Block/Block_Item_Sled.png");	
	        m_pItem_Sled->SetFrustumCulling(true);				
	        m_pItem_Sled->SetBoundingBoxCalc(true);				
	        m_pItem_Sled->SetBlend(true);				
	        m_pItem_Sled->SetShow(false);
	        m_pItem_Sled->SetBackFaceCulling(false);
	        m_pItem_Sled->SetColor(1.0f,1.0f,1.0f,1.0f);
	        pThisScene->Commit(-4,nCreateBlockNumber, "Item_Sled", m_pItem_Sled);
        */


	        m_fStartY			= m_stPos.y;
	        m_fSpeed			= Define.D_BLOCK_SPEED;
	        m_fPlusSpeed		= Define.D_BLOCK_PLUSSPEED;
	        m_fNowDistance		= 0.0f;
	        m_fDistance			= 0.0f;

	        m_fEye = 0.0f;

	        m_eBlockState		= E_BLOCKSTATE.E_BLOCKSTATE_NONE;

	        m_fErosionMaxTime = Define.D_EROSIONTIME;
	        m_fErosionTime = m_fErosionMaxTime;
	        m_fErosionOffsetY = 0.0f;

	        m_bFreezed = false;
	        m_bDraged = false;
	        m_bDolphinHited = false;


	        m_bEye = false;

	        /////////////////////////////////////////////////////

	        m_pBlockAni = CCAnimation.animation();
	        for(int j=0; j<4; j++) {
			        //sprintf(frameName, "Block_%d_%d.png",(int)m_eBlockNumber+1,j+1);
			        m_pBlockAni.addFrameWithFileName("Block_"+((int)m_eBlockNumber+1).ToString()+"_"+(j+1).ToString());
	        }
	        m_pBlockAni.setDelay(0.15f);
	        m_pBlockAnt = CCAnimate.actionWithAnimation(m_pBlockAni);
	        m_pBlock = CCSprite.spriteWithFile("NewSprite");

	        //m_pBlock->setPosition( ccp(m_stPos.x, m_stPos.y));
	
            m_pBlock.position = m_stPos;
            m_pBlock.scaleX = 1.20f;
            m_pBlock.scaleY = 1.20f;

            m_pBlock.runAction(CCRepeatForever.actionWithAction(m_pBlockAnt));
            m_pBlock.anchorPoint = new CCPoint(0.0f, 0.0f);

            

	        m_pThisScene.addChild(m_pBlock, 26);

	        //m_pBlock->runAction(m_pBlockAnt);
	        //m_pBlock->setScale(1.2f);

	        //////////////////////////////////////////////////////
	        m_pBlock_Pause = CCSprite.spriteWithFile("Block_"+((int)m_eBlockNumber+1).ToString()+"_1");
            m_pBlock_Pause.position = m_stPos;
            m_pBlock_Pause.scaleX = 1.20f;
            m_pBlock_Pause.scaleY = 1.20f;
            m_pBlock_Pause.anchorPoint = new CCPoint(0.0f,0.0f);
            m_pThisScene.addChild(m_pBlock_Pause, 26);
            //////////////////////////////////////////////////////
	        m_pBlock_Freeze = CCSprite.spriteWithFile("Block_"+((int)m_eBlockNumber+1).ToString()+"_Freeze");
            m_pBlock_Freeze.position = m_stPos;
            m_pBlock_Freeze.scaleX = 1.20f;
            m_pBlock_Freeze.scaleY = 1.20f;
            m_pBlock_Freeze.anchorPoint = new CCPoint(0.0f,0.0f);
            m_pThisScene.addChild(m_pBlock_Freeze, 26);
	        //////////////////////////////////////////////////////
            m_pBlock_Angry = CCSprite.spriteWithFile("Block_"+((int)m_eBlockNumber+1).ToString()+"_Angry");
            m_pBlock_Angry.position = m_stPos;
            m_pBlock_Angry.scaleX = 1.20f;
            m_pBlock_Angry.scaleY = 1.20f;
            m_pBlock_Angry.anchorPoint = new CCPoint(0.0f,0.0f);
            m_pThisScene.addChild(m_pBlock_Angry, 26);
	        //////////////////////////////////////////////////////
	
	        //////////////////////////////////////////////////////
	        m_pBlock.visible = true;
	        m_pBlock_Pause.visible = true;

	        //for(int i=0; i<E_BLOCKNUMBER_MAX ; i++)
	        //{
	        //	if(i != (int)m_eBlockNumber)
	        //	{
	        //		m_pBlock[i]->setVisible(false);
	        //		m_pBlock_Pause[i]->setVisible(false);
	        //	}
	        //	else if(i == (int)m_eBlockNumber)
	        //	{
	        //		m_pBlock[i]->setVisible(true);
	        //		m_pBlock_Pause[i]->setVisible(true);
	        //		//m_pBlock_Pause[i]->setVisible(false);
	        //	}
	        //}
	        //int nBlockItemRandom = CEMMath::RandomIntInRange(0,10000);

	        //if(nBlockItemRandom >= 0 && nBlockItemRandom <= 500)
	        //{
	        //	m_eBlockItem = E_BLOCKITEM_SLED;
	        //	m_pItem_Sled->SetShow(true);
	        //}
	        //else
	        //{
	        //	m_eBlockItem = E_BLOCKITEM_NONE;
	        //	m_pItem_Sled->SetShow(false);
	        //}


            //int nBlockItemRandom = rand()%10000; //0 ~ 9999

            //if(nBlockItemRandom >= 0 && nBlockItemRandom <= 400) //!< 10% 확률로 썰매
            //{
            //    if(g_nSelectStage >= 7)
            //    {
            //        m_eBlockItem = E_BLOCKITEM_SLED;

            //        //////////////////////////////////////////////////////
            //        sprintf(frameName, "Item_%d.png",(int)m_eBlockItem);


            //        m_pItem = CCSprite::create(frameName);
            //        //m_pItem->setPosition( ccp(m_stPos.x, m_stPos.y) );
            //        m_pItem->setAnchorPoint(ccp(0.0,0.0));
            //        //m_pItem->setScale(1.0f);

            //        m_pItem->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
            //        m_pItem->setScaleX(1.00f * D_SCALE_WIDTH);
            //        m_pItem->setScaleY(1.00f * D_SCALE_HEIGHT);


            //        m_pItem->setOpacity(255 * 0.4f);
            //        m_pThisScene->addChild(m_pItem, 27);
            //        //////////////////////////////////////////////////////
            //    }
            //    else												  //!< 90% 확률로 기본
            //    {
            //        m_eBlockItem = E_BLOCKITEM_NONE;
            //    }

            //}
            //else if(nBlockItemRandom >= 0 && nBlockItemRandom <= 700) //!< 10% 확률로 얼음조각
            //{
            //    if(g_nSelectStage >= 4)
            //    {
            //        m_eBlockItem = E_BLOCKITEM_ICE;

            //        //////////////////////////////////////////////////////
            //        sprintf(frameName, "Item_%d.png",(int)m_eBlockItem);


            //        m_pItem = CCSprite::create(frameName);
            //        //m_pItem->setPosition( ccp(m_stPos.x, m_stPos.y) );
            //        m_pItem->setAnchorPoint(ccp(0.0,0.0));
            //        //m_pItem->setScale(1.0f);

            //        m_pItem->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
            //        m_pItem->setScaleX(1.00f * D_SCALE_WIDTH);
            //        m_pItem->setScaleY(1.00f * D_SCALE_HEIGHT);


            //        m_pItem->setOpacity(255 * 0.4f);
            //        m_pThisScene->addChild(m_pItem, 27);
            //        //////////////////////////////////////////////////////
            //    }
            //    else												  //!< 90% 확률로 기본
            //    {
            //        m_eBlockItem = E_BLOCKITEM_NONE;
            //    }
            //}
            //else												  //!< 90% 확률로 기본
            //{
            //    m_eBlockItem = E_BLOCKITEM_NONE;
		
            //}

            m_pFreeze.visible = m_bFreezed;// (m_bFreezed);
            m_pBlock_Freeze.visible = m_bFreezed;
            m_pBlock_Angry.visible = false;


	        
            m_pFreeze.position = new CCPoint(m_stPos.x + m_stOffsetPos.x, m_stPos.y + m_stOffsetPos.y);
            m_pSelect.position = new CCPoint(m_stPos.x + m_stOffsetPos.x, m_stPos.y + m_stOffsetPos.y);
            m_pBlock.position = new CCPoint(m_stPos.x - 6.4f + m_stOffsetPos.x, m_stPos.y - 6.4f + m_stOffsetPos.y);
            m_pBlock_Pause.position = new CCPoint(m_stPos.x - 6.4f + m_stOffsetPos.x, m_stPos.y - 6.4f + m_stOffsetPos.y);
            m_pBlock_Freeze.position = new CCPoint(m_stPos.x - 6.4f + m_stOffsetPos.x, m_stPos.y - 6.4f + m_stOffsetPos.y);
            m_pBlock_Angry.position = new CCPoint(m_stPos.x - 6.4f + m_stOffsetPos.x, m_stPos.y - 6.4f + m_stOffsetPos.y);

        }
        //public void CreateIt(stVec2i stIndex, E_BLOCKNUMBER eBlockNumber);
	    //void Init(CRootScene* pThisScene, E_BLOCKNUMBER eBlockNumber, stVec2i stIndex,int nCreateBlockNumber);
        public void Update(float dt, float fErosionSpeed)
        {
            if (m_bLive == true)
            {
                //!< m_pErosoin->setVisible(true);
                //!< _pErosoin_Border->setVisible(true);



                m_pFreeze.visible = m_bFreezed; // setVisible(m_bFreezed);
                m_pBlock_Freeze.visible = m_bFreezed;
                m_pBlock_Angry.visible = false;

                if (m_bFreezed == false)
                {
                    m_fEye += dt;


                    if (m_bEye == false && m_fEye >= 3.0f)
                    {
                        m_bEye = true;
                        
                        CCActionManager.sharedManager().resumeTarget(m_pBlock);

                        //m_pBlock.getActionManager().resumeTarget(m_pBlock);
                        m_pBlock.visible = true;
                        m_pBlock_Pause.visible = false;

                        //m_pBlock->getActionManager()->resumeTarget(m_pBlockAnt);
                    }
                    if (m_bEye == true && m_fEye >= 3.75f + m_fEyeContact)
                    {
                        m_fEyeContact -= 0.2f;
                        if (m_fEyeContact <= -0.6f)
                        {
                            m_fEyeContact = 0.0f;
                        }
                        m_fEye = 0.0f;
                        m_bEye = false;
                        
                        CCActionManager.sharedManager().pauseTarget(m_pBlock);
                        m_pBlock.visible = false;
                        m_pBlock_Pause.visible = true;
                    }
                }
                else
                {
                    m_pBlock.stopAction(m_pBlockAnt);
                    m_pBlock_Pause.visible = false;
                    m_pBlock_Freeze.visible = true;
                }

                if (m_fErosionTime <= (Define.D_EROSIONTIME / 2))
                {
                    int nRandSeed = (int)(((Define.D_EROSIONTIME / 2) - m_fErosionTime) * 10000);
                    nRandSeed += 1;

                    Random r = new Random();

                    m_stOffsetPos.x = ((float)((r.Next(0, nRandSeed)) - (r.Next(0, nRandSeed)))) / 10000;

                    m_pBlock_Pause.visible = false;
                    m_pBlock_Angry.visible = true;
                }


                if (m_eBlockState == E_BLOCKSTATE.E_BLOCKSTATE_FALLING && m_bDraged == false)
                {
                    if (m_fNowDistance < m_fDistance)
                    {
                        m_stPos.y -= ((float)m_fSpeed * dt);
                        m_fNowDistance += (m_fSpeed * dt);
                        m_fSpeed += (m_fPlusSpeed * dt);
                        if (m_fNowDistance >= m_fDistance)
                        {
                            m_stPos.y = (float)m_fStartY - (float)m_fDistance;
                            m_fSpeed = Define.D_BLOCK_SPEED;
                            m_fPlusSpeed = Define.D_BLOCK_PLUSSPEED;
                            m_fNowDistance = 0.0f;
                            m_fDistance = 64.0f;
                            m_eBlockState = E_BLOCKSTATE.E_BLOCKSTATE_NONE;
                        }
                    }
                }
                else
                {
                    if (m_stIndex.m_nY == Define.D_BLOCKMAP_HEIGHT - 1)
                    {
                        m_fErosionTime -= (dt * fErosionSpeed);
                    }
                }




                m_pFreeze.position = new CCPoint(m_stPos.x + m_stOffsetPos.x, m_stPos.y + m_stOffsetPos.y);
                m_pSelect.position = new CCPoint(m_stPos.x + m_stOffsetPos.x, m_stPos.y + m_stOffsetPos.y);
                m_pBlock.position = new CCPoint(m_stPos.x - 6.4f + m_stOffsetPos.x, m_stPos.y - 6.4f + m_stOffsetPos.y);
                m_pBlock_Pause.position = new CCPoint(m_stPos.x - 6.4f + m_stOffsetPos.x, m_stPos.y - 6.4f + m_stOffsetPos.y);
                m_pBlock_Freeze.position = new CCPoint(m_stPos.x - 6.4f + m_stOffsetPos.x, m_stPos.y - 6.4f + m_stOffsetPos.y);
                m_pBlock_Angry.position = new CCPoint(m_stPos.x - 6.4f + m_stOffsetPos.x, m_stPos.y - 6.4f + m_stOffsetPos.y);

                if (m_eBlockItem != E_BLOCKITEM.E_BLOCKITEM_NONE)
                {
                    m_pItem.position = new CCPoint(m_stPos.x + m_stOffsetPos.x, m_stPos.y + m_stOffsetPos.y);
                }
            }
            else if (m_bLive == false)
            {
                m_pFreeze.visible = false;
                m_pSelect.visible = false;

            }
        }
        //public void Exit()
        //{

        //}

        public void Die()
        {
            if (m_bLive == true)
            {

                m_pThisScene.removeChild(m_pBlock, true);
                m_pThisScene.removeChild(m_pBlock_Pause, true);
                m_pThisScene.removeChild(m_pBlock_Freeze, true);
                m_pThisScene.removeChild(m_pBlock_Angry, true);
                if (m_eBlockItem != E_BLOCKITEM.E_BLOCKITEM_NONE)
                {
                    m_pThisScene.removeChild(m_pItem, true);
                    m_eBlockItem = E_BLOCKITEM.E_BLOCKITEM_NONE;
                }
            }
            m_bLive = false;

            m_pFreeze.visible = false;
            m_pSelect.visible = false;

        }
        //public void UseItem();
        public bool HitTest(float nX, float nY)
        {
            if (m_bLive == false)
                return false;
            if (nX >= m_stPos.x && nX <= (m_stPos.x + Define.D_BLOCK_WIDTH) &&
                nY >= m_stPos.y && nY <= (m_stPos.y + Define.D_BLOCK_HEIGHT))
            {
                return true;
            }
            return false;
        }
        public bool IsErosoined()
        {
            if (m_fErosionTime < 0)
            {
                return true;
            }
            return false;
        }
        public void ShowUpdate()
        {
            if (m_bLive == false)
            {
                m_pFreeze.visible = false;
                //!< m_pErosoin->setVisible(false);
                //!< m_pErosoin_Border->setVisible(false);
                m_pSelect.visible = false;

                //m_pBlock->setVisible(false);
                //m_pBlock_Pause->setVisible(false);

            }
        }

    };
}
