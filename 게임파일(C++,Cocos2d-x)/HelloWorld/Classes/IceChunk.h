#include "stdafx.h"

USING_NS_CC;

typedef enum
{
	E_BOMB_OPTION_NO,
	E_BOMB_OPTION_ONE, //!< �ſﺹ��
	E_BOMB_OPTION_TWO, //!< ���ֺ���
}E_BOMB_OPTION;

class CIceChunk
{
public:
	CCPoint m_stPos;
	CCPoint m_stTargetPos;
	CCSprite* m_pPlane;

	CCPoint m_stMoveSpeed;

	//float m_fSpitTimer; //!<  Ƣ��� �ð�
	//float m_fSpitDistance; //!< Ƣ��� Y�� �̵��� ����

	bool m_bHited;
	float m_fAlphaTimer;

	E_BOMB_OPTION m_eBombOption;
	float m_fBombTimer;
	float m_fBombTime; //!< ���߽ð�
	int m_nTickNumber;//!< ���� Ƣ��� Ƚ�� ����
public:
	void Init(CCLayer* pThisScene, CCPoint stPos, E_BOMB_OPTION eBombOption, int nTickNumber);
	void Update(float dt);
	void Exit();

	bool Hited();
	bool Finished();
	bool ReadyToBomb(); //!< ���߷���˸�
};
