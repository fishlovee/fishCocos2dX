#include "DxEvenRegister.h"

namespace DxUtils {

	DxEvenRegister DxEvenRegister::_instance;


	DxEvenRegister DxEvenRegister::getInstance()
	{
		return _instance;
	}

	bool DxEvenRegister::RegisterTouchEventOneByOne(
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

		EventDispatcher *pDispatcher = Director::getInstance()->getEventDispatcher();
		pDispatcher->addEventListenerWithSceneGraphPriority(oneTouch, parent);
		return true;
	}


	void DxEvenRegister::RemoveTouchEventOneByOne()
	{

	}

	bool DxEvenRegister::RegisterTouchEventOneByOneWithPriority(
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

		EventDispatcher *pDispatcher = Director::getInstance()->getEventDispatcher();
		pDispatcher->addEventListenerWithFixedPriority(oneTouch, priority);

		return true;
	}

	void DxEvenRegister::RemoveTouchEventOneByOneWithPriority(EventListener* listener)
	{
		EventDispatcher *pDispatcher = CCDirector::getInstance()->getEventDispatcher();
		pDispatcher->removeEventListener(listener);
	}

	void DxEvenRegister::AddNodeToListener(EventListenerTouchOneByOne &listener, std::vector<Node *> nodes)
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