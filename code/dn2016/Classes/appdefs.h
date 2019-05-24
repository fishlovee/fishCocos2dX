#pragma once

#include <cocos2d.h>
USING_NS_CC;

// DX:����

#define DX_APP_WINTITLE "���˵���"

// ƽ̨
#define DX_PLATFORM_IS_IOS					(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define DX_PLATFORM_IS_WIN32				(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define DX_PLATFORM_IS_WINRT				(CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define DX_PLATFORM_IS_MAC				(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#define DX_PLATFORM_IS_ANDROID		(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define DX_PLATFORM_IS_WINDOWS		(DX_PLATFORM_IS_WIN32 || DX_PLATFORM_IS_WINRT)

// ����
#define DX_DEBUG 1

// windows�´����ض���
#if DX_DEBUG
    #if DX_PLATFORM_IS_WINDOWS
        #define DX_REDIRECT_CONSOLE	1
    #else
         #define DX_REDIRECT_CONSOLE	0
    #endif
#else
    #define DX_REDIRECT_CONSOLE	0
#endif

// ����ߴ�
#define DX_DESIGNE_WINDOW_WIDTH 1280    // ��Ƴߴ�-��
#define DX_DESIGNE_WINDOW_HIGHT 720     // ��Ƴߴ�-�� 




// ���ı���
#define DX_ZN_CODE "gb2312" 
#define DX_UFF8_CODE "utf-8"


// ��־���
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


// ����cocos������init����������������while�˳�ǰreturn true���³������
#define DX_SAFE_RETURN_BEGAN	do{
#define DX_SAFE_RETURN_END	return true;}while(0);


// ������CC_BREAK_IF��ֻд���������ǲ�д == �� != ���ʧ��
#define DX_BREAK_IF_TRUE(cond) CC_BREAK_IF((cond) == true)
#define DX_BREAK_IF_FALSE(cond) CC_BREAK_IF((cond)  == false)

#define DX_BREAK_IF_ZERO(cond) CC_BREAK_IF((cond)  == 0)
#define DX_BREAK_IF_NOT_ZERO(cond) CC_BREAK_IF((cond)  != 0)

#define DX_BREAK_IF_NULLPTR(cond) CC_BREAK_IF((cond)  == nullptr)
#define DX_BREAK_IF_NOT_NULLPTR(cond) CC_BREAK_IF((cond)  != nullptr)



// ����
#define DX_FONT_ARIAL  "Arial"
#define DX_FONT_BLACK  "����"
#define FONT_ARIAL_BOLD  "����"


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
