#include "EventManager.h"

DxEventUtils DxEventUtils::_instance;


DxEventUtils DxEventUtils::getInstance()
{
	return _instance;
}

bool DxEventUtils::RegisterTouchEventOneByOne(
	Node *parent,
																					ccTouchBeganCallback beginCall, 
																					ccTouchCallback moveCall,
																					ccTouchCallback endCall,
																					ccTouchCallback cancelCall)
{
	CC_ASSERT(parent != nullptr);
	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->setSwallowTouches(true);
	oneTouch->onTouchBegan = beginCall;
	oneTouch->onTouchMoved = moveCall;
	oneTouch->onTouchEnded = endCall;
	oneTouch->onTouchCancelled = cancelCall;

	EventDispatcher *pDispatcher = CCDirector::getInstance()->getEventDispatcher();
	pDispatcher->addEventListenerWithSceneGraphPriority(oneTouch, parent);
	return true;
}


bool DxEventUtils::RegisterTouchEventOneByOne(
	int priority,
	ccTouchBeganCallback beginCall,
	ccTouchCallback moveCall,
	ccTouchCallback endCall,
	ccTouchCallback cancelCall)
{
	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->setSwallowTouches(true);
	oneTouch->onTouchBegan = beginCall;
	oneTouch->onTouchMoved = moveCall;
	oneTouch->onTouchEnded = endCall;
	oneTouch->onTouchCancelled = cancelCall;

	EventDispatcher *pDispatcher = CCDirector::getInstance()->getEventDispatcher();
	pDispatcher->addEventListenerWithFixedPriority(oneTouch, priority);

	return true;
}

void DxEventUtils::AddNodeToListener(EventListenerTouchOneByOne &listener, std::vector<Node *> nodes)
{
	EventDispatcher *pDispatcher = CCDirector::getInstance()->getEventDispatcher();
	for each (auto node in nodes)
	{
		if (node != nullptr)
		{
			pDispatcher->addEventListenerWithSceneGraphPriority(listener.clone(), node);
		}
	}
}

