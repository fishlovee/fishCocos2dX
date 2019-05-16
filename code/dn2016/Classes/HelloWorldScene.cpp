#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "./testcode/scollview/adLayer.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);



	m_pNormButtonWithoutSelect = Button::create("CloseNormal.png");
	m_pNormButtonWithoutSelect->setPosition(Vec2(origin.x + m_pNormButtonWithoutSelect->getContentSize().width / 2,
		origin.y + m_pNormButtonWithoutSelect->getContentSize().height / 2));
	this->addChild(m_pNormButtonWithoutSelect, 1);




    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World��ã�����", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
	CAdLayer *pAd = CAdLayer::create();
	pAd->setAnchorPoint(Vec2::ZERO);
	pAd->setPosition(0,0);
	//pAd->test1();
	pAd->addItem("ad/adpic1.png");
	pAd->addItem("ad/adpic2.png");
	pAd->showItems();
	//auto ad1 = Sprite::create("ad/adpic1.png");
	//ad1->setPosition(300, 300);
	//this->addChild(ad1);
	this->addChild(pAd);
    //////////////////////////////
    // 1. super init first
    //if ( !Layer::init() )
    //{
    //    return false;
    //}
    //
    //auto rootNode = CSLoader::createNode("MainScene.csb");

    //addChild(rootNode);

    return true;
}

void HelloWorld::menuCloseCallback(Ref *psender)
{
	Director::getInstance()->end();

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	exit(0);
#endif
}

HelloWorld::HelloWorld()
{
	m_pNormButtonWithoutSelect = nullptr;
}
