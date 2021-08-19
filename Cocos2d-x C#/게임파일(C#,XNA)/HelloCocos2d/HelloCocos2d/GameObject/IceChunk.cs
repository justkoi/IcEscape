using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using cocos2d;
using HelloCocos2d.GameObject;
using HelloCocos2d.Library;


namespace HelloCocos2d.GameObject
{

    public enum E_BOMB_OPTION
    {
        E_BOMB_OPTION_NO,
        E_BOMB_OPTION_ONE, //!< 거울복사
        E_BOMB_OPTION_TWO, //!< 세쌍복사
    };

    public class CIceChunk
    {
	    public CCPoint m_stPos;
        public CCPoint m_stTargetPos;
        public CCSprite m_pPlane;

        public CCPoint m_stMoveSpeed;

        public float m_fG;
        public float m_fT;

	    //float m_fSpitTimer; //!<  튀기는 시간
	    //float m_fSpitDistance; //!< 튀기는 Y축 이동량 누적

        public bool m_bHited;
        public float m_fAlphaTimer;

        public E_BOMB_OPTION m_eBombOption;
        public float m_fBombTimer;
        public float m_fBombTime; //!< 폭발시간
        public int m_nTickNumber;//!< 폭발 튀기는 횟수 현재






        public void Init(CCLayer pThisScene, CCPoint stPos, E_BOMB_OPTION eBombOption, int nTickNumber, Random r)
        {
            m_stPos = new CCPoint(0, 0);
            m_stTargetPos = new CCPoint(0, 0);
            m_stMoveSpeed = new CCPoint(0, 0);


            m_stPos = stPos;
            m_fG = 9.8f;
            m_fT = 0.01f;

	        m_fBombTimer = 0.0f;
	        m_nTickNumber = nTickNumber;
	        m_fBombTime = 1.2f - (0.16f * nTickNumber);
	        m_stTargetPos = new CCPoint(240,100);
	        m_eBombOption = eBombOption;
            m_stMoveSpeed.x = (-(float)(r.Next(0, 200)) / 100) + 1.0f;
	        /*if(m_stPos.x > m_stTargetPos.x)
		        m_stMoveSpeed.x = -1.0f;
	        else if(m_stPos.x < m_stTargetPos.x)
		        m_stMoveSpeed.x = 1.0f;*/
	        if(m_stPos.y > m_stTargetPos.y)
		        m_stMoveSpeed.y = (-(float)(r.Next(0,270))/100) + - 1.2f;
	        else if(m_stPos.y < m_stTargetPos.y)
		        m_stMoveSpeed.y = (-(float)(r.Next(0,270))/100) + - 1.2f;

            m_pPlane = CCSprite.spriteWithFile("IceChunk");
            m_pPlane.position = m_stPos;
            m_pPlane.scaleX = (1.00f + (m_nTickNumber * 0.2f));
            m_pPlane.scaleY = (1.00f + (m_nTickNumber * 0.2f));
            m_pPlane.anchorPoint = new CCPoint(0.0f, 0.0f);
            pThisScene.addChild(m_pPlane, 31);


	        m_fAlphaTimer= 0.0f;
	        m_bHited = false;
        //	m_fSpitTimer = 0.0f;
	        //m_fSpitDistance = -32.0f;
        }
        public void Update(float dt)
        {
            if (m_stMoveSpeed.y <= -4.5f)
            {
                m_stMoveSpeed.y = -4.0f;
            }
            if ((int)m_eBombOption >= 1 && m_nTickNumber >= 1)
            {
                m_fBombTimer += dt;
                if (m_fBombTimer >= m_fBombTime)
                {
                    m_fBombTimer = m_fBombTime;
                }
            }
            if (m_bHited == true)
            {
                m_fAlphaTimer += dt;
                if (m_fAlphaTimer >= 1.0f)
                    m_fAlphaTimer = 1.0f;
            }
            if (m_bHited == false)
            {
                /*m_fSpitTimer += dt;

                if(m_fSpitTimer >= 1.5f)
                {
                    m_fSpitTimer = 0.0f;
                    m_stMoveSpeed.y = (-(float)(rand()%220)/100) + - 0.8f;
                }*/
                /*if(m_fSpitDistance <= -64.0f)
                {
                    m_fSpitDistance = 0.0f;
                    m_stMoveSpeed.y = (-(float)(rand()%120)/100) + - 0.4f;
                    m_stMoveSpeed.x *= 0.88f;
                }*/

                if (m_stPos.x < 30.0f)
                {
                    m_stPos.x = 30.0f;
                    m_stMoveSpeed.x *= -1;
                }
                if (m_stPos.x > 450.0f)
                {
                    m_stPos.x = 450.0f;
                    m_stMoveSpeed.x *= -1;
                }
                if (m_stPos.y > 710.0f)
                {
                    m_stPos.y = 710.0f;
                }
                m_stPos.x += m_stMoveSpeed.x * dt * 60;
                //m_stMoveSpeed.x += m_fG * m_fT * 0.2f * dt * 60;

                if (m_stPos.y < m_stTargetPos.y)
                {
                    m_stPos.y += m_stMoveSpeed.y * dt * 60;
                    //			m_fSpitDistance += m_stMoveSpeed.y * dt * 60;
                    m_stMoveSpeed.y += m_fG * m_fT * dt * 60;
                }
                else if (m_stPos.y > m_stTargetPos.y)
                {
                    m_stPos.y -= m_stMoveSpeed.y * dt * 60;
                    //	m_fSpitDistance -= m_stMoveSpeed.y * dt * 60;
                    m_stMoveSpeed.y += m_fG * m_fT * dt * 60;
                }
            }
            if (Hited() == true && m_bHited == false)
            {
                m_bHited = true;
            }


            m_pPlane.position = new CCPoint(m_stPos.x, m_stPos.y);
            //m_pPlane->setPosition(ccp(m_stPos.x * D_SCALE_WIDTH, m_stPos.y * D_SCALE_HEIGHT));
            m_pPlane.Opacity = (byte)(255 - (255 * m_fAlphaTimer));
            //m_pPlane->setOpacity(255 - (255 * m_fAlphaTimer));
            m_pPlane.rotation = (int)((m_stPos.x * 2) + (m_stPos.y * 1)) % 360;
            //m_pPlane->setRotation((int)((m_stPos.x * 5) + (m_stPos.y * 3)) % 360);

        }
        public void Exit()
        {

        }

        public bool Hited()
        {
            if (// m_stPos.x > m_stTargetPos.x - 5 && m_stPos.x < m_stTargetPos.x + 5 &&
                    m_stPos.y > m_stTargetPos.y - 5 && m_stPos.y < m_stTargetPos.y + 5)
            {
                return true;
            }
            return false;
        }
        public bool Finished()
        {
            if (m_fAlphaTimer >= 1.0f)
            {
                return true;
            }
            return false;
        }
        public bool ReadyToBomb()
        {
            if (m_fBombTimer >= m_fBombTime)
            {
                return true;
            }
            return false;
        }//!< 폭발레디알림
    };

}
