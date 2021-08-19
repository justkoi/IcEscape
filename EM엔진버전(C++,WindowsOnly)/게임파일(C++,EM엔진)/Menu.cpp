#include "stdafx.h"

bool g_SoundOnOff = true;
void CMenu::Enter(CSceneWork* pSceneWork)
{
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

		SoundFp = D_SOUND->FileOpen("Data/Sound/Menu_BGM.mp3");
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
	//!=====================================================

	//!=====================================================
	//!화면에 텍스쳐 출력하기
	//!=====================================================

	//!=====================================================
	//!화면에 Plane출력하기
	m_pTitle = new CEMPlane();						//!< 생성자로 Plane을 생성
	m_pTitle->SetSize(1.6f,	1.6f);					//!< Plane의 사이즈 설저
	m_pTitle->SetPos(0.0f, 700.0f, 0.0f);				//!< Plane의 월드좌표 설정
	m_pTitle->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	m_pTitle->SetOffset(0.0f, 0.0f);
	m_pTitle->SetTexture(this, "Data/Image/Menu/Title.png");	//!< Plane위에 랜더링 되어질 텍스쳐
	m_pTitle->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	m_pTitle->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	m_pTitle->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	m_pTitle->SetShow(true);
	Commit(0, "Title", m_pTitle);

	
	//m_pVib[0] = new CEMPlane();						//!< 생성자로 Plane을 생성
	//m_pVib[0]->SetSize(1.0f,	1.0f);					//!< Plane의 사이즈 설저
	//m_pVib[0]->SetPos(D_LINE_START_X + 50, 500.0f, 0.0f);				//!< Plane의 월드좌표 설정
	//m_pVib[0]->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	//m_pVib[0]->SetOffset(0.0f, 0.0f);
	//m_pVib[0]->SetTexture(this, "Data/Image/Logo/Logo_"+IntToEMString((0)+1)+".png");	//!< Plane위에 랜더링 되어질 텍스쳐
	//m_pVib[0]->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	//m_pVib[0]->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	//m_pVib[0]->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	//m_pVib[0]->SetShow(true);
	//Commit(0,0, "블록", m_pVib[0]);
	//
	//m_pVib[1] = new CEMPlane();						//!< 생성자로 Plane을 생성
	//m_pVib[1]->SetSize(1.0f,	1.0f);					//!< Plane의 사이즈 설저
	//m_pVib[1]->SetPos(D_LINE_START_X + 120, -500.0f, 0.0f);				//!< Plane의 월드좌표 설정
	//m_pVib[1]->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	//m_pVib[1]->SetOffset(0.0f, -20.0f);
	//m_pVib[1]->SetTexture(this, "Data/Image/Logo/Logo_"+IntToEMString((1)+1)+".png");	//!< Plane위에 랜더링 되어질 텍스쳐
	//m_pVib[1]->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	//m_pVib[1]->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	//m_pVib[1]->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	//m_pVib[1]->SetShow(true);
	//Commit(0,1, "블록", m_pVib[1]);

	//m_pVib[2] = new CEMPlane();						//!< 생성자로 Plane을 생성
	//m_pVib[2]->SetSize(1.0f,	1.0f);					//!< Plane의 사이즈 설저
	//m_pVib[2]->SetPos(D_LINE_START_X + 170, 500.0f, 0.0f);				//!< Plane의 월드좌표 설정
	//m_pVib[2]->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	//m_pVib[2]->SetOffset(0.0f, -15.0f);
	//m_pVib[2]->SetTexture(this, "Data/Image/Logo/Logo_"+IntToEMString((2)+1)+".png");	//!< Plane위에 랜더링 되어질 텍스쳐
	//m_pVib[2]->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	//m_pVib[2]->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	//m_pVib[2]->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	//m_pVib[2]->SetShow(true);
	//Commit(0,2, "블록", m_pVib[2]);

	//m_pVib[3] = new CEMPlane();						//!< 생성자로 Plane을 생성
	//m_pVib[3]->SetSize(1.0f,	1.0f);					//!< Plane의 사이즈 설저
	//m_pVib[3]->SetPos(D_LINE_START_X + 220, -500.0f, 0.0f);				//!< Plane의 월드좌표 설정
	//m_pVib[3]->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	//m_pVib[3]->SetOffset(0.0f, -15.0f);
	//m_pVib[3]->SetTexture(this, "Data/Image/Logo/Logo_"+IntToEMString((3)+1)+".png");	//!< Plane위에 랜더링 되어질 텍스쳐
	//m_pVib[3]->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	//m_pVib[3]->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	//m_pVib[3]->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	//m_pVib[3]->SetShow(true);
	//Commit(0,3, "블록", m_pVib[3]);

	//m_pVib[4] = new CEMPlane();						//!< 생성자로 Plane을 생성
	//m_pVib[4]->SetSize(1.0f,	1.0f);					//!< Plane의 사이즈 설저
	//m_pVib[4]->SetPos(D_LINE_START_X + 260, 500.0f, 0.0f);				//!< Plane의 월드좌표 설정
	//m_pVib[4]->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	//m_pVib[4]->SetOffset(0.0f, -15.0f);
	//m_pVib[4]->SetTexture(this, "Data/Image/Logo/Logo_"+IntToEMString((4)+1)+".png");	//!< Plane위에 랜더링 되어질 텍스쳐
	//m_pVib[4]->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	//m_pVib[4]->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	//m_pVib[4]->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	//m_pVib[4]->SetShow(true);
	//Commit(0,4, "블록", m_pVib[4]);

	//
	//m_pVib[5] = new CEMPlane();						//!< 생성자로 Plane을 생성
	//m_pVib[5]->SetSize(1.0f,	1.0f);					//!< Plane의 사이즈 설저
	//m_pVib[5]->SetPos(D_LINE_START_X + 300, -500.0f, 0.0f);				//!< Plane의 월드좌표 설정
	//m_pVib[5]->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	//m_pVib[5]->SetOffset(0.0f, -15.0f);
	//m_pVib[5]->SetTexture(this, "Data/Image/Logo/Logo_"+IntToEMString((5)+1)+".png");	//!< Plane위에 랜더링 되어질 텍스쳐
	//m_pVib[5]->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	//m_pVib[5]->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	//m_pVib[5]->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	//m_pVib[5]->SetShow(true);
	//Commit(0,5, "블록", m_pVib[5]);
	//
	//m_pVib[6] = new CEMPlane();						//!< 생성자로 Plane을 생성
	//m_pVib[6]->SetSize(1.0f,	1.0f);					//!< Plane의 사이즈 설저
	//m_pVib[6]->SetPos(D_LINE_START_X + 330, 500.0f, 0.0f);				//!< Plane의 월드좌표 설정
	//m_pVib[6]->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	//m_pVib[6]->SetOffset(0.0f, -15.0f);
	//m_pVib[6]->SetTexture(this, "Data/Image/Logo/Logo_"+IntToEMString((6)+1)+".png");	//!< Plane위에 랜더링 되어질 텍스쳐
	//m_pVib[6]->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	//m_pVib[6]->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	//m_pVib[6]->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	//m_pVib[6]->SetShow(true);
	//Commit(0,6, "블록", m_pVib[6]);
	//
	//m_pVib[7] = new CEMPlane();						//!< 생성자로 Plane을 생성
	//m_pVib[7]->SetSize(1.0f,	1.0f);					//!< Plane의 사이즈 설저
	//m_pVib[7]->SetPos(D_LINE_START_X + 370, -500.0f, 0.0f);				//!< Plane의 월드좌표 설정
	//m_pVib[7]->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	//m_pVib[7]->SetOffset(0.0f, -10.0f);
	//m_pVib[7]->SetTexture(this, "Data/Image/Logo/Logo_"+IntToEMString((7)+1)+".png");	//!< Plane위에 랜더링 되어질 텍스쳐
	//m_pVib[7]->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	//m_pVib[7]->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	//m_pVib[7]->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	//m_pVib[7]->SetShow(true);
	//Commit(0,7, "블록", m_pVib[7]);


	m_pBg = new CEMPlane();		
	m_pBg->SetSize(1.07f,1.07f);					
	m_pBg->SetPos(0.0f, +11.0f, 0.0f);	
	m_pBg->SetLocalVec(0.0f, 0.0f);			
	m_pBg->SetOffset(0.0f, 0.0f);
	m_pBg->SetTexture(this, "Data/Image/Menu/Menu.png");	
	m_pBg->SetFrustumCulling(true);				
	m_pBg->SetBoundingBoxCalc(true);			
	m_pBg->SetBlend(true);						
	m_pBg->SetShow(true);
	Commit(999,"배경", m_pBg);

	m_pBlind = new CEMPlane();		
	m_pBlind->SetSize(1.0f,1.0f);					
	m_pBlind->SetPos(0.0f, 0.0f, 0.0f);	
	m_pBlind->SetLocalVec(0.0f, 0.0f);			
	m_pBlind->SetOffset(0.0f, 0.0f);
	m_pBlind->SetTexture(this, "Data/Image/Effect/Blind.png");	
	m_pBlind->SetFrustumCulling(true);				
	m_pBlind->SetBoundingBoxCalc(true);			
	m_pBlind->SetBlend(true);						
	m_pBlind->SetShow(true);
	Commit(998,"블라인드", m_pBlind);

	

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



	m_pVibrater = new CEMVibrater();
	m_pVibrater->Init(this,5.0f,0.6f, 240.0f, 235.0f,40.0f,80.0f,1.0f);

	m_pVibrater->Input(m_pTitle);
	m_pVibrater->Start();
	/*
	m_pVibrater->Input(m_pVib[0]);
	m_pVibrater->Input(m_pVib[2]);
	m_pVibrater->Input(m_pVib[1]);
	m_pVibrater->Input(m_pVib[3]);
	m_pVibrater->Input(m_pVib[4]);
	m_pVibrater->Input(m_pVib[5]);
	m_pVibrater->Input(m_pVib[6]);
	m_pVibrater->Input(m_pVib[7]);

		
	m_pVibrater->Input(m_pVib[0]);
	m_pVibrater->Input(m_pVib[0]);
	m_pVibrater->Input(m_pVib[1]);
	m_pVibrater->Input(m_pVib[2]);

		
	m_pVibrater->Input(m_pVib[2]);
	m_pVibrater->Input(m_pVib[3]);
	m_pVibrater->Input(m_pVib[4]);
	m_pVibrater->Input(m_pVib[5]);
	m_pVibrater->Input(m_pVib[6]);
	m_pVibrater->Input(m_pVib[7]);


	m_pVibrater->Start();
*/
	m_pBlindTimer = 0;
	m_pBlindSpeed = 1.0f;

	for(int i=0; i<3; i++)
	{
		m_pButtonGameStartImg[i] = new CEMPlane();		
		m_pButtonGameStartImg[i]->SetSize(1.0f,1.0f);					
		m_pButtonGameStartImg[i]->SetPos(0.0f, 0.0f, 0.0f);	
		m_pButtonGameStartImg[i]->SetLocalVec(0.0f, 0.0f);			
		m_pButtonGameStartImg[i]->SetOffset(0.0f, 0.0f);
		m_pButtonGameStartImg[i]->SetTexture(this, "Data/Image/Menu/Button_Start_"+IntToEMString(i+1)+".png");	
		m_pButtonGameStartImg[i]->SetFrustumCulling(true);				
		m_pButtonGameStartImg[i]->SetBoundingBoxCalc(true);			
		m_pButtonGameStartImg[i]->SetBlend(true);						
		m_pButtonGameStartImg[i]->SetShow(true);
		Commit(0,i,"ButtonGameStartImg", m_pButtonGameStartImg[i]);
	}
	m_ButtonGameStart.Init(this,m_pButtonGameStartImg[0],m_pButtonGameStartImg[1],m_pButtonGameStartImg[2],stEMVec2(0.0f, +20.0f), false);
	
	for(int i=0; i<3; i++)
	{
		m_pButtonHowToImg[i] = new CEMPlane();		
		m_pButtonHowToImg[i]->SetSize(1.0f,1.0f);					
		m_pButtonHowToImg[i]->SetPos(0.0f, 0.0f, 0.0f);	
		m_pButtonHowToImg[i]->SetLocalVec(0.0f, 0.0f);			
		m_pButtonHowToImg[i]->SetOffset(0.0f, 0.0f);
		m_pButtonHowToImg[i]->SetTexture(this, "Data/Image/Menu/Button_Howto_"+IntToEMString(i+1)+".png");	
		m_pButtonHowToImg[i]->SetFrustumCulling(true);				
		m_pButtonHowToImg[i]->SetBoundingBoxCalc(true);			
		m_pButtonHowToImg[i]->SetBlend(true);						
		m_pButtonHowToImg[i]->SetShow(true);
		Commit(0,i,"ButtonHowToImg", m_pButtonHowToImg[i]);
	}
	m_ButtonHowTo.Init(this,m_pButtonHowToImg[0],m_pButtonHowToImg[1],m_pButtonHowToImg[2],stEMVec2(10.0f, -60.0f), false);
	

	for(int i=0; i<3; i++)
	{
		m_pButtonCreditImg[i] = new CEMPlane();		
		m_pButtonCreditImg[i]->SetSize(1.0f,1.0f);					
		m_pButtonCreditImg[i]->SetPos(0.0f, 0.0f, 0.0f);	
		m_pButtonCreditImg[i]->SetLocalVec(0.0f, 0.0f);			
		m_pButtonCreditImg[i]->SetOffset(0.0f, 0.0f);
		m_pButtonCreditImg[i]->SetTexture(this, "Data/Image/Menu/Button_Credit_"+IntToEMString(i+1)+".png");	
		m_pButtonCreditImg[i]->SetFrustumCulling(true);				
		m_pButtonCreditImg[i]->SetBoundingBoxCalc(true);			
		m_pButtonCreditImg[i]->SetBlend(true);						
		m_pButtonCreditImg[i]->SetShow(true);
		Commit(0,i,"ButtonCreditImg", m_pButtonCreditImg[i]);
	}
	m_ButtonCredit.Init(this,m_pButtonCreditImg[0],m_pButtonCreditImg[1],m_pButtonCreditImg[2],stEMVec2(0.0f, -140.0f), false);
	

	
	for(int i=0; i<3; i++)
	{
		m_pButtonOptionImg[i] = new CEMPlane();		
		m_pButtonOptionImg[i]->SetSize(1.0f,1.0f);					
		m_pButtonOptionImg[i]->SetPos(0.0f, 0.0f, 0.0f);	
		m_pButtonOptionImg[i]->SetLocalVec(0.0f, 0.0f);			
		m_pButtonOptionImg[i]->SetOffset(0.0f, 0.0f);
		m_pButtonOptionImg[i]->SetTexture(this, "Data/Image/Menu/Button_Option_"+IntToEMString(i+1)+".png");	
		m_pButtonOptionImg[i]->SetFrustumCulling(true);				
		m_pButtonOptionImg[i]->SetBoundingBoxCalc(true);			
		m_pButtonOptionImg[i]->SetBlend(true);						
		m_pButtonOptionImg[i]->SetShow(true);
		Commit(0,i,"ButtonOptionImg", m_pButtonOptionImg[i]);
	}
	m_ButtonOption.Init(this,m_pButtonOptionImg[0],m_pButtonOptionImg[1],m_pButtonOptionImg[2],stEMVec2(0.0f, -220.0f), false);
	
	for(int i=0; i<3; i++)
	{
		m_pButtonExitImg[i] = new CEMPlane();		
		m_pButtonExitImg[i]->SetSize(1.0f,1.0f);					
		m_pButtonExitImg[i]->SetPos(0.0f, 0.0f, 0.0f);	
		m_pButtonExitImg[i]->SetLocalVec(0.0f, 0.0f);			
		m_pButtonExitImg[i]->SetOffset(0.0f, 0.0f);
		m_pButtonExitImg[i]->SetTexture(this, "Data/Image/Menu/Button_Quit_"+IntToEMString(i+1)+".png");	
		m_pButtonExitImg[i]->SetFrustumCulling(true);				
		m_pButtonExitImg[i]->SetBoundingBoxCalc(true);			
		m_pButtonExitImg[i]->SetBlend(true);						
		m_pButtonExitImg[i]->SetShow(true);
		Commit(0,i,"ButtonExitImg", m_pButtonExitImg[i]);
	}
	m_ButtonExit.Init(this,m_pButtonExitImg[0],m_pButtonExitImg[1],m_pButtonExitImg[2],stEMVec2(0.0f, -300.0f), false);
	


	for(int i=0; i<3; i++)
	{
		m_pSoundButtonImg[i] = new CEMPlane();						
		m_pSoundButtonImg[i]->SetSize(1.0f,	1.0f);				
		m_pSoundButtonImg[i]->SetPos(0.0f, 0.0f, 0.0f);				
		m_pSoundButtonImg[i]->SetLocalVec(0.0f, 0.0f);		
		m_pSoundButtonImg[i]->SetOffset(0.0f, 0.0f);
		m_pSoundButtonImg[i]->SetTexture(this, "Data/Image/Menu/Speak_None_"+IntToEMString(i+1)+".png");
		m_pSoundButtonImg[i]->SetFrustumCulling(true);
		m_pSoundButtonImg[i]->SetBoundingBoxCalc(true);
		m_pSoundButtonImg[i]->SetBlend(true);	
		m_pSoundButtonImg[i]->SetShow(true);
		m_pSoundButtonImg[i]->SetBackFaceCulling(false);
		Commit(-1,i, "m_pSoundButtonImg", m_pSoundButtonImg[i]);
	}
	m_SoundButton.Init(this,m_pSoundButtonImg[0],m_pSoundButtonImg[1],m_pSoundButtonImg[2], stEMVec2(175,-330), true);
	
	for(int i=0; i<3; i++)
	{
		m_pSoundButton2Img[i] = new CEMPlane();						
		m_pSoundButton2Img[i]->SetSize(1.0f,	1.0f);				
		m_pSoundButton2Img[i]->SetPos(0.0f, 0.0f, 0.0f);				
		m_pSoundButton2Img[i]->SetLocalVec(0.0f, 0.0f);		
		m_pSoundButton2Img[i]->SetOffset(0.0f, 0.0f);
		m_pSoundButton2Img[i]->SetTexture(this, "Data/Image/Menu/Speak_Off_"+IntToEMString(i+1)+".png");
		m_pSoundButton2Img[i]->SetFrustumCulling(true);
		m_pSoundButton2Img[i]->SetBoundingBoxCalc(true);
		m_pSoundButton2Img[i]->SetBlend(true);	
		m_pSoundButton2Img[i]->SetShow(true);
		m_pSoundButton2Img[i]->SetBackFaceCulling(false);
		Commit(-1,i, "m_pSoundButton2Img", m_pSoundButton2Img[i]);
	}
	m_SoundButton2.Init(this,m_pSoundButton2Img[0],m_pSoundButton2Img[1],m_pSoundButton2Img[2], stEMVec2(144,-338.7), true);
	


	m_bButtonAppear = false;

	m_SnowMng = new CEMSnowMng();
	m_SnowMng->Init(this,100,E_SNOW_OPTION_MENU, CEMColor(255,117,249), 600.0f);

	
/*

	for(int i=0; i<3; i++)
	{
		m_pSkipImg[i] = new CEMPlane();						
		m_pSkipImg[i]->SetSize(1.0f,	1.0f);				
		m_pSkipImg[i]->SetPos(0.0f, 0.0f, 0.0f);
		m_pSkipImg[i]->SetLocalVec(0.0f, 0.0f);		
		m_pSkipImg[i]->SetOffset(0.0f, 0.0f);
		m_pSkipImg[i]->SetTexture(this, "Data/Image/Logo/Skip_"+IntToEMString(i+1)+".png");
		m_pSkipImg[i]->SetFrustumCulling(true);
		m_pSkipImg[i]->SetBoundingBoxCalc(true);
		m_pSkipImg[i]->SetBlend(true);	
		m_pSkipImg[i]->SetShow(false);
		m_pSkipImg[i]->SetBackFaceCulling(false);
		Commit(-30, i, "Skip버튼", m_pSkipImg[i]);
	}
	m_Skip.Init(this,m_pSkipImg[0],m_pSkipImg[1],m_pSkipImg[2],stEMVec2(155.0f,-340.0f),true);
*/
	m_fUpDownTime = 1.0f;
	m_fUpDownSpeed = 0.017f;
	m_fUpDownPlusTime = 0.0f;
	m_fTimer = 0.0f;

	CRootScene::Enter(pSceneWork);
}

void CMenu::Update(CSceneWork* pSceneWork, float dt)
{
	m_SnowMng->Update(dt);
	m_fTimer += dt;

	m_ButtonGameStart.Update(this,dt);
	m_ButtonHowTo.Update(this,dt);
	m_ButtonCredit.Update(this,dt);
	m_ButtonOption.Update(this,dt);
	m_ButtonExit.Update(this,dt);

	m_SoundButton.Update(this,dt);
	m_SoundButton2.Update(this,dt);

	if( m_SoundButton.IsAction() == true )
	{
		m_SoundButton.m_bAction = false;
		g_SoundOnOff =  false;
//		g_bPause = false;

		
		for(int i=0; i<D_SOUND_MAX; i++)
		{
			D_SOUND->Stop(Sound[i]);
		}

	}
	else if( m_SoundButton2.IsAction() == true )
	{
		m_SoundButton2.m_bAction = false;
		g_SoundOnOff =  true;

		for(int i=0; i<D_SOUND_MAX; i++)
		{
			if(bStopSound[i] == true)
			{
				bStopSound[i] = false;
				D_SOUND->Stop(Sound[i]);
			}
		}

		SoundFp = D_SOUND->FileOpen("Data/Sound/Menu_BGM.mp3");
		Sound[1] = D_SOUND->Play(SoundFp,1.0f,true);
		bStopSound[1] = true;


//		g_bPause = false;
	}

	
	if(g_SoundOnOff == true)
	{
		m_SoundButton.m_bVisible = true;
		m_SoundButton2.m_bVisible = false;


	}
	else if(g_SoundOnOff == false)
	{
		m_SoundButton.m_bVisible = false;
		m_SoundButton2.m_bVisible = true;


	}

	//m_Skip.Update(this,dt);
	/*if( m_Skip.IsAction() == true )
	{
		m_Skip.m_bAction = false;
		m_pVibrater->Skip();
		m_Skip.m_bVisible = false;
	}
*/
	
	
	
	if(m_pVibrater != NULL)
		m_pVibrater->Update(dt);

	if(m_fTimer >= 1.5f)
	{
		m_pTitle->MoveY(+m_fUpDownTime);
		m_pBg->MoveY(-m_fUpDownTime);
		m_fUpDownTime -= m_fUpDownSpeed;
		m_fUpDownSpeed += m_fUpDownPlusTime;
		if(m_fUpDownTime <= -0.5f)
		{
			m_fUpDownSpeed = -0.017f;
		}
		else if(m_fUpDownTime >= 0.5f)
		{
			m_fUpDownSpeed = 0.017f;
		}
	}

	// if(m_bButtonAppear == false)
	//{
	//	m_bButtonAppear = true;
	//	m_ButtonGameStart.BlendAppear(1.0f);
	//	m_ButtonHowTo.BlendAppear(1.0f);
	//	m_ButtonOption.BlendAppear(1.0f);
	//	m_ButtonCredit.BlendAppear(1.0f);
	//	m_ButtonExit.BlendAppear(1.0f);
	//}


	if(m_pVibrater != NULL)
	{
		if( m_pVibrater->IsVibrating() == false && m_bButtonAppear == false)
		{
			m_bButtonAppear= true;
			m_ButtonGameStart.BlendAppear(1.0f);
			m_ButtonHowTo.BlendAppear(1.0f);
			m_ButtonOption.BlendAppear(1.0f);
			m_ButtonCredit.BlendAppear(1.0f);
			m_ButtonExit.BlendAppear(1.0f);
		}
	}







	if( m_ButtonGameStart.IsAction() == true)
	{
		m_ButtonGameStart.m_bAction = false;
		D_SCENE->ChangeSceneFade("StageMenu");
	}

	if( m_ButtonHowTo.IsAction() == true)
	{
		m_ButtonHowTo.m_bAction = false;
		D_SCENE->ChangeSceneFade("HowToPlay");
	}

	if( m_ButtonCredit.IsAction() == true)
	{
		m_ButtonCredit.m_bAction = false;
		D_SCENE->ChangeSceneFade("Producer");
	}

	if( m_ButtonOption.IsAction() == true)
	{
		m_ButtonOption.m_bAction = false;
		//D_SCENE->ChangeSceneFade("Producer");
	}

	if( m_ButtonExit.IsAction() == true)
	{
		m_ButtonExit.m_bAction = false;
		exit(1);
	}







	m_pBlindTimer += dt * m_pBlindSpeed;
	if(m_pBlindTimer > 3)
	{
		m_pBlindTimer = 3;
		m_pBlindSpeed *= -1;
	}
	else if(m_pBlindTimer < 0)
	{
		m_pBlindTimer = 0;
		m_pBlindSpeed *= -1;
	}

	m_pBlind->SetColor(0,0,0,((m_pBlindTimer/3)/3));
	//if(m_pTextBox != NULL)
	//	m_pTextBox->Update(dt);
	m_stCamPos.m_fZ = D_CAM_Z_FIXED;
	D_CAMERA->SetPos(m_stCamPos);

	CRootScene::Update(pSceneWork, dt);
}

void CMenu::Render(CSceneWork* pSceneWork)
{


	CRootScene::Render(pSceneWork);
}


void CMenu::Exit(CSceneWork* pSceneWork)
{
	//m_pTextBox->Exit();
	//delete m_pTextBox;
	

	Destroy();				//!< 현재 씬에서 메모리 잡은거 전부 해제
	
	m_pVibrater->Exit();
	delete m_pVibrater;
	

	CRootScene::Exit(pSceneWork);
}

void CMenu::MouseDownEvent(stMouseInfo stPos, enumMouseButton eButton)
{
	/*if(m_bButtonAppear == false)
	{
		m_bButtonAppear = true;
		m_Button.BlendAppear(1.0f);
	}*/
	if(eButton == E_MOUSE_LEFT)
	{
		m_ButtonGameStart.Check_Down(stPos, 0);
		m_ButtonHowTo.Check_Down(stPos, 0);
		m_ButtonCredit.Check_Down(stPos, 0);
		m_ButtonOption.Check_Down(stPos, 0);
		m_ButtonExit.Check_Down(stPos, 0);

		m_SoundButton.Check_Down(stPos, -1);
		
		m_SoundButton2.Check_Down(stPos, -1);


		//m_Skip.Check_Down(stPos,-30);
	}
}

void CMenu::MouseUpEvent(stMouseInfo stPos, enumMouseButton eButton)
{
	if(eButton == E_MOUSE_LEFT)
	{
		m_ButtonGameStart.Check_Up(stPos, 0);
		m_ButtonHowTo.Check_Up(stPos, 0);
		m_ButtonCredit.Check_Up(stPos, 0);
		m_ButtonOption.Check_Up(stPos, 0);
		m_ButtonExit.Check_Up(stPos, 0);
		
		m_SoundButton.Check_Up(stPos, -1);
		m_SoundButton2.Check_Up(stPos, -1);
		//m_Skip.Check_Up(stPos,-30);
	}
}

void CMenu::MouseMoveEvent(stMouseInfo stPos)
{
	m_ButtonGameStart.Check_Move(stPos, 0);
	m_ButtonHowTo.Check_Move(stPos, 0);
	m_ButtonCredit.Check_Move(stPos, 0);
	m_ButtonOption.Check_Move(stPos, 0);
	m_ButtonExit.Check_Move(stPos, 0);
		
	m_SoundButton.Check_Move(stPos, -1);
	m_SoundButton2.Check_Move(stPos, -1);

	//m_Skip.Check_Move(stPos,-30);
}

HRESULT CMenu::WindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_LBUTTONDOWN:
		{
			//D_SCENE->ChangeSceneFade("Stage",(0.1f),(0.1f));
		}break;
	}
	return msg;
}


void CMenu::BeginContact(b2Contact* contact)
{
	CEMPhysicRoot::BeginContact(contact);
	//아래에 코드를 작성하세요


}

void CMenu::EndContact(b2Contact* contact)
{
	CEMPhysicRoot::EndContact(contact);
	//아래에 코드를 작성하세요

}

void CMenu::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	CEMPhysicRoot::PreSolve(contact, oldManifold);
	//아래에 코드를 작성하세요

}

void CMenu::PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
{
	CEMPhysicRoot::PostSolve(contact, impulse);
	//아래에 코드를 작성하세요

}
