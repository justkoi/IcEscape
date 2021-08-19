#include "stdafx.h"

//#define isHangul(str0, str1) ( (str0 >= 0xB0) && (str0 <= 0xC8) && (str1 >= 0xA1) && (str1 <= 0xFE) )

void CEMTextDisplay::Init(CRootScene* pThisScene, stdEMString stdName, float fX, float fY, int nLineWidth, int nLineHeight, stEMVec2 stSize, CEMColor Color, stdEMString stdFont, bool Ortho2D)
{
	m_Color = Color;
	m_stdFont = stdFont;
	m_stSize = stSize;

	m_stPos.m_fX = fX;
	m_stPos.m_fY = fY;
	m_nLineHeight = nLineHeight;
	m_pThisScene = pThisScene;

	m_nNowLine = 0;

	m_pTextList.clear();


	m_NowString = "";
	m_nNowChar = 0;

	m_fNowProgressTime = 0;
	m_nOffsetSpace = 0;

	m_nLineWidth_Basic = nLineWidth;
	m_nLineMaxChar = nLineWidth;
	m_nNowLineMaxChar = m_nLineMaxChar;

	m_nLineChanged = false;

	m_nHangulLevel = 0;

	m_bSkip = false;
	m_bPause = false;
	m_bFastView = false;
}

void CEMTextDisplay::SetText(stdEMString String)
{
	if(IsViewing() == false)
	{

		DestroyText();
		
		m_bSkip = false;
		m_bPause = false;
		m_bFastView = false;

		m_nNowChar = 0;
		m_nNowLine = 0;
		m_nOffsetSpace = 0;
		m_String.clear();
		m_String = String;
		m_nMaxChar = m_String.size();
		m_NowString = "";
		
		m_nLineMaxChar = m_nLineWidth_Basic;
		m_nNowLineMaxChar = m_nLineMaxChar;

		CEMText * m_pText = new CEMText(m_stdFont, "");
		m_pText->SetColor(CEMColor(m_Color.m_fR, m_Color.m_fG, m_Color.m_fB, m_Color.m_fA));
		m_pText->SetPos(m_stPos.m_fX, m_stPos.m_fY + (m_nNowLine * m_nLineHeight));
		m_pText->SetSize(m_stSize.m_fX,m_stSize.m_fY);

		m_pTextList.push_back(m_pText);
		m_pThisScene->Commit(0, m_nNowLine, m_stdName, m_pText);

		m_fNowProgressTime = 0;
	}
}

void CEMTextDisplay::SetProgressTime(float fProgressTime)
{
	m_fProgressTime = fProgressTime;
}

void CEMTextDisplay::Update(float dt)
{ 
	if(m_bPause == true)
		return;

	m_fNowProgressTime += dt;

	if(m_bSkip == false)
	{
		if(m_bFastView == true || m_fNowProgressTime >= m_fProgressTime)
		{
			if(m_fNowProgressTime >= m_fProgressTime)
				m_fNowProgressTime -= m_fProgressTime;

			if(m_nNowChar < m_nMaxChar)
			{
				if(m_nLineChanged == true)
				{
					m_nLineChanged = false;
					m_NowString.clear();
				}

				m_NowString.push_back(m_String[m_nNowChar]);
				m_nNowChar++;
				if(m_NowString[m_NowString.size() - 1] == '/')
				{
					NextLine();
				}
				else
				{

					if(m_nHangulLevel == 1 && m_NowString[m_NowString.size() - 1] & 0x80 )
					{
						m_nHangulLevel = 0;
					}
					else if(m_nHangulLevel == 0 && m_NowString[m_NowString.size() - 1] & 0x80 )
					{
						m_nHangulLevel = 1;
					}

					if(m_nNowChar >= m_nNowLineMaxChar - 1)
					{
						if( m_NowString[m_NowString.size() - 1] & 0x80 && m_nHangulLevel == 0)
						{
							//m_nOffsetSpace++;
							m_nNowChar -= 2;
						}
						else if( m_NowString[m_NowString.size() - 1] & 0x80&& m_nHangulLevel == 1)
						{
							//m_nOffsetSpace++;
							m_nNowChar -= 1;
						}
						else if( m_NowString[m_NowString.size() - 1] & 0x80 )
						{
							//m_nOffsetSpace++;
							m_nNowChar -= 1;
						}
						else
						{
							m_nNowChar -= 1;
						}
						NextLine();
					}
				}
				
			}
			if(!(m_nNowChar < m_nMaxChar))
			{
				if(m_bFastView == true)
					m_bFastView = false;
			}
		

			if(m_NowString.size() >= 1 && (m_NowString.size() + m_nOffsetSpace)%2 == 1)
			{
				if( m_NowString[m_NowString.size() - 1] & 0x80 )
				{
					m_nHangulLevel = 1;

					stdEMString strTemp;
					strTemp = m_NowString;
					strTemp.pop_back();

					list<CEMText*>::iterator it;
					it = m_pTextList.begin();
					for(int i = 0; i < m_nNowLine; i++, it++)
					{
					
					}
					(*it)->SetOutPutString(strTemp);
					m_ViewString = strTemp;
				}
				else
				{
					m_nHangulLevel = 0;
					m_nOffsetSpace++;
					list<CEMText*>::iterator it;
					it = m_pTextList.begin();
					for(int i = 0; i < m_nNowLine; i++, it++)
					{
					
					}
					(*it)->SetOutPutString(m_NowString);
					m_ViewString = m_NowString;
				}
			}
			else
			{
				if( (m_NowString[m_NowString.size() - 1] & 0x80) == false)
				{
					m_nOffsetSpace++;
				}
				list<CEMText*>::iterator it;
				it = m_pTextList.begin();
				for(int i = 0; i < m_nNowLine; i++, it++)
				{
				
				}
				(*it)->SetOutPutString(m_NowString);
				m_ViewString = m_NowString;
			}
	
		
			list<CEMText*>::iterator it;
			it = m_pTextList.begin();
			for(int i = 0; i < m_nNowLine; i++, it++)
			{
			
			}
			(*it)->SetOutPutString(m_ViewString);
		}
	
	}
	else if(m_bSkip == true)
	{
	
		while(m_nNowChar < m_nMaxChar)
		{
			if(m_nNowChar < m_nMaxChar )
			{
				if(m_nLineChanged == true)
				{
					m_nLineChanged = false;
					m_NowString.clear();
				}

				m_NowString.push_back(m_String[m_nNowChar]);
				m_nNowChar++;
				if(m_NowString[m_NowString.size() - 1] == '/')
				{
					NextLine();
				}
				else
				{
					if(m_nHangulLevel == 1 && m_NowString[m_NowString.size() - 1] & 0x80 )
					{
						m_nHangulLevel = 0;
					}
					else if(m_nHangulLevel == 0 && m_NowString[m_NowString.size() - 1] & 0x80 )
					{
						m_nHangulLevel = 1;
					}

					if(m_nNowChar >= m_nNowLineMaxChar - 1)
					{
						if( m_NowString[m_NowString.size() - 1] & 0x80 && m_nHangulLevel == 0)
						{
							//m_nOffsetSpace++;
							m_nNowChar -= 2;
						}
						else if( m_NowString[m_NowString.size() - 1] & 0x80&& m_nHangulLevel == 1)
						{
							//m_nOffsetSpace++;
							m_nNowChar -= 1;
						}
						else if( m_NowString[m_NowString.size() - 1] & 0x80 )
						{
							//m_nOffsetSpace++;
							m_nNowChar -= 1;
						}
						NextLine();
					}
				}
				
			}
		

			if(m_NowString.size() >= 1 && (m_NowString.size() + m_nOffsetSpace)%2 == 1)
			{
				if( m_NowString[m_NowString.size() - 1] & 0x80 )
				{
					m_nHangulLevel = 1;

					stdEMString strTemp;
					strTemp = m_NowString;
					strTemp.pop_back();

					list<CEMText*>::iterator it;
					it = m_pTextList.begin();
					for(int i = 0; i < m_nNowLine; i++, it++)
					{
					
					}
					(*it)->SetOutPutString(strTemp);
					m_ViewString = strTemp;
				}
				else
				{
					m_nHangulLevel = 0;
					m_nOffsetSpace++;
					list<CEMText*>::iterator it;
					it = m_pTextList.begin();
					for(int i = 0; i < m_nNowLine; i++, it++)
					{
					
					}
					(*it)->SetOutPutString(m_NowString);
					m_ViewString = m_NowString;
				}
			}
			else
			{
				if( (m_NowString[m_NowString.size() - 1] & 0x80) == false)
				{
					m_nOffsetSpace++;
				}
				list<CEMText*>::iterator it;
				it = m_pTextList.begin();
				for(int i = 0; i < m_nNowLine; i++, it++)
				{
				
				}
				(*it)->SetOutPutString(m_NowString);
				m_ViewString = m_NowString;
			}
	
		
			list<CEMText*>::iterator it;
			it = m_pTextList.begin();
			for(int i = 0; i < m_nNowLine; i++, it++)
			{
			
			}
			(*it)->SetOutPutString(m_ViewString);
		
		}
		if(!(m_nNowChar < m_nMaxChar))
		{
			m_bSkip = false;
		}
	
	}

}

void CEMTextDisplay::Exit()
{
	DestroyText();
}


bool CEMTextDisplay::IsViewing()
{
	if(m_nNowChar < m_nMaxChar )
		return true;

	return false;
}


void CEMTextDisplay::DestroyText()
{
	//if(IsViewing() == false)
	//{
		list<CEMText*>::iterator itr;
		for(itr = m_pTextList.begin(); itr != m_pTextList.end();)
		{
			m_pThisScene->DeletePlane(*itr);
			(*itr)->Destroy();
			itr = m_pTextList.erase(itr);
		}
		m_pTextList.clear();
	//}
}

void CEMTextDisplay::Skip()
{
	m_bSkip = true;
}


void CEMTextDisplay::SetFastView(bool bFastView)
{
	m_bFastView = bFastView;
}
void CEMTextDisplay::SetPause(bool bPause)
{
	m_bPause = bPause;
}

bool CEMTextDisplay::GetFastView()
{
	return m_bFastView;
}
bool CEMTextDisplay::GetPause()
{
	return m_bPause;
}


void CEMTextDisplay::NextLine()
{
	m_nOffsetSpace = 1;
	m_nNowLine++;
	m_nNowLineMaxChar += m_nLineMaxChar;
	m_NowString = " ";


	list<CEMText*>::iterator it;
	it = m_pTextList.begin();
	CEMText * m_pText = new CEMText(m_stdFont, " ");
	m_pText->SetColor(CEMColor(m_Color.m_fR, m_Color.m_fG, m_Color.m_fB, m_Color.m_fA));
	m_pText->SetPos(m_stPos.m_fX, m_stPos.m_fY + (m_nNowLine * m_nLineHeight));
	m_pText->SetSize(m_stSize.m_fX,m_stSize.m_fY);
	m_pTextList.push_back(m_pText);
	m_pThisScene->Commit(0, m_nNowLine, m_stdName, m_pText);
	m_nLineChanged = true;
}