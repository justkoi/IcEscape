using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using cocos2d;


namespace HelloCocos2d.GameObject
{
    public class CSeaLevel
    {
	    public CCSprite m_pSeaLevel;
        public CCPoint m_stPos;

        public float m_fSeaLevel_Target; //!< 목표 점수
        public float m_fSeaLevel;
        public float m_fSeaLevelMax;

        public float m_fSpeed;

        public void Init(CCLayer pThisScene)
        {
            m_stPos = new CCPoint(0, 0);
            m_stPos.x = 240;
	        m_stPos.y = -160;

            m_pSeaLevel = CCSprite.spriteWithFile("SeaLevel");
            m_pSeaLevel.position = new CCPoint(240, -160);
            m_pSeaLevel.scaleX = 1.00f;
            m_pSeaLevel.scaleY = 1.00f;
            m_pSeaLevel.Opacity = (byte)(255.0f * 0.8f);
            m_pSeaLevel.visible = true;
            pThisScene.addChild(m_pSeaLevel, 30);


	        m_fSeaLevel = 0.0f;
	        m_fSeaLevel_Target = 0.0f;
	        m_fSeaLevelMax = 225.0f;
	        m_fSpeed = 3.0f;
        }
        public void Update(float dt)
        {
            m_stPos.y = -160 + ((m_fSeaLevel / m_fSeaLevelMax) * 585.0f);



            m_pSeaLevel.position = new CCPoint(m_stPos.x, m_stPos.y); // setPosition(ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y * D_SCALE_HEIGHT));

            //m_pSeaLevel.Color.r = (byte)255.0f;
            //m_pSeaLevel.Color.g = (byte)(255 * (1.0f - (m_fSeaLevel / m_fSeaLevelMax)));
            //m_pSeaLevel.Color.b = (byte)(255 * (1.0f - (m_fSeaLevel / m_fSeaLevelMax)));

            m_pSeaLevel.Color = new ccColor3B((byte)255.0f, (byte)(255 * (1.0f - (m_fSeaLevel / m_fSeaLevelMax))), (byte)(255 * (1.0f - (m_fSeaLevel / m_fSeaLevelMax))));
            

            if (m_fSeaLevel < m_fSeaLevel_Target)
            {
                m_fSeaLevel += ((m_fSeaLevel_Target - m_fSeaLevel) / (40 * (60 * dt)));
                {
                    if (m_fSeaLevel > m_fSeaLevel_Target)
                    {
                        m_fSeaLevel = m_fSeaLevel_Target;
                    }
                }
            }
            else if (m_fSeaLevel > m_fSeaLevel_Target)
            {
                m_fSeaLevel -= ((m_fSeaLevel - m_fSeaLevel_Target) / (40 * (60 * dt)));
                {
                    if (m_fSeaLevel < m_fSeaLevel_Target)
                    {
                        m_fSeaLevel = m_fSeaLevel_Target;
                    }
                }
            }

            Check();
        }
        public void Exit()
        {

        }
        public void Check()
        {
            if (m_fSeaLevel > m_fSeaLevelMax)
            {
                m_fSeaLevel = m_fSeaLevelMax;
            }
            if (m_fSeaLevel < 0.0f)
            {
                m_fSeaLevel = 0.0f;
            }

            if (m_fSeaLevel_Target > m_fSeaLevelMax)
            {
                m_fSeaLevel_Target = m_fSeaLevelMax;
            }
            if (m_fSeaLevel_Target < 0.0f)
            {
                m_fSeaLevel_Target = 0.0f;
            }
        }
        public void SetSeaLevelMax(float fSeaLevelMax)
        {
            m_fSeaLevelMax = fSeaLevelMax;
        }
        public bool Warning()
        {
            if (m_fSeaLevel >= m_fSeaLevelMax * 0.85f)
            {
                return true;
            }
            return false;
        }

    };

}
