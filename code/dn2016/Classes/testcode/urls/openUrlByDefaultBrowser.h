#pragma once

#include "dxutils.h"
#include "testcode/testdefs.h"
#include <cocos2d.h>

USING_NS_CC;

// 2019-05-21 �����cocos��װ����application�У�����ƽ̨��һ����Ҳ����ֱ����������ã������ص㣬���𡣿��Բο��������ӣ�
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
