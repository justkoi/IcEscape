#pragma once


#include "stdafx.h" 
using namespace std;

USING_NS_CC;

class CSled
{
private:
	CCLayer* m_pThisScene;			//!< ��� ��� ��
	float m_fMoveSpeed;//!< 
	CCPoint m_stPos;
public:
	CCSprite* m_pSled;//[E_BLOCKNUMBER_MAX];
	CCActionInterval* m_pSledAnt;//[E_BLOCKNUMBER_MAX];
	CCAnimation* m_pSledAni;


	void Init(CCLayer* pThisScene);
	void Update(float dt, CBlock * BlockList, list<CIceChunk*>* IceChunkList, CEffectManager* EffectManager,CocosDenshion::SimpleAudioEngine *Sae );
	void Exit();

public:
	bool Played();//!< �������� Ȯ��
	bool HitTest(CCPoint stPos1, CCPoint stPixel1, CCPoint stPos2, CCPoint stPixel2);
};