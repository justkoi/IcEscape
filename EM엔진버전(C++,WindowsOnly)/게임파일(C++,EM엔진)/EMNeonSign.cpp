#include "stdafx.h"

void CEMNeonSign::Init(float m_fX, float m_fY, int nSpeed, stEMVec2 stSize, CRootScene* pThisScene)
{
	m_stSize = stSize;
	m_nSpeed = nSpeed;
	m_pThisScene = pThisScene;
	m_Pos.m_fX = m_fX;
	m_Pos.m_fY = m_fY;

	FILE* fp = fopen("Data/NeonSign/NeonSign_1.txt","rt");

	fscanf(fp,"%d %d",&m_nWidth,&m_nHeight);

	m_nMaxTile = m_nWidth * m_nHeight;
	m_pTile = new CEMPlane*[m_nMaxTile];
	m_MoveSpeed = new stEMVec2[m_nMaxTile];

	int nTargetX = 0;
	int nTargetY = 0;
	fgetc(fp);
	for(int i=0; i<m_nMaxTile; i++)
	{
		m_nTemp = fgetc(fp) - '0';

		//nTemp = nTemp - '\0';

		m_pTile[i] = new CEMPlane();		
		
		m_pTile[i]->SetTexture(pThisScene, "Data/Image/Tile/Tile_"+IntToEMString(m_nTemp+1)+".png");
		m_pTile[i]->SetSize(m_stSize.m_fX, m_stSize.m_fY);
		m_pTile[i]->SetPos(m_Pos.m_fX + (nTargetX * m_pTile[i]->GetTextureWidthSize() * m_pTile[i]->GetSize().m_fX), m_Pos.m_fY - (nTargetY * m_pTile[i]->GetTexTureHeightSize() * m_pTile[i]->GetSize().m_fY), 0.0f);
		m_pTile[i]->SetLocalVec(0.0f, 0.0f);
		m_pTile[i]->SetOffset(0.0f, 0.0f);	

		m_pTile[i]->SetFrustumCulling(true);
		m_pTile[i]->SetBoundingBoxCalc(true);
		m_pTile[i]->SetBlend(true);						
		m_pTile[i]->SetShow(true);
		m_pTile[i]->SetBackFaceCulling(false);

		pThisScene->Commit(0,i,"Tile", m_pTile[i]);

		nTargetX++;
		if(nTargetX >= m_nWidth)
		{
			nTargetX = 0;
			nTargetY++;
			fgetc(fp);
		}
	}
	m_fTimer = 0.0f;
	m_eNeonState = E_NEONSTATE_NONE;
	m_nStage = 1;
	m_bTrue = false;
}

void CEMNeonSign::Update(float dt)
{
	if(m_eNeonState == E_NEONSTATE_NONE)
		m_fTimer += dt;

	if(m_fTimer >= 3.0f)
	{
		
		if(m_eNeonState == E_NEONSTATE_NONE)
		{
			m_nLevel = 0;

			m_eNeonState = E_NEONSTATE_MOVE;
			if(m_bTrue == false)
			{
				for(int i=0; i<m_nMaxTile; i++)
				{
					float fRandX = CEMMath::RandomFloatInRange(0.0f - (D_SCREEN_SCALE_WIDTH(90)/2) ,D_SCREEN_SCALE_WIDTH(90) - (D_SCREEN_SCALE_WIDTH(90)/2));
					
					float fRandY = CEMMath::RandomFloatInRange(0.0f - (D_SCREEN_SCALE_HEIGHT(80)/2) ,D_SCREEN_SCALE_HEIGHT(80) - (D_SCREEN_SCALE_HEIGHT(80)/2));

					m_MoveSpeed[i].m_fX = (fRandX - m_pTile[i]->GetPosVec2().m_fX) / m_nSpeed;
					m_MoveSpeed[i].m_fY = (fRandY - m_pTile[i]->GetPosVec2().m_fY) / m_nSpeed;
				}
				m_bTrue = true;
				if(m_nStage <= 2)
					m_nStage++;
				m_fTimer = 2.9f;
			}
			else if(m_bTrue == true)
			{
				m_fTimer = 0.0f;
				SetTile(m_nStage);
				m_bTrue = false;
			}
		}
	}

	if(m_eNeonState == E_NEONSTATE_MOVE)
	{
		for(int i=0; i<m_nMaxTile; i++)
		{
			m_pTile[i]->MoveX(m_MoveSpeed[i].m_fX);
			m_pTile[i]->MoveY(m_MoveSpeed[i].m_fY);
		}
		m_nLevel++;
	}
	if(m_nLevel >= m_nSpeed)
	{
		m_eNeonState = E_NEONSTATE_NONE;
	}
};

void CEMNeonSign::SetTile(int nStage)
{
	char strTemp[256];
	sprintf(strTemp, "Data/NeonSign/NeonSign_%d.txt",nStage);
	FILE* fp = fopen(strTemp,"rt");

	fscanf(fp,"%d %d",&m_nWidth,&m_nHeight);

	m_nMaxTile = m_nWidth * m_nHeight;

	int nTargetX = 0;
	int nTargetY = 0;

	fgetc(fp);
	for(int i=0; i<m_nMaxTile; i++)
	{
		m_nTemp = fgetc(fp) - '0';

	
		//m_pTile[i]->SetSize(0.5f, 0.5f);

		//m_pTile[i]->SetPos(m_Pos.m_fX + (nTargetX * 16), m_Pos.m_fY - (nTargetY * 16), 0.0f);

		//float fRandX = CEMMath::RandomFloatInRange(0.0f,D_SCREEN_SCALE_WIDTH(90));
	//	float fRandY = CEMMath::RandomFloatInRange(0.0f,D_SCREEN_SCALE_HEIGHT(80));
		
		m_MoveSpeed[i].m_fX = (m_Pos.m_fX + (nTargetX * m_pTile[i]->GetTextureWidthSize() * m_pTile[i]->GetSize().m_fX) - m_pTile[i]->GetPosVec2().m_fX) / 40;
		m_MoveSpeed[i].m_fY = (m_Pos.m_fY - (nTargetY * m_pTile[i]->GetTexTureHeightSize() * m_pTile[i]->GetSize().m_fY) - m_pTile[i]->GetPosVec2().m_fY) / 40;

		//m_pTile[i]->SetLocalVec(0.0f, 0.0f);
		//m_pTile[i]->SetOffset(0.0f, 0.0f);
		m_pTile[i]->SetTexture(m_pThisScene, "Data/Image/Tile/Tile_"+IntToEMString(m_nTemp+1)+".png");	

		//m_pTile[i]->SetFrustumCulling(true);
		//m_pTile[i]->SetBoundingBoxCalc(true);
		//m_pTile[i]->SetBlend(true);						
		//m_pTile[i]->SetShow(true);
		//m_pTile[i]->SetBackFaceCulling(false);


		nTargetX++;
		if(nTargetX >= m_nWidth)
		{
			nTargetX = 0;
			nTargetY++;
			fgetc(fp);
		}
	}
}