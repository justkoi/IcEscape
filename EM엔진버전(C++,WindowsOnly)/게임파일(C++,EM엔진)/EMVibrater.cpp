#include "stdafx.h"

void CEMVibrater::Init(CRootScene* pThisScene,float fSpeed,float fPlusSpeed,float fBasicLine, float fLastBasicLine,float fVibDistance, float fVibDistanceScale, float fVibDistanceMinus)
{
	m_fLastBasicLine = fLastBasicLine;
	m_pThisScene = pThisScene;
	m_VibrainList.clear();

	m_fSpeed		= fSpeed;
	m_fPlusSpeed = fPlusSpeed;
	m_fBasicLine = fBasicLine;
	m_fVibDistanceScale = fVibDistanceScale;
	m_fVibDistanceMinus = fVibDistanceMinus;

	m_fVibDistance = fVibDistance;

	m_bStart = false;
	m_bSkip = false;

}
void CEMVibrater::Update(float dt)
{
	if(m_bSkip == true)
	{
		while(IsEnd() == true)
		{
			if(m_bStart == true)
			{
				bool bNextAct = false;	//!< 다음 것을 활동시키는 신호표시

				list<stEMVibrain*>::iterator it;
				for(it = m_VibrainList.begin(); it !=m_VibrainList.end(); it++)
				{
					if(bNextAct == true)
					{
						bNextAct = false;
						if((*it)->m_eState == E_VIBACT_STATE_NONE)
							(*it)->m_eState = E_VIBACT_STATE_ACT;
					}

					if( (*it)->m_eState == E_VIBACT_STATE_ACT)
					{
						if( (*it)->m_pPlane->GetPosVec2().m_fY > (*it)->m_fBasicLine )
						{
							(*it)->m_eDerection = E_DERECTION_DOWN;
							(*it)->m_pPlane->MoveY( - ((*it)->m_fSpeed) );
							(*it)->m_fSpeed += (*it)->m_fPlusSpeed;
							if( (*it)->m_pPlane->GetPosVec2().m_fY <= (*it)->m_fBasicLine )
							{
								(*it)->m_pPlane->SetPos((*it)->m_pPlane->GetPosVec2().m_fX,(*it)->m_fBasicLine);
								(*it)->m_eState = E_VIBACT_STATE_VIB;
								(*it)->m_fSpeed = m_fSpeed;
								if(it !=m_VibrainList.end())
								{
									bNextAct = true;
								}
							}
						}
						else if((*it)->m_pPlane->GetPosVec2().m_fY < (*it)->m_fBasicLine)
						{
							(*it)->m_eDerection = E_DERECTION_UP;
							(*it)->m_pPlane->MoveY(  ((*it)->m_fSpeed) );
							(*it)->m_fSpeed += (*it)->m_fPlusSpeed;
							if( (*it)->m_pPlane->GetPosVec2().m_fY >= (*it)->m_fBasicLine )
							{
								(*it)->m_pPlane->SetPos((*it)->m_pPlane->GetPosVec2().m_fX,(*it)->m_fBasicLine);
								(*it)->m_eState = E_VIBACT_STATE_VIB;
								(*it)->m_fSpeed = m_fSpeed;
								if(it !=m_VibrainList.end())
								{
									bNextAct = true;
								}
							}
						}
					}
					else if( (*it)->m_eState == E_VIBACT_STATE_VIB)
					{
						if((*it)->m_eDerection == E_DERECTION_UP)
						{
							(*it)->m_pPlane->MoveY( - ((*it)->m_fSpeed) );
							(*it)->m_fNowVibDistance += (*it)->m_fSpeed;

							(*it)->m_fSpeed += (*it)->m_fPlusSpeed;

							if((*it)->m_fNowVibDistance >= (*it)->m_fVibDistance)
							{
								(*it)->m_fSpeed = m_fSpeed;
								(*it)->m_fNowVibDistance = 0;
								(*it)->m_eDerection = E_DERECTION_DOWN;

								if((*it)->m_bTurn == false)
									(*it)->m_bTurn = true;
								else if((*it)->m_bTurn == true)
								{
									(*it)->m_fVibDistance = ((*it)->m_fVibDistance/100) * m_fVibDistanceScale;
									(*it)->m_fVibDistance -= m_fVibDistanceMinus;
									(*it)->m_bTurn = false;
								}

								if((*it)->m_fVibDistance <= 0)
								{
									(*it)->m_pPlane->SetPos((*it)->m_pPlane->GetPosVec2().m_fX,(*it)->m_fLastBasicLine);
									(*it)->m_eState = E_VIBACT_STATE_STOP;

								}
							}
						}
						else if((*it)->m_eDerection == E_DERECTION_DOWN)
						{
							(*it)->m_fSpeed = m_fSpeed;
							(*it)->m_pPlane->MoveY( + ((*it)->m_fSpeed) );
							(*it)->m_fNowVibDistance += (*it)->m_fSpeed;

							(*it)->m_fSpeed += (*it)->m_fPlusSpeed;

							if((*it)->m_fNowVibDistance >= (*it)->m_fVibDistance)
							{
								(*it)->m_fNowVibDistance = 0;
								(*it)->m_eDerection = E_DERECTION_UP;

								if((*it)->m_bTurn == false)
									(*it)->m_bTurn = true;
								else if((*it)->m_bTurn == true)
								{
									(*it)->m_fVibDistance = ((*it)->m_fVibDistance/100) * m_fVibDistanceScale;
									(*it)->m_fVibDistance -= m_fVibDistanceMinus;
									(*it)->m_bTurn = false;
								}

								if((*it)->m_fVibDistance <= 0)
								{
									(*it)->m_pPlane->SetPos((*it)->m_pPlane->GetPosVec2().m_fX,(*it)->m_fLastBasicLine);
									(*it)->m_eState = E_VIBACT_STATE_STOP;

								}
							}


						}
					}

				}
			}
		}
	}
	else if(m_bSkip == false)
	{
		if(m_bStart == true)
		{
			bool bNextAct = false;	//!< 다음 것을 활동시키는 신호표시

			list<stEMVibrain*>::iterator it;
			for(it = m_VibrainList.begin(); it !=m_VibrainList.end(); it++)
			{
				if(bNextAct == true)
				{
					bNextAct = false;
					if((*it)->m_eState == E_VIBACT_STATE_NONE)
						(*it)->m_eState = E_VIBACT_STATE_ACT;
				}

				if( (*it)->m_eState == E_VIBACT_STATE_ACT)
				{
					if( (*it)->m_pPlane->GetPosVec2().m_fY > (*it)->m_fBasicLine )
					{
						(*it)->m_eDerection = E_DERECTION_DOWN;
						(*it)->m_pPlane->MoveY( - ((*it)->m_fSpeed) );
						(*it)->m_fSpeed += (*it)->m_fPlusSpeed;
						if( (*it)->m_pPlane->GetPosVec2().m_fY <= (*it)->m_fBasicLine )
						{
							(*it)->m_pPlane->SetPos((*it)->m_pPlane->GetPosVec2().m_fX,(*it)->m_fBasicLine);
							(*it)->m_eState = E_VIBACT_STATE_VIB;
							(*it)->m_fSpeed = m_fSpeed;
							if(it !=m_VibrainList.end())
							{
								bNextAct = true;
							}
						}
					}
					else if((*it)->m_pPlane->GetPosVec2().m_fY < (*it)->m_fBasicLine)
					{
						(*it)->m_eDerection = E_DERECTION_UP;
						(*it)->m_pPlane->MoveY(  ((*it)->m_fSpeed) );
						(*it)->m_fSpeed += (*it)->m_fPlusSpeed;
						if( (*it)->m_pPlane->GetPosVec2().m_fY >= (*it)->m_fBasicLine )
						{
							(*it)->m_pPlane->SetPos((*it)->m_pPlane->GetPosVec2().m_fX,(*it)->m_fBasicLine);
							(*it)->m_eState = E_VIBACT_STATE_VIB;
							(*it)->m_fSpeed = m_fSpeed;
							if(it !=m_VibrainList.end())
							{
								bNextAct = true;
							}
						}
					}
				}
				else if( (*it)->m_eState == E_VIBACT_STATE_VIB)
				{
					if((*it)->m_eDerection == E_DERECTION_UP)
					{
						(*it)->m_pPlane->MoveY( - ((*it)->m_fSpeed) );
						(*it)->m_fNowVibDistance += (*it)->m_fSpeed;

						(*it)->m_fSpeed += (*it)->m_fPlusSpeed;

						if((*it)->m_fNowVibDistance >= (*it)->m_fVibDistance)
						{
							(*it)->m_fSpeed = m_fSpeed;
							(*it)->m_fNowVibDistance = 0;
							(*it)->m_eDerection = E_DERECTION_DOWN;

							if((*it)->m_bTurn == false)
								(*it)->m_bTurn = true;
							else if((*it)->m_bTurn == true)
							{
								(*it)->m_fVibDistance = ((*it)->m_fVibDistance/100) * m_fVibDistanceScale;
								(*it)->m_fVibDistance -= m_fVibDistanceMinus;
								(*it)->m_bTurn = false;
							}

							if((*it)->m_fVibDistance <= 0)
							{
								(*it)->m_pPlane->SetPos((*it)->m_pPlane->GetPosVec2().m_fX,(*it)->m_fLastBasicLine);
								(*it)->m_eState = E_VIBACT_STATE_STOP;

							}
						}
					}
					else if((*it)->m_eDerection == E_DERECTION_DOWN)
					{
						(*it)->m_fSpeed = m_fSpeed;
						(*it)->m_pPlane->MoveY( + ((*it)->m_fSpeed) );
						(*it)->m_fNowVibDistance += (*it)->m_fSpeed;

						(*it)->m_fSpeed += (*it)->m_fPlusSpeed;

						if((*it)->m_fNowVibDistance >= (*it)->m_fVibDistance)
						{
							(*it)->m_fNowVibDistance = 0;
							(*it)->m_eDerection = E_DERECTION_UP;

							if((*it)->m_bTurn == false)
								(*it)->m_bTurn = true;
							else if((*it)->m_bTurn == true)
							{
								(*it)->m_fVibDistance = ((*it)->m_fVibDistance/100) * m_fVibDistanceScale;
								(*it)->m_fVibDistance -= m_fVibDistanceMinus;
								(*it)->m_bTurn = false;
							}

							if((*it)->m_fVibDistance <= 0)
							{
								(*it)->m_pPlane->SetPos((*it)->m_pPlane->GetPosVec2().m_fX,(*it)->m_fLastBasicLine);
								(*it)->m_eState = E_VIBACT_STATE_STOP;

							}
						}


					}
				}

			}
		}
	}
}
void CEMVibrater::Exit()
{
	list<stEMVibrain*>::iterator it;
	for(it = m_VibrainList.begin(); it !=m_VibrainList.end();)
	{
		//m_pThisScene->DeletePlane((*it)->m_pPlane);
		//(*it)->m_pPlane->Destroy();
		delete (*it);
		it = m_VibrainList.erase(it);
		//it = m_VibrainList.erase(it);
	}
}

void CEMVibrater::Input(CEMPlane* pPlane)
{
	stEMVibrain* stTempVibrain = new stEMVibrain();

	stTempVibrain->m_pPlane = pPlane;
	stTempVibrain->m_fSpeed = m_fSpeed;
	stTempVibrain->m_fPlusSpeed = m_fPlusSpeed;
	stTempVibrain->m_fBasicLine = m_fBasicLine;
	stTempVibrain->m_fLastBasicLine = m_fLastBasicLine;
	stTempVibrain->m_eState = E_VIBACT_STATE_NONE;
	stTempVibrain->m_fNowVibDistance = 0;
	stTempVibrain->m_fVibDistance = m_fVibDistance;
	stTempVibrain->m_eDerection = E_DERECTION_UP;
	stTempVibrain->m_bTurn = false;
	m_VibrainList.push_back(stTempVibrain);
}

void CEMVibrater::Input(CEMPlane* pPlane, float fSpeed,float fPlusSpeed,float fBasicLine, float fLastBasicLine,float fVibDistance, E_VIBACT_STATE eState)
{
	stEMVibrain* stTempVibrain = new stEMVibrain();

	stTempVibrain->m_pPlane = pPlane;
	stTempVibrain->m_fSpeed = fSpeed;
	stTempVibrain->m_fPlusSpeed = fPlusSpeed;
	stTempVibrain->m_fBasicLine = fBasicLine;
	stTempVibrain->m_fLastBasicLine = fLastBasicLine;
	stTempVibrain->m_eState = eState;
	stTempVibrain->m_fNowVibDistance = 0;
	stTempVibrain->m_fVibDistance = fVibDistance;
	stTempVibrain->m_eDerection = E_DERECTION_UP;
	stTempVibrain->m_bTurn = false;
	m_VibrainList.push_back(stTempVibrain);
}
void CEMVibrater::Start()
{
	m_bStart = true;
	list<stEMVibrain*>::iterator it = m_VibrainList.begin();
	(*it)->m_eState = E_VIBACT_STATE_ACT;
}


bool CEMVibrater::IsVibrating()
{
	list<stEMVibrain*>::iterator it = m_VibrainList.begin();

	for(it; it != m_VibrainList.end(); it++)
	{
		if((*it)->m_eState == E_VIBACT_STATE_ACT)
			return true;
	}
	if(it == m_VibrainList.end())
	{
		return false;
	}

}
bool CEMVibrater::IsEnd()
{
	list<stEMVibrain*>::iterator it = m_VibrainList.begin();

	for(it; it != m_VibrainList.end(); it++)
	{
		if((*it)->m_eState == E_VIBACT_STATE_ACT || (*it)->m_eState == E_VIBACT_STATE_VIB)
			return true;
	}
	if(it == m_VibrainList.end())
	{
		return false;
	}

}


void CEMVibrater::Skip()
{
	m_bSkip = true;
}