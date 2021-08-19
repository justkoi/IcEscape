#pragma once

extern int g_nScore;

extern SAMPLE_HANDLE SoundFp;
extern SAMPLE_HANDLE Sound[D_SOUND_MAX];
extern bool	bStopSound[D_SOUND_MAX];
extern list<stStageInfo*> g_StageInfo;
extern int g_nSelectStage;
extern bool* g_bStageLock;



extern int* g_nHighScore;//최고점수 Save
extern int* g_nScoreLevel;//판정레벨 0, 1, 2, 3 Save


extern int** g_nJudgment;//각각의 판정점 ReadOnly
extern bool	g_bFullScreen;
extern bool g_SoundOnOff;