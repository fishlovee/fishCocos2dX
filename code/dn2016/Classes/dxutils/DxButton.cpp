#include "DxButton.h"


namespace DxUtils
{
	cocos2d::ui::Button * createButtonWithOneImg(const std::string &strPicName, std::function<void(Ref*)> onClicked)
	{
		ui::Button * button = nullptr;

		do
		{
			button = ui::Button::create(strPicName);
			CC_BREAK_IF(button == nullptr);

			button->addClickEventListener(onClicked);
			return button;
		} while (0);

		CC_SAFE_DELETE(button);
		return nullptr;
	}


}


