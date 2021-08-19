#include "stdafx.h"

stEMVec3	MakerPos;
stEMVec3	MakerPos2;
stEMVec3	MakerPos3;

void CProducer::Enter(CSceneWork* pSceneWork)
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

	
	MakerPos = stEMVec3(-300.0f, 0.0f,0.0f);
	MakerPos2 = stEMVec3(0.0f,500.0f,0.0f);
	MakerPos3 = stEMVec3(400.0f,00.0f,0.0f);



	//!=====================================================

	//!=====================================================
	//!화면에 텍스쳐 출력하기
	//!=====================================================

	//!=====================================================
	//!화면에 Plane출력하기
	m_pPlane = new CEMPlane();						//!< 생성자로 Plane을 생성
	m_pPlane->SetSize(2.0f,	1.0f);					//!< Plane의 사이즈 설저
	m_pPlane->SetPos(0.0f, 0.0f, 0.0f);				//!< Plane의 월드좌표 설정
	m_pPlane->SetLocalVec(-3.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	m_pPlane->SetOffset(0.0f, -10.0f);
	m_pPlane->SetTexture(this, "../Data/Logo/Logo_Bg.png");	//!< Plane위에 랜더링 되어질 텍스쳐
	m_pPlane->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	m_pPlane->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	m_pPlane->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	m_pPlane->SetShow(true);
	/*Commit(0, "배경", m_pPlane);*/



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
	m_Maker->SetSize(0.9f,0.9f);
	m_Maker->SetTexture(this,"Data/Image/Producer/Maker1.png");
	m_Maker->SetPos(MakerPos);
	m_Maker->SetFrustumCulling(true);
	m_Maker->SetBoundingBoxCalc(true);
	m_Maker->SetBlend(true);
	m_Maker->SetShow(true);
	m_Maker->SetBackFaceCulling(false);
	m_Maker->SetShow(true);

	Commit(0,"만든이1",m_Maker);

	m_Maker2 = new CEMPlane;
	m_Maker2->SetSize(1.0f);
	m_Maker2->SetTexture(this,"Data/Image/Producer/Maker2.png");
	m_Maker2->SetPos(MakerPos2);
	m_Maker2->SetFrustumCulling(true);
	m_Maker2->SetBoundingBoxCalc(true);
	m_Maker2->SetBlend(true);
	m_Maker2->SetShow(true);
	m_Maker2->SetBackFaceCulling(false);
	m_Maker2->SetShow(true);


	Commit(0,"만든이2",m_Maker2);

	m_Maker3 = new CEMPlane;
	m_Maker3->SetSize(1.0f);
	m_Maker3->SetTexture(this,"Data/Image/Producer/Maker3.png");
	m_Maker3->SetPos(MakerPos3);
	m_Maker3->SetFrustumCulling(true);
	m_Maker3->SetBoundingBoxCalc(true);
	m_Maker3->SetBlend(true);
	m_Maker3->SetShow(true);
	m_Maker3->SetBackFaceCulling(false);
	m_Maker3->SetShow(true);

	Commit(0,"만든이3",m_Maker3);

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
	m_Back.Init(this,m_BackButton[0],m_BackButton[1],m_BackButton[2],stEMVec2(140.0f,-300.0f),true);

	m_fBlendTimer = 0.0f;

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

	m_Speed = 220.0f;
	m_Speed1 = 220.0f;
	m_Speed2 = 220.0f;
	/*
	m_NeonSign.Init(-220,+100,40,stEMVec2(0.5f,0.5f),this);
*/
/*
	m_SnowMng = new CEMSnowMng();
	m_SnowMng->Init(this,2000,E_SNOW_OPTION_MENU, CEMColor(255,117,249), 600.0f);*/
	CRootScene::Enter(pSceneWork);
}

void CProducer::Update(CSceneWork* pSceneWork, float dt)
{
	
	/*m_NeonSign.Update(dt);*/
	m_Back.Update(this,dt);

	

	if(m_Maker1EndCheck == false && MakerPos.m_fX <= 500)
	{
		MakerPos.m_fX += m_Speed*dt;
		m_Speed += 2.65f;
	}
	if(MakerPos.m_fX >= 500)
	{
		m_Maker1EndCheck = true;
		m_Speed = 220.0f;
	}

	if(m_Maker1EndCheck == true && MakerPos2.m_fY >= -600)
	{
		MakerPos2.m_fY -= m_Speed1*dt;
		m_Speed1 += 2.65f;
	}
	if(MakerPos2.m_fY <= -600)
	{
		m_Maker2EndCheck = true;
		m_Speed1 = 220.0f;
	}

	if(m_Maker2EndCheck == true && MakerPos3.m_fX >= -500)
	{
		MakerPos3.m_fX -= m_Speed2*dt;
		m_Speed2 += 2.9f;
	}
	if(MakerPos3.m_fX <= -500)
	{
		m_Maker3EndCheck = true;
		m_Speed2 = 220.0f;
	}
	if(m_Maker3EndCheck == true)
	{
		MakerPos.m_fX = 0.0f; MakerPos.m_fY = 200.0f;
		MakerPos2.m_fX = 0.0f; MakerPos2.m_fY = 0.0f;
		MakerPos3.m_fX = 0.0f; MakerPos3.m_fY = -200.0f;

		//m_Maker->SetAlpha(0.0f);
		//m_Maker2->SetAlpha(0.0f);
		//m_Maker3->SetAlpha(0.0f);
	}

	if(m_Maker3EndCheck == true)
	{
		m_fBlendTimer += dt;

		if(m_fBlendTimer > 3.0f)
		{
			m_fBlendTimer = 3.0f;
		}
		m_Maker->SetAlpha(m_fBlendTimer/3);
		m_Maker2->SetAlpha(m_fBlendTimer/3);
		m_Maker3->SetAlpha(m_fBlendTimer/3);
	}

	if(m_Back.IsAction() == true)
	{
		m_Back.m_bAction = false;
		m_Maker1EndCheck = false;
		m_Maker2EndCheck = false;
		m_Maker3EndCheck = false;
		D_SCENE->ChangeScene("Menu");
	}

	m_Maker->SetPos(MakerPos);
	m_Maker2->SetPos(MakerPos2);
	m_Maker3->SetPos(MakerPos3);

	m_stCamPos.m_fZ = D_CAM_Z_FIXED;
	D_CAMERA->SetPos(m_stCamPos);

	CRootScene::Update(pSceneWork, dt);
}

void CProducer::Render(CSceneWork* pSceneWork)
{


	CRootScene::Render(pSceneWork);
}


void CProducer::Exit(CSceneWork* pSceneWork)
{
	
	
	
	Destroy();				//!< 현재 씬에서 메모리 잡은거 전부 해제
	
	//delete MakerPos;
	//delete MakerPos2;
	//delete MakerPos3;

	CRootScene::Exit(pSceneWork);
}

void CProducer::MouseDownEvent(stMouseInfo stPos, enumMouseButton eButton)
{
	m_Back.Check_Down(stPos,0);
}

void CProducer::MouseUpEvent(stMouseInfo stPos, enumMouseButton eButton)
{
	m_Back.Check_Up(stPos,0);
}

void CProducer::MouseMoveEvent(stMouseInfo stPos)
{
	m_Back.Check_Move(stPos,0);
}

HRESULT CProducer::WindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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


void CProducer::BeginContact(b2Contact* contact)
{
	CEMPhysicRoot::BeginContact(contact);
	//아래에 코드를 작성하세요


}

void CProducer::EndContact(b2Contact* contact)
{
	CEMPhysicRoot::EndContact(contact);
	//아래에 코드를 작성하세요

}

void CProducer::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	CEMPhysicRoot::PreSolve(contact, oldManifold);
	//아래에 코드를 작성하세요

}

void CProducer::PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
{
	CEMPhysicRoot::PostSolve(contact, impulse);
	//아래에 코드를 작성하세요

}
