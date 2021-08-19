
#include "stdafx.h" 

void CFish::Init(CCLayer* pThisScene)
{
	char frameName[256];
	m_pThisScene = pThisScene;
	m_pFishAni = CCAnimation::animation();
	for(int j=0; j<6; j++) {
			sprintf(frameName, "Fish_%d.png",j+1);
			m_pFishAni->addSpriteFrameWithFileName(frameName);
	}
	m_pFishAni->setDelayPerUnit(0.34f);
	m_pFishAnt = CCAnimate::create(m_pFishAni);
	m_pFish = CCSprite::spriteWithFile("Fish_1.png");
	m_pFish->setPosition( ccp(240 * D_SCALE_WIDTH, 400 * D_SCALE_HEIGHT));
	m_pFish->setScaleX(1.0f * D_SCALE_WIDTH);
	m_pFish->setScaleY(1.0f * D_SCALE_HEIGHT);
	m_pThisScene->addChild(m_pFish, 30);
	//m_pBlock->runAction(m_pBlockAnt);
	m_pFish->runAction(CCRepeatForever::actionWithAction(m_pFishAnt));
	m_pFish->setAnchorPoint(ccp(0.0,0.0));

	m_fMoveSpeedX = 80.0f;
	m_fMoveSpeedY = 300.0f;

	m_fG = 9.8f;
	m_fT = 35;
	m_stPos = ccp( 240, 100 );

	m_pFish->setPosition(ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y * D_SCALE_HEIGHT));

}

void CFish::Update(float dt, CBlock * BlockList, CEffectManager* EffectManager,CocosDenshion::SimpleAudioEngine *Sae )
{
	
	if(g_bPause == true)
	{
		m_pFish->getActionManager()->pauseTarget(m_pFish);
	}
	else if(g_bPause == false)
	{
		m_pFish->getActionManager()->resumeTarget(m_pFish);
	}

	if(g_bPause == true)
		return;

	m_stPos.x -= m_fMoveSpeedX * dt;
	m_stPos.y += m_fMoveSpeedY * dt;

	m_fMoveSpeedY -= m_fG * m_fT * dt;
	
	m_pFish->setPosition(ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y * D_SCALE_HEIGHT));
	for(int i=0; i<D_BLOCKMAP_WIDTH * D_BLOCKMAP_HEIGHT; i++)
	{
		if(BlockList[i].m_bFreezed == true && HitTest(BlockList[i].m_stPos,ccp(64,64),m_stPos,ccp(64,64)) == true)
		{
			BlockList[i].m_bFreezed = false;

			if(BlockList[i].m_fErosionTime > BlockList[i].m_fErosionMaxTime - D_FREEZETIME)
			{
				BlockList[i].m_fErosionTime = BlockList[i].m_fErosionMaxTime - D_FREEZETIME;
				BlockList[i].m_fErosionMaxTime -= D_FREEZETIME;
			}
			else
			{
				BlockList[i].m_fErosionMaxTime -= D_FREEZETIME;
			}
			BlockList[i].m_pSelect->setVisible(false);
			BlockList[i].m_bDraged = false;
		}
	}
}

bool CFish::HitTest(CCPoint stPos1, CCPoint stPixel1, CCPoint stPos2, CCPoint stPixel2)
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