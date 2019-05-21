#include "EventManager.h"

namespace DxUtils {

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


	void DxEventUtils::RemoveTouchEventOneByOne()
	{

	}

	bool DxEventUtils::RegisterTouchEventOneByOneWithPriority(
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

	void DxEventUtils::RemoveTouchEventOneByOneWithPriority(EventListener* listener)
	{
		EventDispatcher *pDispatcher = CCDirector::getInstance()->getEventDispatcher();
		pDispatcher->removeEventListener(listener);
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

}