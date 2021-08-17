#include "stdafx.h"



void CIce::Init(CCLayer* pThisScene, CCPoint stPos)
{
	m_stPos = stPos;

	m_fG = 9.8f;
	m_fT = 0.01f;

	m_stTargetPos = ccp(240,700);

	m_stMoveSpeed.x = (float)(rand()%200 - 100)/100;

	if(m_stPos.y > m_stTargetPos.y)
		m_stMoveSpeed.y = (-(float)(rand()%270)/100) + - 3.2f;
	else if(m_stPos.y < m_stTargetPos.y)
		m_stMoveSpeed.y = (-(float)(rand()%270)/100) + - 3.2f;
	

	m_pPlane = CCSprite::create("IceChunk.png");
    m_pPlane->setPosition( m_stPos );
	m_pPlane->setScaleX(2.00f * D_SCALE_WIDTH);
	m_pPlane->setScaleY(2.00f * D_SCALE_HEIGHT);
	m_pPlane->setVisible(true);
    pThisScene->addChild(m_pPlane, 29);

	m_fAlphaTimer= 0.0f;
	m_bHited = false;
//	m_fSpitTimer = 0.0f;
	//m_fSpitDistance = -32.0f;


}
void CIce::Update(float dt)
{
	
	if(m_stMoveSpeed.y <= -4.5f)
	{
		m_stMoveSpeed.y = -4.0f;
	}
	
	if(m_bHited == true)
	{
		m_fAlphaTimer += dt;
		if(m_fAlphaTimer >= 1.0f)
			m_fAlphaTimer = 1.0f;
	}
	if(m_bHited == false)
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

		if(m_stPos.x < 30.0f)
		{
			m_stPos.x = 30.0f;
			m_stMoveSpeed.x *= -1;
		}
		if(m_stPos.x > 450.0f)
		{
			m_stPos.x = 450.0f;
			m_stMoveSpeed.x *= -1;
		}
		if(m_stPos.y > 710.0f)
		{
			m_stPos.y = 710.0f;
		}
		m_stPos.x += m_stMoveSpeed.x * dt * 60;
		m_stMoveSpeed.x += m_fG * m_fT * 0.2f * dt * 60;

		if(m_stPos.y < m_stTargetPos.y)
		{
			m_stPos.y += m_stMoveSpeed.y * dt * 60;
//			m_fSpitDistance += m_stMoveSpeed.y * dt * 60;
			m_stMoveSpeed.y += m_fG * m_fT * dt * 60;
		}
		else if(m_stPos.y > m_stTargetPos.y)
		{
			m_stPos.y -= m_stMoveSpeed.y * dt * 60;
		//	m_fSpitDistance -= m_stMoveSpeed.y * dt * 60;
			m_stMoveSpeed.y += m_fG * m_fT * dt * 60;
		}
	}
	if(Hited() == true && m_bHited == false)
	{
		m_bHited = true;
	}
	

	m_pPlane->setPosition( ccp( m_stPos.x * D_SCALE_WIDTH, m_stPos.y * D_SCALE_HEIGHT));
	m_pPlane->setOpacity(255 - (255 * m_fAlphaTimer));
	m_pPlane->setRotation((int)((m_stPos.x*2) + (m_stPos.y*0.2))%360);
}
void CIce::Exit()
{

}
bool CIce::Hited()
{
	if(// m_stPos.x > m_stTargetPos.x - 5 && m_stPos.x < m_stTargetPos.x + 5 &&
		m_stPos.y > m_stTargetPos.y - 5 && m_stPos.y < m_stTargetPos.y + 5 )
	{
		return true;
	}
	return false;
}
bool CIce::Finished()
{
	if(m_fAlphaTimer >= 1.0f)
	{
		return true;
	}
	return false;
}