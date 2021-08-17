#include "stdafx.h"
#include "main.h"
#include <crtdbg.h>
#define CRTDBG_MAP_ALLOC
#ifdef _DEBUG
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif


USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( 167466 ); 
#endif
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView& eglView = CCEGLView::sharedOpenGLView();
    eglView.setViewName("Hello World");


    eglView.setFrameSize(480 * 0.75f, 800 * 0.75f);
    //// set the design resolution screen size, if you want to use Design Resoulution scaled to current screen, please uncomment next line.
    eglView.setDesignResolutionSize(480, 800);


	
    //eglView.setFrameSize(720 * 0.5f, 1280 * 0.5f);
    // set the design resolution screen size, if you want to use Design Resoulution scaled to current screen, please uncomment next line.
   // eglView.setDesignResolutionSize(720, 1280);


    return CCApplication::sharedApplication().run();
}
