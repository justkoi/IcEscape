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
	unsigned char* m_pFileData; //!< ���� Data
	char* m_strFIlePath;//!< ���� ���
	int m_nNumber; //!< ��� ����
	int m_nIndex;
	vector<int> m_nNumberList; //!< �Ľ����� ���ں���
	

public:
	 void Init(char* strFIlePath);
	 void Parse();

public:
	 int getNumber();
};