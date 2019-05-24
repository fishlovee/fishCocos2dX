#include <cocos2d.h>
#include <string>
USING_NS_CC;

namespace DxUtils
{
	void RegisterCustomEvent(std::string &eventname, const std::function<void(EventCustom*)>& callback);
}