#include "stdafx.h"

USING_NS_CC;
static int Random = 0;
void CBlock::Init(CCLayer* pThisScene, int nId)
{
	m_pThisScene = pThisScene;
	m_bLive = false;

	m_nId = nId;
	m_fNextDistance = 64.0f;
	m_stOffsetPos = ccp(0,0);

	m_stIndex.m_nX = 0;
	m_stIndex.m_nY = 0;
	m_fEyeContact = 0.0f;

	m_stIndex = m_stIndex;

	m_stPos.x = D_LINE_START_X + (m_stIndex.m_nX * 64);
	m_stPos.y = D_LINE_START_Y - (m_stIndex.m_nY * 64);

	//m_stPos.x = 240;
	//m_stPos.y = 400;

	Random = rand()%E_BLOCKNUMBER_MAX;
	m_eBlockNumber = (E_BLOCKNUMBER)Random;

	

	//for(int i=0; i<E_BLOCKNUMBER_MAX; i++)
	//{


	///////////////////////////////////////////////////////
	//m_pBlockAni = CCAnimation::animation();
	//for(int j=0; j<3; j++) {
	//		sprintf(frameName, "Block_%d_%d.png",(int)m_eBlockNumber+1,j+1);
	//		m_pBlockAni->addSpriteFrameWithFileName(frameName);
	//}
	//m_pBlockAni->setDelayPerUnit(0.15f);
	//m_pBlockAnt = CCAnimate::create(m_pBlockAni);
	//m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
	//m_pBlock->setPosition( ccp(m_stPos.x, m_stPos.y));
	//pThisScene->addChild(m_pBlock, 26);
	////m_pBlock->runAction(m_pBlockAnt);
	//m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
	//m_pBlock->setAnchorPoint(ccp(0.0,0.0));
	//m_pBlock->setScale(1.2f);
	////////////////////////////////////////////////////////
	//sprintf(frameName, "Block_%d_1.png",(int)m_eBlockNumber+1);


	//m_pBlock_Pause = CCSprite::create(frameName);
	//m_pBlock_Pause->setPosition( ccp(m_stPos.x, m_stPos.y) );
	//m_pBlock_Pause->setAnchorPoint(ccp(0.0,0.0));
	//m_pBlock_Pause->setScale(1.2f);
	//pThisScene->addChild(m_pBlock_Pause, 26);
	////////////////////////////////////////////////////////


	//}



	m_pSelect = CCSprite::create("Block_Select.png");
   // m_pSelect->setPosition( ccp(m_stPos.x, m_stPos.y) );

	m_pSelect->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pSelect->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pSelect->setScaleY(1.00f * D_SCALE_HEIGHT);

	m_pSelect->setOpacity(255 * 0.6f);
	m_pSelect->setAnchorPoint(ccp(0.0,0.0));
	m_pSelect->setVisible(false);
	pThisScene->addChild(m_pSelect, 28);

	/*m_pErosoin = CCSprite::create("Block_Erosoin.png");
    m_pErosoin->setPosition( ccp(m_stPos.x, m_stPos.y) );
	m_pErosoin->setOpacity(255 * 0.3f);
	m_pErosoin->setAnchorPoint(ccp(0.0,0.0));
	m_pErosoin->setVisible(true);*/
	//pThisScene->addChild(m_pErosoin, 25);
	
	/*m_pErosoin_Border = CCSprite::create("Block_Erosoin_Border.png");
    m_pErosoin_Border->setPosition( ccp(m_stPos.x, m_stPos.y) );
	m_pErosoin_Border->setOpacity(255 * 1.0f);
	m_pErosoin_Border->setAnchorPoint(ccp(0.0,0.0));*/
	//pThisScene->addChild(m_pErosoin_Border, 25);

	m_pFreeze = CCSprite::create("Block_Freeze.png");

	m_pFreeze->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pFreeze->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pFreeze->setScaleY(1.00f * D_SCALE_HEIGHT);


	m_pFreeze->setOpacity(255 * 1.0f);
	m_pFreeze->setAnchorPoint(ccp(0.25,0.25));
	m_pFreeze->setOpacity(255 * 0.6f);
	pThisScene->addChild(m_pFreeze, 27);


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
	m_fSpeed			= D_BLOCK_SPEED;
	m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
	m_fNowDistance		= 0.0f;
	m_fDistance			= 0.0f;

	m_fEye = 0.0f;

	m_eBlockState		= E_BLOCKSTATE_NONE;

	m_fErosionMaxTime = D_EROSIONTIME;
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

void CBlock::Create(stVec2i stIndex)
{
	
	char frameName[256];

	m_bLive = true;
	m_stIndex = stIndex;
	m_fNextDistance = 64.0f;
	m_stOffsetPos = ccp(0,0);

	m_stPos.x = D_LINE_START_X + (stIndex.m_nX * 64);
	m_stPos.y = D_LINE_START_Y - (stIndex.m_nY * 64);

	//m_stPos.x = 240;
	//m_stPos.y = 400;
	
	

	Random = rand()%E_BLOCKNUMBER_MAX;
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
	m_fSpeed			= D_BLOCK_SPEED;
	m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
	m_fNowDistance		= 0.0f;
	m_fDistance			= 0.0f;

	m_fEye = 0.0f;

	m_eBlockState		= E_BLOCKSTATE_NONE;

	m_fErosionMaxTime = D_EROSIONTIME;
	m_fErosionTime = m_fErosionMaxTime;
	m_fErosionOffsetY = 0.0f;

	m_bFreezed = false;
	m_bDraged = false;
	m_bDolphinHited = false;


	m_bEye = false;

	/////////////////////////////////////////////////////
	m_pBlockAni = CCAnimation::animation();
	for(int j=0; j<4; j++) {
			sprintf(frameName, "Block_%d_%d.png",(int)m_eBlockNumber+1,j+1);
			m_pBlockAni->addSpriteFrameWithFileName(frameName);
	}
	m_pBlockAni->setDelayPerUnit(0.15f);
	m_pBlockAnt = CCAnimate::create(m_pBlockAni);
	m_pBlock = CCSprite::spriteWithFile("NewSprite.png");

	//m_pBlock->setPosition( ccp(m_stPos.x, m_stPos.y));
	
	m_pBlock->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock->setScaleX(1.20f * D_SCALE_WIDTH);
	m_pBlock->setScaleY(1.20f * D_SCALE_HEIGHT);


	m_pThisScene->addChild(m_pBlock, 26);
	//m_pBlock->runAction(m_pBlockAnt);
	m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
	m_pBlock->setAnchorPoint(ccp(0.0,0.0));
	//m_pBlock->setScale(1.2f);
	//////////////////////////////////////////////////////
	sprintf(frameName, "Block_%d_1.png",(int)m_eBlockNumber+1);


	m_pBlock_Pause = CCSprite::create(frameName);

	//m_pBlock_Pause->setPosition( ccp(m_stPos.x, m_stPos.y) );

	m_pBlock_Pause->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock_Pause->setScaleX(1.20f * D_SCALE_WIDTH);
	m_pBlock_Pause->setScaleY(1.20f * D_SCALE_HEIGHT);

	m_pBlock_Pause->setAnchorPoint(ccp(0.0,0.0));
	//m_pBlock_Pause->setScale(1.2f);

	m_pThisScene->addChild(m_pBlock_Pause, 26);
	//////////////////////////////////////////////////////

	sprintf(frameName, "Block_%d_Freeze.png",(int)m_eBlockNumber+1);


	m_pBlock_Freeze = CCSprite::create(frameName);

	//m_pBlock_Freeze->setPosition( ccp(m_stPos.x, m_stPos.y) );

	m_pBlock_Freeze->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock_Freeze->setScaleX(1.20f * D_SCALE_WIDTH);
	m_pBlock_Freeze->setScaleY(1.20f * D_SCALE_HEIGHT);

	m_pBlock_Freeze->setAnchorPoint(ccp(0.0,0.0));
	//m_pBlock_Freeze->setScale(1.2f);

	m_pThisScene->addChild(m_pBlock_Freeze, 26);
	//////////////////////////////////////////////////////
	
	sprintf(frameName, "Block_%d_Angry.png",(int)m_eBlockNumber+1);


	m_pBlock_Angry = CCSprite::create(frameName);

	m_pBlock_Angry->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock_Angry->setScaleX(1.20f * D_SCALE_WIDTH);
	m_pBlock_Angry->setScaleY(1.20f * D_SCALE_HEIGHT);

	//m_pBlock_Angry->setPosition( ccp(m_stPos.x, m_stPos.y) );
	m_pBlock_Angry->setAnchorPoint(ccp(0.0,0.0));
	//m_pBlock_Angry->setScale(1.2f);



	m_pThisScene->addChild(m_pBlock_Angry, 26);
	//////////////////////////////////////////////////////


	m_pBlock->setVisible(true);
	m_pBlock_Pause->setVisible(true);

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

	int nBlockItemRandom = rand()%10000; //0 ~ 9999

	if(nBlockItemRandom >= 0 && nBlockItemRandom <= 400) //!< 10% È®·ü·Î ½ä¸Å
	{
		if(g_nSelectStage >= 7)
		{
			m_eBlockItem = E_BLOCKITEM_SLED;

			//////////////////////////////////////////////////////
			sprintf(frameName, "Item_%d.png",(int)m_eBlockItem);


			m_pItem = CCSprite::create(frameName);
			//m_pItem->setPosition( ccp(m_stPos.x, m_stPos.y) );
			m_pItem->setAnchorPoint(ccp(0.0,0.0));
			//m_pItem->setScale(1.0f);

			m_pItem->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
			m_pItem->setScaleX(1.00f * D_SCALE_WIDTH);
			m_pItem->setScaleY(1.00f * D_SCALE_HEIGHT);


			m_pItem->setOpacity(255 * 0.4f);
			m_pThisScene->addChild(m_pItem, 27);
			//////////////////////////////////////////////////////
		}
		else												  //!< 90% È®·ü·Î ±âº»
		{
			m_eBlockItem = E_BLOCKITEM_NONE;
		}

	}
	else if(nBlockItemRandom >= 0 && nBlockItemRandom <= 700) //!< 10% È®·ü·Î ¾óÀ½Á¶°¢
	{
		if(g_nSelectStage >= 4)
		{
			m_eBlockItem = E_BLOCKITEM_ICE;

			//////////////////////////////////////////////////////
			sprintf(frameName, "Item_%d.png",(int)m_eBlockItem);


			m_pItem = CCSprite::create(frameName);
			//m_pItem->setPosition( ccp(m_stPos.x, m_stPos.y) );
			m_pItem->setAnchorPoint(ccp(0.0,0.0));
			//m_pItem->setScale(1.0f);

			m_pItem->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
			m_pItem->setScaleX(1.00f * D_SCALE_WIDTH);
			m_pItem->setScaleY(1.00f * D_SCALE_HEIGHT);


			m_pItem->setOpacity(255 * 0.4f);
			m_pThisScene->addChild(m_pItem, 27);
			//////////////////////////////////////////////////////
		}
		else												  //!< 90% È®·ü·Î ±âº»
		{
			m_eBlockItem = E_BLOCKITEM_NONE;
		}
	}
	else												  //!< 90% È®·ü·Î ±âº»
	{
		m_eBlockItem = E_BLOCKITEM_NONE;
		
	}
	
	m_pFreeze->setVisible(m_bFreezed);
	m_pBlock_Freeze->setVisible(m_bFreezed);
	m_pBlock_Angry->setVisible(false);


	m_pFreeze->setPosition(ccp((m_stPos.x + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y + m_stOffsetPos.y)  * D_SCALE_HEIGHT));
	//!< m_pErosoin->setPosition(m_stPos);
	//m_pErosoin->setPositionY(m_stPos.y - (D_BLOCK_HEIGHT * m_fErosionOffsetY));
	//!< m_pErosoin_Border->setPosition(m_stPos);
	m_pSelect->setPosition(ccp((m_stPos.x + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y + m_stOffsetPos.y) * D_SCALE_HEIGHT));
		
	m_pBlock->setPosition(ccp( (m_stPos.x - 6.4f + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y - 6.4f + m_stOffsetPos.y) * D_SCALE_HEIGHT ));
	m_pBlock_Pause->setPosition(ccp( (m_stPos.x - 6.4f + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y - 6.4f + m_stOffsetPos.y) * D_SCALE_HEIGHT));
	m_pBlock_Freeze->setPosition(ccp( (m_stPos.x - 6.4f + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y - 6.4f + m_stOffsetPos.y) * D_SCALE_HEIGHT));
	m_pBlock_Angry->setPosition(ccp( (m_stPos.x - 6.4f + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y - 6.4f + m_stOffsetPos.y) * D_SCALE_HEIGHT));

}

void CBlock::CreateIt(stVec2i stIndex, E_BLOCKNUMBER eBlockNumber)
{
	char frameName[256];
	
	m_stOffsetPos = ccp(0,0);

	m_bLive = true;
	m_stIndex = stIndex;
	m_fNextDistance = 64.0f;
	

	m_stPos.x = D_LINE_START_X + (stIndex.m_nX * 64);
	m_stPos.y = D_LINE_START_Y - (stIndex.m_nY * 64);

	//m_stPos.x = 240;
	//m_stPos.y = 400;
	
	

	//Random = rand()%E_BLOCKNUMBER_MAX;
	m_eBlockNumber = eBlockNumber;
	
	
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
	m_fSpeed			= D_BLOCK_SPEED;
	m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
	m_fNowDistance		= 0.0f;
	m_fDistance			= 0.0f;

	m_fEye = 0.0f;

	m_eBlockState		= E_BLOCKSTATE_NONE;

	m_fErosionMaxTime = D_EROSIONTIME;
	m_fErosionTime = m_fErosionMaxTime;
	m_fErosionOffsetY = 0.0f;

	m_bFreezed = false;
	m_bDraged = false;
	m_bDolphinHited = false;


	m_bEye = false;

	/////////////////////////////////////////////////////
	m_pBlockAni = CCAnimation::animation();
	for(int j=0; j<4; j++) {
			sprintf(frameName, "Block_%d_%d.png",(int)m_eBlockNumber+1,j+1);
			m_pBlockAni->addSpriteFrameWithFileName(frameName);
	}
	m_pBlockAni->setDelayPerUnit(0.15f);
	m_pBlockAnt = CCAnimate::create(m_pBlockAni);
	m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
	//m_pBlock->setPosition( ccp(m_stPos.x, m_stPos.y));

	m_pBlock->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock->setScaleX(1.20f * D_SCALE_WIDTH);
	m_pBlock->setScaleY(1.20f * D_SCALE_HEIGHT);


	m_pThisScene->addChild(m_pBlock, 26);
	//m_pBlock->runAction(m_pBlockAnt);
	m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
	m_pBlock->setAnchorPoint(ccp(0.0,0.0));
	//m_pBlock->setScale(1.2f);
	//////////////////////////////////////////////////////
	sprintf(frameName, "Block_%d_1.png",(int)m_eBlockNumber+1);


	m_pBlock_Pause = CCSprite::create(frameName);

	//m_pBlock_Pause->setPosition( ccp(m_stPos.x, m_stPos.y) );
	m_pBlock_Pause->setAnchorPoint(ccp(0.0,0.0));
	//m_pBlock_Pause->setScale(1.2f);

	m_pBlock_Pause->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock_Pause->setScaleX(1.20f * D_SCALE_WIDTH);
	m_pBlock_Pause->setScaleY(1.20f * D_SCALE_HEIGHT);


	m_pThisScene->addChild(m_pBlock_Pause, 26);
	//////////////////////////////////////////////////////
	
	sprintf(frameName, "Block_%d_Freeze.png",(int)m_eBlockNumber+1);


	m_pBlock_Freeze = CCSprite::create(frameName);

	//m_pBlock_Freeze->setPosition( ccp(m_stPos.x, m_stPos.y) );
	m_pBlock_Freeze->setAnchorPoint(ccp(0.0,0.0));
	//m_pBlock_Freeze->setScale(1.2f);

	m_pBlock_Freeze->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock_Freeze->setScaleX(1.20f * D_SCALE_WIDTH);
	m_pBlock_Freeze->setScaleY(1.20f * D_SCALE_HEIGHT);

	m_pThisScene->addChild(m_pBlock_Freeze, 26);
	//////////////////////////////////////////////////////
	
	sprintf(frameName, "Block_%d_Angry.png",(int)m_eBlockNumber+1);


	m_pBlock_Angry = CCSprite::create(frameName);

	//m_pBlock_Angry->setPosition( ccp(m_stPos.x, m_stPos.y) );
	m_pBlock_Angry->setAnchorPoint(ccp(0.0,0.0));
	//m_pBlock_Angry->setScale(1.2f);

	m_pBlock_Angry->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
	m_pBlock_Angry->setScaleX(1.20f * D_SCALE_WIDTH);
	m_pBlock_Angry->setScaleY(1.20f * D_SCALE_HEIGHT);


	m_pThisScene->addChild(m_pBlock_Angry, 26);
	//////////////////////////////////////////////////////


	m_pBlock->setVisible(true);
	m_pBlock_Pause->setVisible(true);

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
	int nBlockItemRandom = rand()%10000; //0 ~ 9999

	if(nBlockItemRandom >= 0 && nBlockItemRandom <= 400) //!< 10% È®·ü·Î ½ä¸Å
	{
		if(g_nSelectStage >= 7)
		{
			m_eBlockItem = E_BLOCKITEM_SLED;

			//////////////////////////////////////////////////////
			sprintf(frameName, "Item_%d.png",(int)m_eBlockItem);


			m_pItem = CCSprite::create(frameName);

			//m_pItem->setPosition( ccp(m_stPos.x, m_stPos.y) );
			m_pItem->setAnchorPoint(ccp(0.0,0.0));
			//m_pItem->setScale(1.0f);

			m_pItem->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
			m_pItem->setScaleX(1.00f * D_SCALE_WIDTH);
			m_pItem->setScaleY(1.00f * D_SCALE_HEIGHT);

			m_pItem->setOpacity(255 * 0.4f);
			m_pThisScene->addChild(m_pItem, 27);
			//////////////////////////////////////////////////////
		}
		else												  //!< 90% È®·ü·Î ±âº»
		{
			m_eBlockItem = E_BLOCKITEM_NONE;
		}

	}
	else if(nBlockItemRandom >= 0 && nBlockItemRandom <= 700) //!< 10% È®·ü·Î ¾óÀ½Á¶°¢
	{
		if(g_nSelectStage >= 4)
		{
			m_eBlockItem = E_BLOCKITEM_ICE;

			//////////////////////////////////////////////////////
			sprintf(frameName, "Item_%d.png",(int)m_eBlockItem);


			m_pItem = CCSprite::create(frameName);

			//m_pItem->setPosition( ccp(m_stPos.x, m_stPos.y) );
			m_pItem->setAnchorPoint(ccp(0.0,0.0));
			//m_pItem->setScale(1.0f);

			m_pItem->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y  * D_SCALE_HEIGHT) );
			m_pItem->setScaleX(1.00f * D_SCALE_WIDTH);
			m_pItem->setScaleY(1.00f * D_SCALE_HEIGHT);

			m_pItem->setOpacity(255 * 0.4f);
			m_pThisScene->addChild(m_pItem, 27);
			//////////////////////////////////////////////////////
		}
		else												  //!< 90% È®·ü·Î ±âº»
		{
			m_eBlockItem = E_BLOCKITEM_NONE;
		}
	}
	else												  //!< 90% È®·ü·Î ±âº»
	{
		m_eBlockItem = E_BLOCKITEM_NONE;
	}
	m_pFreeze->setVisible(m_bFreezed);
	m_pBlock_Freeze->setVisible(m_bFreezed);
	m_pBlock_Angry->setVisible(false);

	m_pFreeze->setPosition(ccp((m_stPos.x + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y + m_stOffsetPos.y)  * D_SCALE_HEIGHT));
	//!< m_pErosoin->setPosition(m_stPos);
	//m_pErosoin->setPositionY(m_stPos.y - (D_BLOCK_HEIGHT * m_fErosionOffsetY));
	//!< m_pErosoin_Border->setPosition(m_stPos);
	m_pSelect->setPosition(ccp((m_stPos.x + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y + m_stOffsetPos.y) * D_SCALE_HEIGHT));
		
	m_pBlock->setPosition(ccp( (m_stPos.x - 6.4f + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y - 6.4f + m_stOffsetPos.y) * D_SCALE_HEIGHT ));
	m_pBlock_Pause->setPosition(ccp( (m_stPos.x - 6.4f + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y - 6.4f + m_stOffsetPos.y) * D_SCALE_HEIGHT));
	m_pBlock_Freeze->setPosition(ccp( (m_stPos.x - 6.4f + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y - 6.4f + m_stOffsetPos.y) * D_SCALE_HEIGHT));
	m_pBlock_Angry->setPosition(ccp( (m_stPos.x - 6.4f + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y - 6.4f + m_stOffsetPos.y) * D_SCALE_HEIGHT));

}
//
//void CBlock::Init(CRootScene* pThisScene, E_BLOCKNUMBER eBlockNumber, stVec2i stIndex,int nCreateBlockNumber)
//{
//	m_stIndex = stIndex;
//
//	m_stPos.m_fX = D_LINE_START_X + (stIndex.m_fX * 64);
//	m_stPos.m_fY = D_LINE_START_Y - (stIndex.m_fY * 64);
//
//	m_eBlockNumber = eBlockNumber;
//
///*
//	m_pPlane = new CEMPlane();					
//	m_pPlane->SetSize(1.0f,	1.0f);					
//	m_pPlane->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
//	m_pPlane->SetLocalVec(0.0f, 0.0f);				
//	m_pPlane->SetOffset(0.0f, 0.0f);
//	m_pPlane->SetTexture(pThisScene, "Data/Image/Block/Block_"+ IntToEMString(m_eBlockNumber+1) + ".png");	
//	m_pPlane->SetFrustumCulling(true);				
//	m_pPlane->SetBoundingBoxCalc(true);				
//	m_pPlane->SetBlend(true);				
//	m_pPlane->SetShow(true);
//	m_pPlane->SetBackFaceCulling(false);
//	pThisScene->Commit(-2,nCreateBlockNumber, "ºí·Ï", m_pPlane);
//*/
//	m_pBlock = new CEMAnimation(3);			
//	m_pBlock->SetTime(0.15f);
//	m_pBlock->SetSize(1.0f,	1.0f);					
//	m_pBlock->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
//	m_pBlock->SetLocalVec(0.0f, 0.0f);				
//	m_pBlock->SetOffset(0.0f, 0.0f);
//	if((m_eBlockNumber+1) == 1)
//		m_pBlock->SetTexture(pThisScene,3, "Data/Image/Block/Block_1_1.png", "Data/Image/Block/Block_1_2.png", "Data/Image/Block/Block_1_3.png");	
//	else if((m_eBlockNumber+1) == 2)
//		m_pBlock->SetTexture(pThisScene,3, "Data/Image/Block/Block_2_1.png", "Data/Image/Block/Block_2_2.png", "Data/Image/Block/Block_2_3.png");	
//	else if((m_eBlockNumber+1) == 3)
//		m_pBlock->SetTexture(pThisScene,3, "Data/Image/Block/Block_3_1.png", "Data/Image/Block/Block_3_2.png", "Data/Image/Block/Block_3_3.png");	
//	else if((m_eBlockNumber+1) == 4)
//		m_pBlock->SetTexture(pThisScene,3, "Data/Image/Block/Block_4_1.png", "Data/Image/Block/Block_4_2.png", "Data/Image/Block/Block_4_3.png");	
//	
//
//	m_pBlock->SetFrustumCulling(true);				
//	m_pBlock->SetBoundingBoxCalc(true);				
//	m_pBlock->SetBlend(true);				
//	m_pBlock->SetShow(true);
//	m_pBlock->SetPause(true);
//	m_pBlock->SetBackFaceCulling(false);
//	pThisScene->Commit(-2,nCreateBlockNumber, "ºí·Ï", m_pBlock);
//
//
//
//
//
//	m_pSelect = new CEMPlane();					
//	m_pSelect->SetSize(1.0f, 1.0f);					
//	m_pSelect->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
//	m_pSelect->SetLocalVec(0.0f, 0.0f);				
//	m_pSelect->SetOffset(0.0f, 0.0f);
//	m_pSelect->SetTexture(pThisScene, "Data/Image/Block/Block_Select.png");	
//	m_pSelect->SetFrustumCulling(true);				
//	m_pSelect->SetBoundingBoxCalc(true);				
//	m_pSelect->SetBlend(true);				
//	m_pSelect->SetShow(false);
//	m_pSelect->SetBackFaceCulling(false);
//	m_pSelect->SetColor(1.0f,1.0f,1.0f,0.3f);
//	pThisScene->Commit(-5,nCreateBlockNumber, "¼±ÅÃµÊ", m_pSelect);
//
//	
//	m_pErosoin = new CEMPlane();					
//	m_pErosoin->SetSize(1.0f, 1.0f);					
//	m_pErosoin->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
//	m_pErosoin->SetLocalVec(0.0f, 0.0f);				
//	m_pErosoin->SetOffset(0.0f, 0.0f);
//	m_pErosoin->SetTexture(pThisScene, "Data/Image/Block/Block_Erosoin.png");	
//	m_pErosoin->SetFrustumCulling(true);				
//	m_pErosoin->SetBoundingBoxCalc(true);				
//	m_pErosoin->SetBlend(true);				
//	m_pErosoin->SetShow(true);
//	m_pErosoin->SetBackFaceCulling(false);
//	m_pErosoin->SetColor(1.0f,1.0f,1.0f,0.3f);
//	pThisScene->Commit(-5,nCreateBlockNumber, "Ä§½Ä·ü", m_pErosoin);
//
//	
//	m_pErosoin_Border = new CEMPlane();					
//	m_pErosoin_Border->SetSize(1.0f, 1.0f);					
//	m_pErosoin_Border->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
//	m_pErosoin_Border->SetLocalVec(0.0f, 0.0f);				
//	m_pErosoin_Border->SetOffset(0.0f, 0.0f);
//	m_pErosoin_Border->SetTexture(pThisScene, "Data/Image/Block/Block_Erosoin_Border.png");	
//	m_pErosoin_Border->SetFrustumCulling(true);				
//	m_pErosoin_Border->SetBoundingBoxCalc(true);				
//	m_pErosoin_Border->SetBlend(true);				
//	m_pErosoin_Border->SetShow(true);
//	m_pErosoin_Border->SetBackFaceCulling(false);
//	m_pErosoin_Border->SetColor(1.0f,1.0f,1.0f,0.5f);
//	pThisScene->Commit(-6,nCreateBlockNumber, "Ä§½Ä·üÆ²", m_pErosoin_Border);
//	
//	m_pFreeze = new CEMPlane();					
//	m_pFreeze->SetSize(1.0f, 1.0f);					
//	m_pFreeze->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
//	m_pFreeze->SetLocalVec(0.0f, 0.0f);				
//	m_pFreeze->SetOffset(0.0f, 0.0f);
//	m_pFreeze->SetTexture(pThisScene, "Data/Image/Block/Block_Freeze.png");	
//	m_pFreeze->SetFrustumCulling(true);				
//	m_pFreeze->SetBoundingBoxCalc(true);				
//	m_pFreeze->SetBlend(true);				
//	m_pFreeze->SetShow(true);
//	m_pFreeze->SetBackFaceCulling(false);
//	m_pFreeze->SetColor(1.0f,1.0f,1.0f,1.0f);
//	pThisScene->Commit(-4,nCreateBlockNumber, "¾óÀ½", m_pFreeze);
//
//	m_pItem_Sled = new CEMPlane();					
//	m_pItem_Sled->SetSize(1.0f, 1.0f);					
//	m_pItem_Sled->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
//	m_pItem_Sled->SetLocalVec(0.0f, 0.0f);				
//	m_pItem_Sled->SetOffset(0.0f, 0.0f);
//	m_pItem_Sled->SetTexture(pThisScene, "Data/Image/Block/Block_Item_Sled.png");	
//	m_pItem_Sled->SetFrustumCulling(true);				
//	m_pItem_Sled->SetBoundingBoxCalc(true);				
//	m_pItem_Sled->SetBlend(true);				
//	m_pItem_Sled->SetShow(false);
//	m_pItem_Sled->SetBackFaceCulling(false);
//	m_pItem_Sled->SetColor(1.0f,1.0f,1.0f,1.0f);
//	pThisScene->Commit(-4,nCreateBlockNumber, "Item_Sled", m_pItem_Sled);
//
//
//
//	m_fStartY			= m_stPos.m_fY;
//	m_fSpeed			= D_BLOCK_SPEED;
//	m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
//	m_fNowDistance		= 0.0f;
//	m_fDistance			= 0.0f;
//
//	m_fEye = 0.0f;
//
//	m_eBlockState		= E_BLOCKSTATE_NONE;
//
//	m_fErosionMaxTime = D_EROSIONTIME;
//	m_fErosionTime = m_fErosionMaxTime;
//	m_fErosionOffsetY = 0.0f;
//
//	m_bFreezed = false;
//	m_bDraged = false;
//	m_bDolphinHited = false;
//
//
//	m_bEye = false;
//
//	int nBlockItemRandom = CEMMath::RandomIntInRange(0,10000);
//
//	if(nBlockItemRandom >= 0 && nBlockItemRandom <= 500)
//	{
//		m_eBlockItem = E_BLOCKITEM_SLED;
//		m_pItem_Sled->SetShow(true);
//	}
//	else
//	{
//		m_eBlockItem = E_BLOCKITEM_NONE;
//		m_pItem_Sled->SetShow(false);
//	}
//}
void CBlock::Update(float dt, float fErosionSpeed)
{		
	if(m_bLive == true)
	{
		//!< m_pErosoin->setVisible(true);
		//!< _pErosoin_Border->setVisible(true);

		

		m_pFreeze->setVisible(m_bFreezed);
		m_pBlock_Freeze->setVisible(m_bFreezed);
		m_pBlock_Angry->setVisible(false);

		if(m_bFreezed == false)
		{
			m_fEye += dt;

		
			if(m_bEye == false && m_fEye >= 3.0f)
			{
				m_bEye = true;
				m_pBlock->getActionManager()->resumeTarget(m_pBlock);
				m_pBlock->setVisible(true);
				m_pBlock_Pause->setVisible(false);

				//m_pBlock->getActionManager()->resumeTarget(m_pBlockAnt);
			}
			if(m_bEye == true && m_fEye >= 3.75f + m_fEyeContact)
			{
				m_fEyeContact -= 0.2f;
				if(m_fEyeContact <= -0.6f)
				{
					m_fEyeContact = 0.0f;
				}
				m_fEye = 0.0f;
				m_bEye = false;
				m_pBlock->getActionManager()->pauseTarget(m_pBlock);
				m_pBlock->setVisible(false);
				m_pBlock_Pause->setVisible(true);
			}
		}
		else
		{
			m_pBlock->stopAction(m_pBlockAnt);
			m_pBlock_Pause->setVisible(false);
			m_pBlock_Freeze->setVisible(true);
		}

		if(m_fErosionTime <= (D_EROSIONTIME/2))
		{
			int nRandSeed = ((D_EROSIONTIME/2) - m_fErosionTime) * 10000;
			nRandSeed+=1;
			m_stOffsetPos.x = ( (float) ((rand()%nRandSeed) - (rand()%nRandSeed)) ) / 10000;
			
			m_pBlock_Pause->setVisible(false);
			m_pBlock_Angry->setVisible(true);
		}


		if(m_eBlockState == E_BLOCKSTATE_FALLING && m_bDraged == false)
		{
			if(m_fNowDistance < m_fDistance)
			{
				m_stPos.y -= (m_fSpeed * dt) ;
				m_fNowDistance += (m_fSpeed * dt) ;
				m_fSpeed += (m_fPlusSpeed * dt);
				if(m_fNowDistance >= m_fDistance)
				{
					m_stPos.y		    = m_fStartY - m_fDistance;
					m_fSpeed			= D_BLOCK_SPEED;
					m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
					m_fNowDistance		= 0.0f;
					m_fDistance			= 64.0f;
					m_eBlockState		= E_BLOCKSTATE_NONE;
				}
			}
		}
		else
		{
			/*if(Sled->m_bOnOff == true && Sled->m_bSledMoved == true)
			{
				Sled->m_fHp -= (dt * fErosionSpeed);
			}
			else 
			{*/
				if(m_stIndex.m_nY == D_BLOCKMAP_HEIGHT - 1)
				{
					m_fErosionTime -= (dt * fErosionSpeed);
				}
			//}
		}

		
	
		//!< m_pErosoin->setScaleY(m_fErosionTime/m_fErosionMaxTime);
		//m_fErosionOffsetY = (1.0f - (m_fErosionTime/m_fErosionMaxTime))/2;

		m_pFreeze->setPosition(ccp((m_stPos.x + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y + m_stOffsetPos.y)  * D_SCALE_HEIGHT));
		//!< m_pErosoin->setPosition(m_stPos);
		//m_pErosoin->setPositionY(m_stPos.y - (D_BLOCK_HEIGHT * m_fErosionOffsetY));
		//!< m_pErosoin_Border->setPosition(m_stPos);
		m_pSelect->setPosition(ccp((m_stPos.x + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y + m_stOffsetPos.y) * D_SCALE_HEIGHT));
		
		m_pBlock->setPosition(ccp( (m_stPos.x - 6.4f + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y - 6.4f + m_stOffsetPos.y) * D_SCALE_HEIGHT ));
		m_pBlock_Pause->setPosition(ccp( (m_stPos.x - 6.4f + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y - 6.4f + m_stOffsetPos.y) * D_SCALE_HEIGHT));
		m_pBlock_Freeze->setPosition(ccp( (m_stPos.x - 6.4f + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y - 6.4f + m_stOffsetPos.y) * D_SCALE_HEIGHT));
		m_pBlock_Angry->setPosition(ccp( (m_stPos.x - 6.4f + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y - 6.4f + m_stOffsetPos.y) * D_SCALE_HEIGHT));

		if(m_eBlockItem != E_BLOCKITEM_NONE)
		{
			m_pItem->setPosition(ccp((m_stPos.x + m_stOffsetPos.x) * D_SCALE_WIDTH, (m_stPos.y + m_stOffsetPos.y)* D_SCALE_HEIGHT));
		}
	//	m_pItem_Sled->setPosition(m_stPos);
	}
	else if(m_bLive == false)
	{
		m_pFreeze->setVisible(false);
		//!< m_pErosoin->setVisible(false);
		//!< m_pErosoin_Border->setVisible(false);
		m_pSelect->setVisible(false);
		
		// m_pBlock->setVisible(false);
		// m_pBlock_Pause->setVisible(false);
	}
}

void CBlock::Die()
{
	
	if(m_bLive == true)
	{
		m_pThisScene->removeChild(m_pBlock,true);
		m_pThisScene->removeChild(m_pBlock_Pause,true);
		m_pThisScene->removeChild(m_pBlock_Freeze,true);
		m_pThisScene->removeChild(m_pBlock_Angry,true);
		if(m_eBlockItem != E_BLOCKITEM_NONE)
		{
			m_pThisScene->removeChild(m_pItem,true);
			m_eBlockItem = E_BLOCKITEM_NONE;
		}
	}
	/*delete m_pBlockAni;
	delete m_pBlockAnt;*/

	m_bLive = false;

	m_pFreeze->setVisible(false);


	
	//m_pBlockAni->autorelease();
	//m_pBlockAnt->autorelease();
	//delete m_pBlockAni;
	//delete m_pBlockAnt;

	//!< m_pErosoin->setVisible(true);
	//!< m_pErosoin_Border->setVisible(true);
/*
	for(int i=0; i<E_BLOCKNUMBER_MAX ; i++)
	{
		m_pBlock[i]->setVisible(true);
		m_pBlock_Pause[i]->setVisible(true);
	}*/
	/*m_pBlock->setVisible(true);
	m_pBlock_Pause->setVisible(true);
*/
	m_pSelect->setVisible(false);

}
bool CBlock::HitTest(float nX, float nY)
{
	if(m_bLive == false)
		return false;
	if(nX >= m_stPos.x * D_SCALE_WIDTH && nX <= (m_stPos.x + D_BLOCK_WIDTH) * D_SCALE_WIDTH &&
		nY >= m_stPos.y * D_SCALE_HEIGHT && nY <= (m_stPos.y + D_BLOCK_HEIGHT) * D_SCALE_HEIGHT)
	{
		return true;
	}
	return false;
}


bool CBlock::IsErosoined()
{
	if(m_fErosionTime < 0)
	{
		return true;
	}
	return false;
}

void CBlock::ShowUpdate()
{
	if(m_bLive == false)
	{
		m_pFreeze->setVisible(false);
		//!< m_pErosoin->setVisible(false);
		//!< m_pErosoin_Border->setVisible(false);
		m_pSelect->setVisible(false);
		
		//m_pBlock->setVisible(false);
		//m_pBlock_Pause->setVisible(false);
		
	}
}

void CBlock::UseItem()
{
	m_pThisScene->removeChild(m_pItem,true);
	m_eBlockItem = E_BLOCKITEM_NONE;
}