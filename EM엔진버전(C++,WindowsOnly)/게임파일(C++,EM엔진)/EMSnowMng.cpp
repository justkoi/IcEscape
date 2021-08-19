#include "stdafx.h"

void CEMSnowMng::Init(CRootScene* pScene, int nMaxSnow, E_SNOW_OPTION_SCENE eSnowOption, CEMColor SnowColor, float fSpeed)
{
	m_pThisScene = pScene;

	m_nMaxSnow = nMaxSnow;

	m_eSnowOption = eSnowOption;
	m_SnowColor = SnowColor;
	m_stSnowList = new stSnow[m_nMaxSnow];
	m_fSpeed = fSpeed;
	for(int i=0; i<m_nMaxSnow; i++)
	{
		
		m_stSnowList[i].m_stSize.m_fX = CEMMath::RandomFloatInRange(0.2f,0.9f);
		m_stSnowList[i].m_stSize.m_fY = CEMMath::RandomFloatInRange(m_stSnowList[i].m_stSize.m_fX, 0.9f);

		m_stSnowList[i].m_stPos.m_fX = D_SNOW_RAND_POS_X;
		m_stSnowList[i].m_stPos.m_fY = D_SNOW_RAND_POS_Y;

		m_stSnowList[i].m_pSnow = new CEMPlane();		

		m_stSnowList[i].m_fRot = 0;
		m_stSnowList[i].m_fRotSpeed = CEMMath::RandomFloatInRange(50.0f, 150.0f);

		m_stSnowList[i].m_pSnow->SetSize(m_stSnowList[i].m_stSize.m_fX , m_stSnowList[i].m_stSize.m_fY);					
		m_stSnowList[i].m_pSnow->SetPos(m_stSnowList[i].m_stPos.m_fX , m_stSnowList[i].m_stPos.m_fY, 0);				
		m_stSnowList[i].m_pSnow->SetLocalVec(0.0f, 0.0f);		
		m_stSnowList[i].m_pSnow->SetOffset(0.0f, 0.0f);
		m_stSnowList[i].m_pSnow->SetTexture(m_pThisScene, "Data/Image/Effect/Snow"+IntToEMString(CEMMath::RandomIntInRange(1,D_SNOW_MAX+1))+".png");	
		m_stSnowList[i].m_pSnow->SetFrustumCulling(false);				
		m_stSnowList[i].m_pSnow->SetBoundingBoxCalc(false);			
		m_stSnowList[i].m_pSnow->SetBlend(true);					
		m_stSnowList[i].m_pSnow->SetShow(true);
		m_stSnowList[i].m_pSnow->SetBackFaceCulling(false);

		m_SnowColor.m_fA = CEMMath::RandomFloatInRange(0.7f,1.0f);

		
		if(eSnowOption == E_SNOW_OPTION_MENU)
		{
			m_SnowColor.m_fR = CEMMath::RandomFloatInRange(0.8f,1.0f);
			m_SnowColor.m_fG= CEMMath::RandomFloatInRange(0.7f,1.0f);
			m_SnowColor.m_fB = CEMMath::RandomFloatInRange(1.0f,1.0f);
			if(m_stSnowList[i].m_stSize.m_fX <= 0.65f)
				m_pThisScene->Commit(333,i, "Snow", m_stSnowList[i].m_pSnow);
			else
				m_pThisScene->Commit(333,i, "Snow", m_stSnowList[i].m_pSnow);
			m_stSnowList[i].m_pSnow->SetColor(m_SnowColor);
		}
		else if(eSnowOption == E_SNOW_OPTION_STAGE)
		{
			if(m_stSnowList[i].m_stSize.m_fX <= 0.65f)
				m_pThisScene->Commit(0,i, "Snow", m_stSnowList[i].m_pSnow);
			else
				m_pThisScene->Commit(-9,i, "Snow", m_stSnowList[i].m_pSnow);
			m_stSnowList[i].m_pSnow->SetColor(m_SnowColor);
		}

	}

}

void CEMSnowMng::Update(float dt)
{
	for(int i=0; i<m_nMaxSnow; i++)
	{
		m_stSnowList[i].m_stPos.m_fX += (-m_fSpeed * dt * m_stSnowList[i].m_stSize.m_fX);
		m_stSnowList[i].m_stPos.m_fY += (-m_fSpeed/2) * dt *  m_stSnowList[i].m_stSize.m_fY;

		if(m_stSnowList[i].m_stPos.m_fX <= -250 || m_stSnowList[i].m_stPos.m_fY <= -400)
		{
			m_stSnowList[i].m_stPos.m_fX = D_SNOW_RAND_POS_X;
			m_stSnowList[i].m_stPos.m_fY = D_SNOW_RAND_POS_Y;
		}

		m_stSnowList[i].m_fRot += m_stSnowList[i].m_fRotSpeed * dt;

		m_stSnowList[i].m_pSnow->SetPos(m_stSnowList[i].m_stPos);
		m_stSnowList[i].m_pSnow->SetZRot(m_stSnowList[i].m_fRot);
	}

}