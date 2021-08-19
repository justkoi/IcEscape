#include "stdafx.h"


void CEMEffectManager::Init(CRootScene* pThisScene)
{
	
	m_pThisScene = pThisScene;
}

void CEMEffectManager::Insert(int nIndex, float fX, float fY, float fSizeW, float fSizeH)
{
	CEMAnimation * m_pEffect;
	switch(nIndex)
	{

	case 1:
		m_pEffect = new CEMAnimation(10);
		m_pEffect->SetTexture(m_pThisScene,10,"Data/Image/Effect/Ice_1.png","Data/Image/Effect/Ice_2.png","Data/Image/Effect/Ice_3.png","Data/Image/Effect/Ice_4.png","Data/Image/Effect/Ice_5.png","Data/Image/Effect/Ice_6.png","Data/Image/Effect/Ice_7.png","Data/Image/Effect/Ice_8.png","Data/Image/Effect/Ice_9.png","Data/Image/Effect/Ice_10.png");
		m_pEffect->SetTime(0.07f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(-8.0f, -8.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(-5,m_pEffectList.size(),"Effect1",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;

	case 2:
		m_pEffect = new CEMAnimation(11);
		m_pEffect->SetTexture(m_pThisScene,11,"../Data/Effect/Jump0.png","../Data/Effect/Jump1.png","../Data/Effect/Jump2.png","../Data/Effect/Jump3.png","../Data/Effect/Jump4.png","../Data/Effect/Jump5.png","../Data/Effect/Jump6.png","../Data/Effect/Jump7.png","../Data/Effect/Jump8.png","../Data/Effect/Jump9.png","../Data/Effect/Jump10.png");
		m_pEffect->SetTime(0.09f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(0,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;

	case 3:
		m_pEffect = new CEMAnimation(5);
		m_pEffect->SetTexture(m_pThisScene,5,"../Data/Effect/Hit0.png","../Data/Effect/Hit1.png","../Data/Effect/Hit2.png","../Data/Effect/Hit3.png","../Data/Effect/Hit4.png");
		m_pEffect->SetTime(0.18f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(0,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;

	case 4:
		m_pEffect = new CEMAnimation(2);
		m_pEffect->SetTexture(m_pThisScene,2,"Data/Image/Effect/Combo.png","Data/Image/Effect/Combo.png");
		m_pEffect->SetTime(1.0f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(-9,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;

	case 1001:
		m_pEffect = new CEMAnimation(2);
		m_pEffect->SetTexture(m_pThisScene,2,"Data/Image/Effect/Combo.png","Data/Image/Effect/Combo.png");
		m_pEffect->SetTime(1.0f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(-9,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;

	case 1002:
		m_pEffect = new CEMAnimation(2);
		m_pEffect->SetTexture(m_pThisScene,2,"Data/Image/Effect/Combo.png","Data/Image/Effect/Combo.png");
		m_pEffect->SetTime(1.0f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(-9,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;
	
	case 1003:
		m_pEffect = new CEMAnimation(2);
		m_pEffect->SetTexture(m_pThisScene,2,"Data/Image/Effect/Combo.png","Data/Image/Effect/Combo.png");
		m_pEffect->SetTime(1.0f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(-9,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;
	
	case 1004:
		m_pEffect = new CEMAnimation(2);
		m_pEffect->SetTexture(m_pThisScene,2,"Data/Image/Effect/Combo.png","Data/Image/Effect/Combo.png");
		m_pEffect->SetTime(1.0f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(-9,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;
	
	case 1005:
		m_pEffect = new CEMAnimation(2);
		m_pEffect->SetTexture(m_pThisScene,2,"Data/Image/Effect/Combo.png","Data/Image/Effect/Combo.png");
		m_pEffect->SetTime(1.0f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(-9,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;
	
	case 1006:
		m_pEffect = new CEMAnimation(2);
		m_pEffect->SetTexture(m_pThisScene,2,"Data/Image/Effect/Combo.png","Data/Image/Effect/Combo.png");
		m_pEffect->SetTime(1.0f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(-9,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;
	
	case 1007:
		m_pEffect = new CEMAnimation(2);
		m_pEffect->SetTexture(m_pThisScene,2,"Data/Image/Effect/Combo.png","Data/Image/Effect/Combo.png");
		m_pEffect->SetTime(1.0f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(-9,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;
	
	case 1008:
		m_pEffect = new CEMAnimation(2);
		m_pEffect->SetTexture(m_pThisScene,2,"Data/Image/Effect/Combo.png","Data/Image/Effect/Combo.png");
		m_pEffect->SetTime(1.0f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(-9,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;
	
	case 1009:
		m_pEffect = new CEMAnimation(2);
		m_pEffect->SetTexture(m_pThisScene,2,"Data/Image/Effect/Combo.png","Data/Image/Effect/Combo.png");
		m_pEffect->SetTime(1.0f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(-9,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;
	
	case 1000:
		m_pEffect = new CEMAnimation(2);
		m_pEffect->SetTexture(m_pThisScene,2,"Data/Image/Effect/Combo.png","Data/Image/Effect/Combo.png");
		m_pEffect->SetTime(1.0f);
		m_pEffect->SetSize(fSizeW, fSizeH);					//!< Plane의 사이즈 설저
		m_pEffect->SetPos(fX, fY, 0);				//!< Plane의 월드좌표 설정
		m_pEffect->SetLocalVec(0.0f, 0.0f);				//!< Plane의 로컬좌표 설정
		m_pEffect->SetOffset(0.0f, 0.0f);
		m_pEffect->SetFrustumCulling(true);				//!< Plane이 카메라가 바라보는 위치에서 벗어날 경우 plane을 그려주지 않습니다. false는 반대
		m_pEffect->SetBoundingBoxCalc(true);				//!< FrustumCulling을 하려면 꼭 BoundingBoxCalc계산을 해줘야합니다 
		m_pEffect->SetBlend(true);						//!< 블렌딩을 하고 싶다면 true해주세요 기본값은 false입니다.
		m_pEffect->SetShow(true);
		m_pEffect->SetBackFaceCulling(false);
		m_pEffect->SetAnimationEndingType(E_ANI_ENDING_TYPE_DESTROY);
		m_pThisScene->Commit(-9,m_pEffectList.size(),"Effect",m_pEffect);
		m_pEffectList.push_back(m_pEffect);
	break;

	return;

	}
}



void CEMEffectManager::Update(float dt)
{
	list<CEMAnimation*>::iterator itr;
	for(itr = m_pEffectList.begin(); itr != m_pEffectList.end();)
	{
		if((*itr)->GetCurFrameNumber() == (*itr)->GetTotalFrame() - 1)
		{
			(*itr)->Destroy();
			itr = m_pEffectList.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void CEMEffectManager::Exit()
{
	m_pEffectList.clear();
}