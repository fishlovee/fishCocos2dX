#pragma once

#include "dxutils.h"
#include "testcode/testdefs.h"
#include <cocos2d.h>

USING_NS_CC;

// 2019-05-21 浏览器cocos封装在了application中，各个平台不一样，也不能直接在这里调用，不是重点，挂起。可以参考以下链接：
// http://www.voidcn.com/article/p-gwjhypwi-hn.html 

class OpenUrlByDefaultBrowser:public DxLayer
{
public:
	void runCase();
	bool init();
	CREATE_FUNC(OpenUrlByDefaultBrowser);

	CREATE_TEST_FUNC(OpenUrlByDefaultBrowser);
private:

};
