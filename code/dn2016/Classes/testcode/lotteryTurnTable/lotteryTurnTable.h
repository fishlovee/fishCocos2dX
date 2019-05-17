#pragma once

#include <cocos2d.h>
#include "dxutils/EventManager.h"
#include "testcode/testdefs.h"


USING_NS_CC;

class LotteryTurnTable:public Layer
{
public:
	LotteryTurnTable();
	~LotteryTurnTable();
	void runCase();
	bool init(CCSize size);
	static LotteryTurnTable * create();
	CREATE_TEST_FUNC(LotteryTurnTable);
private:

};

