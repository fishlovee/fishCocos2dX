#pragma once

#include <cocos2d.h>
#include <ui/UIButton.h>
#include <string>

USING_NS_CC;

namespace DxUtils
{
	ui::Button *createButtonWithOneImg(const std::string &strPicName, std::function<void(Ref*)> onClicked); 
}
