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
	1. 물리 안붙은 Plane
		- 물리가 붙이 않았으므로 충돌 계산을 사용자가 직접 해줘야합니다
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

	int m_nTtLevel; // 튜토리얼 레벨
	int m_nMaxSnow;
	CEMDolphin* m_Dolphine;

	CEMSled* m_Sled;

	CEMText*	m_pText;	//!< 글자출력
	CEMText*	m_pTextNowBlock;	//!< 현재 클릭된 블록 출력
	CEMText*	m_pTextMouseList;	//!< MouseList블록 출력
	CEMText*	m_pTextErosionSpeed;	//!< 침식속도배율
	CEMText*	m_pTextCreateTime;	//!< 생성시간
	CEMText*	m_pTextErosionPlusSpeed;	//!< 침식가속도
	CEMText*	m_pTextFreeDrag;	//!< 침식가속도

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
	CEMNumber*	m_pNumberEndScore;	//!< 최종 점수 출력
	float		m_fGameEndBlind;
	
	CEMPlane*	m_pInterfaceBox;
	CEMNumber*	m_pNumberTimeLimit;	//!< 제한시간 출력
	CEMNumber*	m_pNumberStage;	//!< 스테이지 출력
	CEMNumber*	m_pNumberScore;	//!< 점수 출력

	list<CEMBlock*> m_BlockList;
	list<CEMBlock*>	m_MouseList;

	int	m_nFirstCreateBlockNumber;
	float	m_fFirstCreateBlockTimer;
	float	m_fFirstCreateBlockTime;

	bool m_IsMouseDown;//!< 현재 마우스를 누르는 중인지 확인
	int	 m_nTurnStep; //!< 방향회전 단계 기본 0 , 1 , 2에서 회전가능
	bool m_bTurnAble; //!< 방향회전 가능 여부 true이면 가능 false이면 불가능
	E_BLOCKACT m_eBlockAct;//!< 블록의 활동방향
	E_BLOCKDRAG_DEFECTION m_eBlockDragDerection;//!< 블록 드래그 방향
	bool m_bBlockAct;//!< 블록활동중
	int m_nTurnSkipBlock;//!<3번째 + 추가된블록누적수

	bool m_bOptionOnOff;
		
	CEMMap*		m_Map;
	int			m_nCreateBlockNumber;

	stEMVec3	m_stCamPos;	//!< 카메라 위치 저장 벡터

	float		m_fGravityTimer;
	
	float		m_fTimeLimit;
	int			m_nStage;

	float		m_fErosionSpeed; //!< 갈수록 빨라지는 침식속도
	int			m_nErosionPlusSpeed;//!< 침식가속도

	float		m_fCreateTimer;//!< 블록 내려오는 타이머 
	float		m_fCraeteTime;//!< 만드는 시간
	

	bool		m_bFreeMove;//!< 프리드래그 여부

	float		m_fComboTimer; //!< 콤보 타이머
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


	virtual void Enter				(CSceneWork* pSceneWork);										//!< 진입(로딩)
	virtual void Update				(CSceneWork*, float dt);										//!< Update
	virtual void Render				(CSceneWork*);													//!< Render
	virtual void Exit				(CSceneWork* pSceneWork);										//!< 탈출(메모리 해제등)
	virtual void MouseDownEvent		(stMouseInfo stPos, enumMouseButton eButton);					//!< 마우스 다운 이벤트
	virtual void MouseUpEvent		(stMouseInfo stPos, enumMouseButton eButton);					//!< 마우스 업 이벤트
	virtual void MouseMoveEvent		(stMouseInfo stPos);											//!< 마우스 이동 이벤트
	virtual HRESULT WindowMessage	(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);			//!< 윈도우 이벤트

	//!=================================================================================================
	//! 물리 충돌 이벤트들 입니다.
	virtual void BeginContact		(b2Contact* contact); 											//!< 충돌시작  되면 자동 호출된다
	virtual void EndContact			(b2Contact* contact); 											//!< 충돌이 끝나고 떨어질때 자동 호출된다
	virtual void PreSolve			(b2Contact* contact, const b2Manifold* oldManifold);			//!< 물리량계산이 발생했을때(충격이 발생했을때처리^^(
	virtual void PostSolve			(const b2Contact* contact, const b2ContactImpulse* impulse);	//!< 물리량계산이 끝났을때


};