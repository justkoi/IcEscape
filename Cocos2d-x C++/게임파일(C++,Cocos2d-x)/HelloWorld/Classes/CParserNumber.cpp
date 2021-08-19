
#include "stdafx.h" 

void CParserNumber::Init(char* strFIlePath)
{
	m_pFileData = NULL;
	m_bufferSize = 0;
	m_nIndex = 0;
	m_nNumber = 0;
	m_strFIlePath = strFIlePath;

	m_pFileData = m_FileUitil.getFileData(strFIlePath,"r",&m_bufferSize);
}
void CParserNumber::Parse()
{
	
	int nCount = 0;
	int nXN = 1; //!< Á¦°öÈ½¼ö
	int nXNT = 0; //!< ¸ñÇ¥ Ä«¿îÅÍ µµ´Þ Á¦°öÈ¸¼ö
	m_nNumberList.clear();
	m_nNumber = 0;
	while(m_pFileData[m_nIndex] != '\\' && m_pFileData[m_nIndex] != '\n') //!< 
	{
		m_nNumberList.push_back(m_pFileData[m_nIndex] - '0');
		m_nIndex++;
		nCount++;
	}
	m_nIndex++;

	for(int i=0; i<nCount; i++)
	{
		nXN  = 1;
		nXNT = 1;
		while(nXNT < (nCount - i))
		{
			nXN *= 10;
			nXNT++;
		}

		m_nNumber += m_nNumberList[i] * nXN;
	}
}

int CParserNumber::getNumber()
{
	return m_nNumber;
}
