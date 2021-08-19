#include "stdafx.h"

void CSeaLevel::Init(CCLayer* pThisScene)
{
	
	m_stPos.x = 240;
	m_stPos.y = -160;

	m_pSeaLevel = CCSprite::create("SeaLevel.png");
    m_pSeaLevel->setPosition( m_stPos );
	m_pSeaLevel->setScaleX(1.00f * D_SCALE_WIDTH);
	m_pSeaLevel->setScaleY(1.00f * D_SCALE_HEIGHT);
	m_pSeaLevel->setVisible(true);
	m_pSeaLevel->setOpacity(255 * 0.6f);
    pThisScene->addChild(m_pSeaLevel, 27); //!>, Àá°ÜÀÕÀ½ 27

	m_fSeaLevel = 0.0f;
	m_fSeaLevel_Target = 0.0f;
	m_fSeaLevelMax = 225.0f;
	m_fSpeed = 3.0f;

}
void CSeaLevel::Update(float dt)
{

	m_stPos.y = -160 + ((m_fSeaLevel/m_fSeaLevelMax) * 585.0f);



    m_pSeaLevel->setPosition( ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y * D_SCALE_HEIGHT) );

	if( (m_fSeaLevel/m_fSeaLevelMax) >= 0.9f )
	{
		m_pSeaLevel->setColor(ccc3(255,255 * (1.0f - (m_fSeaLevel/m_fSeaLevelMax)), 255 * (1.0f - (m_fSeaLevel/m_fSeaLevelMax)))); 
	}
	else
	{
		m_pSeaLevel->setColor(ccc3(255,255 * (1.0f - (m_fSeaLevel/m_fSeaLevelMax)), 255 * (1.0f - (m_fSeaLevel/m_fSeaLevelMax)))); 
	}
	

	if(m_fSeaLevel < m_fSeaLevel_Target)
	{
		m_fSeaLevel += ((m_fSeaLevel_Target - m_fSeaLevel)/(40 * (60 * dt)));
		{
			if(m_fSeaLevel > m_fSeaLevel_Target)
			{
				m_fSeaLevel = m_fSeaLevel_Target;
			}
		}
	}
	else if(m_fSeaLevel > m_fSeaLevel_Target)
	{
		m_fSeaLevel -= ((m_fSeaLevel - m_fSeaLevel_Target)/(40 * (60 * dt)));
		{
			if(m_fSeaLevel < m_fSeaLevel_Target)
			{
				m_fSeaLevel = m_fSeaLevel_Target;
			}
		}
	}
	
	Check();


}
void CSeaLevel::Exit()
{

}

void CSeaLevel::Check()
{
	if(m_fSeaLevel > m_fSeaLevelMax)
	{
		m_fSeaLevel = m_fSeaLevelMax;
	}
	if(m_fSeaLevel < 0.0f)
	{
		m_fSeaLevel = 0.0f;
	}

	if(m_fSeaLevel_Target > m_fSeaLevelMax)
	{
		m_fSeaLevel_Target = m_fSeaLevelMax;
	}
	if(m_fSeaLevel_Target < 0.0f)
	{
		m_fSeaLevel_Target = 0.0f;
	}
}
void CSeaLevel::SetSeaLevelMax(float fSeaLevelMax)
{
	m_fSeaLevelMax = fSeaLevelMax;
}
bool CSeaLevel::Warning()
{
	if( m_fSeaLevel >= m_fSeaLevelMax * 0.85f )
	{
		return true;
	}
	return false;
}