#pragma once

#include "stdafx.h"
//=====================================================

/**
	@file    : < EMEffectManager >
	@author  : < 백노연 >
	@version : < 0.1 >
	@brief   : < 이펙트를 STL LIST에 추가하여 보여주는 클래스 입니다. >
 */


//=====================================================

class CEMEffectManager
{
public:
	CRootScene* m_pThisScene;			//!< 출력 대상 신
	list<CEMAnimation*> m_pEffectList;	//!< 모든 출력중인 이펙트 보관 STL LIST

public:

	CEMEffectManager()
	{
		
	};
	~CEMEffectManager()
	{

	};
	//=====================================================
	/**
		@brief     : 출력할 이펙트 등록

		@param : 이펙트 번호
		@param : 출력 X좌표
		@param : 출력 Y좌표
		@param : 
		@param : 

		@return : 없음.
	*/
	//=====================================================
	void Insert(int nIndex, float fX, float fY, float fSizeW = 1.0f, float fSizeH = 1.0f);	
	//=====================================================
	/**
		@brief     : 초기화 (출력 대상 씬 보관)

		@param : 출력 대상 씬
		@param : 
		@param : 
		@param : 
		@param : 

		@return : 없음.
	*/
	//=====================================================
	void Init(CRootScene* pThisScene);
	//=====================================================
	/**
		@brief     : 업데이트

		@param : 실시간으로 이펙트 출력이 완료된 이펙트의 메모리 해제
		@param : 
		@param : 
		@param : 
		@param : 

		@return : 없음.
	*/
	//=====================================================
	void Update(float dt);
	//=====================================================
	/**
		@brief     : 종료 ( 모든 메모리 해제)

		@param : 
		@param : 
		@param : 
		@param : 
		@param : 

		@return : 없음.
	*/
	//=====================================================
	void Exit();

	

};