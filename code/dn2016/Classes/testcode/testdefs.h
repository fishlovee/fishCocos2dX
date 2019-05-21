#pragma once

#include "appdefs.h"

#define CREATE_TEST_FUNC(_testClass) \
	static void run(Node *_parent) \
	{ \
		auto t = _testClass::create(); \
		if (t)\
		{\
			t->runCase();\
			_parent->addChild(t);\
		}\
		else \
		{\
			CC_SAFE_DELETE(t);\
		}\
	}


//#define ADD_TEST_CASE(_classname,_describe) do \
//{\
//
//} while (0);

	
