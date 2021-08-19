using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using cocos2d;


public class CNumber
{

    private List<CCSprite> m_pNumberList;//!< 보관될 넘버
    private int m_nNumber;//!< 표시할 숫자
    private int m_nTargetNumber;//!< 표시할 숫자
    private CCLayer m_pThisScene;
    private int m_nLayer;
    private bool m_bVisible;


    public CCPoint m_stPos;
    public CCPoint m_stSize;

    public void Init(CCLayer pThisScene, CCPoint stSize, int nNumber, CCPoint stPos, int nLayer)
    {
        m_stPos = new CCPoint();
        m_stSize = new CCPoint();
        m_pNumberList = new List<CCSprite>();

        m_nNumber = nNumber;
        m_stPos = stPos;
        m_pThisScene = pThisScene;
        m_nLayer = nLayer;
        m_stSize = stSize;

        m_bVisible = true;

        SetNumber(m_nNumber);
        SetVisible(m_bVisible);
    }
    public void Update(float dt)
    {
        if (m_nNumber < 0)
        {
            m_nNumber = 0;
        }

        if (m_nTargetNumber < 0)
        {
            m_nTargetNumber = 0;
        }

        if (m_nNumber < m_nTargetNumber)
        {
            m_nNumber++;
            SetNumber(m_nNumber);
            if (m_nNumber > m_nTargetNumber)
            {
                m_nNumber = m_nTargetNumber;
            }
        }

        SetVisible(m_bVisible);
    }

    public void SetNumber(int nNumber)
    {
        //char strTemp[256];
        int nCount = 0;
        int nCountNumber = 0;


        m_nNumber = nNumber;

        if (m_nNumber < 0)
        {
            m_nNumber = 0;
        }


        nCountNumber = m_nNumber;


        int nIt;
        if (m_pNumberList.Count >= 1)
        {
            for (nIt = 0; nIt < m_pNumberList.Count; nIt++)
            {
                m_pThisScene.removeChild(m_pNumberList[nIt], true);
                //m_pThisScene->removeChild((*it),true);
                //it = m_pNumberList.erase(it);
                //m_pNumberList.RemoveAt(nIt);
            }
        }
        m_pNumberList.Clear();
        do
        {


            //sprintf(strTemp,"%d.png",(int)nCountNumber%10);


            CCSprite m_pTemp = CCSprite.spriteWithFile(((int)nCountNumber % 10).ToString());
            m_pTemp.position = new CCPoint(m_stPos.x - ((30 * m_stSize.x) * nCount), m_stPos.y);


            // m_pTemp->setPositionX( m_stPos.x - ((30*m_stSize.x) * nCount) );
            // m_pTemp->setPositionY( m_stPos.y );
            m_pTemp.scaleX = m_stSize.x;
            m_pTemp.scaleY = m_stSize.y;

            //m_pTemp->setScaleX(m_stSize.x);
            //m_pTemp->setScaleY(m_stSize.y);
            //m_pTemp->setVisible(m_bVisible);

            m_pTemp.visible = m_bVisible;
            m_pThisScene.addChild(m_pTemp, m_nLayer);
            m_pNumberList.Add(m_pTemp);
            //m_pThisScene->addChild(m_pTemp, m_nLayer); //!>, 잠겨잇음 27
            //m_pNumberList.push_back(m_pTemp);


            nCount++;
        } while ((nCountNumber /= 10) > 0);

        nCount -= 1;

        if (nCount >= 1)
        {
            for (nIt = 0; nIt < m_pNumberList.Count; nIt++)
            {
                m_pNumberList[nIt].position = new CCPoint(m_pNumberList[nIt].position.x + (((30 * m_stSize.x) * (nCount)) / 2), m_stPos.y);

                //(*it)->setPositionX( (*it)->getPositionX() + (((30*m_stSize.x) * (nCount))/2));
            }
        }
    }
    public void SetSize(CCPoint stSize)
    {
        m_stSize = stSize;
    }
    public void SetVisible(bool bVisible)
    {
        int nCount = 0;
        m_bVisible = bVisible;
        if (m_pNumberList.Count >= 1)
        {
            for (nCount = 0; nCount < m_pNumberList.Count; nCount++)
            {
                m_pNumberList[nCount].visible = m_bVisible;
                // (*it)->setVisible(m_bVisible);
            }
        }
    }
    public void EffectNumber(int nNumber)
    {
        m_nTargetNumber = nNumber;
    }
    public void SetPositionY(float fPosY)
    {
        m_stPos = new CCPoint(m_stPos.x, fPosY);

        int nCount = 0;
        for (nCount = 0; nCount < m_pNumberList.Count; nCount++)
        {
            m_pNumberList[nCount].position = new CCPoint(m_stPos.x, m_stPos.y);
        }
    }
};