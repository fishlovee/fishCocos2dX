#pragma once

#include <cocos2d.h>
#include <vector>
#include "base/CCEventListenerTouch.h"

USING_NS_CC;

typedef std::function<bool(Touch*, Event*)> ccTouchBeganCallback;
typedef std::function<void(Touch*, Event*)> ccTouchCallback;

enum EventTouchListenerType
{
	EN_WithSceneGraphPriority = 0,
	EN_WithFixedPriority,
};

class DxEventUtils
{
public:
	static DxEventUtils getInstance();

	bool DxEventUtils::RegisterTouchEventOneByOne(
		int priority,
		ccTouchBeganCallback beginCall,
		ccTouchCallback moveCall,
		ccTouchCallback endCall,
		ccTouchCallback cancelCall);

	bool RegisterTouchEventOneByOne( Node *parent,  
		                                                                 ccTouchBeganCallback beginCall,
		                                                                ccTouchCallback moveCall,
		                                                                ccTouchCallback endCall,
		                                                                ccTouchCallback cancelCall);

	void AddNodeToListener(EventListenerTouchOneByOne &listener, std::vector<Node *> nodes);
protected:
private:
	DxEventUtils() {};
	static DxEventUtils _instance;	
};