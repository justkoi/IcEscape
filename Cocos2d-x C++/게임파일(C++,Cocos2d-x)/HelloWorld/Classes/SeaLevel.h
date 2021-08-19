#include "stdafx.h"

USING_NS_CC;

class CSeaLevel
{
public:
	
	CCSprite* m_pSeaLevel;
	CCPoint	 m_stPos;
	
	float m_fSeaLevel_Target; //!< ��ǥ ����
	float m_fSeaLevel;
	float m_fSeaLevelMax;
	
	float m_fSpeed; 
public:

	void Init(CCLayer* pThisScene);
	void Update(float dt);
	void Exit();

	void Check();
	void SetSeaLevelMax(float fSeaLevelMax);
	bool Warning(); //!< ���ǥ�� �Ҷ��� �Ǿ��°�

};
