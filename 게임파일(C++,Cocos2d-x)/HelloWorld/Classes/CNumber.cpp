#include "stdafx.h"


void CNumber::Init(CCLayer* pThisScene, CCPoint stSize, int nNumber, CCPoint stPos, int nLayer)
{
	m_nNumber = nNumber;
	m_stPos = stPos;
	m_pThisScene = pThisScene;
	m_nLayer = nLayer;
	m_stSize = stSize;

	m_bVisible = true;

	SetNumber(m_nNumber);
	SetVisible(m_bVisible);
}
void CNumber::Update(float dt)
{
	if(m_nNumber < 0)
	{
		m_nNumber = 0;
	}
	
	if(m_nTargetNumber < 0)
	{
		m_nTargetNumber = 0;
	}

	if(m_nNumber < m_nTargetNumber)
	{
		m_nNumber++;
		SetNumber(m_nNumber);
		if(m_nNumber > m_nTargetNumber)
		{
			m_nNumber = m_nTargetNumber;
		}
	}

	SetVisible(m_bVisible);
}

void CNumber::SetPositionY(float fPosY)
{
	m_stPos.y = fPosY;
	vector<CCSprite*>::iterator it;
	for(it = m_pNumberList.begin(); it != m_pNumberList.end(); it++)
	{
		(*it)->setPositionY( m_stPos.y );
	}
}
void CNumber::Exit()
{

}

void CNumber::SetNumber(int nNumber)
{
	char strTemp[256];
	int nCount = 0;
	int nCountNumber = 0;

	
	m_nNumber = nNumber;

	if(m_nNumber < 0)
	{
		m_nNumber = 0;
	}


	nCountNumber = m_nNumber;


	vector<CCSprite*>::iterator it;
	if(m_pNumberList.size() >= 1)
	{
		for(it = m_pNumberList.begin(); it != m_pNumberList.end();)
		{
			m_pThisScene->removeChild((*it),true);
			it = m_pNumberList.erase(it);
		}
	}
	m_pNumberList.clear();
	do 
	{
		sprintf(strTemp,"%d.png",(int)nCountNumber%10);
		CCSprite* m_pTemp = CCSprite::create(strTemp);
		m_pTemp->setPositionX( m_stPos.x - ((30*m_stSize.x) * nCount) );
		m_pTemp->setPositionY( m_stPos.y );
		m_pTemp->setScaleX(m_stSize.x);
		m_pTemp->setScaleY(m_stSize.y);
		m_pTemp->setVisible(m_bVisible);
		m_pThisScene->addChild(m_pTemp, m_nLayer); //!>, Àá°ÜÀÕÀ½ 27
		m_pNumberList.push_back(m_pTemp);
		nCount++;
	}while((nCountNumber /= 10) > 0);

	nCount-=1;

	if(nCount >= 1)
	{
		for(it = m_pNumberList.begin(); it != m_pNumberList.end(); it++)
		{
			(*it)->setPositionX( (*it)->getPositionX() + (((30*m_stSize.x) * (nCount))/2));
		}
	}
}

void CNumber::EffectNumber(int nNumber)
{
	m_nTargetNumber = nNumber;
}
void CNumber::SetSize(CCPoint stSize)
{
	m_stSize = stSize;
}
void CNumber::SetVisible(bool bVisible)
{
	vector<CCSprite*>::iterator it;
	m_bVisible = bVisible;
	if(m_pNumberList.size() >= 1)
	{
		for(it = m_pNumberList.begin(); it != m_pNumberList.end(); it++)
		{
			(*it)->setVisible(m_bVisible);
		}
	}
}