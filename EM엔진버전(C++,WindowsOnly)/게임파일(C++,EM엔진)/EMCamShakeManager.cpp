#include "stdafx.h"

void CEMCamShakeManager::Init(stEMVec3* TargetCamPos)
{
	m_TargetCamPos = TargetCamPos;
	m_nNowShakeNumber = 1;
	m_nMaxShakeNumber = 0;
	m_nNowRotNumber = 1;
	m_nMaxRotNumber = 0;

}

void CEMCamShakeManager::Update(float dt)
{
	
	if(m_eDerection == E_DERECTION_UPDOWN)
	{
		if(m_nNowShakeNumber <= m_nMaxShakeNumber)
		{
		
			CEMMath Math;

			m_TargetCamPos->m_fY += m_fCamShakeSpeed * dt;
			m_fCamAccrueShake += Math.Abs<float>(m_fCamShakeSpeed * dt);
			if(m_fCamShakeSpeed > 0)
				m_fCamShakeSpeed += m_fCamPlusSpeed * dt;
			if(m_fCamShakeSpeed < 0)
				m_fCamShakeSpeed -= m_fCamPlusSpeed * dt;

			if(m_nNowShakeNumber == 0 || m_nNowShakeNumber == m_nMaxShakeNumber)
			{
				if(m_fCamAccrueShake >= m_fCamMaxShakeDistance)
				{
					if(m_fCamShakeSpeed > 0)
					{
						m_TargetCamPos->m_fY -= m_fCamAccrueShake - m_fCamMaxShakeDistance;
					}
					else if(m_fCamShakeSpeed < 0)
					{
						m_TargetCamPos->m_fY += m_fCamAccrueShake - m_fCamMaxShakeDistance;
					}

					m_fCamAccrueShake = 0;
					m_fCamShakeSpeed_Basic *= -1;
					m_fCamShakeSpeed = m_fCamShakeSpeed_Basic;
					m_nNowShakeNumber++;
				
				
				}
			}
			else
			{
				if(m_fCamAccrueShake >= m_fCamMaxShakeDistance * 2)
				{
					if(m_fCamShakeSpeed > 0)
					{
						m_TargetCamPos->m_fY -= m_fCamAccrueShake - (m_fCamMaxShakeDistance*2);
					}
					else if(m_fCamShakeSpeed < 0)
					{
						m_TargetCamPos->m_fY += m_fCamAccrueShake - (m_fCamMaxShakeDistance*2);
					}


					m_fCamAccrueShake = 0;
					m_fCamShakeSpeed_Basic *= -1;
					m_fCamShakeSpeed = m_fCamShakeSpeed_Basic;
					m_nNowShakeNumber++;
				
				
				}
			}
		}
	}
	else if(m_eDerection == E_DERECTION_LEFTRIGHT)
	{
		if(m_nNowShakeNumber <= m_nMaxShakeNumber)
		{
		
			CEMMath Math;

			m_TargetCamPos->m_fX += m_fCamShakeSpeed * dt;
			m_fCamAccrueShake += Math.Abs<float>(m_fCamShakeSpeed * dt);
			if(m_fCamShakeSpeed > 0)
				m_fCamShakeSpeed += m_fCamPlusSpeed * dt;
			if(m_fCamShakeSpeed < 0)
				m_fCamShakeSpeed -= m_fCamPlusSpeed * dt;

			if(m_nNowShakeNumber == 0 || m_nNowShakeNumber == m_nMaxShakeNumber)
			{
				if(m_fCamAccrueShake >= m_fCamMaxShakeDistance)
				{

					if(m_fCamShakeSpeed > 0)
					{
						m_TargetCamPos->m_fX -= m_fCamAccrueShake - (m_fCamMaxShakeDistance);
					}
					else if(m_fCamShakeSpeed < 0)
					{
						m_TargetCamPos->m_fX += m_fCamAccrueShake - (m_fCamMaxShakeDistance);
					}

					m_fCamAccrueShake = 0;
					m_fCamShakeSpeed_Basic *= -1;
					m_fCamShakeSpeed = m_fCamShakeSpeed_Basic;
					m_nNowShakeNumber++;
				
				
				}
			}
			else
			{
				if(m_fCamAccrueShake >= m_fCamMaxShakeDistance * 2)
				{
					if(m_fCamShakeSpeed > 0)
					{
						m_TargetCamPos->m_fX -= m_fCamAccrueShake - (m_fCamMaxShakeDistance*2);
					}
					else if(m_fCamShakeSpeed < 0)
					{
						m_TargetCamPos->m_fX += m_fCamAccrueShake - (m_fCamMaxShakeDistance*2);
					}
					m_fCamAccrueShake = 0;
					m_fCamShakeSpeed_Basic *= -1;
					m_fCamShakeSpeed = m_fCamShakeSpeed_Basic;
					m_nNowShakeNumber++;
				
				
				}
			}
		}
	}
	


	if(m_nNowRotNumber <= m_nMaxRotNumber)
	{
		if(m_nNowRotNumber == 0 || m_nNowRotNumber == m_nMaxRotNumber)
		{
			if(m_fRotAccrue < m_fMaxRot)
			{
				CEMMath Math;
				D_CAMERA->RotZ(m_fRotSpeed);
				m_fRotAccrue += Math.Abs<float>(m_fRotSpeed);
			}
			if(m_fRotAccrue >= m_fMaxRot)
			{
				// D_CAMERA->RotZ(-(m_fMaxRot - m_fRotAccrue));
				m_fRotSpeed *= -1;
				m_fRotAccrue = 0;
				m_nNowRotNumber++;
			}
		}
		else
		{
			if(m_fRotAccrue < m_fMaxRot * 2)
			{
				CEMMath Math;
				D_CAMERA->RotZ(m_fRotSpeed);
				m_fRotAccrue += Math.Abs<float>(m_fRotSpeed);
			}
			if(m_fRotAccrue >= m_fMaxRot * 2)
			{
				//D_CAMERA->RotZ(-(m_fMaxRot - m_fRotAccrue));
				m_fRotSpeed *= -1;
				m_fRotAccrue = 0;
				m_nNowRotNumber++;
			}
		}
		
		
	}
}

void CEMCamShakeManager::Shake(E_DERECTION eDerection, int nNumber, float fCamShakeSpeed, float fCamPlusSpeed, float	fCamMaxShakeDistance, float fMaxRot, float fRotSpeed, int nRotNumber)
{
	m_eDerection = eDerection;

	m_TargetCamPos->m_fY = D_BASIC_CAM_OFFSET;
	m_fCamAccrueShake = 0;
	m_nMaxShakeNumber = nNumber * 2;
	m_nNowShakeNumber = 0;
	m_fCamShakeSpeed = fCamShakeSpeed;
	m_fCamShakeSpeed_Basic = fCamShakeSpeed;
	m_fCamPlusSpeed = fCamPlusSpeed;
	m_fCamMaxShakeDistance = fCamMaxShakeDistance;


	m_fMaxRot = fMaxRot;
	m_fRotSpeed = fRotSpeed;
	m_fRotAccrue = 0;
	m_nMaxRotNumber = nRotNumber * 2;
	m_nNowRotNumber = 0;


}
void  CEMCamShakeManager::Shake_AddNumber(int nNumber, int nRotNumber)
{
	if(nNumber > 0)
		m_nMaxShakeNumber += nNumber * 2;
	if(nRotNumber > 0)
		m_nMaxRotNumber += nRotNumber * 2;
}
bool CEMCamShakeManager::IsShaking()
{
	if(m_nNowShakeNumber <= m_nMaxShakeNumber || m_nNowRotNumber <= m_nMaxRotNumber)
		return true;

	return false;
}