#include "stdafx.h" 

void CEffectManager::Init(CCLayer* pThisScene)
{
	m_pThisScene = pThisScene;

}
void CEffectManager::Update(float dt)
{
	if(m_pEffectList.size() >= 1)
	{
		list<stAnimation*>::iterator it;
		for(it = m_pEffectList.begin(); it != m_pEffectList.end();)
		{
			(*it)->m_fTimer += dt;
			if((*it)->m_fTimer >= 0.63f)
			{
				m_pThisScene->removeChild((*it)->m_pBlock,true);
				//delete (*it)->m_pBlock;
				//delete (*it)->m_pBlockAni;
				delete (*it);
				it = m_pEffectList.erase(it);
			}
			else
			{
				it++;
			}
		
		}
	}
}
void CEffectManager::Insert(int nIndex, float fX, float fY, float fSizeW , float fSizeH)
{
	char frameName[256];
	CCAnimation* m_pBlockAni = CCAnimation::animation();
	for(int j=0; j<10; j++) {
			sprintf(frameName, "Ice_%d.png",j+1);
			m_pBlockAni->addSpriteFrameWithFileName(frameName);
	}
	m_pBlockAni->setDelayPerUnit(0.07f);
	CCActionInterval * m_pBlockAnt = CCAnimate::create(m_pBlockAni);
	CCSprite * m_pBlock = CCSprite::spriteWithFile("NewSprite.png");
	m_pBlock->setPosition( ccp(fX, fY));
	m_pBlock->setScaleX( fSizeW * D_SCALE_WIDTH);
	m_pBlock->setScaleY( fSizeH * D_SCALE_HEIGHT);
	m_pThisScene->addChild(m_pBlock, 25);
	//m_pBlock->runAction(m_pBlockAnt);
	m_pBlock->runAction(CCRepeatForever::actionWithAction(m_pBlockAnt));
	m_pBlock->setAnchorPoint(ccp(0.0,0.0));

	stAnimation* pTempAni = new stAnimation();
	pTempAni->m_pBlockAni = m_pBlockAni;
	pTempAni->m_pBlock = m_pBlock;
	pTempAni->m_nIndex = 1;
	pTempAni->m_fTimer = 0.0f;
	m_pEffectList.push_back(pTempAni);

	
}
