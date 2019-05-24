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
#define DX_DESIGNE_WINDOW_WIDTH 1280    // 设计尺寸-宽
#define DX_DESIGNE_WINDOW_HIGHT 720     // 设计尺寸-高 




// 中文编码
#define DX_ZN_CODE "gb2312" 
#define DX_UFF8_CODE "utf-8"


// 日志输出
#define DX_LV_INVALID		0
#define DX_LV_INFO				1
#define DX_LV_WARNNING	2
#define DX_LV_ERROR			3

#define DX_LOG(format, ...)				cocos2d::log(format, ##__VA_ARGS__)
#define DX_LOG_ERROR(format,...)	cocos2d::log(format, ##__VA_ARGS__)
#define DX_LOG_INFO(format,...)		cocos2d::log(format, ##__VA_ARGS__)
#define DX_LOG_WARNNING(...)		__CCLOGWITHFUNCTION(__VA_ARGS__)

#define DX_PRINT 	DX_LOG_INFO

//#define DX_PRINT_LEVEL(_lv,format,...) do \
//{\
//	if (_lv == DX_LV_INFO)\
//	{\
//		DX_LOG("%s:", "DX_LV_INFO",);\
//		DX_LOG(format, ...); \
//	}\
//	else if (_lv == DX_LV_WARNNING)\
//	{\
//		DX_LOG("%s:", "DX_LV_WARNNING");\
//		DX_LOG(format, ...); \
//	}\
//	else if (_lv == DX_LV_ERROR)\
//	{
//		DX_LOG("%s:", "DX_LV_ERROR");\
//		DX_LOG(format, ...); \
//	}\
//} while (0);


template<typename T>
bool isInRange(const T v, const T _min, const T _max)
{
	T beg = min(_min, _max);
	T end = max(_min, _max);
	return v >= beg && v <= end;
}


// 用于cocos相关类的init函数，经常忘记在while退出前return true导致程序错误
#define DX_SAFE_RETURN_BEGAN	do{
#define DX_SAFE_RETURN_END	return true;}while(0);


// 经常在CC_BREAK_IF中只写变量，但是不写 == 或 != 造成失误
#define DX_BREAK_IF_TRUE(cond) CC_BREAK_IF((cond) == true)
#define DX_BREAK_IF_FALSE(cond) CC_BREAK_IF((cond)  == false)

#define DX_BREAK_IF_ZERO(cond) CC_BREAK_IF((cond)  == 0)
#define DX_BREAK_IF_NOT_ZERO(cond) CC_BREAK_IF((cond)  != 0)

#define DX_BREAK_IF_NULLPTR(cond) CC_BREAK_IF((cond)  == nullptr)
#define DX_BREAK_IF_NOT_NULLPTR(cond) CC_BREAK_IF((cond)  != nullptr)



// 字体
#define DX_FONT_ARIAL  "Arial"
#define DX_FONT_BLACK  "黑体"
#define FONT_ARIAL_BOLD  "黑体"


// pi
#ifndef PI
#define PI 3.1415926535897932385f
#endif

#ifndef DEG_RAD
#define DEG_RAD (PI / 180)
#endif

#ifndef RAD_DEG
#define RAD_DEG (180 / PI)
#endif
