#pragma once

#include <cocos2d.h>
#include "dxutils.h"
#include "testcode/testdefs.h"


USING_NS_CC;

class LotteryTurnTable:public DxLayer
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

