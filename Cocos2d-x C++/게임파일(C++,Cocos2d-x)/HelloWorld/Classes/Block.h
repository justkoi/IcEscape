#pragma once

#include "stdafx.h"

USING_NS_CC;

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
	E_BLOCKITEM_ICE,
}E_BLOCKITEM;

typedef struct stVec2i
{
	 int m_nX;
	 int m_nY;

	 stVec2i()
	 {
		 m_nX = 0;
		 m_nY = 0;
	 };
	 stVec2i(int nX, int nY)
	 {
		 m_nX = nX;
		 m_nY = nY;
	 };
	 ~stVec2i()
	 {

	 };

}stVec2i;

class CBlock
{
	
public:
	
	//CEMPlane*	m_pPlane;
	CCSprite* m_pBlock;//[E_BLOCKNUMBER_MAX];
	CCActionInterval* m_pBlockAnt;//[E_BLOCKNUMBER_MAX];
	CCAnimation* m_pBlockAni;//[E_BLOCKNUMBER_MAX];
	
	CCSprite*	m_pBlock_Pause;
	CCSprite*	m_pBlock_Freeze;
	CCSprite*	m_pBlock_Angry;

	float m_fEyeContact;

	//[E_BLOCKNUMBER_MAX];
	CCSprite*	m_pSelect;
	//!< CCSprite*	m_pErosoin;
	//!< CCSprite*	m_pErosoin_Border;
	CCSprite*	m_pFreeze;
	//CCSprite*	m_pItem_Sled;
	CCSprite* m_pItem;


	float m_fEye;
	bool m_bEye;


	int m_nGT;
	int m_nGC;

	int m_nId;

	E_BLOCKNUMBER m_eBlockNumber;

	E_BLOCKITEM		m_eBlockItem;

	double			m_fStartY;
	double			m_fSpeed;
	double			m_fPlusSpeed;
	double			m_fNowDistance;
	double			m_fDistance;
	double			m_fNextDistance;

	float			m_fErosionTime;
	float			m_fErosionMaxTime;
	float			m_fErosionOffsetY;

	bool			m_bFreezed;
	bool			m_bDraged;
	bool			m_bDolphinHited;

	bool			m_bLive;
	CCLayer*		m_pThisScene;
	CCPoint		m_stPos;
	CCPoint		m_stOffsetPos;
	stVec2i		m_stIndex;
	E_BLOCKSTATE	m_eBlockState;
public:
	CBlock(){};
	~CBlock(){};

	void Init(CCLayer* pThisScene, int nId);
	void Create(stVec2i stIndex);
	void CreateIt(stVec2i stIndex, E_BLOCKNUMBER eBlockNumber);
	//void Init(CRootScene* pThisScene, E_BLOCKNUMBER eBlockNumber, stVec2i stIndex,int nCreateBlockNumber);
	void Update(float dt, float fErosionSpeed);
	void Exit();

	void Die();
	void UseItem();
	bool HitTest(float nX, float nY);
	bool IsErosoined();
	void ShowUpdate();

};