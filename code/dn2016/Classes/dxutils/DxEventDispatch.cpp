#include "DxEventDispatch.h"


namespace DxUtils
{

	EventDispatcher * DxEventDispach::getDispatcher()
	{
		if (_DispachInstance == nullptr)
		{
			_DispachInstance = Director::getInstance()->getEventDispatcher();
		}

		return _DispachInstance;
	}

	void DxEventDispach::registerEvent()
	{
		
	}

	EventDispatcher * DxEventDispach::_DispachInstance = nullptr;
}