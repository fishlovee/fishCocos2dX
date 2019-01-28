# 07 menu-菜单

## 使用菜单
**步骤**
- 新建一个到三个 Sprite 并使用 Sprite 创建 MenuItemSprite ，并将按钮与回调绑定
- 设置 MenuItem 位置
- 使用一个或多个MenuItem创建Menu，并设置位置

```C++
	Sprite *startButton = Sprite::createWithSpriteFrame(CImgManager::GetInstance()->GetSpriteFrameByPicName("button_play"));
	Sprite *avtiveStartButton = Sprite::createWithSpriteFrame(CImgManager::GetInstance()->GetSpriteFrameByPicName("button_play"));
	MenuItemSprite *startMenu = MenuItemSprite::create(startButton, avtiveStartButton, NULL, CC_CALLBACK_1(CWelcomeLayer::onMenuStart, this));
	startMenu->setPosition(Point(orgSize.x + visiblesize.width/2 ,orgSize.y + visiblesize.height*2/5));
	auto menu = Menu::create(startMenu,NULL);
	menu->setPosition(orgSize);
	this->addChild(menu);
```

## 使用button
> cocos中的Menue菜单有点反人类，可以使用button代替。

```C++
void MyBottonBastLayer::initLayer() {
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCScale9Sprite *psc9Selected = CCScale9Sprite::create("btn-about-selected.png");
    CCLabelTTF *label = CCLabelTTF::create("My Button", "Marker Felt", 30);
    CCScale9Sprite *psc9ButtonBG = CCScale9Sprite::create("extensions/buttonHighlighted.png");
    CCControlButton *button = CCControlButton::create(label, psc9ButtonBG);

    /*set the button is pressed state*/
    button->setPosition(ccp(500.0f, size.height / 3.0f));
    button->setBackgroundSpriteForState(psc9Selected, CCControlStateSelected);
    button->setTitleColorForState(ccWHITE, CCControlStateHighlighted);

    button->addTargetWithActionForControlEvents(this, cccontrol_selector(MyBottonBastLayer::buttonCallBack), CCControlEventTouchDown);
    this->addChild(button, 1);
}
```

### 一个button使用参考
[cocos2dx 3.x（Button传统按钮）](http://www.cnblogs.com/luorende/p/5983189.html)
```C++
//
//  ATTLoagingScene.hpp
//  ATT
//
//  Created by work on 16/10/13.
//
//

#ifndef ATTLoagingScene_hpp
#define ATTLoagingScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"//使用按钮事件，必须要需要的头文件
USING_NS_CC_EXT;//使用按钮事件，必须要需要的命名空间

class ATTLoagingScene : public cocos2d::Layer

{

   
private:

    cocos2d::ui::Button * m_soundOnButton;//私有的成员变量

    cocos2d::ui::Button * m_btnPlus;

      

public:

    static cocos2d::Scene* createScene();    

    virtual bool init();

//声明点击事件

    void menuCloseCallback(Ref *ref,cocos2d::extension::Control::EventType event);//对原来的关闭事件进行改造，增加参数，让其支持cccontrol_selector

    // implement the "static create()" method manually

    CREATE_FUNC(ATTLoagingScene);

};

#endif /* ATTLoagingScene_hpp */
```

```c++
//
//  ATTLoagingScene.cpp
//  ATT
//
//  Created by work on 16/10/13.
//
//

#include "ATTLoagingScene.hpp"
#include "SimpleAudioEngine.h"
#include "ATTGameScene.hpp"
USING_NS_CC;

Scene* ATTLoagingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ATTLoagingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool ATTLoagingScene::init()
{
    
    
    if ( !Layer::init() )
    {
        return false;
    }


auto soundbg=cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("gobang_option_sound_off.png");
    soundbg->setScale(0.667);
    m_soundOnButton=ControlButton::create(soundbg);
    m_soundOnButton->setPreferredSize(cocos2d::Size(162,58));
    m_soundOnButton->setPosition(getPoint(1136, 627));
    m_soundOnButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GoBangScene::buttonSoundOnCallBack), Control::EventType::TOUCH_UP_INSIDE);
    this->addChild(m_soundOnButton,2);
    m_soundOnButton->setVisible(false);//设置为隐藏，true为可见。
    m_soundOnButton->setEnabled(false);//设置为禁用，true为可用。
    m_soundOnButton->setOpacity(200);//透明度 setOpacity 透明度 0~255(取值范围)，255不透明，0全透明 

   

//

    return true;
}

// 实现点击方法
#pragma mark - ATTGameScene::optionCB(设置按钮)
void ATTGameScene::buttonSoundOnCallBack(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    /* 
     *判断当前点击类型（只响应一次，松开时生效）
     */
    if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        return;
    }
    // 直接取反 （判断当前节点是否被隐藏，若隐藏直接取反）
    //m_optionNode->setVisible(!m_optionNode->isVisible());

}
```