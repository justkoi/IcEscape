#include "stdafx.h"

void CEMDolphin::Init(CRootScene* pThisScene, int Index, float CreateTime)
{

	m_pThisScene = pThisScene;
	m_pDolphin = new CEMAnimation(6);
	m_pDolphin->SetSize(1.2f, 1.2f);					
	m_pDolphin->SetPos(0.0f, 0.0f, 0.0f);			
	m_pDolphin->SetLocalVec(0.0f, 0.0f);			
	m_pDolphin->SetOffset(0.0f, 0.0f);
	m_pDolphin->SetTime(0.25f);
	m_pDolphin->SetTexture(m_pThisScene, 6, "Data/Image/Item/Dolphin_1.png", "Data/Image/Item/Dolphin_2.png", "Data/Image/Item/Dolphin_3.png", "Data/Image/Item/Dolphin_4.png", "Data/Image/Item/Dolphin_5.png", "Data/Image/Item/Dolphin_6.png");
	m_pDolphin->SetFrustumCulling(true);				
	m_pDolphin->SetBoundingBoxCalc(true);				
	m_pDolphin->SetBlend(true);						
	m_pDolphin->SetShow(true);
	m_pDolphin->SetPause(true);
	m_pDolphin->SetBackFaceCulling(false);

	m_pThisScene->Commit(-9,Index,"Dolphin",m_pDolphin);


	m_stPos.m_fX = 0;
	m_stPos.m_fY = 0;

	m_fG = 9.8f;
	m_fT = 0.04f;
	m_fJumpSpeed = 0.0f;
	m_fJumpPower = 14.0f;

	m_fMoveSpeed = 5.0f;

	m_eState = E_DOLPHIN_STATE_NONE;

	m_fCreateTimer = 0.0f;
	m_fCreateTime = CreateTime;
	
};

void CEMDolphin::Update(float dt, list<CEMBlock*> BlockList)
{
	

	if(m_eState == E_DOLPHIN_STATE_NONE)
	{
		m_pDolphin->SetShow(false);
		m_fCreateTimer += dt;
		if(m_fCreateTimer >= m_fCreateTime)
		{
			m_fCreateTime = CEMMath::RandomFloatInRange(6.0f, 20.0f);
			m_fCreateTimer = 0.0f;
			m_eState = E_DOLPHIN_STATE_PLAY;

			m_stPos.m_fX = 150.0f;
			m_stPos.m_fY = -300.0f;
			m_pDolphin->SetPause(false);
			m_pDolphin->SetLoopType(E_ANI_LOOP,0,E_ANI_ENDING_TYPE_LASTFRAMEOUTPUT);
			float fRand = CEMMath::RandomFloatInRange(70.0f,130.0f);
			m_fJumpSpeed = (m_fJumpPower/100) * fRand;
			m_pDolphin->SetTime(0.25f * (fRand/100.0f));
		}
	}
	else if(m_eState == E_DOLPHIN_STATE_PLAY)
	{
		m_pDolphin->SetShow(true);
		if(m_pDolphin->GetCurFrameNumber() >= m_pDolphin->GetTotalFrame() - 1)
		{
			m_pDolphin->SetPause(true);
		}

		list<CEMBlock*>::iterator it;
		for(it = BlockList.begin(); it != BlockList.end(); it++)
		{
			
			if(m_stPos.m_fX + 75 >= (*it)->m_stPos.m_fX && m_stPos.m_fX + 75 <= (*it)->m_stPos.m_fX + D_BLOCK_WIDTH &&
				m_stPos.m_fY + 75 >= (*it)->m_stPos.m_fY && m_stPos.m_fY + 75 <= (*it)->m_stPos.m_fY + D_BLOCK_HEIGHT )
			{
				if((*it)->m_bFreezed == true && (*it)->m_bDolphinHited == false)
				{
					(*it)->m_bDolphinHited = true;
					(*it)->m_bFreezed = false;
					(*it)->m_pBlock->SetPause(false);
					(*it)->m_fErosionTime -= D_FREEZETIME;
					//int nRandNumber = (int)CEMMath::RandomIntInRange(0,D_BLOCK_NUMBER);
					//(*it)->m_eBlockNumber = (E_BLOCKNUMBER)nRandNumber;

					
					//if( nRandNumber +1 == 1 )
					//	(*it)->m_pBlock->SetTexture(m_pThisScene,3, "Data/Image/Block/Block_1_1.png", "Data/Image/Block/Block_1_2.png", "Data/Image/Block/Block_1_3.png");	
					//else if( nRandNumber+1 == 2)
					//	(*it)->m_pBlock->SetTexture(m_pThisScene,3, "Data/Image/Block/Block_2_1.png", "Data/Image/Block/Block_2_2.png", "Data/Image/Block/Block_2_3.png");	
					//else if( nRandNumber+1 == 3)
					//	(*it)->m_pBlock->SetTexture(m_pThisScene,3, "Data/Image/Block/Block_3_1.png", "Data/Image/Block/Block_3_2.png", "Data/Image/Block/Block_3_3.png");	
	
				//	(*it)->m_pBlock->SetTexture(m_pThisScene,3, "Data/Image/Block/Block_"+ IntToEMString((*it)->m_eBlockNumber+1)+"_"+"1"+".png", "Data/Image/Block/Block_"+ IntToEMString((*it)->m_eBlockNumber+1)+"_"+"2"+".png", "Data/Image/Block/Block_"+ IntToEMString((*it)->m_eBlockNumber+1)+"_"+"3"+".png");
				}
			}
		}

		m_stPos.m_fY += m_fJumpSpeed;
		m_fJumpSpeed -= m_fG * m_fT;
		m_stPos.m_fX -= m_fMoveSpeed;

		if(m_stPos.m_fY <= -350.0f)
		{
			m_eState = E_DOLPHIN_STATE_NONE;
			m_stPos.m_fY = -1000.0f;
			m_fCreateTimer = 0.0f;

			list<CEMBlock*>::iterator it;
			for(it = BlockList.begin(); it != BlockList.end(); it++)
			{
				(*it)->m_bDolphinHited = false;
			}
			
		}
		
	}

	m_pDolphin->SetPos(m_stPos);
};

void CEMDolphin::Exit()
{

};