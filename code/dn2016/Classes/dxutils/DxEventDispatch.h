#pragma once
#include <cocos2d.h>

USING_NS_CC;

namespace DxUtils
{
	class DxEventDispach
	{
	public:
		static EventDispatcher * getDispatcher();
		void registerEvent(unsigned int eventNo);
	protected:
		
	private:
		static EventDispatcher *  _DispachInstance;
	};
}