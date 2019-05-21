#include "openUrlByDefaultBrowser.h"
#include "dxutils.h"



void OpenUrlByDefaultBrowser::runCase()
{

}

bool OpenUrlByDefaultBrowser::init()
{
	Sprite *helloworld = nullptr;
	ui::Button *closeButton = nullptr;
	do 
	{
		if (!DxLayer::init())
		{
			break;
		}

		helloworld = Sprite::create("HelloWorld.png");
		CC_BREAK_IF(helloworld == nullptr);

		helloworld->setAnchorPoint(Vec2::ZERO);
		helloworld->setPosition(Vec2::ZERO);
		this->addChild(helloworld);

		closeButton = createButtonWithOneImg("CloseNormal.png",
			[&](Ref *) {
			    // 此处无法调用 application::openurl ....
			DX_LOG("to open url:%s", "www.baidu.com");
			}
		);
		CC_BREAK_IF(closeButton == nullptr);

		closeButton->setAnchorPoint(Vec2::ZERO);
		closeButton->setPosition(Vec2::ZERO);
		this->addChild(closeButton);
		return true;
	} while (0);

	CC_SAFE_DELETE(helloworld);

	return false;
}

