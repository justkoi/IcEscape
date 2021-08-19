#include "stdafx.h"

USING_NS_CC;

typedef enum
{
	E_BOMB_OPTION_NO,
	E_BOMB_OPTION_ONE, //!< °Å¿ïº¹»ç
	E_BOMB_OPTION_TWO, //!< ¼¼½Öº¹»ç
}E_BOMB_OPTION;

class CIceChunk
{
public:
	CCPoint m_stPos;
	CCPoint m_stTargetPos;
	CCSprite* m_pPlane;

	CCPoint m_stMoveSpeed;

	//float m_fSpitTimer; //!<  Æ¢±â´Â ½Ã°£
	//float m_fSpitDistance; //!< Æ¢±â´Â YÃà ÀÌµ¿·® ´©Àû

	bool m_bHited;
	float m_fAlphaTimer;

	E_BOMB_OPTION m_eBombOption;
	float m_fBombTimer;
	float m_fBombTime; //!< Æø¹ß½Ã°£
	int m_nTickNumber;//!< Æø¹ß Æ¢±â´Â È½¼ö ÇöÀç
public:
	void Init(CCLayer* pThisScene, CCPoint stPos, E_BOMB_OPTION eBombOption, int nTickNumber);
	void Update(float dt);
	void Exit();

	bool Hited();
	bool Finished();
	bool ReadyToBomb(); //!< Æø¹ß·¹µð¾Ë¸²
};
