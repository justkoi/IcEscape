#include "stdafx.h"



void CHowToPlay::Enter(CSceneWork* pSceneWork)
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

		SoundFp = D_SOUND->FileOpen("Data/Sound/Producer_BGM.mp3");
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
	


	m_pBg = new CEMPlane();		
	m_pBg->SetSize(1.0f,1.0f);					
	m_pBg->SetPos(0.0f, +5.0f, 0.0f);	
	m_pBg->SetLocalVec(0.0f, 0.0f);			
	m_pBg->SetOffset(0.0f, 0.0f);
	m_pBg->SetTexture(this, "Data/Image/Logo/Logo_Bg.png");	
	m_pBg->SetFrustumCulling(true);				
	m_pBg->SetBoundingBoxCalc(true);			
	m_pBg->SetBlend(true);						
	m_pBg->SetShow(true);
	Commit(999,"배경", m_pBg);


	m_Maker = new CEMPlane;
	m_Maker->SetSize(1.0f,1.0f);
	m_Maker->SetTexture(this,"Data/Image/HowToPlay/HowToPlay.png");
	m_Maker->SetPos(0.0f,0.0f,0.0f);
	m_Maker->SetFrustumCulling(true);
	m_Maker->SetBoundingBoxCalc(true);
	m_Maker->SetBlend(true);
	m_Maker->SetShow(true);
	m_Maker->SetBackFaceCulling(false);
	m_Maker->SetShow(true);

	Commit(88,"만든이1",m_Maker);


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
		Commit(0, i, "만든이버튼", m_BackButton[i]);
	}
	m_Back.Init(this,m_BackButton[0],m_BackButton[1],m_BackButton[2],stEMVec2(-130.0f,-310.0f),true);


	for(int i=0; i<3; i++)
	{
		m_StageButton[i] = new CEMPlane();						
		m_StageButton[i]->SetSize(1.0f,	1.0f);				
		m_StageButton[i]->SetPos(0.0f, 0.0f, 0.0f);
		m_StageButton[i]->SetLocalVec(0.0f, 0.0f);		
		m_StageButton[i]->SetOffset(0.0f, 0.0f);
		m_StageButton[i]->SetTexture(this, "Data/Image/Menu/Button_Start_"+IntToEMString(i+1)+".png");
		m_StageButton[i]->SetFrustumCulling(true);
		m_StageButton[i]->SetBoundingBoxCalc(true);
		m_StageButton[i]->SetBlend(true);	
		m_StageButton[i]->SetShow(false);
		m_StageButton[i]->SetBackFaceCulling(false);
		Commit(0, i, "게임시작버튼", m_StageButton[i]);
	}
	m_Stage.Init(this,m_StageButton[0],m_StageButton[1],m_StageButton[2],stEMVec2(+100.0f, -310.0f),true);



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
	m_pBlind->SetAlpha(0.8f);
	Commit(998,"블라인드", m_pBlind);

	/*
	m_NeonSign.Init(-220,+100,40,stEMVec2(0.5f,0.5f),this);
*/
/*
	m_SnowMng = new CEMSnowMng();
	m_SnowMng->Init(this,2000,E_SNOW_OPTION_MENU, CEMColor(255,117,249), 600.0f);*/
	CRootScene::Enter(pSceneWork);
}

void CHowToPlay::Update(CSceneWork* pSceneWork, float dt)
{
	
	m_Back.Update(this,dt);
	m_Stage.Update(this,dt);


	

	if(m_Back.IsAction() == true)
	{
		m_Back.m_bAction = false;
		D_SCENE->ChangeSceneFade("Menu");
	}
	if(m_Stage.IsAction() == true)
	{
		m_Stage.m_bAction = false;
		D_SCENE->ChangeSceneFade("StageMenu");
	}


	m_stCamPos.m_fZ = D_CAM_Z_FIXED;
	D_CAMERA->SetPos(m_stCamPos);

	CRootScene::Update(pSceneWork, dt);
}

void CHowToPlay::Render(CSceneWork* pSceneWork)
{


	CRootScene::Render(pSceneWork);
}


void CHowToPlay::Exit(CSceneWork* pSceneWork)
{
	
	
	
	Destroy();				//!< 현재 씬에서 메모리 잡은거 전부 해제
	
	//delete MakerPos;
	//delete MakerPos2;
	//delete MakerPos3;

	CRootScene::Exit(pSceneWork);
}

void CHowToPlay::MouseDownEvent(stMouseInfo stPos, enumMouseButton eButton)
{
	m_Back.Check_Down(stPos,0);
	m_Stage.Check_Down(stPos,0);
}

void CHowToPlay::MouseUpEvent(stMouseInfo stPos, enumMouseButton eButton)
{
	m_Back.Check_Up(stPos,0);
	m_Stage.Check_Up(stPos,0);
}

void CHowToPlay::MouseMoveEvent(stMouseInfo stPos)
{
	m_Back.Check_Move(stPos,0);
	m_Stage.Check_Move(stPos,0);
}

HRESULT CHowToPlay::WindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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


void CHowToPlay::BeginContact(b2Contact* contact)
{
	CEMPhysicRoot::BeginContact(contact);
	//아래에 코드를 작성하세요


}

void CHowToPlay::EndContact(b2Contact* contact)
{
	CEMPhysicRoot::EndContact(contact);
	//아래에 코드를 작성하세요

}

void CHowToPlay::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	CEMPhysicRoot::PreSolve(contact, oldManifold);
	//아래에 코드를 작성하세요

}

void CHowToPlay::PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
{
	CEMPhysicRoot::PostSolve(contact, impulse);
	//아래에 코드를 작성하세요

}
