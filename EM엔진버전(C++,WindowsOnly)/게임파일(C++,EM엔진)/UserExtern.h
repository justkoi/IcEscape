#pragma once

extern int g_nScore;

extern SAMPLE_HANDLE SoundFp;
extern SAMPLE_HANDLE Sound[D_SOUND_MAX];
extern bool	bStopSound[D_SOUND_MAX];
extern list<stStageInfo*> g_StageInfo;
extern int g_nSelectStage;
extern bool* g_bStageLock;



extern int* g_nHighScore;//�ְ����� Save
extern int* g_nScoreLevel;//�������� 0, 1, 2, 3 Save


extern int** g_nJudgment;//������ ������ ReadOnly
extern bool	g_bFullScreen;
extern bool g_SoundOnOff;