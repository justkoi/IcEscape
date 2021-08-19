#include "stdafx.h"

#include <crtdbg.h>
//#define CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
	//#define new DEBUG_NEW
	//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

SAMPLE_HANDLE SoundFp;
SAMPLE_HANDLE Sound[D_SOUND_MAX];
bool	bStopSound[D_SOUND_MAX];
bool	g_bFullScreen = false;
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR,  int)
{
#ifdef _DEBUG
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks( );
#endif
	HICON hIcon;
	hIcon = LoadIcon(D_WORLD->GetWinCreateInfo()->GetHinstance(), MAKEINTRESOURCE( IDI_ICON1 ));
	
	D_WORLD->WorldInit("IceEscape",  D_SCREEN_SCALE_WIDTH(90) * 1.0, D_SCREEN_SCALE_HEIGHT(80) * 1.0, g_bFullScreen, hIcon);			//!< 월드를 설정합니다
	//D_WORLD->WorldInit("IceEscape",  1024, 768, g_bFullScreen);			//!< 월드를 설정합니다
	//D_WORLD->WorldInit("IcEscape",  600, 600, false);			//!< 월드를 설정합니다
	D_WORLD->SetBackColor(CEMColor(255, 255, 255));													//!< 배경색을 지정합니다.
	//D_WORLD->Commit(new CEMGrid());																	//!< 그리드 추가합니다.
	//D_WORLD->SetBoundingBoxShowFlag(true);															//!< 바운딩 박스 보여주게합니다
	//D_WORLD->SetFpsShowFlag(true);
 	D_WORLD->SetMouseCursor( "Data/Image/Cursor/Cursor_2.png",
 					 		  stEMVec2(12.0f, -12.0f),
 							 "Data/image/Cursor/Cursor_1.png",
 							  stEMVec2(12.0f, -12.0f)			//!< 그림 의 맨왼쪽위로 offset이 이동해야하므로 그림 사이즈(32) - 16만큼 해주면 됩니다
							 );	

	
	
	D_WORLD->SetMaxFrame(E_FRAMESKIP_MAX, 60.0f);				//! 키입력/물리/오브젝트 까지 전부 50프레임으로 고정합니다
	
	D_SCENE->Commit(new CLogo, "Logo");
	D_SCENE->Commit(new CMenu, "Menu");
	D_SCENE->Commit(new CStage, "Stage");
	D_SCENE->Commit(new CStageMenu, "StageMenu");
	D_SCENE->Commit(new CProducer, "Producer");	
	D_SCENE->Commit(new CHowToPlay, "HowToPlay");	
	D_SCENE->ChangeScene("Logo");

	for(int i=0; i<D_SOUND_MAX; i++)
	{
		bStopSound[i] = false;
	}
	
	//_crtBreakAlloc = 223;
	D_WORLD->RunLoop();
	_CrtDumpMemoryLeaks( );
	return 1;
}