#pragma once

#include <cocos2d.h>
#include <ui/UIButton.h>
#include <string>

USING_NS_CC;

namespace DxUtils
{
	ui::Button *createButtonWithOneImg(const std::string &strPicName, std::function<void(Ref*)> onClicked); 
	ui::Button *createButtonWithSelectedImg(const std::string &strNorm, const std::string &strSelected, std::function<void(Ref*)> onClicked);
	ui::Button *createButtonWithSelectedAndDisableImg(const std::string &strNorm, const std::string &strSelected, const std::string &strDisable, std::function<void(Ref*)> onClicked);
}
