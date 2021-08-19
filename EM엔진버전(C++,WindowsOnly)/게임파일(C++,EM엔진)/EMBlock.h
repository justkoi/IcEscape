#pragma once

#include "stdafx.h"

typedef enum
{
	E_BLOCKNUMBER_POLARBEAR,
	E_BLOCKNUMBER_SEAL,
	E_BLOCKNUMBER_PENGUIN,
	E_BLOCKNUMBER_BREA,
	E_BLOCKNUMBER_MAX,

}E_BLOCKNUMBER;

typedef enum
{
	E_BLOCKSTATE_NONE,
	E_BLOCKSTATE_FALLING,
}E_BLOCKSTATE;

typedef enum
{
	E_BLOCKITEM_NONE,
	E_BLOCKITEM_SLED,
}E_BLOCKITEM;


class CEMSled;

class CEMBlock
{
	private:



	public:
	
		//CEMPlane*	m_pPlane;
	
		CEMAnimation* m_pBlock;

		CEMPlane*	m_pSelect;
		CEMPlane*	m_pErosoin;
		CEMPlane*	m_pErosoin_Border;
		CEMPlane*	m_pFreeze;
		CEMPlane*	m_pItem_Sled;

		float m_fEye;
		bool m_bEye;


		int m_nGT;
		int m_nGC;

		E_BLOCKNUMBER m_eBlockNumber;

		E_BLOCKITEM		m_eBlockItem;

		float			m_fStartY;
		float			m_fSpeed;
		float			m_fPlusSpeed;
		float			m_fNowDistance;
		float			m_fDistance;

		float			m_fErosionTime;
		float			m_fErosionMaxTime;
		float			m_fErosionOffsetY;

		bool			m_bFreezed;
		bool			m_bDraged;
		bool			m_bDolphinHited;

		stEMVec2	m_stPos;
		stVec2i		m_stIndex;
		E_BLOCKSTATE	m_eBlockState;
		//bool			m_bSelected;

		void Init(CRootScene* pThisScene, stVec2i stIndex,int nCreateBlockNumber);
		void Init(CRootScene* pThisScene, E_BLOCKNUMBER eBlockNumber, stVec2i stIndex,int nCreateBlockNumber);
		void Update(float dt, float fErosionSpeed, CEMSled* Sled);
		void Exit();

		bool IsErosoined();


};