#pragma once

#include <cocos2d.h>
USING_NS_CC;

// DX:东兴

#define DX_APP_WINTITLE "东兴电子"

// 平台
#define DX_PLATFORM_IS_IOS					(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define DX_PLATFORM_IS_WIN32				(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define DX_PLATFORM_IS_WINRT				(CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define DX_PLATFORM_IS_MAC				(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#define DX_PLATFORM_IS_ANDROID		(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define DX_PLATFORM_IS_WINDOWS		(DX_PLATFORM_IS_WIN32 || DX_PLATFORM_IS_WINRT)

// 调试
#define DX_DEBUG 1

// windows下窗口重定向
#if DX_DEBUG
    #if DX_PLATFORM_IS_WINDOWS
        #define DX_REDIRECT_CONSOLE	1
    #else
         #define DX_REDIRECT_CONSOLE	0
    #endif
#else
    #define DX_REDIRECT_CONSOLE	0
#endif

// 窗体尺寸
#define DX_DESIGNE_WINDOW_WIDTH 960    // 设计尺寸-宽
#define DX_DESIGNE_WINDOW_HIGHT 720     // 设计尺寸-高 




// 中文编码
#define DX_ZN_CODE "gb2312" 
#define DX_UFF8_CODE "utf-8"


// 日志输出
#define DX_LV_INFO				1
#define DX_LV_WARNNING	2
#define DX_LV_ERROR			3

#define DX_LOG(format, ...)				cocos2d::log(format, ##__VA_ARGS__)
#define DX_LOG_ERROR(format,...)	cocos2d::log(format, ##__VA_ARGS__)
#define DX_LOG_INFO(format,...)		cocos2d::log(format, ##__VA_ARGS__)
#define DX_LOG_WARNNING(...)		__CCLOGWITHFUNCTION(__VA_ARGS__)

#define DX_PRINT 	DX_LOG_INFO


template<typename T>
bool isInRange(const T v, const T _min, const T _max)
{
	T beg = min(_min, _max);
	T end = max(_min, _max);
	return v >= beg && v <= end;
}


