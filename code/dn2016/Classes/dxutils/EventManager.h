#pragma once

#include <cocos2d.h>
#include <vector>
#include "base/CCEventListenerTouch.h"

USING_NS_CC;

namespace DxUtils {
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

		// for fixed priority£¬use ths need to remove touch event by yourself
		bool RegisterTouchEventOneByOneWithPriority(
			int priority,
			ccTouchBeganCallback beginCall,
			ccTouchCallback moveCall,
			ccTouchCallback endCall,
			ccTouchCallback cancelCall);
	
		// if you call RegisterTouchEventOneByOneWithPriority,you should call this function to remove listener when your node destory
		void RemoveTouchEventOneByOneWithPriority(EventListener* listener);

		// for WithSceneGraphPriority
		bool RegisterTouchEventOneByOne( Node *parent,  
																			 ccTouchBeganCallback beginCall,
																			ccTouchCallback moveCall,
																			ccTouchCallback endCall,
																			ccTouchCallback cancelCall);

		// do nothing
		void RemoveTouchEventOneByOne();

		void AddNodeToListener(EventListenerTouchOneByOne &listener, std::vector<Node *> nodes);

	protected:
	private:
		DxEventUtils() {};
		static DxEventUtils _instance;	
	};

}