#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

void RedirectToConsole()
{
#if DX_REDIRECT_CONSOLE
	if (AllocConsole())
	{
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		SetConsoleTitle(_TEXT(DX_APP_WINTITLE));
		DX_PRINT(toUtf8String(DX_ZN_CODE, "±¿ÄñÏÈ·É£¬·É¹ýÌ«Ñô~").c_str());
	}
#endif
}

void CloseConsoles()
{
#if DX_REDIRECT_CONSOLE
	fclose(stdin);
	fclose(stdout);
	fclose(stderr);
#endif
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


	RedirectToConsole();
	
    AppDelegate app;
    bool ret = Application::getInstance()->run();
	CloseConsoles();
	return ret;
}
