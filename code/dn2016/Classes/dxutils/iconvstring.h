#pragma once

#include "appdefs.h"
#include <string>

using namespace std;

#if DX_PLATFORM_IS_WIN32
       #include "../cocos2d/external/win32-specific/icon/include/iconv.h"
#else if DX_PLATFORM_IS_ANDROID
	   
#endif


string toUtf8String(const string fromcode, const string strSrc);
std::string GBKToUTF8(const char *strChar, const char* toCode, const char* formCode);

