#pragma once


#include "stdafx.h" 
#include <vector>
using namespace std;

USING_NS_CC;


class CParserNumber
{
public:
	CCFileUtils m_FileUitil;
	unsigned long m_bufferSize;
	unsigned char* m_pFileData; //!< 저장 Data
	char* m_strFIlePath;//!< 파일 경로
	int m_nNumber; //!< 출력 숫자
	int m_nIndex;
	vector<int> m_nNumberList; //!< 파싱중인 숫자벡터
	

public:
	 void Init(char* strFIlePath);
	 void Parse();

public:
	 int getNumber();
};