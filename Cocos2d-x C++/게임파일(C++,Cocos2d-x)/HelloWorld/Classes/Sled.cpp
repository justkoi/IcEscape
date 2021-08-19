#include "stdafx.h" 

void CSled::Init(CCLayer* pThisScene)
{
	char frameName[256];

	m_pThisScene = pThisScene;
	
	m_stPos.x = (D_LINE_START_X + (8 * 64) ) * D_SCALE_WIDTH;
	m_stPos.y = D_LINE_START_Y - (11 * 64) +20;

	/////////////////////////////////////////////////////
	m_pSledAni = CCAnimation::animation();
	for(int j=0; j<4; j++) {
			sprintf(frameName, "Sled_%d.png",j+1);
			m_pSledAni->addSpriteFrameWithFileName(frameName);
	}
	m_pSledAni->setDelayPerUnit(0.15f);
	m_pSledAnt = CCAnimate::create(m_pSledAni);
	m_pSled = CCSprite::spriteWithFile("NewSprite.png");
	m_pSled->setPosition( ccp(m_stPos.x, m_stPos.y));
	m_pThisScene->addChild(m_pSled, 31);
	//m_pBlock->runAction(m_pBlockAnt);
	m_pSled->runAction(CCRepeatForever::actionWithAction(m_pSledAnt));
	m_pSled->setAnchorPoint(ccp(0.0,0.0));
	m_pSled->setScaleX(1.2f * D_SCALE_WIDTH);
	m_pSled->setScaleY(1.2f * D_SCALE_HEIGHT);
	//////////////////////////////////////////////////////


	m_fMoveSpeed = 250.0f;
}
void CSled::Update(float dt, CBlock * BlockList, list<CIceChunk*>* IceChunkList, CEffectManager* EffectManager,CocosDenshion::SimpleAudioEngine *Sae)
{
	if(g_bPause == true)
	{
		m_pSled->getActionManager()->pauseTarget(m_pSled);
	}
	else if(g_bPause == false)
	{
		m_pSled->getActionManager()->resumeTarget(m_pSled);
	}

	if(g_bPause == true)
		return;


	m_stPos.x -= m_fMoveSpeed * dt;
	m_pSled->setPosition( ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y * D_SCALE_HEIGHT) );
	for(int i=0; i<D_BLOCKMAP_WIDTH * D_BLOCKMAP_HEIGHT; i++)
	{
		if(BlockList[i].m_stIndex.m_nY != D_BLOCKMAP_HEIGHT - 1)
			continue;
		if(BlockList[i].m_bLive == true && BlockList[i].m_bFreezed == false)
		{
			if(HitTest(BlockList[i].m_stPos,ccp(64,64),ccp(m_stPos.x + 64,64),ccp(64,64)) == true)
			{
				BlockList[i].m_bFreezed = true;
				BlockList[i].m_fErosionMaxTime += D_FREEZETIME;
				BlockList[i].m_fErosionTime += D_FREEZETIME;

				BlockList[i].m_pSelect->setVisible(false);
				BlockList[i].m_bDraged = false;
				g_nScore += (D_SCORE_ICEBLOCK);

				for(int j=0; j<2; j++)
				{
					CIceChunk* pTempIce = new CIceChunk();
					pTempIce->Init(m_pThisScene,ccp(BlockList[i].m_stPos.x +( D_BLOCK_WIDTH/2),BlockList[i].m_stPos.y+( D_BLOCK_HEIGHT/2)),E_BOMB_OPTION_NO,1);
					IceChunkList->push_back(pTempIce);
				}
				EffectManager->Insert(1,BlockList[i].m_stPos.x -( D_BLOCK_WIDTH/2),BlockList[i].m_stPos.y-( D_BLOCK_HEIGHT/2));
				Sae->playEffect("Ice.wav");		
				
			
			}
		}
	}
}
bool CSled::Played()
{
	if(m_stPos.x < D_LINE_START_X - 256)
	{
		return true;
	}
	return false;
}
void CSled::Exit()
{
	m_pThisScene->removeChild(m_pSled,true);
}

bool CSled::HitTest(CCPoint stPos1, CCPoint stPixel1, CCPoint stPos2, CCPoint stPixel2)
{
	float x1 = stPos1.x - (stPixel1.x/2);
	float x2 = stPos2.x - (stPixel2.x/2);
	float y1 = stPos1.y - (stPixel1.y/2);
	float y2 = stPos2.y - (stPixel2.y/2);
	float w = 0;
	float h = 0;

	if(x1 <= x2)
	{
		w = stPixel1.x;
	}
	else
	{
		w = stPixel2.x;
	}
	
	if(y1 <= y2)
	{
		h = stPixel1.y;
	}
	else
	{
		h = stPixel2.y;
	}

	if(abs(x1-x2) <= w && abs(y1-y2) <= h)
		return true;
	else
		return false;
}