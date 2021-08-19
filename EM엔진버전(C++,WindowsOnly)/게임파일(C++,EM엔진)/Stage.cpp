#include "stdafx.h"
stEMVec2	stMousePos;
int g_nScore = 0;
bool	g_bPause = false;
// Speak_None_1
CEMBlock* CStage::CreateBlock()
{
	CEMBlock* m_pBlock = new CEMBlock();
	int nRandX = CEMMath::RandomIntInRange(0,D_BLOCKMAP_WIDTH);
	int nRandY = CEMMath::RandomIntInRange(0,D_BLOCKMAP_HEIGHT);
	m_pBlock->Init(this,stVec2i(nRandX,nRandY),m_nCreateBlockNumber);
	m_Map->m_nBlockMap[m_pBlock->m_stIndex.m_fY][m_pBlock->m_stIndex.m_fX] = 1;
	m_nCreateBlockNumber++;
	g_nScore += D_SCORE_CREATEBLOCK;
	return m_pBlock;
}

CEMBlock* CStage::CreateBlock(int nX, int nY)
{
	CEMBlock* m_pBlock = new CEMBlock();
	m_pBlock->Init(this,stVec2i(nX,nY),m_nCreateBlockNumber);
	m_Map->m_nBlockMap[m_pBlock->m_stIndex.m_fY][m_pBlock->m_stIndex.m_fX] = 1;
	m_nCreateBlockNumber++; 
	g_nScore += D_SCORE_CREATEBLOCK;
	return m_pBlock;
}

CEMBlock* CStage::CreateBlock(int nX, int nY, int nBlockNumber)
{
	CEMBlock* m_pBlock = new CEMBlock();
	m_pBlock->Init(this,(E_BLOCKNUMBER)nBlockNumber,stVec2i(nX,nY),m_nCreateBlockNumber);
	m_Map->m_nBlockMap[m_pBlock->m_stIndex.m_fY][m_pBlock->m_stIndex.m_fX] = 1;
	m_nCreateBlockNumber++; 
	g_nScore += D_SCORE_CREATEBLOCK;
	return m_pBlock;
}
CEMBlock* CStage::CreateBlock(int nY)
{
	CEMBlock* m_pBlock = new CEMBlock();
	int nRandX = CEMMath::RandomIntInRange(0,D_BLOCKMAP_WIDTH);
	m_pBlock->Init(this,stVec2i(nRandX,nY),m_nCreateBlockNumber);
	m_Map->m_nBlockMap[m_pBlock->m_stIndex.m_fY][m_pBlock->m_stIndex.m_fX] = 1;
	m_nCreateBlockNumber++;
	g_nScore += D_SCORE_CREATEBLOCK;
	return m_pBlock;
}
void CStage::CreateLine(list<CEMBlock*>* BlockList, CEMCamShakeManager* CamShakeMng)
{
	if(CamShakeMng->IsShaking() == false)
	{
		for(int i=0; i<D_BLOCKMAP_WIDTH; i++)
		{
			BlockList->push_back(CreateBlock(i,0));
		}
		CamShakeMng->Shake(E_DERECTION_UPDOWN,3,300,150,10,4,2,2);
	}

}
void CStage::SaveStage()
{
	int m_nMaxStage = 0;
	FILE * fp = fopen("Data/StageInfo.txt","rt");
	FILE * fpw = fopen("Data/StageSave.sav","wb");
	FILE * fpw2 = fopen("Data/StageJudgment.sav","wb");

	fscanf(fp,"%d",&m_nMaxStage);


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
	fclose(fp);
	fclose(fpw2);

}
void CStage::ReadMap(int nStage)
{
	char sFileName[256];
	sprintf(sFileName,"Data/Map/Stage%d.txt",nStage);
	FILE* fp = fopen(sFileName,"rt");
	for(int i=0; i<D_BLOCKMAP_HEIGHT; i++)
	{
		for(int j=0; j<D_BLOCKMAP_WIDTH; j++)
		{
			int nTemp = fgetc(fp);
			if(nTemp == 'R')
			{
				m_Map->m_nBlockMap[i][j] = 1;	
				m_BlockList.push_back(CreateBlock(j,i));
			}
			else if(nTemp == '1')
			{
				m_Map->m_nBlockMap[i][j] = 1;
				m_BlockList.push_back(CreateBlock(j,i,1));
			}
			else if(nTemp == '2')
			{
				m_Map->m_nBlockMap[i][j] = 1;
				m_BlockList.push_back(CreateBlock(j,i,2));
			}
			else if(nTemp == '3')
			{
				m_Map->m_nBlockMap[i][j] = 1;
				m_BlockList.push_back(CreateBlock(j,i,3));
			}
			else if(nTemp == '4')
			{
				m_Map->m_nBlockMap[i][j] = 1;
				m_BlockList.push_back(CreateBlock(j,i,4));
			}
		}
		fgetc(fp);
	}
}

void CStage::Enter(CSceneWork* pSceneWork)
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


	m_nTtLevel = 0;

	int m_nNoteNumber = 0;
	m_fComboTimer = 0.0f;


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

		SoundFp = D_SOUND->FileOpen("Data/Sound/Game_BGM.mp3");
		Sound[2] = D_SOUND->Play(SoundFp,1.0f,true);
		bStopSound[2] = true;
	}
	else if(g_SoundOnOff == false)
	{
		for(int i=0; i<D_SOUND_MAX; i++)
		{
			bStopSound[i] = false;
			D_SOUND->Stop(Sound[i]);
		}
	}


	

	m_SoundIceFp = D_SOUND->FileOpen("Data/Sound/Ice.wav");

	m_SoundButtonFp = D_SOUND->FileOpen("Data/Sound/Button.wav");
	m_SoundEffectTtFp = D_SOUND->FileOpen("Data/Sound/TtEffect.wav");
	
	m_SoundPause1Fp = D_SOUND->FileOpen("Data/Sound/Pause1.wav");
	m_SoundPause2Fp = D_SOUND->FileOpen("Data/Sound/Pause2.wav");

	
	m_SoundWinFp = D_SOUND->FileOpen("Data/Sound/Game_Win.wav");
	m_SoundLoseFp = D_SOUND->FileOpen("Data/Sound/Game_Lose.wav");


	m_nCreateBlockNumber = 0;
	g_nScore = 0;



#ifdef _DEBUG
	//!=====================================================
	m_pBar = TwNewBar("Test");

	TwAddVarRW(m_pBar, "Camera_x", TW_TYPE_FLOAT, &m_stCamPos.m_fX, " label = 'Camera x' min=-1000 max=2500 step=0.1 keyIncr=z keyDecr=Z help = 'Camera x' ");
	TwAddVarRW(m_pBar, "Camera_y", TW_TYPE_FLOAT, &m_stCamPos.m_fY, " label = 'Camera y' min=-1000 max=2500 step=0.1 keyIncr=z keyDecr=Z help = 'Camera y' ");
	TwAddVarRW(m_pBar, "Camera_z", TW_TYPE_FLOAT, &m_stCamPos.m_fZ, " label = 'Camera z' min=-1000 max=2500 step=0.1 keyIncr=z keyDecr=Z help = 'Camera z' ");
	TwAddVarRW(m_pBar, "TimeLimit", TW_TYPE_FLOAT, &m_fTimeLimit, " label = 'TimeLimit' min=-1000 max=2500 step=1.0 keyIncr=z keyDecr=Z help = 'TimeLimit' ");
	TwAddVarRW(m_pBar, "Score", TW_TYPE_INT32, &g_nScore, " label = 'Score' min=-1000 max=2500 step=10.0 keyIncr=z keyDecr=Z help = 'Score' ");
#endif

	//!=====================================================

	//!툴바 붙이기
	//!=====================================================

	//!=====================================================
	//!화면에 텍스쳐 출력하기
	m_pText = new CEMText("으뜸체", "마우스 좌표 출력");		//!< 화면에 출력될 내용
	m_pText->SetColor(CEMColor(0, 0, 0, 255));					//!< 색상 r,g,b,a
	m_pText->SetSize(0.8f,0.8f);
	m_pText->SetPos(D_INTERFACE_START_X, 105.0f);									//!< 출력위치 x,y

	Commit(-30, "테스트", m_pText);


	//m_TextDisplay = new CEMTextDisplay();
	//m_TextDisplay->Init(this,"TextDisplay",20,120,50,30,stEMVec2(0.8f,0.8f),CEMColor(0, 0, 0, 255));
	//m_TextDisplay->SetProgressTime(0.03f);
	
	//m_pTtMsg = new CEMText("으뜸체", "튜토리얼 메세지");
	//m_pTtMsg->SetColor(CEMColor(0, 0, 0, 255));					//!< 색상 r,g,b,a
	//m_pTtMsg->SetSize(0.8f,0.8f);
	//m_pTtMsg->SetPos(D_INTERFACE_START_X, 600.0f);									//!< 출력위치 x,y

	//Commit(-30, "튜토리얼메세지", m_pTtMsg);

	//!=====================================================
	m_pTextNowBlock = new CEMText("으뜸체", "현재 클릭된 블록 출력");		//!< 화면에 출력될 내용
	m_pTextNowBlock->SetColor(CEMColor(0, 0, 0, 255));					//!< 색상 r,g,b,a
	m_pTextNowBlock->SetSize(0.8f,0.8f);
	m_pTextNowBlock->SetPos(D_INTERFACE_START_X, D_INTERFACE_NOWBLOCK_TEXT_Y);									//!< 출력위치 x,y

	Commit(-30, "현재클릭된블록Text", m_pTextNowBlock);
	//!=====================================================
	m_pTextMouseList = new CEMText("으뜸체", "MouseList블록 출력");		//!< 화면에 출력될 내용
	m_pTextMouseList->SetColor(CEMColor(0, 0, 0, 255));					//!< 색상 r,g,b,a
	m_pTextMouseList->SetSize(0.8f,0.8f);
	m_pTextMouseList->SetPos(D_INTERFACE_START_X, D_INTERFACE_MOUSELIST_TEXT_Y);									//!< 출력위치 x,y

	Commit(-30, "MouseList블록Text", m_pTextMouseList);
	//!=====================================================

	//!=====================================================

	m_pTextErosionSpeed = new CEMText("으뜸체", "");		//!< 화면에 출력될 내용
	m_pTextErosionSpeed->SetColor(CEMColor(0, 0, 0, 255));					//!< 색상 r,g,b,a
	m_pTextErosionSpeed->SetSize(0.8f,0.8f);
	m_pTextErosionSpeed->SetPos(D_INTERFACE_START_X, D_INTERFACE_EROSIONSPEED_TEXT_Y);									//!< 출력위치 x,y

	Commit(-30, "침식속도Text", m_pTextErosionSpeed);
	//!=====================================================

	m_pTextCreateTime = new CEMText("으뜸체", "");		//!< 화면에 출력될 내용
	m_pTextCreateTime->SetColor(CEMColor(0, 0, 0, 255));					//!< 색상 r,g,b,a
	m_pTextCreateTime->SetSize(0.8f,0.8f);
	m_pTextCreateTime->SetPos(D_INTERFACE_START_X, D_INTERFACE_CREATETIME_TEXT_Y);									//!< 출력위치 x,y

	Commit(-30, "생성시간Text", m_pTextCreateTime);

	//!=====================================================

	m_pTextErosionPlusSpeed = new CEMText("으뜸체", "");		//!< 화면에 출력될 내용
	m_pTextErosionPlusSpeed->SetColor(CEMColor(0, 0, 0, 255));					//!< 색상 r,g,b,a
	m_pTextErosionPlusSpeed->SetSize(0.8f,0.8f);
	m_pTextErosionPlusSpeed->SetPos(D_INTERFACE_START_X, D_INTERFACE_EROSIONPLUSSPEED_TEXT_Y);									//!< 출력위치 x,y

	Commit(-30, "침식가속도Text", m_pTextErosionPlusSpeed);
	//!=====================================================

	m_pTextFreeDrag = new CEMText("으뜸체", "");		//!< 화면에 출력될 내용
	m_pTextFreeDrag->SetColor(CEMColor(0, 0, 0, 255));					//!< 색상 r,g,b,a
	m_pTextFreeDrag->SetSize(0.8f,0.8f);
	m_pTextFreeDrag->SetPos(D_INTERFACE_START_X, D_INTERFACE_FREEMOVE_TEXT_Y);									//!< 출력위치 x,y

	Commit(-30, "프리드래그Text", m_pTextFreeDrag);

	//!=====================================================


	for(int i=0; i<5; i++)
	{
		//!화면에 Plane출력하기
		m_pBackGround[i] = new CEMPlane();						//!< 생성자로 Plane을 생성
		m_pBackGround[i]->SetSize(1.02f,	1.02f);					//!< Plane의 사이즈 설저
		m_pBackGround[i]->SetPos(0.0f, -1.0f, 0.0f);				//!< Plane의 월드좌표 설정
		m_pBackGround[i]->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pBackGround[i]->SetOffset(0.0f, 0.0f);
		m_pBackGround[i]->SetTexture(this, "Data/Image/Stage/Stage_"+IntToEMString(i)+".png");	//!< Plane위에 랜더링 되어질 텍스쳐
		m_pBackGround[i]->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pBackGround[i]->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pBackGround[i]->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pBackGround[i]->SetShow(true);
		m_pBackGround[i]->SetBackFaceCulling(false);
		if(i == 0)
			Commit(999,5-i, "배경", m_pBackGround[i]);
		else if(i == 1)
			Commit(99,5-i, "배경", m_pBackGround[i]);
		else if(i == 2)
		{
			m_pBackGround[i]->SetColor(1.0f,1.0f,1.0f,0.35f);
			Commit(0,5-i, "배경", m_pBackGround[i]);

		}
		else if(i == 3)
			Commit(-10,5-i, "배경", m_pBackGround[i]);
		else if(i == 4)
		{
			m_pBackGround[i]->SetPos(0.0f, -25.0f, 0.0f);				//!< Plane의 월드좌표 설정
			Commit(-11,5-i, "배경", m_pBackGround[i]);
		}
	}

	//!화면에 Plane출력하기
	m_pGameOver = new CEMPlane();						//!< 생성자로 Plane을 생성
	m_pGameOver->SetSize(1.02f,	1.02f);					//!< Plane의 사이즈 설저
	m_pGameOver->SetPos(0.0f, 3.0f, 0.0f);				//!< Plane의 월드좌표 설정
	m_pGameOver->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	m_pGameOver->SetOffset(0.0f, 0.0f);
	m_pGameOver->SetTexture(this, "Data/Image/Stage/GameOver.png");	//!< Plane위에 랜더링 되어질 텍스쳐
	m_pGameOver->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	m_pGameOver->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	m_pGameOver->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	m_pGameOver->SetShow(false);
	m_pGameOver->SetBackFaceCulling(false);

	Commit(-99, "게임패배", m_pGameOver);


	//!화면에 Plane출력하기
	m_pPause = new CEMPlane();						//!< 생성자로 Plane을 생성
	m_pPause->SetSize(1.02f,	1.02f);					//!< Plane의 사이즈 설저
	m_pPause->SetPos(0.0f, 3.0f, 0.0f);				//!< Plane의 월드좌표 설정
	m_pPause->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	m_pPause->SetOffset(0.0f, 0.0f);
	m_pPause->SetTexture(this, "Data/Image/Effect/Pause.png");	//!< Plane위에 랜더링 되어질 텍스쳐
	m_pPause->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	m_pPause->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	m_pPause->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	m_pPause->SetShow(true);
	//m_pPause->SetOrtho2D(true);
	m_pPause->SetBackFaceCulling(false);

	Commit(-999, "일시정지", m_pPause);


	m_pBlind = new CEMPlane();		
	m_pBlind->SetSize(1.02f,1.02f);					
	m_pBlind->SetPos(0.0f, 0.0f, 0.0f);	
	m_pBlind->SetLocalVec(0.0f, 0.0f);			
	m_pBlind->SetOffset(0.0f, 0.0f);
	m_pBlind->SetTexture(this, "Data/Image/Effect/Blind.png");	
	m_pBlind->SetFrustumCulling(true);				
	m_pBlind->SetBoundingBoxCalc(true);			
	m_pBlind->SetBlend(true);						
	m_pBlind->SetShow(false);
	//m_pBlind->SetOrtho2D(true);
	m_pBlind->SetBackFaceCulling(false);
	Commit(-998,"블라인드", m_pBlind);

	m_fBlindTimer = 0.0f;

	//!화면에 Plane출력하기
	m_pWhite = new CEMPlane();						//!< 생성자로 Plane을 생성
	m_pWhite->SetSize(2.0f,	2.0f);					//!< Plane의 사이즈 설저
	m_pWhite->SetPos(0.0f, 0.0f, 0.0f);				//!< Plane의 월드좌표 설정
	m_pWhite->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	m_pWhite->SetOffset(0.0f, 0.0f);
	m_pWhite->SetTexture(this, "Data/Image/Stage/White.png");	//!< Plane위에 랜더링 되어질 텍스쳐
	m_pWhite->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	m_pWhite->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	m_pWhite->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	m_pWhite->SetShow(true);
	m_pWhite->SetBackFaceCulling(false);

	Commit(9999, "White", m_pWhite);
	
	//!=====================================================/
	m_pGameClear = new CEMPlane();						//!< 생성자로 Plane을 생성
	m_pGameClear->SetSize(1.02f,	1.02f);					//!< Plane의 사이즈 설저
	m_pGameClear->SetPos(0.0f, 3.0f, 0.0f);				//!< Plane의 월드좌표 설정
	m_pGameClear->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	m_pGameClear->SetOffset(0.0f, 0.0f);
	m_pGameClear->SetTexture(this, "Data/Image/Stage/GameClear.png");	//!< Plane위에 랜더링 되어질 텍스쳐
	m_pGameClear->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	m_pGameClear->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	m_pGameClear->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	m_pGameClear->SetShow(false);
	m_pGameClear->SetBackFaceCulling(false);

	Commit(-99, "게임승리", m_pGameClear);

	//!=====================================================/
	//!=====================================================//!화면에 Plane출력하기
	m_pInterfaceBox = new CEMPlane();						//!< 생성자로 Plane을 생성
	m_pInterfaceBox->SetSize(1.0f,	1.0f);					//!< Plane의 사이즈 설저
	m_pInterfaceBox->SetPos(0.0f, 0.0f, 0.0f);				//!< Plane의 월드좌표 설정
	m_pInterfaceBox->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	m_pInterfaceBox->SetOffset(0.0f, 0.0f);
	m_pInterfaceBox->SetTexture(this, "Data/Image/Stage/Interface.png");	//!< Plane위에 랜더링 되어질 텍스쳐
	m_pInterfaceBox->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	m_pInterfaceBox->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	m_pInterfaceBox->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	m_pInterfaceBox->SetShow(false);
	m_pInterfaceBox->SetBackFaceCulling(false);
	m_pInterfaceBox->SetOrtho2D(true);

	Commit(-29, "인터페이스", m_pInterfaceBox);
	//!=====================================================

	//!=====================================================

	//!화면에 Plane출력하기
	m_pButtonUpCreateTimeImg[0] = new CEMPlane();						
	m_pButtonUpCreateTimeImg[0]->SetSize(1.0f,	1.0f);				
	m_pButtonUpCreateTimeImg[0]->SetPos(0.0f, 0.0f, 0.0f);				
	m_pButtonUpCreateTimeImg[0]->SetLocalVec(0.0f, 0.0f);		
	m_pButtonUpCreateTimeImg[0]->SetOffset(0.0f, 0.0f);
	m_pButtonUpCreateTimeImg[0]->SetTexture(this, "Data/Image/Button/Button_Up_1.png");
	m_pButtonUpCreateTimeImg[0]->SetFrustumCulling(true);
	m_pButtonUpCreateTimeImg[0]->SetBoundingBoxCalc(true);
	m_pButtonUpCreateTimeImg[0]->SetBlend(true);	
	m_pButtonUpCreateTimeImg[0]->SetShow(true);
	m_pButtonUpCreateTimeImg[0]->SetBackFaceCulling(false);

	Commit(-30,0, "ButtonUpCreateTimeImg", m_pButtonUpCreateTimeImg[0]);

	//!=====================================================
	//!화면에 Plane출력하기
	m_pButtonUpCreateTimeImg[1] = new CEMPlane();						
	m_pButtonUpCreateTimeImg[1]->SetSize(1.0f,	1.0f);				
	m_pButtonUpCreateTimeImg[1]->SetPos(0.0f, 0.0f, 0.0f);				
	m_pButtonUpCreateTimeImg[1]->SetLocalVec(0.0f, 0.0f);		
	m_pButtonUpCreateTimeImg[1]->SetOffset(0.0f, 0.0f);
	m_pButtonUpCreateTimeImg[1]->SetTexture(this, "Data/Image/Button/Button_Up_2.png");
	m_pButtonUpCreateTimeImg[1]->SetFrustumCulling(true);
	m_pButtonUpCreateTimeImg[1]->SetBoundingBoxCalc(true);
	m_pButtonUpCreateTimeImg[1]->SetBlend(true);	
	m_pButtonUpCreateTimeImg[1]->SetShow(true);
	m_pButtonUpCreateTimeImg[1]->SetBackFaceCulling(false);

	Commit(-30,1, "ButtonUpCreateTimeImg", m_pButtonUpCreateTimeImg[1]);

	//!=====================================================
	//!화면에 Plane출력하기
	m_pButtonUpCreateTimeImg[2] = new CEMPlane();						
	m_pButtonUpCreateTimeImg[2]->SetSize(1.0f,	1.0f);				
	m_pButtonUpCreateTimeImg[2]->SetPos(0.0f, 0.0f, 0.0f);				
	m_pButtonUpCreateTimeImg[2]->SetLocalVec(0.0f, 0.0f);		
	m_pButtonUpCreateTimeImg[2]->SetOffset(0.0f, 0.0f);
	m_pButtonUpCreateTimeImg[2]->SetTexture(this, "Data/Image/Button/Button_Up_3.png");
	m_pButtonUpCreateTimeImg[2]->SetFrustumCulling(true);
	m_pButtonUpCreateTimeImg[2]->SetBoundingBoxCalc(true);
	m_pButtonUpCreateTimeImg[2]->SetBlend(true);	
	m_pButtonUpCreateTimeImg[2]->SetShow(true);
	m_pButtonUpCreateTimeImg[2]->SetBackFaceCulling(false);

	Commit(-30,2, "ButtonUpCreateTimeImg", m_pButtonUpCreateTimeImg[2]);
	//!=====================================================

	//!화면에 Plane출력하기
	m_pButtonDownCreateTimeImg[0] = new CEMPlane();						
	m_pButtonDownCreateTimeImg[0]->SetSize(1.0f,	1.0f);				
	m_pButtonDownCreateTimeImg[0]->SetPos(0.0f, 0.0f, 0.0f);				
	m_pButtonDownCreateTimeImg[0]->SetLocalVec(0.0f, 0.0f);		
	m_pButtonDownCreateTimeImg[0]->SetOffset(0.0f, 0.0f);
	m_pButtonDownCreateTimeImg[0]->SetTexture(this, "Data/Image/Button/Button_Down_1.png");
	m_pButtonDownCreateTimeImg[0]->SetFrustumCulling(true);
	m_pButtonDownCreateTimeImg[0]->SetBoundingBoxCalc(true);
	m_pButtonDownCreateTimeImg[0]->SetBlend(true);	
	m_pButtonDownCreateTimeImg[0]->SetShow(true);
	m_pButtonDownCreateTimeImg[0]->SetBackFaceCulling(false);

	Commit(-30,0, "ButtonDownCreateTimeImg", m_pButtonDownCreateTimeImg[0]);

	//!=====================================================
	//!화면에 Plane출력하기
	m_pButtonDownCreateTimeImg[1] = new CEMPlane();						
	m_pButtonDownCreateTimeImg[1]->SetSize(1.0f,	1.0f);				
	m_pButtonDownCreateTimeImg[1]->SetPos(0.0f, 0.0f, 0.0f);				
	m_pButtonDownCreateTimeImg[1]->SetLocalVec(0.0f, 0.0f);		
	m_pButtonDownCreateTimeImg[1]->SetOffset(0.0f, 0.0f);
	m_pButtonDownCreateTimeImg[1]->SetTexture(this, "Data/Image/Button/Button_Down_2.png");
	m_pButtonDownCreateTimeImg[1]->SetFrustumCulling(true);
	m_pButtonDownCreateTimeImg[1]->SetBoundingBoxCalc(true);
	m_pButtonDownCreateTimeImg[1]->SetBlend(true);	
	m_pButtonDownCreateTimeImg[1]->SetShow(true);
	m_pButtonDownCreateTimeImg[1]->SetBackFaceCulling(false);

	Commit(-30,1, "ButtonDownCreateTimeImg", m_pButtonDownCreateTimeImg[1]);

	//!=====================================================
	//!화면에 Plane출력하기
	m_pButtonDownCreateTimeImg[2] = new CEMPlane();						
	m_pButtonDownCreateTimeImg[2]->SetSize(1.0f,	1.0f);				
	m_pButtonDownCreateTimeImg[2]->SetPos(0.0f, 0.0f, 0.0f);				
	m_pButtonDownCreateTimeImg[2]->SetLocalVec(0.0f, 0.0f);		
	m_pButtonDownCreateTimeImg[2]->SetOffset(0.0f, 0.0f);
	m_pButtonDownCreateTimeImg[2]->SetTexture(this, "Data/Image/Button/Button_Down_3.png");
	m_pButtonDownCreateTimeImg[2]->SetFrustumCulling(true);
	m_pButtonDownCreateTimeImg[2]->SetBoundingBoxCalc(true);
	m_pButtonDownCreateTimeImg[2]->SetBlend(true);	
	m_pButtonDownCreateTimeImg[2]->SetShow(true);
	m_pButtonDownCreateTimeImg[2]->SetBackFaceCulling(false);

	Commit(-30,2, "ButtonDownCreateTimeImg", m_pButtonDownCreateTimeImg[2]);
	//!=====================================================

	for(int i=0; i<3; i++)
	{
		m_pButtonUpErosionPlusSpeedImg[i] = new CEMPlane();						
		m_pButtonUpErosionPlusSpeedImg[i]->SetSize(1.0f,	1.0f);				
		m_pButtonUpErosionPlusSpeedImg[i]->SetPos(0.0f, 0.0f, 0.0f);				
		m_pButtonUpErosionPlusSpeedImg[i]->SetLocalVec(0.0f, 0.0f);		
		m_pButtonUpErosionPlusSpeedImg[i]->SetOffset(0.0f, 0.0f);
		m_pButtonUpErosionPlusSpeedImg[i]->SetTexture(this, "Data/Image/Button/Button_Up_"+IntToEMString(i+1)+".png");
		m_pButtonUpErosionPlusSpeedImg[i]->SetFrustumCulling(true);
		m_pButtonUpErosionPlusSpeedImg[i]->SetBoundingBoxCalc(true);
		m_pButtonUpErosionPlusSpeedImg[i]->SetBlend(true);	
		m_pButtonUpErosionPlusSpeedImg[i]->SetShow(true);
		m_pButtonUpErosionPlusSpeedImg[i]->SetBackFaceCulling(false);
		Commit(-30,i, "ButtonUpErosionPlusSpeedImg", m_pButtonUpErosionPlusSpeedImg[i]);
	}
	for(int i=0; i<3; i++)
	{
		m_pButtonDownErosionPlusSpeedImg[i] = new CEMPlane();						
		m_pButtonDownErosionPlusSpeedImg[i]->SetSize(1.0f,	1.0f);				
		m_pButtonDownErosionPlusSpeedImg[i]->SetPos(0.0f, 0.0f, 0.0f);				
		m_pButtonDownErosionPlusSpeedImg[i]->SetLocalVec(0.0f, 0.0f);		
		m_pButtonDownErosionPlusSpeedImg[i]->SetOffset(0.0f, 0.0f);
		m_pButtonDownErosionPlusSpeedImg[i]->SetTexture(this, "Data/Image/Button/Button_Down_"+IntToEMString(i+1)+".png");
		m_pButtonDownErosionPlusSpeedImg[i]->SetFrustumCulling(true);
		m_pButtonDownErosionPlusSpeedImg[i]->SetBoundingBoxCalc(true);
		m_pButtonDownErosionPlusSpeedImg[i]->SetBlend(true);	
		m_pButtonDownErosionPlusSpeedImg[i]->SetShow(true);
		m_pButtonDownErosionPlusSpeedImg[i]->SetBackFaceCulling(false);
		Commit(-30,i, "ButtonDownErosionPlusSpeedImg", m_pButtonDownErosionPlusSpeedImg[i]);
	}

	for(int i=0; i<3; i++)
	{
		m_pButtonUpErosionSpeedImg[i] = new CEMPlane();						
		m_pButtonUpErosionSpeedImg[i]->SetSize(1.0f,	1.0f);				
		m_pButtonUpErosionSpeedImg[i]->SetPos(0.0f, 0.0f, 0.0f);				
		m_pButtonUpErosionSpeedImg[i]->SetLocalVec(0.0f, 0.0f);		
		m_pButtonUpErosionSpeedImg[i]->SetOffset(0.0f, 0.0f);
		m_pButtonUpErosionSpeedImg[i]->SetTexture(this, "Data/Image/Button/Button_Up_"+IntToEMString(i+1)+".png");
		m_pButtonUpErosionSpeedImg[i]->SetFrustumCulling(true);
		m_pButtonUpErosionSpeedImg[i]->SetBoundingBoxCalc(true);
		m_pButtonUpErosionSpeedImg[i]->SetBlend(true);	
		m_pButtonUpErosionSpeedImg[i]->SetShow(true);
		m_pButtonUpErosionSpeedImg[i]->SetBackFaceCulling(false);
		Commit(-30,i, "ButtonUpErosionSpeedImg", m_pButtonUpErosionSpeedImg[i]);
	}
	for(int i=0; i<3; i++)
	{
		m_pButtonDownErosionSpeedImg[i] = new CEMPlane();						
		m_pButtonDownErosionSpeedImg[i]->SetSize(1.0f,	1.0f);				
		m_pButtonDownErosionSpeedImg[i]->SetPos(0.0f, 0.0f, 0.0f);				
		m_pButtonDownErosionSpeedImg[i]->SetLocalVec(0.0f, 0.0f);		
		m_pButtonDownErosionSpeedImg[i]->SetOffset(0.0f, 0.0f);
		m_pButtonDownErosionSpeedImg[i]->SetTexture(this, "Data/Image/Button/Button_Down_"+IntToEMString(i+1)+".png");
		m_pButtonDownErosionSpeedImg[i]->SetFrustumCulling(true);
		m_pButtonDownErosionSpeedImg[i]->SetBoundingBoxCalc(true);
		m_pButtonDownErosionSpeedImg[i]->SetBlend(true);	
		m_pButtonDownErosionSpeedImg[i]->SetShow(true);
		m_pButtonDownErosionSpeedImg[i]->SetBackFaceCulling(false);
		Commit(-30,i, "ButtonDownErosionSpeedImg", m_pButtonDownErosionSpeedImg[i]);
	}

	for(int i=0; i<3; i++)
	{
		m_pButtonFreeMove[i] = new CEMPlane();						
		m_pButtonFreeMove[i]->SetSize(1.0f,	1.0f);				
		m_pButtonFreeMove[i]->SetPos(0.0f, 0.0f, 0.0f);				
		m_pButtonFreeMove[i]->SetLocalVec(0.0f, 0.0f);		
		m_pButtonFreeMove[i]->SetOffset(0.0f, 0.0f);
		m_pButtonFreeMove[i]->SetTexture(this, "Data/Image/Button/Button_Stop_"+IntToEMString(i+1)+".png");
		m_pButtonFreeMove[i]->SetFrustumCulling(true);
		m_pButtonFreeMove[i]->SetBoundingBoxCalc(true);
		m_pButtonFreeMove[i]->SetBlend(true);	
		m_pButtonFreeMove[i]->SetShow(true);
		m_pButtonFreeMove[i]->SetBackFaceCulling(false);
		Commit(-30,i, "mButtonFreeMove", m_pButtonFreeMove[i]);
	}

	
	m_ButtonUpErosionSpeed.Init(this,m_pButtonUpErosionSpeedImg[0],m_pButtonUpErosionSpeedImg[1],m_pButtonUpErosionSpeedImg[2], stEMVec2(D_INTERFACE_X,225), true);
	m_ButtonDownErosionSpeed.Init(this,m_pButtonDownErosionSpeedImg[0],m_pButtonDownErosionSpeedImg[1],m_pButtonDownErosionSpeedImg[2], stEMVec2(D_INTERFACE_X,195), true);

	m_ButtonUpCreateTime.Init(this,m_pButtonUpCreateTimeImg[0],m_pButtonUpCreateTimeImg[1],m_pButtonUpCreateTimeImg[2], stEMVec2(D_INTERFACE_X,165), true);
	m_ButtonDownCreateTime.Init(this,m_pButtonDownCreateTimeImg[0],m_pButtonDownCreateTimeImg[1],m_pButtonDownCreateTimeImg[2], stEMVec2(D_INTERFACE_X,135), true);

	m_ButtonUpErosionPlusSpeed.Init(this,m_pButtonUpErosionPlusSpeedImg[0],m_pButtonUpErosionPlusSpeedImg[1],m_pButtonUpErosionPlusSpeedImg[2], stEMVec2(D_INTERFACE_X,105), true);
	m_ButtonDownErosionPlusSpeed.Init(this,m_pButtonDownErosionPlusSpeedImg[0],m_pButtonDownErosionPlusSpeedImg[1],m_pButtonDownErosionPlusSpeedImg[2], stEMVec2(D_INTERFACE_X,75), true);


	m_ButtonFreeMove.Init(this,m_pButtonFreeMove[0],m_pButtonFreeMove[1],m_pButtonFreeMove[2],stEMVec2(D_INTERFACE_X,35), true);

	m_CamShakeMng = new CEMCamShakeManager();
	m_CamShakeMng->Init(&m_stCamPos);
	

	for(int i=0; i<5; i++)
	{
		m_pTtImg[i] = new CEMPlane();						
		m_pTtImg[i]->SetSize(1.0f,	1.0f);				
		m_pTtImg[i]->SetPos(0.0f, 70.0f, 0.0f);				
		m_pTtImg[i]->SetLocalVec(0.0f, 0.0f);		
		m_pTtImg[i]->SetOffset(0.0f, 0.0f);
		m_pTtImg[i]->SetTexture(this, "Data/Image/TtMsg/TtMsg_"+IntToEMString(i+1)+".png");
		m_pTtImg[i]->SetFrustumCulling(true);
		m_pTtImg[i]->SetBoundingBoxCalc(true);
		m_pTtImg[i]->SetBlend(true);	
		m_pTtImg[i]->SetShow(false);
		m_pTtImg[i]->SetBackFaceCulling(false);
		Commit(-99,i, "pTtImg", m_pTtImg[i]);
	}

	for(int i=0; i<3; i++)
	{
		m_pStar[i] = new CEMPlane();						
		m_pStar[i]->SetSize(1.0f,	1.0f);				
		m_pStar[i]->SetPos(+60.0f + (60*i), -100.0f, 0.0f);				
		m_pStar[i]->SetLocalVec(0.0f, 0.0f);		
		m_pStar[i]->SetOffset(0.0f, 0.0f);
		m_pStar[i]->SetTexture(this, "Data/Image/StageMenu/Star.png");
		m_pStar[i]->SetFrustumCulling(true);
		m_pStar[i]->SetBoundingBoxCalc(true);
		m_pStar[i]->SetBlend(true);	
		m_pStar[i]->SetShow(false);
		m_pStar[i]->SetBackFaceCulling(false);
		Commit(-1000,i, "pStar", m_pStar[i]);
	}



	m_Sled = new CEMSled();
	m_Sled->Init(this);

	m_Map = new CEMMap();
	m_Map->Init();

	m_BlockList.clear();

	m_stCamPos.m_fX = 0.0f;
	m_stCamPos.m_fY = 0.0f;
	m_stCamPos.m_fZ = D_CAM_Z_FIXED;
	m_fGravityTimer = 0.0f;

	m_fGameEndBlind = 0.0f;

	m_nStage = g_nSelectStage + 1;

	m_MouseList.clear();

	m_nMaxSnow = 0;
	m_IsMouseDown = false;
	m_nTurnStep = 0;
	m_bTurnAble = true;
	m_eBlockAct = E_BLOCKACT_NONE;
	m_bBlockAct = false;
	m_eBlockDragDerection = E_BLOCKDRAG_DEFECTION_LEFT;
	m_nTurnSkipBlock = 0;

	m_EffectMng = new CEMEffectManager();
	m_EffectMng->Init(this);
	int i = 0;
	list<stStageInfo*>::iterator it;
	for(i=0, it = g_StageInfo.begin(); i<g_nSelectStage; i++, it++);

	m_fTimeLimit = (*it)->m_fTimeLimit;
	m_fCraeteTime = (*it)->m_fCraeteTime;
	m_fErosionSpeed = (*it)->m_fErosionSpeed;
	m_nErosionPlusSpeed = (*it)->m_nErosionPlusSpeed;
	m_nMaxSnow = (*it)->m_nMaxSnow;

	float fSnowSpeed = 400.0f + (g_nSelectStage*40);
	if(fSnowSpeed >= 750.0f)
		fSnowSpeed = 750.0f;
	
	m_SnowMng = new CEMSnowMng();
	m_SnowMng->Init(this, m_nMaxSnow,E_SNOW_OPTION_STAGE, CEMColor(255,255,255), fSnowSpeed);


	m_fCreateTimer = 0.0;

	m_bFreeMove = false;
	m_bOptionOnOff = false;

	m_nFirstCreateBlockNumber = 0;
	m_fFirstCreateBlockTimer = 0.0f;
	m_fFirstCreateBlockTime = 0.5f;


	m_pNumberTimeLimit = new CEMNumber(10);
	m_pNumberTimeLimit->SetSize(1.0f, 1.0f);				
	m_pNumberTimeLimit->SetPos(-15.0f, 300.0f, 0.0f);				
	m_pNumberTimeLimit->SetLocalVec(0.0f, 0.0f);		
	m_pNumberTimeLimit->SetOffset(0.0f, 0.0f);
	m_pNumberTimeLimit->SetTexture(this,10, "Data/Image/Number/0.png", "Data/Image/Number/1.png", "Data/Image/Number/2.png", "Data/Image/Number/3.png", "Data/Image/Number/4.png", "Data/Image/Number/5.png", "Data/Image/Number/6.png", "Data/Image/Number/7.png", "Data/Image/Number/8.png", "Data/Image/Number/9.png");
	m_pNumberTimeLimit->SetFrustumCulling(true);
	m_pNumberTimeLimit->SetBoundingBoxCalc(true);
	m_pNumberTimeLimit->SetBlend(true);	
	m_pNumberTimeLimit->SetShow(true);
	m_pNumberTimeLimit->SetColor(0.5f,1.0f,0.5f);
	m_pNumberTimeLimit->SetBackFaceCulling(false);
	Commit(-30,"NumberTimeLimit", m_pNumberTimeLimit);


	m_pNumberStage = new CEMNumber(10);
	m_pNumberStage->SetSize(0.8f, 0.8f);				
	m_pNumberStage->SetPos(158.0f, 350.0f, 0.0f);				
	m_pNumberStage->SetLocalVec(0.0f, 0.0f);		
	m_pNumberStage->SetOffset(0.0f, 0.0f);
	m_pNumberStage->SetTexture(this,10, "Data/Image/Number/0.png", "Data/Image/Number/1.png", "Data/Image/Number/2.png", "Data/Image/Number/3.png", "Data/Image/Number/4.png", "Data/Image/Number/5.png", "Data/Image/Number/6.png", "Data/Image/Number/7.png", "Data/Image/Number/8.png", "Data/Image/Number/9.png");
	m_pNumberStage->SetFrustumCulling(true);
	m_pNumberStage->SetBoundingBoxCalc(true);
	m_pNumberStage->SetBlend(true);	
	m_pNumberStage->SetShow(true);
	m_pNumberStage->SetColor(0.5f,1.0f,0.5f);
	m_pNumberStage->SetBackFaceCulling(false);
	Commit(-30,"NumberStage", m_pNumberStage);



	m_pNumberScore = new CEMNumber(10);
	m_pNumberScore->SetSize(0.8f, 0.8f);				
	m_pNumberScore->SetPos(-130.0f, 350.0f, 0.0f);				
	m_pNumberScore->SetLocalVec(0.0f, 0.0f);		
	m_pNumberScore->SetOffset(0.0f, 0.0f);
	m_pNumberScore->SetTexture(this,10, "Data/Image/Number/0.png", "Data/Image/Number/1.png", "Data/Image/Number/2.png", "Data/Image/Number/3.png", "Data/Image/Number/4.png", "Data/Image/Number/5.png", "Data/Image/Number/6.png", "Data/Image/Number/7.png", "Data/Image/Number/8.png", "Data/Image/Number/9.png");
	m_pNumberScore->SetFrustumCulling(true);
	m_pNumberScore->SetBoundingBoxCalc(true);
	m_pNumberScore->SetBlend(true);	
	m_pNumberScore->SetShow(true);
	m_pNumberScore->SetColor(0.5f,1.0f,0.5f);
	m_pNumberScore->SetBackFaceCulling(false);
	Commit(-30,"NumberScore", m_pNumberScore);

	m_pNumberEndScore = new CEMNumber(10);
	m_pNumberEndScore->SetSize(1.4f, 1.4f);				
	m_pNumberEndScore->SetPos(100.0f, 50.0f, 0.0f);				
	m_pNumberEndScore->SetLocalVec(0.0f, 0.0f);		
	m_pNumberEndScore->SetOffset(0.0f, 0.0f);
	m_pNumberEndScore->SetTexture(this,10, "Data/Image/Number/0.png", "Data/Image/Number/1.png", "Data/Image/Number/2.png", "Data/Image/Number/3.png", "Data/Image/Number/4.png", "Data/Image/Number/5.png", "Data/Image/Number/6.png", "Data/Image/Number/7.png", "Data/Image/Number/8.png", "Data/Image/Number/9.png");
	m_pNumberEndScore->SetFrustumCulling(true);
	m_pNumberEndScore->SetBoundingBoxCalc(true);
	m_pNumberEndScore->SetBlend(true);	
	m_pNumberEndScore->SetShow(false);
	m_pNumberEndScore->SetColor(0.5f,1.0f,0.5f);
	m_pNumberEndScore->SetBackFaceCulling(false);
	Commit(-100,"NumberEndScore", m_pNumberEndScore);

	m_eGameResult = E_GAMERESULT_NONE;
	m_eGameStep = E_GAMESTEP_PLAY;

	m_Dolphine = new CEMDolphin();
	m_Dolphine->Init(this,0,2.0f);

	m_nCombo = 0;
	m_bSetText = false;
	ReadMap(g_nSelectStage+1);

	
	for(int i=0; i<3; i++)
	{
		m_pButtonGameStartImg[i] = new CEMPlane();		
		m_pButtonGameStartImg[i]->SetSize(0.7f,0.7f);					
		m_pButtonGameStartImg[i]->SetPos(0.0f, 0.0f, 0.0f);	
		m_pButtonGameStartImg[i]->SetLocalVec(0.0f, 0.0f);			
		m_pButtonGameStartImg[i]->SetOffset(0.0f, 0.0f);
		m_pButtonGameStartImg[i]->SetTexture(this, "Data/Image/Menu/Button_Start_"+IntToEMString(i+1)+".png");	
		m_pButtonGameStartImg[i]->SetFrustumCulling(true);				
		m_pButtonGameStartImg[i]->SetBoundingBoxCalc(true);			
		m_pButtonGameStartImg[i]->SetBlend(true);						
		m_pButtonGameStartImg[i]->SetShow(true);
		Commit(-1001,i,"ButtonGameStartImg", m_pButtonGameStartImg[i]);
	}
	m_ButtonGameStart.Init(this,m_pButtonGameStartImg[0],m_pButtonGameStartImg[1],m_pButtonGameStartImg[2],stEMVec2(-5.0f, -113.0f), true);
	
	m_ButtonGameStart.m_bVisible = false;

	for(int i=0; i<3; i++)
	{
		m_pButtonExitImg[i] = new CEMPlane();		
		m_pButtonExitImg[i]->SetSize(0.7f,0.7f);					
		m_pButtonExitImg[i]->SetPos(0.0f, 0.0f, 0.0f);	
		m_pButtonExitImg[i]->SetLocalVec(0.0f, 0.0f);			
		m_pButtonExitImg[i]->SetOffset(0.0f, 0.0f);
		m_pButtonExitImg[i]->SetTexture(this, "Data/Image/Menu/Button_Quit_"+IntToEMString(i+1)+".png");	
		m_pButtonExitImg[i]->SetFrustumCulling(true);				
		m_pButtonExitImg[i]->SetBoundingBoxCalc(true);			
		m_pButtonExitImg[i]->SetBlend(true);						
		m_pButtonExitImg[i]->SetShow(true);
		Commit(-1001,i,"ButtonExitImg", m_pButtonExitImg[i]);
	}
	m_ButtonExit.Init(this,m_pButtonExitImg[0],m_pButtonExitImg[1],m_pButtonExitImg[2],stEMVec2(-5.0f, -187.0f), true);
	
	m_ButtonExit.m_bVisible = false;


	for(int i=0; i<3; i++)
	{
		m_pButtonStopImg[i] = new CEMPlane();		
		m_pButtonStopImg[i]->SetSize(1.0f,1.0f);					
		m_pButtonStopImg[i]->SetPos(0.0f, 0.0f, 0.0f);	
		m_pButtonStopImg[i]->SetLocalVec(0.0f, 0.0f);			
		m_pButtonStopImg[i]->SetOffset(0.0f, 0.0f);
		m_pButtonStopImg[i]->SetTexture(this, "Data/Image/Stage/Stop_"+IntToEMString(i+1)+".png");	
		m_pButtonStopImg[i]->SetFrustumCulling(true);				
		m_pButtonStopImg[i]->SetBoundingBoxCalc(true);			
		m_pButtonStopImg[i]->SetBlend(true);						
		m_pButtonStopImg[i]->SetShow(true);
		Commit(-99,i,"ButtonStopImg", m_pButtonStopImg[i]);
	}
	m_ButtonStop.Init(this,m_pButtonStopImg[0],m_pButtonStopImg[1],m_pButtonStopImg[2],stEMVec2(193.0f, 295.0f), true);
	


	
	m_ButtonGameStart.m_bAction = false;
	m_fBlindTimer = 0.0f;
	g_bPause = false;
	m_ButtonGameStart.m_bVisible = false;
	m_ButtonExit.m_bVisible = false;

	CRootScene::Enter(pSceneWork);
}

void CStage::Update(CSceneWork* pSceneWork, float dt)
{
	m_ButtonGameStart.Update(this,dt);
	m_ButtonExit.Update(this,dt);
	m_ButtonStop.Update(this,dt);
	
	if( m_ButtonGameStart.IsAction() == true )
	{
		m_ButtonGameStart.m_bAction = false;
		m_fBlindTimer = 0.0f;
		g_bPause = false;
		m_ButtonGameStart.m_bVisible = false;
		m_ButtonGameStart.ChangeState(CNoneState::Instance());
		m_ButtonExit.m_bVisible = false;
		m_ButtonExit.ChangeState(CNoneState::Instance());
		if(g_SoundOnOff == true)
		{
			D_SOUND->Play(m_SoundPause2Fp,1.5f);
		}
	}

	if( m_ButtonExit.IsAction() == true )
	{
		m_ButtonExit.m_bAction = false;
		m_ButtonGameStart.m_bVisible = true;
		m_ButtonExit.m_bVisible = true;
		D_SCENE->ChangeSceneFade("StageMenu");
	}

	if( m_ButtonStop.IsAction() == true )
	{
		m_ButtonStop.m_bAction = false;
		m_ButtonStop.ChangeState(CNoneState::Instance());
		g_bPause = true;
		m_ButtonGameStart.m_bVisible = true;
		m_ButtonExit.m_bVisible = true;
		if(g_SoundOnOff == true)
		{
			D_SOUND->Play(m_SoundPause1Fp,1.5f);
		}
	}
	for(int i=0; i<5; i++)
	{
		m_pTtImg[i]->SetShow(false);
	}
	if(g_bPause == false)
	{
		//m_TextDisplay->Update(dt);

		if(m_nStage == 1)
		{
			//튜토리얼 시작
			switch(m_nTtLevel)//침식들
			{
			case 0://블록을 움직여 보세요.
				//m_pTtMsg->SetOutPutString("");
				m_pTtImg[0]->SetShow(true);
				break;
			case 1://블록을 드래그하여 터트려 보세요.
				//m_pTtMsg->SetOutPutString("");
				
				m_pTtImg[1]->SetShow(true);
				break;
			case 2://아이템이 들어있는 블록을 터트려 보세요.
				m_pTtImg[2]->SetShow(true);
				break;
			case 3://돌고래에 블록이 닿으면 얼음이 풀립니다.
				m_pTtImg[3]->SetShow(true);
				break;
			}
		}

		m_EffectMng->Update(dt);
		m_CamShakeMng->Update(dt);
		m_Sled->Update(dt);

		if(m_fComboTimer >= 0.0f)
		{
			m_fComboTimer -= dt;
			if(m_fComboTimer < 0)
				m_fComboTimer = 0.0f;
		}

		if(m_eGameStep == E_GAMESTEP_PLAY)
		{
			m_SnowMng->Update(dt);
			m_Dolphine->Update(dt,m_BlockList);

			if(m_nFirstCreateBlockNumber < 10)
			{
				m_fFirstCreateBlockTimer += dt;
				if(m_fFirstCreateBlockTimer >= m_fFirstCreateBlockTime)
				{
					m_nFirstCreateBlockNumber++;
					m_fFirstCreateBlockTimer = 0.0f;
					m_BlockList.push_back(CreateBlock(0));
				}
			}
			else
			{
				m_fCreateTimer += dt;
				if(m_fCreateTimer >= m_fCraeteTime)
				{
					m_fCreateTimer = 0.0f;
					CreateLine(&m_BlockList,m_CamShakeMng);
				}
			}

			m_ButtonUpCreateTime.Update(this,dt);
			m_ButtonDownCreateTime.Update(this,dt);

			m_ButtonUpErosionPlusSpeed.Update(this,dt);
			m_ButtonDownErosionPlusSpeed.Update(this,dt);


			m_ButtonUpErosionSpeed.Update(this,dt);
			m_ButtonDownErosionSpeed.Update(this,dt);

			m_ButtonFreeMove.Update(this,dt);

			m_ButtonUpCreateTime.m_bVisible = m_bOptionOnOff;
			m_ButtonDownCreateTime.m_bVisible = m_bOptionOnOff;

			m_ButtonUpErosionPlusSpeed.m_bVisible = m_bOptionOnOff;
			m_ButtonDownErosionPlusSpeed.m_bVisible = m_bOptionOnOff;

			m_ButtonUpErosionSpeed.m_bVisible = m_bOptionOnOff;
			m_ButtonDownErosionSpeed.m_bVisible = m_bOptionOnOff;
			m_ButtonFreeMove.m_bVisible = m_bOptionOnOff;


			m_pText->SetShow(m_bOptionOnOff);	
			m_pTextNowBlock->SetShow(m_bOptionOnOff);	
			m_pTextMouseList->SetShow(m_bOptionOnOff);	
			m_pTextErosionSpeed->SetShow(m_bOptionOnOff);	
			m_pTextCreateTime->SetShow(m_bOptionOnOff);	
			m_pTextErosionPlusSpeed->SetShow(m_bOptionOnOff);	
			m_pTextFreeDrag->SetShow(m_bOptionOnOff);

			if(m_ButtonUpCreateTime.IsAction() == true)
			{
				m_ButtonUpCreateTime.m_bAction = false;
				m_fCraeteTime += 1.0f;
			}
			if(m_ButtonDownCreateTime.IsAction() == true)
			{
				m_ButtonDownCreateTime.m_bAction = false;
				m_fCraeteTime -= 1.0f;
			}

			if(m_ButtonUpErosionPlusSpeed.IsAction() == true)
			{
				m_ButtonUpErosionPlusSpeed.m_bAction = false;
				m_nErosionPlusSpeed += 10;
			}
			if(m_ButtonDownErosionPlusSpeed.IsAction() == true)
			{
				m_ButtonDownErosionPlusSpeed.m_bAction = false;
				m_nErosionPlusSpeed -= 10;
			}

			if(m_ButtonUpErosionSpeed.IsAction() == true)
			{
				m_ButtonUpErosionSpeed.m_bAction = false;
				m_fErosionSpeed += 0.1f;
			}
			if(m_ButtonDownErosionSpeed.IsAction() == true)
			{
				m_ButtonDownErosionSpeed.m_bAction = false;
				m_fErosionSpeed -= 0.1f;
			}

			if(m_ButtonFreeMove.IsAction() == true)
			{
				m_ButtonFreeMove.m_bAction = false;
				if(m_bFreeMove == true)
					m_bFreeMove = false;
				else if(m_bFreeMove == false)
					m_bFreeMove = true;
			}
			m_pTextErosionSpeed->SetOutPutString("침식속도배율 : "+FloatToEMString(m_fErosionSpeed));
			m_pTextCreateTime->SetOutPutString("생성시간 : "+FloatToEMString(m_fCraeteTime)+"초");
			m_pTextErosionPlusSpeed->SetOutPutString("침식가속도 고정 : 초당 "+FloatToEMString((float)m_nErosionPlusSpeed/10000.0f)+" 상승");

			if(m_bFreeMove == true)
				m_pTextFreeDrag->SetOutPutString("프리드래그 여부 : Off");
			else if(m_bFreeMove == false)
				m_pTextFreeDrag->SetOutPutString("프리드래그 여부 : On");



			m_fErosionSpeed += (dt/10000) * m_nErosionPlusSpeed;//!< 고정으로 초당 0.01씩 상승

		


			m_fGravityTimer += dt;
			m_fTimeLimit -= dt;
			m_pNumberTimeLimit->SetNumber((int)m_fTimeLimit);
			m_pNumberStage->SetNumber((int)m_nStage);
			m_pNumberScore->SetNumber((int)g_nScore);
			m_pNumberEndScore->SetNumber((int)g_nScore);

			int nTemp = (int)g_nScore;
			int nCount = 0;
			while(nTemp > 0)
			{
				nTemp /= 10;
				nCount++;
			}
			m_pNumberScore->SetPos(-130.0f - (nCount*20), 350.0f, 0.0f);
			m_pNumberEndScore->SetPos(-80.0f - (nCount*30), -80.0f, 0.0f);

			nTemp = (int)m_fTimeLimit;
			nCount = 0;
			if(nTemp == 0)
			{
				float fTempSize = 1.0f + (float)((float)( (int)(m_fTimeLimit*1000) % 1000) / 1000 );
				m_pNumberTimeLimit->SetSize(fTempSize, fTempSize);
				m_pNumberTimeLimit->SetPos(20.0f - (1*20) + (3*fTempSize) - 2, 308.0f, 0.0f);
				m_pNumberTimeLimit->SetColor(1.0f,0.0f,0.0f);
			}
			else
			{
				while(nTemp > 0)
				{
					nTemp /= 10;
					nCount++;
				}
				m_pNumberTimeLimit->SetPos(20.0f - (nCount*20), 308.0f, 0.0f);
			}

			if(nCount == 1)
			{
				float fTempSize = 1.0f + (float)((float)( (int)(m_fTimeLimit*1000) % 1000) / 1000 );
				m_pNumberTimeLimit->SetSize(fTempSize, fTempSize);
				m_pNumberTimeLimit->SetPos(20.0f - (nCount*20) + (3*fTempSize) - 2, 308.0f, 0.0f);
				m_pNumberTimeLimit->SetColor(1.0f,0.0f,0.0f);
			}
			
			nTemp = (int)m_nStage;
			nCount = 0;
			while(nTemp > 0)
			{
				nTemp /= 10;
				nCount++;
			}
			m_pNumberStage->SetPos(178.0f - (nCount*20), 350.0f, 0.0f);

			list<CEMBlock*>::iterator it;
			list<CEMBlock*>::iterator itrm;
			for(it = m_BlockList.begin(); it != m_BlockList.end(); it++)
			{
				if((*it)->m_eBlockState == E_BLOCKSTATE_FALLING)
					continue;
				if((*it)->m_bDraged == true)
					continue;
				if((*it)->m_stIndex.m_fY != D_BLOCKMAP_HEIGHT - 1)
				{
					if(m_Map->m_nBlockMap[(*it)->m_stIndex.m_fY+1][(*it)->m_stIndex.m_fX] == 0)
					{
						m_Map->m_nBlockMap[(*it)->m_stIndex.m_fY][(*it)->m_stIndex.m_fX] = 0;
						m_Map->m_nBlockMap[(*it)->m_stIndex.m_fY+1][(*it)->m_stIndex.m_fX] = 1;


						(*it)->m_eBlockState = E_BLOCKSTATE_FALLING;
						(*it)->m_fStartY = (*it)->m_stPos.m_fY;
						(*it)->m_fDistance = 64.0f;
						(*it)->m_stIndex.m_fY += 1;
					}
				}
			}

			int nSpaceCount = 0;
			//!< 침식속도가 면적에 비례함
			for(int i=0; i<D_BLOCKMAP_WIDTH; i++)
			{
				if(m_Map->m_nBlockMap[D_BLOCKMAP_HEIGHT-1][i] == 0)
					nSpaceCount++;
			}

			int fErosionSpeed = m_fErosionSpeed * ((nSpaceCount+7)/ 7);
			//
			for(it = m_BlockList.begin(); it != m_BlockList.end(); it++)
			{
				(*it)->Update(dt, fErosionSpeed, m_Sled);
			}

			for(it = m_BlockList.begin(); it != m_BlockList.end();)
			{
				if( (*it)->IsErosoined() == true )
				{
					if(m_nStage == 1 && m_nTtLevel == 0)
					{
						m_bSetText = false;
						m_nTtLevel++;
						if(g_SoundOnOff == true)
						{
							D_SOUND->Play(m_SoundEffectTtFp,1.5f);
						}
					}

					m_Map->m_nBlockMap[(*it)->m_stIndex.m_fY][(*it)->m_stIndex.m_fX] = 0;
					//DeletePlane((*it)->m_pPlane);
					//DeletePlane((*it)->m_pSelect);
					//DeletePlane((*it)->m_pErosoin);
					//DeletePlane((*it)->m_pErosoin_Border);
					(*it)->m_pBlock->Destroy();
					(*it)->m_pSelect->Destroy();
					(*it)->m_pErosoin->Destroy();
					(*it)->m_pErosoin_Border->Destroy();
					(*it)->m_pFreeze->Destroy();
					(*it)->m_pItem_Sled->Destroy();
					//delete (*it);
					for(itrm = m_MouseList.begin(); itrm != m_MouseList.end(); itrm++)
					{
						if((*it)->m_stIndex.m_fX == (*itrm)->m_stIndex.m_fX && (*it)->m_stIndex.m_fY == (*itrm)->m_stIndex.m_fY)
						{
							m_MouseList.erase(itrm);
							break;
						}
					}
					delete (*it);
					it = m_BlockList.erase(it);
					g_nScore += D_SCORE_EROSIONBLOCK;

				}
				else
				{
					it++;
				}
			}

			/*for(it = m_BlockList.begin(); it != m_BlockList.end(); it++)
			{
				if( (*it)->m_eBlockState != E_BLOCKSTATE_FALLING ) 
				{
					if((*it)->m_stPos.m_fX != D_LINE_START_X + ((*it)->m_stIndex.m_fX * D_BLOCK_WIDTH))
					{
						(*it)->m_stPos.m_fX = D_LINE_START_X + ((*it)->m_stIndex.m_fX * D_BLOCK_WIDTH);
					}

					if((*it)->m_stPos.m_fY != D_LINE_START_Y + ((*it)->m_stIndex.m_fY * D_BLOCK_HEIGHT))
					{
						(*it)->m_stPos.m_fY = D_LINE_START_Y + ((*it)->m_stIndex.m_fY * D_BLOCK_HEIGHT);
					}
				}
			}*/
			stdEMString strTemp;

			list<CEMBlock*>::iterator itr;
			for(itr = m_MouseList.begin(); itr != m_MouseList.end(); itr++)
			{
				strTemp.append((*itr)->m_pBlock->GetName());
			}
			m_pTextMouseList->SetOutPutString(strTemp);


			if(m_eGameStep == E_GAMESTEP_PLAY && m_nFirstCreateBlockNumber >= 10)
			{
				if(m_fTimeLimit <= 0)
				{
					m_eGameResult = E_GAMERESULT_VICTORY;
					m_eGameStep = E_GAMESTEP_END;
					if(g_SoundOnOff == true)
					{
						D_SOUND->Play(m_SoundWinFp,1.5f);
					}
				}
				else
				{
					if(m_BlockList.size() == 0)
					{
						m_eGameResult = E_GAMERESULT_DEFEAT;
						m_eGameStep = E_GAMESTEP_END;
						if(g_SoundOnOff == true)
						{
							D_SOUND->Play(m_SoundLoseFp,1.5f);
						}
					}
					else
					{
						if(m_eBlockAct == E_BLOCKACT_MOVE)
						{
							if((m_BlockList.size() - m_MouseList.size()) <= 0)
							{
								m_eGameResult = E_GAMERESULT_DEFEAT;
								m_eGameStep = E_GAMESTEP_END;
							}
						}
					}
				}
			}
		}
		else if(m_eGameStep == E_GAMESTEP_END)
		{
			if(m_eGameResult == E_GAMERESULT_DEFEAT)
			{
				if(m_fGameEndBlind < D_GAMEOVER_BLINDTIME)
				{
					m_fGameEndBlind += dt;
					if(m_fGameEndBlind >= D_GAMEOVER_BLINDTIME)
						m_fGameEndBlind = D_GAMEOVER_BLINDTIME;
				}
				m_pGameOver->SetShow(true);
				m_pGameOver->SetColor(1.0f,1.0f,1.0f,m_fGameEndBlind/D_GAMEOVER_BLINDTIME);
				m_pNumberEndScore->SetShow(true);
				m_pNumberEndScore->SetColor(1.0f,1.0f,1.0f,m_fGameEndBlind/D_GAMEOVER_BLINDTIME);
				
				/*	for(int i=0; i<3; i++)
				{
					m_pStar[i]->SetShow(true);
					m_pStar[i]->SetColor(1.0f,1.0f,1.0f,m_fGameEndBlind/D_GAMEOVER_BLINDTIME);
					m_pStar[i]->SetSize(0.5f+((m_fGameEndBlind/D_GAMEOVER_BLINDTIME)*0.5f),0.5f+((m_fGameEndBlind/D_GAMEOVER_BLINDTIME)*0.5f));
					m_pStar[i]->SetZRot((m_fGameEndBlind/D_GAMEOVER_BLINDTIME)*360.0f);
				}*/
			

				//m_pGameOver->SetSize(m_fGameEndBlind/D_GAMEOVER_BLINDTIME,m_fGameEndBlind/D_GAMEOVER_BLINDTIME);
			}
			else if(m_eGameResult == E_GAMERESULT_VICTORY)
			{
				if(m_fGameEndBlind < D_GAMEOVER_BLINDTIME)
				{
					m_fGameEndBlind += dt;
					if(m_fGameEndBlind >= D_GAMEOVER_BLINDTIME)
						m_fGameEndBlind = D_GAMEOVER_BLINDTIME;
				}
				m_pGameClear->SetShow(true);
				m_pGameClear->SetColor(1.0f,1.0f,1.0f,m_fGameEndBlind/D_GAMEOVER_BLINDTIME);
				m_pNumberEndScore->SetShow(true);
				m_pNumberEndScore->SetColor(1.0f,1.0f,1.0f,m_fGameEndBlind/D_GAMEOVER_BLINDTIME);
				g_bStageLock[g_nSelectStage+1] = true;
				
				

				if(g_nScore > g_nHighScore[m_nStage - 1])
				{
					g_nHighScore[m_nStage - 1] = g_nScore;
				}
				if(g_nScore >= g_nJudgment[m_nStage - 1][2])
				{
					g_nScoreLevel[m_nStage - 1] = 3;
					for(int i=0; i<3; i++)
					{
						m_pStar[i]->SetShow(true);
						m_pStar[i]->SetColor(1.0f,1.0f,1.0f,m_fGameEndBlind/D_GAMEOVER_BLINDTIME);
						m_pStar[i]->SetSize(0.5f+((m_fGameEndBlind/D_GAMEOVER_BLINDTIME)*0.5f),0.5f+((m_fGameEndBlind/D_GAMEOVER_BLINDTIME)*0.5f));
						m_pStar[i]->SetZRot((m_fGameEndBlind/D_GAMEOVER_BLINDTIME)*360.0f);
					}
				}
				else if(g_nScore >= g_nJudgment[m_nStage - 1][1])
				{
					g_nScoreLevel[m_nStage - 1] = 2;
					for(int i=0; i<2; i++)
					{
						m_pStar[i]->SetShow(true);
						m_pStar[i]->SetColor(1.0f,1.0f,1.0f,m_fGameEndBlind/D_GAMEOVER_BLINDTIME);
						m_pStar[i]->SetSize(0.5f+((m_fGameEndBlind/D_GAMEOVER_BLINDTIME)*0.5f),0.5f+((m_fGameEndBlind/D_GAMEOVER_BLINDTIME)*0.5f));
						m_pStar[i]->SetZRot((m_fGameEndBlind/D_GAMEOVER_BLINDTIME)*360.0f);
					}
				}
				else if(g_nScore >= g_nJudgment[m_nStage - 1][0])
				{
					g_nScoreLevel[m_nStage - 1] = 1;
					for(int i=0; i<1; i++)
					{
						m_pStar[i]->SetShow(true);
						m_pStar[i]->SetColor(1.0f,1.0f,1.0f,m_fGameEndBlind/D_GAMEOVER_BLINDTIME);
						m_pStar[i]->SetSize(0.5f+((m_fGameEndBlind/D_GAMEOVER_BLINDTIME)*0.5f),0.5f+((m_fGameEndBlind/D_GAMEOVER_BLINDTIME)*0.5f));
						m_pStar[i]->SetZRot((m_fGameEndBlind/D_GAMEOVER_BLINDTIME)*360.0f);
					}
				}
			
				//m_pGameOver->SetSize(m_fGameEndBlind/D_GAMEOVER_BLINDTIME,m_fGameEndBlind/D_GAMEOVER_BLINDTIME);
			}

			
		}
		

		m_stCamPos.m_fZ = D_CAM_Z_FIXED;
		D_CAMERA->SetPos(m_stCamPos);
	}
	if(g_bPause == true)
		{
			m_fBlindTimer += dt;
			if(m_fBlindTimer >= 0.6f)
				m_fBlindTimer = 0.6f;
		}

	m_pPause->SetShow(g_bPause);
	m_pBlind->SetShow(g_bPause);
	m_pBlind->SetAlpha((m_fBlindTimer / 0.6f) * 0.7);

		


	CRootScene::Update(pSceneWork, dt);

}

void CStage::Render(CSceneWork* pSceneWork)
{


	CRootScene::Render(pSceneWork);
}

void CStage::Exit(CSceneWork* pSceneWork)
{
	
	
	
	SaveStage();

	list<CEMBlock*>::iterator it;
	for(it = m_BlockList.begin(); it != m_BlockList.end();)
	{
		m_Map->m_nBlockMap[(*it)->m_stIndex.m_fY][(*it)->m_stIndex.m_fX] = 0;

		(*it)->m_pBlock->Destroy();
		(*it)->m_pSelect->Destroy();
		(*it)->m_pErosoin->Destroy();
		(*it)->m_pErosoin_Border->Destroy();
		(*it)->m_pFreeze->Destroy();

		delete (*it);

		it = m_BlockList.erase(it);
	}


	m_BlockList.clear();
	m_MouseList.clear();
	

	m_EffectMng->Exit();
	delete m_EffectMng;

	delete m_CamShakeMng;

	delete m_Map;

	delete m_Dolphine;
	

	delete m_SnowMng;
	delete m_Sled;
	Destroy();				//!< 현재 씬에서 메모리 잡은거 전부 해제



#ifdef _DEBUG
	TwDeleteBar(m_pBar);	//!< 툴바 삭제
#endif

	CRootScene::Exit(pSceneWork);
}

void CStage::MouseDownEvent(stMouseInfo stPos, enumMouseButton eButton)
{
	if(eButton == E_MOUSE_LEFT)
	{
		m_ButtonGameStart.Check_Down(stPos,-1001);
		m_ButtonExit.Check_Down(stPos,-1001);
	}
	if(g_bPause == false)
	{
		//m_Sled->Sleding();
		//m_BlockList.push_back(CreateBlock(0,0));
		if(eButton == E_MOUSE_LEFT)
		{
			
			
			if(m_eGameStep == E_GAMESTEP_PLAY)
			{
				
				m_ButtonStop.Check_Down(stPos,-99);

				m_ButtonUpCreateTime.Check_Down(stPos, -1);
				m_ButtonDownCreateTime.Check_Down(stPos, -1);

				m_ButtonUpErosionPlusSpeed.Check_Down(stPos, -1);
				m_ButtonDownErosionPlusSpeed.Check_Down(stPos, -1);

				m_ButtonUpErosionSpeed.Check_Down(stPos, -1);
				m_ButtonDownErosionSpeed.Check_Down(stPos, -1);

				m_ButtonFreeMove.Check_Down(stPos, -1);
				
				
				m_IsMouseDown = true;
				stEMVec2 stTemp = CEMMath::ScreenToWorld((int)stPos.m_nX,(int)stPos.m_nY);
				if(D_WORLD->GetWinInfo().m_stRt.bottom > D_WORLD->GetWinInfo().m_stRt.right)
				{
					stTemp.m_fX = (stTemp.m_fX/180) * 100;
					stTemp.m_fY = (stTemp.m_fY/180) * 100;
				}
				//stTemp.m_fX = (stTemp.m_fX/205) * 100;
				//stTemp.m_fY = (stTemp.m_fY/205) * 100;
				m_pText->SetOutPutString("마우스 좌표 (" + IntToEMString((int)stTemp.m_fX) + "," + IntToEMString((int)stTemp.m_fY) + ")");



				CEMPlane* pTemp = AABBvsRay(stPos.m_nX,stPos.m_nY,-2);

				list<CEMBlock*>::iterator it;
				for(it = m_BlockList.begin(); it != m_BlockList.end(); it++)
				{
					if( (*it)->m_pBlock != pTemp )
						continue;
					if( (*it)->m_eBlockState == E_BLOCKSTATE_FALLING )
						continue;

					if((*it)->m_bFreezed == false)
					{
						(*it)->m_pSelect->SetShow(true);
						m_MouseList.push_back((*it));
						m_pTextNowBlock->SetOutPutString((*it)->m_pBlock->GetName());
						m_bBlockAct = true;
						if(g_SoundOnOff == true)
						{
							m_SoundButton = D_SOUND->Play(m_SoundButtonFp,1.0f,false);
						}
					}
					break;

				}
				if(it == m_BlockList.end())
				{
					m_bBlockAct = false;
					m_pTextNowBlock->SetOutPutString("선택된 블록 없음");
				}
			}
			if(m_eGameStep == E_GAMESTEP_END && m_fGameEndBlind >= D_GAMEOVER_BLINDTIME)
			{
				D_SCENE->ChangeSceneFade("StageMenu");
			}
		}
	}

	//stTemp
}

void CStage::MouseUpEvent(stMouseInfo stPos, enumMouseButton eButton)
{
	if(eButton == E_MOUSE_LEFT)
	{
		m_ButtonGameStart.Check_Up(stPos,-1001);
		m_ButtonExit.Check_Up(stPos,-1001);
	}

	if(g_bPause == false)
	{
		if(eButton == E_MOUSE_LEFT)
		{
			
			if(m_eGameStep == E_GAMESTEP_PLAY)
			{
				
				
				bool bSled = false;
				
				m_ButtonStop.Check_Up(stPos,-99);


				m_ButtonUpCreateTime.Check_Up(stPos, -1);
				m_ButtonDownCreateTime.Check_Up(stPos, -1);
				m_ButtonUpErosionPlusSpeed.Check_Up(stPos, -1);
				m_ButtonDownErosionPlusSpeed.Check_Up(stPos, -1);
				m_ButtonUpErosionSpeed.Check_Up(stPos, -1);
				m_ButtonDownErosionSpeed.Check_Up(stPos, -1);
				m_ButtonFreeMove.Check_Up(stPos, -1);
				
				m_IsMouseDown = false;
				m_bBlockAct = false;
				m_nTurnStep = 0;
				m_bTurnAble = true;
				m_bBlockAct = false;
				m_eBlockDragDerection = E_BLOCKDRAG_DEFECTION_LEFT;
				m_nTurnSkipBlock = 0;

				stEMVec2 stTemp = CEMMath::ScreenToWorld((int)stPos.m_nX,(int)stPos.m_nY);
				if(D_WORLD->GetWinInfo().m_stRt.bottom > D_WORLD->GetWinInfo().m_stRt.right)
				{
					stTemp.m_fX = (stTemp.m_fX/180) * 100;
					stTemp.m_fY = (stTemp.m_fY/180) * 100;
				}
				list<CEMBlock*>::iterator itMouseList;
				int nCount = 0;
				if(m_eBlockAct == E_BLOCKACT_DRAG)
				{
					if(m_MouseList.size() >= 3)
					{
						for(itMouseList = m_MouseList.begin(); itMouseList != m_MouseList.end(); itMouseList++)
						{
							nCount++;
							if((*itMouseList)->m_eBlockItem == E_BLOCKITEM_SLED)
							{
								(*itMouseList)->m_eBlockItem = E_BLOCKITEM_NONE;
								(*itMouseList)->m_pItem_Sled->SetShow(false);
								bSled = true;
							}

							(*itMouseList)->m_bFreezed = true;
							(*itMouseList)->m_fErosionMaxTime += D_FREEZETIME;
							(*itMouseList)->m_fErosionTime += D_FREEZETIME;

							(*itMouseList)->m_pSelect->SetShow(false);
							(*itMouseList)->m_bDraged = false;
							g_nScore += (D_SCORE_ICEBLOCK * m_MouseList.size());
							//for(int i=0; i<D_SOUND_ICE_CHANNEL; i++)
							//{
								//if(D_SOUND->IsPlaying(m_SoundIce[i]) == false)
								//{
							if(g_SoundOnOff == true)
							{
								m_SoundIce[0] = D_SOUND->Play(m_SoundIceFp,1.0f,false);
							}
							//	break;
								//}
							//}
							//if(nCount >= m_MouseList.size())
								//m_EffectMng->Insert(4,(*itMouseList)->m_stPos.m_fX + 70, (*itMouseList)->m_stPos.m_fY + 0);

							m_EffectMng->Insert(1,(*itMouseList)->m_stPos.m_fX,(*itMouseList)->m_stPos.m_fY);
							m_fComboTimer = D_COMBOTIME;
						}

						if(m_nStage == 1 && m_nTtLevel == 2)
						{
							m_bSetText = false;
							m_nTtLevel++;
							if(g_SoundOnOff == true)
							{
								D_SOUND->Play(m_SoundEffectTtFp,1.5f);
							}
						}

						if(bSled == true)
						{
						
							if(m_Sled->m_bOnOff == false)
								m_Sled->Sleding();
							else if(m_Sled->m_bOnOff == true)
								m_Sled->m_fHp = m_Sled->m_fMaxHp;

							if(m_nStage == 1 && m_nTtLevel == 3)
							{
								m_bSetText = false;
								m_nTtLevel++;
								if(g_SoundOnOff == true)
								{
									D_SOUND->Play(m_SoundEffectTtFp,1.5f);
								}
							}

						}

					}
					else
					{
						for(itMouseList = m_MouseList.begin(); itMouseList != m_MouseList.end(); itMouseList++)
						{
							(*itMouseList)->m_pSelect->SetShow(false);
							(*itMouseList)->m_bDraged = false;
						}
					}

				}
				else if(m_eBlockAct == E_BLOCKACT_MOVE)
				{

					int nIndex_X = ((stTemp.m_fX - D_CALC_START_X)/D_BLOCK_WIDTH);
					int nIndex_Y = ((D_CALC_START_Y - stTemp.m_fY)/D_BLOCK_HEIGHT);

					if(nIndex_X < 0)
						nIndex_X = 0;
					if(nIndex_X >= D_BLOCKMAP_WIDTH)
						nIndex_X = D_BLOCKMAP_WIDTH - 1;

					if(nIndex_Y < 0)
						nIndex_Y = 0;
					if(nIndex_Y >= D_BLOCKMAP_HEIGHT - 1)
						nIndex_Y = D_BLOCKMAP_HEIGHT - 1;



					for(itMouseList = m_MouseList.begin(); itMouseList != m_MouseList.end(); itMouseList++)
					{
						(*itMouseList)->m_pSelect->SetShow(false);
						(*itMouseList)->m_bDraged = false;

						if( m_Map->m_nBlockMap[nIndex_Y][nIndex_X] == 0)
						{
							m_Map->m_nBlockMap[(*itMouseList)->m_stIndex.m_fY][(*itMouseList)->m_stIndex.m_fX] = 0;
							m_Map->m_nBlockMap[nIndex_Y][nIndex_X] = 1;
							(*itMouseList)->m_stIndex.m_fX = nIndex_X;
							(*itMouseList)->m_stIndex.m_fY = nIndex_Y;
						}
						if(m_nStage == 1 && m_nTtLevel == 1)
						{
							m_nTtLevel++;
							if(g_SoundOnOff == true)
							{
								m_SoundEffectTt = D_SOUND->Play(m_SoundButtonFp, 1.5f);
							}
						}
						(*itMouseList)->m_stPos.m_fX = D_LINE_START_X + ((*itMouseList)->m_stIndex.m_fX * D_BLOCK_WIDTH);
						(*itMouseList)->m_stPos.m_fY = D_LINE_START_Y - ((*itMouseList)->m_stIndex.m_fY * D_BLOCK_HEIGHT);
					}
				}
				else if(m_eBlockAct == E_BLOCKACT_NONE || m_eBlockAct == E_BLOCKACT_NOT)
				{
					for(itMouseList = m_MouseList.begin(); itMouseList != m_MouseList.end(); itMouseList++)
					{
						(*itMouseList)->m_pSelect->SetShow(false);
						(*itMouseList)->m_bDraged = false;
					}
				}


				m_eBlockAct = E_BLOCKACT_NONE;

				m_MouseList.clear();
			}
		}
	}
}



void CStage::MouseMoveEvent(stMouseInfo stPos)
{

	m_ButtonGameStart.Check_Move(stPos,-1001);
	m_ButtonExit.Check_Move(stPos,-1001);


	if(g_bPause == false)
	{

		if(m_eGameStep == E_GAMESTEP_PLAY)
		{

			
			m_ButtonStop.Check_Move(stPos, -99);


			m_ButtonUpCreateTime.Check_Move(stPos, -1);
			m_ButtonDownCreateTime.Check_Move(stPos, -1);
			m_ButtonUpErosionPlusSpeed.Check_Move(stPos, -1);
			m_ButtonDownErosionPlusSpeed.Check_Move(stPos, -1);
			m_ButtonUpErosionSpeed.Check_Move(stPos, -1);
			m_ButtonDownErosionSpeed.Check_Move(stPos, -1);
			m_ButtonFreeMove.Check_Move(stPos, -1);
			
			//AABBvsRay 넘겨받은 Plane과 블록속에있는 Plane을 비교 /
			//비교되었다면 해당 블록의 Plane과 Index값 참조
			//List에 해당 블록추가.
			//해당 블록의 상태는 m_bDowned = true이며
			//이 상태에는 Plane이 찡그린 표정으로 바뀜

			//!< 이미 들어있는 놈은 검사하여 break;
			//

			if(m_IsMouseDown == false)
				return;

			list<CEMBlock*>::iterator itLastBlock; //!< 가장 마지막 블록

			list<CEMBlock*>::iterator itMouseList;//!< MouseList의 iterator

			list<CEMBlock*>::iterator itBlockList;//!< BlockList의 iterator

			stEMVec2 stTemp = CEMMath::ScreenToWorld((int)stPos.m_nX,(int)stPos.m_nY);
			if(D_WORLD->GetWinInfo().m_stRt.bottom > D_WORLD->GetWinInfo().m_stRt.right)
			{
				stTemp.m_fX = (stTemp.m_fX/180) * 100;
				stTemp.m_fY = (stTemp.m_fY/180) * 100;
			}



			CEMPlane* pTemp = AABBvsRay(stPos.m_nX,stPos.m_nY,-2);


			int i = 0;
			if(m_IsMouseDown == true  && m_MouseList.size() >= 1 && m_bBlockAct == true)
			{
				for(itLastBlock = m_MouseList.begin(); i < m_MouseList.size() - 1; itLastBlock++, i++)
				{
					//
				}
			}

			bool bFirstBlock = false; //!< 처음 블록과 일치


			bool bMouseBlock = false; //!< 이미 마우스블록에 들어있던 블록과 일치


			if(m_MouseList.size() >= 1)
			{
				if(m_eBlockAct == E_BLOCKACT_NONE)
				{
					if( pTemp == (*itLastBlock)->m_pBlock) //!< 움직이는데 처음 클릭한 블록이면 빠져나감
					{
						bFirstBlock = true;
					}	
					else
					{
						for(itBlockList = m_BlockList.begin(); itBlockList != m_BlockList.end(); itBlockList++)
						{
							if( pTemp == (*itBlockList)->m_pBlock) //!< 처음 클릭한 블록이 아니고 인접한 블록 중 하나이면 Drag판정을 내림
							{
								if((*itBlockList)->m_eBlockState == E_BLOCKSTATE_FALLING)
									break;


								int m_nLR = (*itLastBlock)->m_stIndex.m_fX - (*itBlockList)->m_stIndex.m_fX;
								int m_nUD = (*itLastBlock)->m_stIndex.m_fY - (*itBlockList)->m_stIndex.m_fY;
								//!< 블록이 인접한 것인지 Check
								if( 
									(m_nUD == 0 && m_nLR == 1) ||	//좌
									(m_nUD == 0 && m_nLR == -1) ||	//우
									(m_nUD == 1 && m_nLR == 0) ||	//상
									(m_nUD == -1 && m_nLR == 0)	//하
									)
								{
									if(m_bFreeMove == true)
									{
										m_eBlockAct = E_BLOCKACT_NOT;
									}
									if((*itLastBlock)->m_eBlockNumber == (*itBlockList)->m_eBlockNumber)//!< 같은 종류인지 Check
									{
										if((*itBlockList)->m_bFreezed == false)//!< 얼어있는 녀석인지
										{
											(*itBlockList)->m_pSelect->SetShow(true);
											m_MouseList.push_back((*itBlockList));
											m_pTextNowBlock->SetOutPutString((*itBlockList)->m_pBlock->GetName());
											m_eBlockAct = E_BLOCKACT_DRAG;
											if(g_SoundOnOff == true)
											{
												m_SoundButton = D_SOUND->Play(m_SoundButtonFp,1.0f,false);
											}
											break;
										}
									}
								}
							}
						}
						if(itBlockList == m_BlockList.end() && m_eBlockAct != E_BLOCKACT_NOT) //!< 인접한 블록이 아닐경우 Move판정
						{
							//if((*itBlockList)->m_eBlockState != E_BLOCKSTATE_FALLING)
							//{
							(*itLastBlock)->m_pSelect->SetShow(true);
							//m_MouseList.push_back((*itLastBlock));
							(*itLastBlock)->m_bDraged = true;
							m_eBlockAct = E_BLOCKACT_MOVE;
							//}
						}
					}
				}
				else if(m_eBlockAct == E_BLOCKACT_DRAG)
				{
					for(itMouseList = m_MouseList.begin(); itMouseList != m_MouseList.end(); itMouseList++)
					{
						if(pTemp == (*itMouseList)->m_pBlock)
						{
							bMouseBlock = true;
							break;
						}
					}

					if(bMouseBlock == false) //!< 이미 들어있는 블록이 아닐경우
					{
						for(itBlockList = m_BlockList.begin(); itBlockList != m_BlockList.end(); itBlockList++)
						{
							if( pTemp == (*itBlockList)->m_pBlock) //!< 처음 클릭한 블록이 아니고 인접한 블록 중 하나이면 Drag판정을 내림
							{
								int m_nLR = (*itLastBlock)->m_stIndex.m_fX - (*itBlockList)->m_stIndex.m_fX;
								int m_nUD = (*itLastBlock)->m_stIndex.m_fY - (*itBlockList)->m_stIndex.m_fY;
								//!< 블록이 인접한 것인지 Check
								if( 
									(m_nUD == 0 && m_nLR == 1) ||	//좌
									(m_nUD == 0 && m_nLR == -1) ||	//우
									(m_nUD == 1 && m_nLR == 0) ||	//상
									(m_nUD == -1 && m_nLR == 0)	//하
									)
								{
									if((*itLastBlock)->m_eBlockNumber == (*itBlockList)->m_eBlockNumber)//!< 같은 종류인지 Check
									{
										if((*itBlockList)->m_bFreezed == false)//!< 얼어있는 녀석인지
										{
											(*itBlockList)->m_pSelect->SetShow(true);
											m_MouseList.push_back((*itBlockList));
											m_pTextNowBlock->SetOutPutString((*itBlockList)->m_pBlock->GetName());
											
											if(g_SoundOnOff == true)
											{
												m_SoundButton = D_SOUND->Play(m_SoundButtonFp,1.0f,false);
											}
										
										}
									}
								}
							}
						}
					}
				}
				else if(m_eBlockAct == E_BLOCKACT_MOVE)
				{
					stEMVec2 stLastBlockPos;

					int nIndex_X = ((stTemp.m_fX - D_CALC_START_X)/D_BLOCK_WIDTH);
					int nIndex_Y = ((D_CALC_START_Y - stTemp.m_fY)/D_BLOCK_HEIGHT);

					stLastBlockPos = (*itLastBlock)->m_stPos;

					(*itLastBlock)->m_stPos.m_fX = stTemp.m_fX;
					(*itLastBlock)->m_stPos.m_fY = stTemp.m_fY;

					list<CEMBlock*>::iterator itBlockList;
					for(itBlockList = m_BlockList.begin(); itBlockList != m_BlockList.end(); itBlockList++)
					{
						if((*itLastBlock) == (*itBlockList))
							continue;

						/*if( 
						CEMMath::Abs<float>((*itLastBlock)->m_stPos.m_fX - (*itBlockList)->m_stPos.m_fX) <= D_BLOCK_WIDTH &&
						CEMMath::Abs<float>((*itLastBlock)->m_stPos.m_fY - (*itBlockList)->m_stPos.m_fY) <= D_BLOCK_HEIGHT )
						{
							if(stTemp.m_fY < (*itBlockList)->m_stPos.m_fY)
							{
								(*itLastBlock)->m_stPos.m_fY = stLastBlockPos.m_fY;
							}
							break;
						}*/

					}



					//if( m_Map->m_nBlockMap[nIndex_Y][nIndex_X] == 0)
					//{
					//	m_Map->m_nBlockMap[(*itLastBlock)->m_stIndex.m_fY][(*itLastBlock)->m_stIndex.m_fX] = 0;
					//	m_Map->m_nBlockMap[nIndex_Y][nIndex_X] = 1;
					//	(*itLastBlock)->m_stIndex.m_fX = nIndex_X;
					//	(*itLastBlock)->m_stIndex.m_fY = nIndex_Y;




					// (*itLastBlock)->m_stPos.m_fX = D_LINE_START_X + (nIndex_X * D_BLOCK_WIDTH);
					// (*itLastBlock)->m_stPos.m_fY = D_LINE_START_Y - (nIndex_Y * D_BLOCK_HEIGHT);
					//}
				}
			}
		}
	}

}

HRESULT CStage::WindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_LBUTTONDOWN:
		{

		}break;
	case WM_MOUSEMOVE:
		{
			stMousePos.m_fX = LOWORD(lParam);
			stMousePos.m_fY = HIWORD(lParam);


		}break;
	case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
			{
				if(g_bPause == false)
				{
					g_bPause = true;
					m_ButtonGameStart.m_bVisible = true;
					m_ButtonExit.m_bVisible = true;
				}
				else if(g_bPause == true)
				{
					m_fBlindTimer = 0.0f;
					g_bPause = false;
					m_ButtonGameStart.m_bVisible = false;
					m_ButtonExit.m_bVisible = false;
				}
			}
			/*
			if(wParam == 'S')
			{
				CreateLine(&m_BlockList, m_CamShakeMng);
			}
			else if(wParam == 'I')
			{
				if(m_bOptionOnOff == true)
				{
					m_bOptionOnOff = false;
				}
				else if(m_bOptionOnOff == false)
				{
					m_bOptionOnOff = true;
				}
			}*/
		}break;
	}
	return msg;
}


void CStage::BeginContact(b2Contact* contact)
{
	CEMPhysicRoot::BeginContact(contact);
	//아래에 코드를 작성하세요


}

void CStage::EndContact(b2Contact* contact)
{
	CEMPhysicRoot::EndContact(contact);
	//아래에 코드를 작성하세요

}

void CStage::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	CEMPhysicRoot::PreSolve(contact, oldManifold);
	//아래에 코드를 작성하세요

}

void CStage::PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
{
	CEMPhysicRoot::PostSolve(contact, impulse);
	//아래에 코드를 작성하세요

}
