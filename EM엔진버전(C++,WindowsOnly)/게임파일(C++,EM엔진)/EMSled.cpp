#include "stdafx.h"

void CEMSled::Init(CRootScene* m_pThisScene)
{
	m_pSled = new CEMPlane();
	m_pSled->SetSize(2.0f , 2.0f);
	m_pSled->SetPos(0.0f, 0.0f, 0.0f);				//!< Plane의 월드좌표 설정
	m_pSled->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	m_pSled->SetOffset(0.0f, 0.0f);
	m_pSled->SetTexture(m_pThisScene, "Data/Image/Stage/Sled.png");	//!< Plane위에 랜더링 되어질 텍스쳐
	m_pSled->SetFrustumCulling(false);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	m_pSled->SetBoundingBoxCalc(false);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	m_pSled->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	m_pSled->SetShow(true);
	m_pSled->SetBackFaceCulling(false);
	m_pThisScene->Commit(-9, "Sled", m_pSled);

	m_pSled_IceLoad = new CEMPlane();
	m_pSled_IceLoad->SetSize(1.0f , 1.0f);
	m_pSled_IceLoad->SetPos(0.0f, 0.0f, 0.0f);				//!< Plane의 월드좌표 설정
	m_pSled_IceLoad->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
	m_pSled_IceLoad->SetOffset(0.0f, 0.0f);
	m_pSled_IceLoad->SetTexture(m_pThisScene, "Data/Image/Stage/Sled_IceLoad.png");	//!< Plane위에 랜더링 되어질 텍스쳐
	m_pSled_IceLoad->SetFrustumCulling(false);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
	m_pSled_IceLoad->SetBoundingBoxCalc(false);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
	m_pSled_IceLoad->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
	m_pSled_IceLoad->SetShow(true);
	m_pSled_IceLoad->SetBackFaceCulling(false);
	m_pThisScene->Commit(-9, "Sled_IceLoad", m_pSled_IceLoad);


	m_fMoveSpeed = 300.0f;

	m_fMaxHp = 30.0f;
	m_fHp = m_fMaxHp;

	m_stPos.m_fX = 300.0f;
	m_stPos.m_fY = -310.0f;

	m_bOnOff = false;


};


void CEMSled::Update(float dt)
{
	m_pSled->SetShow(false);
	m_pSled_IceLoad->SetShow(false);

	if(m_bOnOff == true)
	{
		m_pSled_IceLoad->SetShow(true);
		if(m_stPos.m_fX >= -250.0f)
		{
			m_pSled->SetShow(true);
			m_stPos.m_fX -= m_fMoveSpeed * dt;
		}
		else
		{
			m_bSledMoved = true;
		}

		if(m_fHp <= 0.0f)
			m_bOnOff = false;
	}
	
	m_pSled_IceLoad->SetAlpha((m_fHp/m_fMaxHp) - 0.3f);
	m_pSled->SetPos(m_stPos);
	m_pSled_IceLoad->SetPos(m_stPos.m_fX + 256, m_stPos.m_fY);
}

void CEMSled::Sleding()
{
	m_bOnOff = true;
	m_bSledMoved = false;
	
	m_stPos.m_fX = 300.0f;
	m_stPos.m_fY = -325.0f;

	m_fHp = m_fMaxHp;
}