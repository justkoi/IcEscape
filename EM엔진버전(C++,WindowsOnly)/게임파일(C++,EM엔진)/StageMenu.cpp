#include "stdafx.h"


list<stStageInfo*> g_StageInfo;
int g_nSelectStage;

bool* g_bStageLock;

CEMPlane***			m_pLockImg;


int* g_nHighScore;//최고점수 Save
int* g_nScoreLevel;//판정레벨 0, 1, 2, 3 Save


int** g_nJudgment;//각각의 판정점 ReadOnly

int m_nNowStage;
int	m_nMaxStage;
void CStageMenu::LoadStage()
{
	FILE * fp = fopen("Data/StageInfo.txt","rt");
	FILE * fp2 = fopen("Data/StageJudgment.txt","rt");
	FILE * frb = fopen("Data/StageSave.sav","rb");
	FILE * frb2 = fopen("Data/StageJudgment.sav","rb");

	fscanf(fp,"%d",&m_nMaxStage);



	for(int i=0; i<m_nMaxStage; i++)
	{
		stStageInfo* stTemp = new stStageInfo();
		fscanf(fp,"%f %f %f %d %d",&stTemp->m_fTimeLimit,&stTemp->m_fErosionSpeed,&stTemp->m_fCraeteTime,&stTemp->m_nErosionPlusSpeed,&stTemp->m_nMaxSnow);
		g_StageInfo.push_back(stTemp);
	}


	g_bStageLock = new bool[m_nMaxStage];
	for(int i=0; i<m_nMaxStage; i++)
	{
		fread(&g_bStageLock[i],sizeof(bool),1,frb);
	}
	
	g_nHighScore = new int[m_nMaxStage];
	g_nScoreLevel = new int[m_nMaxStage];

	for(int i=0; i<m_nMaxStage; i++)
	{
		fread(&g_nScoreLevel[i],sizeof(int),1,frb2);
	}
	for(int i=0; i<m_nMaxStage; i++)
	{
		fread(&g_nHighScore[i],sizeof(int),1,frb2);
	}

	g_nJudgment = new int*[m_nMaxStage];

	for(int i=0; i<m_nMaxStage; i++)
		g_nJudgment[i] = new int[3];

	for(int i=0; i<m_nMaxStage; i++)
	{
		fscanf(fp2,"%d %d %d",&g_nJudgment[i][0],&g_nJudgment[i][1],&g_nJudgment[i][2]);
	}



	fclose(fp);
	fclose(fp2);
	fclose(frb);
	fclose(frb2);

	m_nNowStage = 1;

}


void CStageMenu::SaveStage()
{
	FILE * fpw = fopen("Data/StageSave.sav","wb");
	FILE * fpw2 = fopen("Data/StageJudgment.sav","wb");

	for(int i=0; i<m_nMaxStage; i++)
	{
		fwrite(&g_bStageLock[i],sizeof(bool),1,fpw);
	}

	for(int i=0; i<m_nMaxStage; i++)
	{
		fwrite(&g_nScoreLevel[i],sizeof(int),1,fpw2);
	}
	for(int i=0; i<m_nMaxStage; i++)
	{
		fwrite(&g_nHighScore[i],sizeof(int),1,fpw2);
	}

	fclose(fpw);
	fclose(fpw2);

}
void CStageMenu::Enter(CSceneWork* pSceneWork)
{
	if(g_bFullScreen == true)
	{
		m_pBlack[0] = new CEMPlane();		
		m_pBlack[0]->SetSize(1.0f,1.0f);					
		m_pBlack[0]->SetPos(-230.0f, 512.0f, 0.0f);	
		m_pBlack[0]->SetLocalVec(0.0f, 0.0f);			
		m_pBlack[0]->SetOffset(0.0f, 0.0f);
		m_pBlack[0]->SetTexture(this, "Data/Image/Effect/Blind.png");	
		m_pBlack[0]->SetFrustumCulling(true);				
		m_pBlack[0]->SetBoundingBoxCalc(true);			
		m_pBlack[0]->SetBlend(true);						
		m_pBlack[0]->SetShow(true);
		m_pBlack[0]->SetOrtho2D(true);
		Commit(-99999,0,"pBlack", m_pBlack[0]);
		m_pBlack[1] = new CEMPlane();		
		m_pBlack[1]->SetSize(1.0f,1.0f);					
		m_pBlack[1]->SetPos(1024.0f + 230.0f, 512.0f, 0.0f);	
		m_pBlack[1]->SetLocalVec(0.0f, 0.0f);			
		m_pBlack[1]->SetOffset(0.0f, 0.0f);
		m_pBlack[1]->SetTexture(this, "Data/Image/Effect/Blind.png");	
		m_pBlack[1]->SetFrustumCulling(true);				
		m_pBlack[1]->SetBoundingBoxCalc(true);			
		m_pBlack[1]->SetBlend(true);						
		m_pBlack[1]->SetShow(true);
		m_pBlack[1]->SetOrtho2D(true);
		Commit(-99999,1,"pBlack", m_pBlack[1]);
	}
	g_nSelectStage = 0;
	m_nMaxStage = 0;
	
	LoadStage();
	for(int i=0; i<m_nMaxStage; i++)
	{
		g_bStageLock[i] = false;
	}
	g_bStageLock[0] = true;
	for(int i=0; i<m_nMaxStage; i++)
	{
		g_nScoreLevel[i] = 0;
	}
	SaveStage();
	float fTargetX = 0;
	float fTargetY = 0;

	//!=====================================================

	if(g_SoundOnOff == true)
	{
		
		for(int i=0; i<D_SOUND_MAX; i++)
		{
			if(bStopSound[i] == true)
			{
				bStopSound[i] = false;
				D_SOUND->Stop(Sound[i]);
			}
		}

		SoundFp = D_SOUND->FileOpen("Data/Sound/StageMenu_BGM.mp3");
		Sound[1] = D_SOUND->Play(SoundFp,1.0f,true);
		bStopSound[1] = true;
	}
	else if(g_SoundOnOff == false)
	{
		for(int i=0; i<D_SOUND_MAX; i++)
		{
			bStopSound[i] = false;
			D_SOUND->Stop(Sound[i]);
		}
	}


	//m_nMaxStage = 6;
	
	//!=====================================================

	//!=====================================================
	//!화면에 텍스쳐 출력하기
	//!=====================================================

	//!=====================================================
	//!화면에 Plane출력하기
	
	m_pBg = new CEMPlane();		
	m_pBg->SetSize(1.02f,1.02f);					
	m_pBg->SetPos(0.0f, 0.0f, 0.0f);	
	m_pBg->SetLocalVec(0.0f, 0.0f);			
	m_pBg->SetOffset(0.0f, 0.0f);
	m_pBg->SetTexture(this, "Data/Image/StageMenu/StageMenu_Bg.png");	
	m_pBg->SetFrustumCulling(true);				
	m_pBg->SetBoundingBoxCalc(true);			
	m_pBg->SetBlend(true);						
	m_pBg->SetShow(true);
	Commit(999,"배경", m_pBg);

	//m_pTextBox = new CEMTextDisplay();
	//m_pTextBox->Init(this,"씬표시",10,40,50,30,stEMVec2(1.0f,1.0f),CEMColor(0,0,0,255));
	//m_pTextBox->SetProgressTime(0.1f);

	//m_pTextBox->SetText("[Menu : 게임의 메뉴 입니다.]");


	//

	m_pButtonImg = new CEMPlane**[m_nMaxStage];
	m_pLockImg = new CEMPlane**[m_nMaxStage];

	m_pStar = new CEMPlane**[m_nMaxStage];




	for(int j=0; j<m_nMaxStage; j++)
	{
		m_pButtonImg[j] = new CEMPlane*[3];
		m_pLockImg[j] = new CEMPlane*[2];
		m_pStar[j] = new CEMPlane*[3];
	}

	fTargetX = D_STAGEMENU_START_X;
	fTargetY = D_STAGEMENU_START_Y;
	
	
	for(int j=0; j<m_nMaxStage; j++)
	{
		for(int i=0; i<3; i++)
		{
			m_pButtonImg[j][i] = new CEMPlane();						
			m_pButtonImg[j][i]->SetSize(1.0f,	1.0f);				
			m_pButtonImg[j][i]->SetPos(0.0f, 0.0f, 0.0f);
			m_pButtonImg[j][i]->SetLocalVec(0.0f, 0.0f);		
			m_pButtonImg[j][i]->SetOffset(0.0f, 0.0f);
			m_pButtonImg[j][i]->SetTexture(this, "Data/Image/StageMenu/Button_SelectMenu_"+IntToEMString(i+1)+".png");
			m_pButtonImg[j][i]->SetFrustumCulling(true);
			m_pButtonImg[j][i]->SetBoundingBoxCalc(true);
			m_pButtonImg[j][i]->SetBlend(true);	
			m_pButtonImg[j][i]->SetShow(true);
			m_pButtonImg[j][i]->SetBackFaceCulling(false);
			Commit(-30,(j*100) + i, "버튼", m_pButtonImg[j][i]);

		}

		for(int i=0; i<2; i++)
		{
			m_pLockImg[j][i] = new CEMPlane();						
			m_pLockImg[j][i]->SetSize(1.0f,	1.0f);				
			m_pLockImg[j][i]->SetPos(0.0f, 0.0f, 0.0f);				
			m_pLockImg[j][i]->SetLocalVec(0.0f, 0.0f);		
			m_pLockImg[j][i]->SetOffset(0.0f, 0.0f);
			m_pLockImg[j][i]->SetTexture(this, "Data/Image/Lock/Lock_"+IntToEMString(i+1)+".png");
			m_pLockImg[j][i]->SetFrustumCulling(true);
			m_pLockImg[j][i]->SetBoundingBoxCalc(true);
			m_pLockImg[j][i]->SetBlend(true);	
			m_pLockImg[j][i]->SetShow(true);
			m_pLockImg[j][i]->SetBackFaceCulling(false);
			Commit(-33,(j*100000) + i, "Lock", m_pLockImg[j][i]);

		}

		for(int i=0; i<3; i++)
		{
			m_pStar[j][i] = new CEMPlane();						
			m_pStar[j][i]->SetSize(0.5f, 0.5f);				
			m_pStar[j][i]->SetPos(fTargetX + (i*30) - 25, fTargetY - 30, 0.0f);				
			m_pStar[j][i]->SetLocalVec(0.0f, 0.0f);		
			m_pStar[j][i]->SetOffset(0.0f, 0.0f);
			m_pStar[j][i]->SetTexture(this, "Data/Image/StageMenu/Star.png");
			m_pStar[j][i]->SetFrustumCulling(true);
			m_pStar[j][i]->SetBoundingBoxCalc(true);
			m_pStar[j][i]->SetBlend(true);	
			m_pStar[j][i]->SetShow(true);
			m_pStar[j][i]->SetBackFaceCulling(false);
			Commit(-44,(j*100000) + i, "Star", m_pStar[j][i]);
			

		}

		fTargetX += D_STAGEMENU_DISTANCE;
		if(fTargetX >= D_STAGEMENU_START_X + (D_STAGEMENU_DISTANCE*3))
		{
			fTargetX = D_STAGEMENU_START_X;
			fTargetY -= D_STAGEMENU_DISTANCE;
		}
	}
	

	m_NumberButton = new CEMNumber*[m_nMaxStage];
	fTargetX = D_STAGEMENU_START_X;
	fTargetY = D_STAGEMENU_START_Y;
	
	

	
	for(int j=0; j<m_nMaxStage; j++)
	{
		int m_nStage = j+1;
		float fOffsetX = 0;

		while(1)
		{
			m_nStage /= 10;
			if(m_nStage <= 0)
				break;
			fOffsetX -= 22;
		}

		m_NumberButton[j] = new CEMNumber(10);
		m_NumberButton[j]->SetSize(1.2f, 1.2f);				
		m_NumberButton[j]->SetPos(fTargetX + fOffsetX, fTargetY, 0.0f);				
		m_NumberButton[j]->SetLocalVec(0.0f, 0.0f);		
		m_NumberButton[j]->SetOffset(0.0f, 0.0f);
		m_NumberButton[j]->SetTexture(this,10, "Data/Image/Number/0.png", "Data/Image/Number/1.png", "Data/Image/Number/2.png", "Data/Image/Number/3.png", "Data/Image/Number/4.png", "Data/Image/Number/5.png", "Data/Image/Number/6.png", "Data/Image/Number/7.png", "Data/Image/Number/8.png", "Data/Image/Number/9.png");
		m_NumberButton[j]->SetFrustumCulling(true);
		m_NumberButton[j]->SetBoundingBoxCalc(true);
		m_NumberButton[j]->SetBlend(true);	
		m_NumberButton[j]->SetShow(true);
		m_NumberButton[j]->SetBackFaceCulling(false);
		m_NumberButton[j]->SetNumber(j+1);
		Commit(-50,j,"NumberButton", m_NumberButton[j]);

		fTargetX += D_STAGEMENU_DISTANCE;
		if(fTargetX >= D_STAGEMENU_START_X + (D_STAGEMENU_DISTANCE*3))
		{
			fTargetX = D_STAGEMENU_START_X;
			fTargetY -= D_STAGEMENU_DISTANCE;
		}
	}

	m_Button = new CEMStyleButton[m_nMaxStage];
	
	fTargetX = D_STAGEMENU_START_X;
	fTargetY = D_STAGEMENU_START_Y;
	for(int j=0; j<m_nMaxStage; j++)
	{
		m_Button[j].Init(this,m_pButtonImg[j][0],m_pButtonImg[j][1],m_pButtonImg[j][2],stEMVec2(fTargetX, fTargetY), true);
		m_pLockImg[j][0]->SetPos(fTargetX, fTargetY, 0.0f);
		m_pLockImg[j][1]->SetPos(fTargetX, fTargetY, 0.0f);
		fTargetX += D_STAGEMENU_DISTANCE;
		if(fTargetX >= D_STAGEMENU_START_X + (D_STAGEMENU_DISTANCE*3))
		{
			fTargetX = D_STAGEMENU_START_X;
			fTargetY -= D_STAGEMENU_DISTANCE;
		}
	}
	for(int i=0; i<m_nMaxStage; i++)
	{
		if( g_bStageLock[i] == true )
		{
			m_pLockImg[i][0]->SetShow(true);
			m_pLockImg[i][1]->SetShow(false);
		}
		else if( g_bStageLock[i] == false )
		{
			m_pLockImg[i][0]->SetShow(false);
			m_pLockImg[i][1]->SetShow(true);
		}
	}


	for(int i=0; i<3; i++)
	{
		m_BackButton[i] = new CEMPlane();						
		m_BackButton[i]->SetSize(0.7f,	0.7f);				
		m_BackButton[i]->SetPos(0.0f, 0.0f, 0.0f);
		m_BackButton[i]->SetLocalVec(0.0f, 0.0f);		
		m_BackButton[i]->SetOffset(0.0f, 0.0f);
		m_BackButton[i]->SetTexture(this, "Data/Image/Button/Button_Back_"+IntToEMString(i+1)+".png");
		m_BackButton[i]->SetFrustumCulling(true);
		m_BackButton[i]->SetBoundingBoxCalc(true);
		m_BackButton[i]->SetBlend(true);	
		m_BackButton[i]->SetShow(false);
		m_BackButton[i]->SetBackFaceCulling(false);
		Commit(0, i, "뒤로가기버튼", m_BackButton[i]);
	}
	m_Back.Init(this,m_BackButton[0],m_BackButton[1],m_BackButton[2],stEMVec2(140.0f,-340.0f),true);


	m_fStarRot = 0.0f;
	CRootScene::Enter(pSceneWork);
}

void CStageMenu::Update(CSceneWork* pSceneWork, float dt)
{
	
	m_Back.Update(this,dt);
	m_fStarRot += dt;
	if(m_fStarRot >= 3.0f)
	{
		m_fStarRot = 0.0f;
	}
	
	for(int i=0; i<m_nMaxStage; i++)
	{
		for(int j=0; j<3; j++)
		{
			m_pStar[i][j]->SetShow(false);
		}

	}
	for(int i=0; i<m_nMaxStage; i++)
	{
		if( g_bStageLock[i] == true )
		{
			m_pLockImg[i][0]->SetShow(true);
			m_pLockImg[i][1]->SetShow(false);

			for(int j=0; j<g_nScoreLevel[i]; j++)
			{
				m_pStar[i][j]->SetShow(true);
				
				if(m_fStarRot <= 1.0f)
				{
					float fTemp = (m_fStarRot/1.0f) * 450.0f - (j*30);
					if(fTemp >= 360.0f)
						fTemp = 360.0f;

					m_pStar[i][j]->SetZRot( fTemp );
				}
			}
		}
		else if( g_bStageLock[i] == false )
		{
			m_pLockImg[i][0]->SetShow(false);
			m_pLockImg[i][1]->SetShow(true);
		}

		
	}

	if(m_Back.IsAction() == true)
	{
		m_Back.m_bAction = false;
		D_SCENE->ChangeSceneFade("Menu");
	}
	

	for(int j=0; j<m_nMaxStage; j++)
	{
		if(g_bStageLock[j] == true)
		{
			if( m_Button[j].IsAction() == true)
			{
				m_Button[j].m_bAction = false;
				D_SCENE->ChangeSceneFade("Stage");
				g_nSelectStage = j;
				break;
			}
		}
		else if(g_bStageLock[j] == false)
		{
			if( m_Button[j].IsAction() == true)
			{
				m_Button[j].m_bAction = false;
				break;
			}
		}
	}

	
	//if(m_pTextBox != NULL)
	//	m_pTextBox->Update(dt);

	for(int j=0; j<m_nMaxStage; j++)
	{
		//if(g_bStageLock[j] == true)
			m_Button[j].Update(this,dt);
	}
	

	m_stCamPos.m_fZ = D_CAM_Z_FIXED;
	D_CAMERA->SetPos(m_stCamPos);

	CRootScene::Update(pSceneWork, dt);
}

void CStageMenu::Render(CSceneWork* pSceneWork)
{


	CRootScene::Render(pSceneWork);
}


void CStageMenu::Exit(CSceneWork* pSceneWork)
{
	//m_pTextBox->Exit();
	//delete m_pTextBox;

	/*for(int j=0; j<m_nMaxStage; j++)
	{
		delete[]			m_pButtonImg[j];
	}
	delete[]			m_pButtonImg;
*/

	//for(int j=0; j<m_nMaxStage; j++)
	//{
	//	delete[]			m_NumberButton[j];
	//}
	//delete[]			m_NumberButton;

	SaveStage();

	delete[] m_Button;
	//delete[] g_bStageLock;
	Destroy();				//!< 현재 씬에서 메모리 잡은거 전부 해제
	
	

	CRootScene::Exit(pSceneWork);
}

void CStageMenu::MouseDownEvent(stMouseInfo stPos, enumMouseButton eButton)
{
	if(eButton == E_MOUSE_LEFT)
	{
		for(int j=0; j<m_nMaxStage; j++)
		{
			//if(g_bStageLock[j] == true)
				m_Button[j].Check_Down(stPos, -30);
		}

		m_Back.Check_Down(stPos,0);
	}
}

void CStageMenu::MouseUpEvent(stMouseInfo stPos, enumMouseButton eButton)
{
	if(eButton == E_MOUSE_LEFT)
	{
		for(int j=0; j<m_nMaxStage; j++)
		{
			//if(g_bStageLock[j] == true)
				m_Button[j].Check_Up(stPos, -30);
		}

		m_Back.Check_Up(stPos,0);	
	}
}

void CStageMenu::MouseMoveEvent(stMouseInfo stPos)
{
	for(int j=0; j<m_nMaxStage; j++)
	{
		//if(g_bStageLock[j] == true)
			m_Button[j].Check_Move(stPos, -30);
	}
	m_Back.Check_Move(stPos,0);
}

HRESULT CStageMenu::WindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_LBUTTONDOWN:
		{
			//D_SCENE->ChangeSceneFade("Stage",(0.1f),(0.1f));
		}break;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case 'N':
				g_bStageLock[m_nNowStage] = true;
				m_nNowStage++;
				break;

			case 'R':
				for(int i=0; i<m_nMaxStage; i++)
				{
					g_bStageLock[i] = false;
				}
				g_bStageLock[0] = true;
				m_nNowStage = 1;
				break;
			}
		}break;
	}
	return msg;
}


void CStageMenu::BeginContact(b2Contact* contact)
{
	CEMPhysicRoot::BeginContact(contact);
	//아래에 코드를 작성하세요


}

void CStageMenu::EndContact(b2Contact* contact)
{
	CEMPhysicRoot::EndContact(contact);
	//아래에 코드를 작성하세요

}

void CStageMenu::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	CEMPhysicRoot::PreSolve(contact, oldManifold);
	//아래에 코드를 작성하세요

}

void CStageMenu::PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
{
	CEMPhysicRoot::PostSolve(contact, impulse);
	//아래에 코드를 작성하세요

}
