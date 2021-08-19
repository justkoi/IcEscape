using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using cocos2d;



namespace HelloCocos2d.Library
{
   
    public struct stAnimation
    {
	    public CCAnimation m_pBlockAni;
        public CCSprite m_pBlock;
        public int m_nIndex;
        public float m_fTimer;

        public void SetTimer(float fValue)
        {
            m_fTimer = fValue;
        }

        public void PlusTimer(float fValue)
        {
            m_fTimer += fValue;
        }
    };

    public class CEffectManager
    {
	    public CCLayer m_pThisScene;			//!< 출력 대상 신
	
	    public List<stAnimation> m_pEffectList;	//!< 모든 출력중인 이펙트 보관 STL LIST

        public void Init(CCLayer pThisScene)
        {
            m_pThisScene = pThisScene;
        }

        public void Insert(int nIndex, float fX, float fY, float fSizeW, float fSizeH)
        {

	        CCAnimation m_pBlockAni = CCAnimation.animation();
	        for(int j=0; j<10; j++) {
			        m_pBlockAni.addFrameWithFileName("Ice_"+(j+1).ToString());
	        }
	        m_pBlockAni.setDelay(0.07f);
	        CCActionInterval m_pBlockAnt = CCAnimate.actionWithAnimation(m_pBlockAni);
	        CCSprite m_pBlock = CCSprite.spriteWithFile("NewSprite.png");
	        m_pBlock.position = new CCPoint(fX, fY);
	        m_pBlock.scaleX = 1.00f * fSizeW;
            m_pBlock.scaleY = 1.00f * fSizeH;
	        m_pThisScene.addChild(m_pBlock, 25);
	        //m_pBlock->runAction(m_pBlockAnt);
            m_pBlock.runAction(CCRepeatForever.actionWithAction(m_pBlockAnt));
            m_pBlock.anchorPoint = new CCPoint(0.0f, 0.0f);

            ////////////////////////////////////////////////////


	        stAnimation pTempAni = new stAnimation();
	        pTempAni.m_pBlockAni = m_pBlockAni;
	        pTempAni.m_pBlock = m_pBlock;
	        pTempAni.m_nIndex = 1;
	        pTempAni.m_fTimer = 0.0f;
            m_pEffectList.Add(pTempAni);
	        //m_pEffectList.push_back(pTempAni);

        }
        public void Update(float dt)
        {
            if(m_pEffectList.Count >= 1)
	        {
		       // list<stAnimation*>::iterator it;
                int i = 0;
		        for(i = 0; i < m_pEffectList.Count; i++)
		        {
                    m_pEffectList[i].PlusTimer(dt);
                   // m_pEffectList.ElementAt(i).m_fTimer += dt;
			        if( m_pEffectList[i].m_fTimer >= 0.63f)
			        {
                        m_pThisScene.removeChild(m_pEffectList[i].m_pBlock, true);
				        //m_pThisScene->removeChild((*it)->m_pBlock,true);
				        //delete (*it)->m_pBlock;
				        //delete (*it)->m_pBlockAni;
				        //delete (*it);
				        //it = m_pEffectList.erase(it);
			        }
			        else
			        {
				        //it++;
			        }
		
		        }


	        }
        }
        public void Exit()
        {

        }
    };
}