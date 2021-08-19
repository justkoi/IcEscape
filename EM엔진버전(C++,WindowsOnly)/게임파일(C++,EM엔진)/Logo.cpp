#include "stdafx.h"


void CLogo::Enter(CSceneWork* pSceneWork)
{
	for(int i=0; i<D_SOUND_MAX; i++)
	{
		if(bStopSound[i] == true)
		{
			bStopSound[i] = false;
			D_SOUND->Stop(Sound[i]);
		}
	}


	SoundFp = D_SOUND->FileOpen("Data/Sound/KG_BGM.mp3");
	Sound[0] = D_SOUND->Play(SoundFp,1.0f,true);
	bStopSound[0] = true;

	//!=====================================================
	
	//!=====================================================

	//!=====================================================
	//!ȭ�鿡 �ؽ��� ����ϱ�
	
	//!=====================================================
	
	//!=====================================================
	//!ȭ�鿡 Plane����ϱ�
	m_pPlane = new CEMPlane();						//!< �����ڷ� Plane�� ����
	m_pPlane->SetSize(1.1f,	1.1f);					//!< Plane�� ������ ����
	m_pPlane->SetPos(0.0f, 0.0f, 0.0f);				//!< Plane�� ������ǥ ����
	m_pPlane->SetLocalVec(0.0f, 0.0f);				//x!< Plane�� ������ǥ ����
	m_pPlane->SetOffset(0.0f, 0.0f);
	m_pPlane->SetTexture(this, "Data/Image/Logo/Logo.png");	//!< Plane���� ������ �Ǿ��� �ؽ���
	m_pPlane->SetFrustumCulling(true);				//!< Plane�� ī�޶� �ٶ󺸴� ��ġ���� ��� ��� plane�� �׷����� �ʽ��ϴ�. false�� �ݴ�
	m_pPlane->SetBoundingBoxCalc(true);				//!< FrustumCulling�� �Ϸ��� �� BoundingBoxCalc����� ������մϴ� 
	m_pPlane->SetBlend(true);						//!< ������ �ϰ� �ʹٸ� true���ּ��� �⺻���� false�Դϴ�.
	m_pPlane->SetShow(true);
	
	Commit(0, "�ΰ�", m_pPlane);

	
	m_fTimer = 0.0f;
	m_fChange = false;

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
		Commit(-30, i, "Skip��ư", m_pSkipImg[i]);
	}
	m_Skip.Init(this,m_pSkipImg[0],m_pSkipImg[1],m_pSkipImg[2],stEMVec2(155.0f,-340.0f),true);

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


	CRootScene::Enter(pSceneWork);
}

void CLogo::Update(CSceneWork* pSceneWork, float dt)
{
	m_Skip.Update(this,dt);
	m_fTimer += dt;
	if(m_fTimer >= 3.0f && m_fChange == false)
	{
		m_fChange = true;
		D_SCENE->ChangeSceneFade("Menu");
	}
	if( m_Skip.IsAction() == true )
	{
		m_Skip.m_bAction = false;
		D_SCENE->ChangeSceneFade("Menu");
	}

	m_stCamPos.m_fZ = D_CAM_Z_FIXED;
	D_CAMERA->SetPos(m_stCamPos);
	CRootScene::Update(pSceneWork, dt);
}

void CLogo::Render(CSceneWork* pSceneWork)
{


	CRootScene::Render(pSceneWork);
}

void CLogo::Exit(CSceneWork* pSceneWork)
{
	Destroy();				//!< ���� ������ �޸� ������ ���� ����

	CRootScene::Exit(pSceneWork);
}

void CLogo::MouseDownEvent(stMouseInfo stPos, enumMouseButton eButton)
{
	m_Skip.Check_Down(stPos,-30);
}

void CLogo::MouseUpEvent(stMouseInfo stPos, enumMouseButton eButton)
{
	m_Skip.Check_Up(stPos,-30);
}
void CLogo::MouseMoveEvent(stMouseInfo stPos)
{
	m_Skip.Check_Move(stPos,-30);
}

HRESULT CLogo::WindowMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_LBUTTONDOWN:
		{
			int x = 0;
		}break;
	}
	return msg;
}


void CLogo::BeginContact(b2Contact* contact)
{
	CEMPhysicRoot::BeginContact(contact);
	//�Ʒ��� �ڵ带 �ۼ��ϼ���


}

void CLogo::EndContact(b2Contact* contact)
{
	CEMPhysicRoot::EndContact(contact);
	//�Ʒ��� �ڵ带 �ۼ��ϼ���

}

void CLogo::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	CEMPhysicRoot::PreSolve(contact, oldManifold);
	//�Ʒ��� �ڵ带 �ۼ��ϼ���

}

void CLogo::PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
{
	CEMPhysicRoot::PostSolve(contact, impulse);
	//�Ʒ��� �ڵ带 �ۼ��ϼ���

}
