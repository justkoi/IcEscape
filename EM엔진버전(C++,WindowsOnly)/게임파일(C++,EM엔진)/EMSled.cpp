#include "stdafx.h"

void CEMSled::Init(CRootScene* m_pThisScene)
{
	m_pSled = new CEMPlane();
	m_pSled->SetSize(2.0f , 2.0f);
	m_pSled->SetPos(0.0f, 0.0f, 0.0f);				//!< Plane�� ������ǥ ����
	m_pSled->SetLocalVec(0.0f, 0.0f);				//!< Plane�� ������ǥ ����
	m_pSled->SetOffset(0.0f, 0.0f);
	m_pSled->SetTexture(m_pThisScene, "Data/Image/Stage/Sled.png");	//!< Plane���� ������ �Ǿ��� �ؽ���
	m_pSled->SetFrustumCulling(false);				//!< Plane�� ī�޶� �ٶ󺸴� ��ġ���� ��� ��� plane�� �׷����� �ʽ��ϴ�. false�� �ݴ�
	m_pSled->SetBoundingBoxCalc(false);				//!< FrustumCulling�� �Ϸ��� �� BoundingBoxCalc����� ������մϴ� 
	m_pSled->SetBlend(true);						//!< ������ �ϰ� �ʹٸ� true���ּ��� �⺻���� false�Դϴ�.
	m_pSled->SetShow(true);
	m_pSled->SetBackFaceCulling(false);
	m_pThisScene->Commit(-9, "Sled", m_pSled);

	m_pSled_IceLoad = new CEMPlane();
	m_pSled_IceLoad->SetSize(1.0f , 1.0f);
	m_pSled_IceLoad->SetPos(0.0f, 0.0f, 0.0f);				//!< Plane�� ������ǥ ����
	m_pSled_IceLoad->SetLocalVec(0.0f, 0.0f);				//!< Plane�� ������ǥ ����
	m_pSled_IceLoad->SetOffset(0.0f, 0.0f);
	m_pSled_IceLoad->SetTexture(m_pThisScene, "Data/Image/Stage/Sled_IceLoad.png");	//!< Plane���� ������ �Ǿ��� �ؽ���
	m_pSled_IceLoad->SetFrustumCulling(false);				//!< Plane�� ī�޶� �ٶ󺸴� ��ġ���� ��� ��� plane�� �׷����� �ʽ��ϴ�. false�� �ݴ�
	m_pSled_IceLoad->SetBoundingBoxCalc(false);				//!< FrustumCulling�� �Ϸ��� �� BoundingBoxCalc����� ������մϴ� 
	m_pSled_IceLoad->SetBlend(true);						//!< ������ �ϰ� �ʹٸ� true���ּ��� �⺻���� false�Դϴ�.
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