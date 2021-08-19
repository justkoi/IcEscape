#include "stdafx.h"

void CEMBlock::Init(CRootScene* pThisScene, stVec2i stIndex, int nCreateBlockNumber)
{
	m_stIndex = stIndex;

	m_stPos.m_fX = D_LINE_START_X + (stIndex.m_fX * 64);
	m_stPos.m_fY = D_LINE_START_Y - (stIndex.m_fY * 64);

	m_eBlockNumber = (E_BLOCKNUMBER)CEMMath::RandomIntInRange(0,E_BLOCKNUMBER_MAX);

/*
	m_pPlane = new CEMPlane();					
	m_pPlane->SetSize(1.0f,	1.0f);					
	m_pPlane->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pPlane->SetLocalVec(0.0f, 0.0f);				
	m_pPlane->SetOffset(0.0f, 0.0f);
	m_pPlane->SetTexture(pThisScene, "Data/Image/Block/Block_"+ IntToEMString(m_eBlockNumber+1) + ".png");	
	m_pPlane->SetFrustumCulling(true);				
	m_pPlane->SetBoundingBoxCalc(true);				
	m_pPlane->SetBlend(true);				
	m_pPlane->SetShow(true);
	m_pPlane->SetBackFaceCulling(false);
	pThisScene->Commit(-2,nCreateBlockNumber, "ºí·Ï", m_pPlane);
*/
	m_pBlock = new CEMAnimation(3);			
	m_pBlock->SetTime(0.15f);
	m_pBlock->SetSize(1.0f,	1.0f);					
	m_pBlock->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pBlock->SetLocalVec(0.0f, 0.0f);				
	m_pBlock->SetOffset(0.0f, 0.0f);
	if((m_eBlockNumber+1) == 1)
		m_pBlock->SetTexture(pThisScene,3, "Data/Image/Block/Block_1_1.png", "Data/Image/Block/Block_1_2.png", "Data/Image/Block/Block_1_3.png");	
	else if((m_eBlockNumber+1) == 2)
		m_pBlock->SetTexture(pThisScene,3, "Data/Image/Block/Block_2_1.png", "Data/Image/Block/Block_2_2.png", "Data/Image/Block/Block_2_3.png");	
	else if((m_eBlockNumber+1) == 3)
		m_pBlock->SetTexture(pThisScene,3, "Data/Image/Block/Block_3_1.png", "Data/Image/Block/Block_3_2.png", "Data/Image/Block/Block_3_3.png");	
	else if((m_eBlockNumber+1) == 4)
		m_pBlock->SetTexture(pThisScene,3, "Data/Image/Block/Block_4_1.png", "Data/Image/Block/Block_4_2.png", "Data/Image/Block/Block_4_3.png");	
	

	m_pBlock->SetFrustumCulling(true);				
	m_pBlock->SetBoundingBoxCalc(true);				
	m_pBlock->SetBlend(true);				
	m_pBlock->SetShow(true);
	m_pBlock->SetPause(true);
	m_pBlock->SetBackFaceCulling(false);
	pThisScene->Commit(-2,nCreateBlockNumber, "ºí·Ï", m_pBlock);





	m_pSelect = new CEMPlane();					
	m_pSelect->SetSize(1.0f, 1.0f);					
	m_pSelect->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pSelect->SetLocalVec(0.0f, 0.0f);				
	m_pSelect->SetOffset(0.0f, 0.0f);
	m_pSelect->SetTexture(pThisScene, "Data/Image/Block/Block_Select.png");	
	m_pSelect->SetFrustumCulling(true);				
	m_pSelect->SetBoundingBoxCalc(true);				
	m_pSelect->SetBlend(true);				
	m_pSelect->SetShow(false);
	m_pSelect->SetBackFaceCulling(false);
	m_pSelect->SetColor(1.0f,1.0f,1.0f,0.3f);
	pThisScene->Commit(-5,nCreateBlockNumber, "¼±ÅÃµÊ", m_pSelect);

	
	m_pErosoin = new CEMPlane();					
	m_pErosoin->SetSize(1.0f, 1.0f);					
	m_pErosoin->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pErosoin->SetLocalVec(0.0f, 0.0f);				
	m_pErosoin->SetOffset(0.0f, 0.0f);
	m_pErosoin->SetTexture(pThisScene, "Data/Image/Block/Block_Erosoin.png");	
	m_pErosoin->SetFrustumCulling(true);				
	m_pErosoin->SetBoundingBoxCalc(true);				
	m_pErosoin->SetBlend(true);				
	m_pErosoin->SetShow(true);
	m_pErosoin->SetBackFaceCulling(false);
	m_pErosoin->SetColor(1.0f,1.0f,1.0f,0.3f);
	pThisScene->Commit(-5,nCreateBlockNumber, "Ä§½Ä·ü", m_pErosoin);

	
	m_pErosoin_Border = new CEMPlane();					
	m_pErosoin_Border->SetSize(1.0f, 1.0f);					
	m_pErosoin_Border->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pErosoin_Border->SetLocalVec(0.0f, 0.0f);				
	m_pErosoin_Border->SetOffset(0.0f, 0.0f);
	m_pErosoin_Border->SetTexture(pThisScene, "Data/Image/Block/Block_Erosoin_Border.png");	
	m_pErosoin_Border->SetFrustumCulling(true);				
	m_pErosoin_Border->SetBoundingBoxCalc(true);				
	m_pErosoin_Border->SetBlend(true);				
	m_pErosoin_Border->SetShow(true);
	m_pErosoin_Border->SetBackFaceCulling(false);
	m_pErosoin_Border->SetColor(1.0f,1.0f,1.0f,0.5f);
	pThisScene->Commit(-6,nCreateBlockNumber, "Ä§½Ä·üÆ²", m_pErosoin_Border);
	
	m_pFreeze = new CEMPlane();					
	m_pFreeze->SetSize(1.0f, 1.0f);					
	m_pFreeze->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pFreeze->SetLocalVec(0.0f, 0.0f);				
	m_pFreeze->SetOffset(0.0f, 0.0f);
	m_pFreeze->SetTexture(pThisScene, "Data/Image/Block/Block_Freeze.png");	
	m_pFreeze->SetFrustumCulling(true);				
	m_pFreeze->SetBoundingBoxCalc(true);				
	m_pFreeze->SetBlend(true);				
	m_pFreeze->SetShow(true);
	m_pFreeze->SetBackFaceCulling(false);
	m_pFreeze->SetColor(1.0f,1.0f,1.0f,1.0f);
	pThisScene->Commit(-4,nCreateBlockNumber, "¾óÀ½", m_pFreeze);

	m_pItem_Sled = new CEMPlane();					
	m_pItem_Sled->SetSize(1.0f, 1.0f);					
	m_pItem_Sled->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pItem_Sled->SetLocalVec(0.0f, 0.0f);				
	m_pItem_Sled->SetOffset(0.0f, 0.0f);
	m_pItem_Sled->SetTexture(pThisScene, "Data/Image/Block/Block_Item_Sled.png");	
	m_pItem_Sled->SetFrustumCulling(true);				
	m_pItem_Sled->SetBoundingBoxCalc(true);				
	m_pItem_Sled->SetBlend(true);				
	m_pItem_Sled->SetShow(false);
	m_pItem_Sled->SetBackFaceCulling(false);
	m_pItem_Sled->SetColor(1.0f,1.0f,1.0f,1.0f);
	pThisScene->Commit(-4,nCreateBlockNumber, "Item_Sled", m_pItem_Sled);



	m_fStartY			= m_stPos.m_fY;
	m_fSpeed			= D_BLOCK_SPEED;
	m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
	m_fNowDistance		= 0.0f;
	m_fDistance			= 0.0f;

	m_fEye = 0.0f;

	m_eBlockState		= E_BLOCKSTATE_NONE;

	m_fErosionMaxTime = D_EROSIONTIME;
	m_fErosionTime = m_fErosionMaxTime;
	m_fErosionOffsetY = 0.0f;

	m_bFreezed = false;
	m_bDraged = false;
	m_bDolphinHited = false;


	m_bEye = false;

	int nBlockItemRandom = CEMMath::RandomIntInRange(0,10000);

	if(nBlockItemRandom >= 0 && nBlockItemRandom <= 500)
	{
		m_eBlockItem = E_BLOCKITEM_SLED;
		m_pItem_Sled->SetShow(true);
	}
	else
	{
		m_eBlockItem = E_BLOCKITEM_NONE;
		m_pItem_Sled->SetShow(false);
	}

}


void CEMBlock::Init(CRootScene* pThisScene, E_BLOCKNUMBER eBlockNumber, stVec2i stIndex,int nCreateBlockNumber)
{
	m_stIndex = stIndex;

	m_stPos.m_fX = D_LINE_START_X + (stIndex.m_fX * 64);
	m_stPos.m_fY = D_LINE_START_Y - (stIndex.m_fY * 64);

	m_eBlockNumber = eBlockNumber;

/*
	m_pPlane = new CEMPlane();					
	m_pPlane->SetSize(1.0f,	1.0f);					
	m_pPlane->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pPlane->SetLocalVec(0.0f, 0.0f);				
	m_pPlane->SetOffset(0.0f, 0.0f);
	m_pPlane->SetTexture(pThisScene, "Data/Image/Block/Block_"+ IntToEMString(m_eBlockNumber+1) + ".png");	
	m_pPlane->SetFrustumCulling(true);				
	m_pPlane->SetBoundingBoxCalc(true);				
	m_pPlane->SetBlend(true);				
	m_pPlane->SetShow(true);
	m_pPlane->SetBackFaceCulling(false);
	pThisScene->Commit(-2,nCreateBlockNumber, "ºí·Ï", m_pPlane);
*/
	m_pBlock = new CEMAnimation(3);			
	m_pBlock->SetTime(0.15f);
	m_pBlock->SetSize(1.0f,	1.0f);					
	m_pBlock->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pBlock->SetLocalVec(0.0f, 0.0f);				
	m_pBlock->SetOffset(0.0f, 0.0f);
	if((m_eBlockNumber+1) == 1)
		m_pBlock->SetTexture(pThisScene,3, "Data/Image/Block/Block_1_1.png", "Data/Image/Block/Block_1_2.png", "Data/Image/Block/Block_1_3.png");	
	else if((m_eBlockNumber+1) == 2)
		m_pBlock->SetTexture(pThisScene,3, "Data/Image/Block/Block_2_1.png", "Data/Image/Block/Block_2_2.png", "Data/Image/Block/Block_2_3.png");	
	else if((m_eBlockNumber+1) == 3)
		m_pBlock->SetTexture(pThisScene,3, "Data/Image/Block/Block_3_1.png", "Data/Image/Block/Block_3_2.png", "Data/Image/Block/Block_3_3.png");	
	else if((m_eBlockNumber+1) == 4)
		m_pBlock->SetTexture(pThisScene,3, "Data/Image/Block/Block_4_1.png", "Data/Image/Block/Block_4_2.png", "Data/Image/Block/Block_4_3.png");	
	

	m_pBlock->SetFrustumCulling(true);				
	m_pBlock->SetBoundingBoxCalc(true);				
	m_pBlock->SetBlend(true);				
	m_pBlock->SetShow(true);
	m_pBlock->SetPause(true);
	m_pBlock->SetBackFaceCulling(false);
	pThisScene->Commit(-2,nCreateBlockNumber, "ºí·Ï", m_pBlock);





	m_pSelect = new CEMPlane();					
	m_pSelect->SetSize(1.0f, 1.0f);					
	m_pSelect->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pSelect->SetLocalVec(0.0f, 0.0f);				
	m_pSelect->SetOffset(0.0f, 0.0f);
	m_pSelect->SetTexture(pThisScene, "Data/Image/Block/Block_Select.png");	
	m_pSelect->SetFrustumCulling(true);				
	m_pSelect->SetBoundingBoxCalc(true);				
	m_pSelect->SetBlend(true);				
	m_pSelect->SetShow(false);
	m_pSelect->SetBackFaceCulling(false);
	m_pSelect->SetColor(1.0f,1.0f,1.0f,0.3f);
	pThisScene->Commit(-5,nCreateBlockNumber, "¼±ÅÃµÊ", m_pSelect);

	
	m_pErosoin = new CEMPlane();					
	m_pErosoin->SetSize(1.0f, 1.0f);					
	m_pErosoin->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pErosoin->SetLocalVec(0.0f, 0.0f);				
	m_pErosoin->SetOffset(0.0f, 0.0f);
	m_pErosoin->SetTexture(pThisScene, "Data/Image/Block/Block_Erosoin.png");	
	m_pErosoin->SetFrustumCulling(true);				
	m_pErosoin->SetBoundingBoxCalc(true);				
	m_pErosoin->SetBlend(true);				
	m_pErosoin->SetShow(true);
	m_pErosoin->SetBackFaceCulling(false);
	m_pErosoin->SetColor(1.0f,1.0f,1.0f,0.3f);
	pThisScene->Commit(-5,nCreateBlockNumber, "Ä§½Ä·ü", m_pErosoin);

	
	m_pErosoin_Border = new CEMPlane();					
	m_pErosoin_Border->SetSize(1.0f, 1.0f);					
	m_pErosoin_Border->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pErosoin_Border->SetLocalVec(0.0f, 0.0f);				
	m_pErosoin_Border->SetOffset(0.0f, 0.0f);
	m_pErosoin_Border->SetTexture(pThisScene, "Data/Image/Block/Block_Erosoin_Border.png");	
	m_pErosoin_Border->SetFrustumCulling(true);				
	m_pErosoin_Border->SetBoundingBoxCalc(true);				
	m_pErosoin_Border->SetBlend(true);				
	m_pErosoin_Border->SetShow(true);
	m_pErosoin_Border->SetBackFaceCulling(false);
	m_pErosoin_Border->SetColor(1.0f,1.0f,1.0f,0.5f);
	pThisScene->Commit(-6,nCreateBlockNumber, "Ä§½Ä·üÆ²", m_pErosoin_Border);
	
	m_pFreeze = new CEMPlane();					
	m_pFreeze->SetSize(1.0f, 1.0f);					
	m_pFreeze->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pFreeze->SetLocalVec(0.0f, 0.0f);				
	m_pFreeze->SetOffset(0.0f, 0.0f);
	m_pFreeze->SetTexture(pThisScene, "Data/Image/Block/Block_Freeze.png");	
	m_pFreeze->SetFrustumCulling(true);				
	m_pFreeze->SetBoundingBoxCalc(true);				
	m_pFreeze->SetBlend(true);				
	m_pFreeze->SetShow(true);
	m_pFreeze->SetBackFaceCulling(false);
	m_pFreeze->SetColor(1.0f,1.0f,1.0f,1.0f);
	pThisScene->Commit(-4,nCreateBlockNumber, "¾óÀ½", m_pFreeze);

	m_pItem_Sled = new CEMPlane();					
	m_pItem_Sled->SetSize(1.0f, 1.0f);					
	m_pItem_Sled->SetPos(m_stPos.m_fX, m_stPos.m_fY, 0.0f);				
	m_pItem_Sled->SetLocalVec(0.0f, 0.0f);				
	m_pItem_Sled->SetOffset(0.0f, 0.0f);
	m_pItem_Sled->SetTexture(pThisScene, "Data/Image/Block/Block_Item_Sled.png");	
	m_pItem_Sled->SetFrustumCulling(true);				
	m_pItem_Sled->SetBoundingBoxCalc(true);				
	m_pItem_Sled->SetBlend(true);				
	m_pItem_Sled->SetShow(false);
	m_pItem_Sled->SetBackFaceCulling(false);
	m_pItem_Sled->SetColor(1.0f,1.0f,1.0f,1.0f);
	pThisScene->Commit(-4,nCreateBlockNumber, "Item_Sled", m_pItem_Sled);



	m_fStartY			= m_stPos.m_fY;
	m_fSpeed			= D_BLOCK_SPEED;
	m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
	m_fNowDistance		= 0.0f;
	m_fDistance			= 0.0f;

	m_fEye = 0.0f;

	m_eBlockState		= E_BLOCKSTATE_NONE;

	m_fErosionMaxTime = D_EROSIONTIME;
	m_fErosionTime = m_fErosionMaxTime;
	m_fErosionOffsetY = 0.0f;

	m_bFreezed = false;
	m_bDraged = false;
	m_bDolphinHited = false;


	m_bEye = false;

	int nBlockItemRandom = CEMMath::RandomIntInRange(0,10000);

	if(nBlockItemRandom >= 0 && nBlockItemRandom <= 500)
	{
		m_eBlockItem = E_BLOCKITEM_SLED;
		m_pItem_Sled->SetShow(true);
	}
	else
	{
		m_eBlockItem = E_BLOCKITEM_NONE;
		m_pItem_Sled->SetShow(false);
	}
}
void CEMBlock::Update(float dt, float fErosionSpeed, CEMSled* Sled)
{		
	m_pFreeze->SetShow(m_bFreezed);

	if(m_bFreezed == false)
	{
		if(m_bEye == false)
			m_fEye += dt;

		if(m_fEye >= 3.0f)
		{
			m_fEye = 0.0f;
			m_pBlock->SetLoopType(E_ANI_LOOP,1);
			m_bEye = true;
			m_pBlock->SetPause(false);
		}

		m_nGT = m_pBlock->GetTotalFrame();
		m_nGC = m_pBlock->GetCurFrameNumber();

		if(m_bEye == true && m_nGC <= 0)
		{
			m_bEye = false;
			m_pBlock->SetPause(true);
		}
	}
	else
	{
		m_pBlock->SetPause(true);
	}


	if(m_eBlockState == E_BLOCKSTATE_FALLING && m_bDraged == false)
	{
		if(m_fNowDistance < m_fDistance)
		{
			m_stPos.m_fY -= (m_fSpeed * dt);
			m_fNowDistance += (m_fSpeed * dt);
			m_fSpeed += (m_fPlusSpeed * dt);
			if(m_fNowDistance >= m_fDistance)
			{
				m_stPos.m_fY		= m_fStartY - m_fDistance;
				m_fSpeed			= D_BLOCK_SPEED;
				m_fPlusSpeed		= D_BLOCK_PLUSSPEED;
				m_fNowDistance		= 0.0f;
				m_fDistance			= 0.0f;
				m_eBlockState		= E_BLOCKSTATE_NONE;
			}
		}
	}
	else
	{
		if(Sled->m_bOnOff == true && Sled->m_bSledMoved == true)
		{
			Sled->m_fHp -= (dt * fErosionSpeed);
		}
		else 
		{
			if(m_stIndex.m_fY == D_BLOCKMAP_HEIGHT - 1)
			{
				m_fErosionTime -= (dt * fErosionSpeed);
			}
		}
	}
	
	m_pErosoin->SetSize(1.0f, m_fErosionTime/m_fErosionMaxTime);
	m_fErosionOffsetY = (1.0f - (m_fErosionTime/m_fErosionMaxTime))/2;

	m_pFreeze->SetPos(m_stPos);
	m_pErosoin->SetPos(m_stPos.m_fX, m_stPos.m_fY - (D_BLOCK_HEIGHT * m_fErosionOffsetY));
	m_pErosoin_Border->SetPos(m_stPos);
	m_pSelect->SetPos(m_stPos);
	m_pBlock->SetPos(m_stPos);
	m_pItem_Sled->SetPos(m_stPos);
}

bool CEMBlock::IsErosoined()
{
	if(m_fErosionTime < 0)
	{
		return true;
	}
	return false;
}