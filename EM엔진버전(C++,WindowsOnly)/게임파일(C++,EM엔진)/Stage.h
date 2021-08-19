#pragma once

#include "stdafx.h"

typedef enum
{
	E_BLOCKDRAG_DEFECTION_LEFT,
	E_BLOCKDRAG_DEFECTION_RIGHT,
	E_BLOCKDRAG_DEFECTION_UP,
	E_BLOCKDRAG_DEFECTION_DOWN,
}E_BLOCKDRAG_DEFECTION;
typedef enum
{
	E_BLOCKACT_NONE,
	E_BLOCKACT_MOVE,
	E_BLOCKACT_DRAG,
	E_BLOCKACT_NOT
}E_BLOCKACT;
typedef enum
{
	E_GAMERESULT_NONE,
	E_GAMERESULT_VICTORY,
	E_GAMERESULT_DEFEAT,

}E_GAMERESULT;
typedef enum
{
	E_GAMESTEP_READY,
	E_GAMESTEP_PLAY,
	E_GAMESTEP_END,

}E_GAMESTEP;


/*
	1. ���� �Ⱥ��� Plane
		- ������ ���� �ʾ����Ƿ� �浹 ����� ����ڰ� ���� ������մϴ�
*/
class CStage : public CRootScene
{
public:
	
	CEMPlane*	m_pBlack[2];
	CEMCamShakeManager* m_CamShakeMng;
	CEMEffectManager* m_EffectMng;
	CEMSnowMng*	m_SnowMng;
	//CEMTextDisplay* m_TextDisplay;
	bool m_bSetText;
	
	CEMStyleButton m_ButtonGameStart;
	CEMStyleButton m_ButtonExit;
	CEMPlane*	m_pButtonGameStartImg[3];
	CEMPlane*	m_pButtonExitImg[3];
	
	
	CEMStyleButton m_ButtonStop;
	CEMPlane*	m_pButtonStopImg[3];


public:
	SOUND_HANDLE m_SoundIceFp;

	SOUND_HANDLE m_SoundIce[D_SOUND_ICE_CHANNEL];

	SOUND_HANDLE m_SoundButtonFp;
	SOUND_HANDLE m_SoundButton;

	
	SOUND_HANDLE m_SoundEffectTtFp;
	SOUND_HANDLE m_SoundEffectTt;

	
	SOUND_HANDLE m_SoundPause1Fp;
	SOUND_HANDLE m_SoundPause2Fp;

	
	SOUND_HANDLE m_SoundWinFp;
	SOUND_HANDLE m_SoundLoseFp;
#ifdef _DEBUG
	TwBar*		m_pBar;
#endif

	int m_nTtLevel; // Ʃ�丮�� ����
	int m_nMaxSnow;
	CEMDolphin* m_Dolphine;

	CEMSled* m_Sled;

	CEMText*	m_pText;	//!< �������
	CEMText*	m_pTextNowBlock;	//!< ���� Ŭ���� ��� ���
	CEMText*	m_pTextMouseList;	//!< MouseList��� ���
	CEMText*	m_pTextErosionSpeed;	//!< ħ�ļӵ�����
	CEMText*	m_pTextCreateTime;	//!< �����ð�
	CEMText*	m_pTextErosionPlusSpeed;	//!< ħ�İ��ӵ�
	CEMText*	m_pTextFreeDrag;	//!< ħ�İ��ӵ�

	//CEMText*	m_pTtMsg;
	
	CEMPlane*	m_pPause;
	CEMPlane*	m_pBlind;
	float		m_fBlindTimer;

	CEMPlane*	m_pBackGround[5];
	CEMPlane*	m_pWhite;

	CEMPlane*	m_pTtImg[5];
	CEMPlane*	m_pStar[3];

	CEMPlane*	m_pGameOver;
	CEMPlane*	m_pGameClear;
	CEMNumber*	m_pNumberEndScore;	//!< ���� ���� ���
	float		m_fGameEndBlind;
	
	CEMPlane*	m_pInterfaceBox;
	CEMNumber*	m_pNumberTimeLimit;	//!< ���ѽð� ���
	CEMNumber*	m_pNumberStage;	//!< �������� ���
	CEMNumber*	m_pNumberScore;	//!< ���� ���

	list<CEMBlock*> m_BlockList;
	list<CEMBlock*>	m_MouseList;

	int	m_nFirstCreateBlockNumber;
	float	m_fFirstCreateBlockTimer;
	float	m_fFirstCreateBlockTime;

	bool m_IsMouseDown;//!< ���� ���콺�� ������ ������ Ȯ��
	int	 m_nTurnStep; //!< ����ȸ�� �ܰ� �⺻ 0 , 1 , 2���� ȸ������
	bool m_bTurnAble; //!< ����ȸ�� ���� ���� true�̸� ���� false�̸� �Ұ���
	E_BLOCKACT m_eBlockAct;//!< ����� Ȱ������
	E_BLOCKDRAG_DEFECTION m_eBlockDragDerection;//!< ��� �巡�� ����
	bool m_bBlockAct;//!< ���Ȱ����
	int m_nTurnSkipBlock;//!<3��° + �߰��Ⱥ�ϴ�����

	bool m_bOptionOnOff;
		
	CEMMap*		m_Map;
	int			m_nCreateBlockNumber;

	stEMVec3	m_stCamPos;	//!< ī�޶� ��ġ ���� ����

	float		m_fGravityTimer;
	
	float		m_fTimeLimit;
	int			m_nStage;

	float		m_fErosionSpeed; //!< ������ �������� ħ�ļӵ�
	int			m_nErosionPlusSpeed;//!< ħ�İ��ӵ�

	float		m_fCreateTimer;//!< ��� �������� Ÿ�̸� 
	float		m_fCraeteTime;//!< ����� �ð�
	

	bool		m_bFreeMove;//!< �����巡�� ����

	float		m_fComboTimer; //!< �޺� Ÿ�̸�
	int			m_nCombo;

	E_GAMERESULT	m_eGameResult;
	E_GAMESTEP		m_eGameStep;

	CEMStyleButton m_ButtonUpCreateTime;
	CEMPlane*	m_pButtonUpCreateTimeImg[3];


	CEMStyleButton m_ButtonDownCreateTime;
	CEMPlane*	m_pButtonDownCreateTimeImg[3];

	
	CEMStyleButton m_ButtonUpErosionSpeed;
	CEMPlane*	m_pButtonUpErosionSpeedImg[3];
	CEMStyleButton m_ButtonDownErosionSpeed;
	CEMPlane*	m_pButtonDownErosionSpeedImg[3];
	
	CEMStyleButton m_ButtonUpErosionPlusSpeed;
	CEMPlane*	m_pButtonUpErosionPlusSpeedImg[3];
	CEMStyleButton m_ButtonDownErosionPlusSpeed;
	CEMPlane*	m_pButtonDownErosionPlusSpeedImg[3];
	
	CEMStyleButton m_ButtonFreeMove;
	CEMPlane*	m_pButtonFreeMove[3];

public:
	float		m_fRot;		
	float		m_fSize;	

public:
	CStage(void)
	{	
		//m_pBackGround = NULL;
		m_pText = NULL;
		m_fRot = 0.0f;
		m_fSize = 3.0f;
		m_fGravityTimer = 0.0f;
		m_stCamPos = stEMVec3(0.0f, 3.0f,400.0f);
	};
	virtual ~CStage(void)
	{
		
	};
public:
	
	void SaveStage();

	CEMBlock*		CreateBlock();
	CEMBlock*		CreateBlock(int nX, int nY);
	CEMBlock*		CreateBlock(int nX, int nY , int nBlockNumber);
	CEMBlock*		CreateBlock(int nY);
	void			CreateLine(list<CEMBlock*>* BlockList, CEMCamShakeManager* CamShakeMng);

	void ReadMap(int nStage);
public:


	virtual void Enter				(CSceneWork* pSceneWork);										//!< ����(�ε�)
	virtual void Update				(CSceneWork*, float dt);										//!< Update
	virtual void Render				(CSceneWork*);													//!< Render
	virtual void Exit				(CSceneWork* pSceneWork);										//!< Ż��(�޸� ������)
	virtual void MouseDownEvent		(stMouseInfo stPos, enumMouseButton eButton);					//!< ���콺 �ٿ� �̺�Ʈ
	virtual void MouseUpEvent		(stMouseInfo stPos, enumMouseButton eButton);					//!< ���콺 �� �̺�Ʈ
	virtual void MouseMoveEvent		(stMouseInfo stPos);											//!< ���콺 �̵� �̺�Ʈ
	virtual HRESULT WindowMessage	(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);			//!< ������ �̺�Ʈ

	//!=================================================================================================
	//! ���� �浹 �̺�Ʈ�� �Դϴ�.
	virtual void BeginContact		(b2Contact* contact); 											//!< �浹����  �Ǹ� �ڵ� ȣ��ȴ�
	virtual void EndContact			(b2Contact* contact); 											//!< �浹�� ������ �������� �ڵ� ȣ��ȴ�
	virtual void PreSolve			(b2Contact* contact, const b2Manifold* oldManifold);			//!< ����������� �߻�������(����� �߻�������ó��^^(
	virtual void PostSolve			(const b2Contact* contact, const b2ContactImpulse* impulse);	//!< ����������� ��������


};