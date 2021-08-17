#pragma once
extern int g_nScore;
extern int g_nSelectStage;
extern stStageInfo g_StageInfo[D_STAGE_MAX];
extern bool	g_bStageLock[D_STAGE_MAX];
extern int g_nScoreLevel[D_STAGE_MAX];//판정레벨 0, 1, 2, 3 Save
extern int g_nJudgment[D_STAGE_MAX][3];//각각의 판정점 ReadOnly

extern bool g_bBGM_Sound;
extern bool g_bEFFECT_Sound;

extern bool g_bPause;
extern CCSize g_PhoneSize;