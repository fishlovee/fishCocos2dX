# 02 helloworld源码阅读

## main.cpp
```c++
// main.cpp
#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;    // using namespace cocos2d;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
```
**功能说明**
> AppDelegate继承于Application，它实例化一个Application对象，并在Application::getInstance()->run() 中调用AppDelegate::applicationDidFinishLaunching以加载第一个场景！


## AppDelegate类
```c++
// AppDelegate.h 
#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_
#include "cocos2d.h"
/**
@brief    The cocos2d Application.
The reason for implement as private inheritance is to hide some interface call by Director.
实现私有继承的原因是要隐藏一些由Director调用的接口。
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();
    virtual bool applicationDidFinishLaunching();         /**@brief    实现 Director 和 Scene 的初始化.*/
    virtual void applicationDidEnterBackground();         /**@brief  切换后台/打电话时调用*/
    virtual void applicationWillEnterForeground();        /**@brief  后台切换回来调用*/
};

#endif // _APP_DELEGATE_H_
```


**AppDelegate说明**
    AppDelegate 继承自 cocos2d::Application ，Application::getInstance()->run() 调用基类的run函数，然后调用 AppDelegate::applicationDidFinishLaunching 完成 Director 的实例化以及第一个场景场景的加载在、运行。

```c++
// AppDelegate.cpp
bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();       // 获取或实例化 Director 
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(true);                // 打开 FPS 显示
    director->setAnimationInterval(1.0 / 60);       // 设置帧率
    auto scene = HelloWorld::createScene();         // 创建一个场景，createScene返回的是一个智能指针，可以自动析构
    director->runWithScene(scene);                  // 运行第一个场景
    return true;
}


void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

```


## HelloWorld.cpp
```c++
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();               // there's no 'id' in cpp, so we recommend returning the class instance pointer
    virtual bool init();                                // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    void menuCloseCallback(cocos2d::Ref* pSender);      // a selector callback
    CREATE_FUNC(HelloWorld);                            // implement the "static create()" method manually
};

#endif // __HELLOWORLD_SCENE_H__
```

```c++
// HelloWorldScene.h
#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

// 扩展后
static HelloWorld* create()
{
    HelloWorld *pRet = new HelloWorld();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
}
```

```c++
// HelloWorldScene.cpp
#include "HelloWorldScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();             // 'scene' is an autorelease object
    auto layer = HelloWorld::create();        // 'layer' is an autorelease object
    scene->addChild(layer);                   // add layer as a child to scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )  // 初始化基类
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 添加关闭按钮
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
   
   // 设置位置
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // 创建菜单，智能指针，自动释放
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);    // 该位置是相对于 closeItem 的位置，比如Vec2(-10,-20)表示相对于 closeItem 向左、向下移动10，20个像素
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    // 创建标签
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    // 设置标签位置
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // 将 label 添加到场景的子节点
    this->addChild(label, 1);

    // 创建精灵
    auto sprite = Sprite::create("HelloWorld.png");

    // 放置精灵：置中
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // 将 sprite 添加到本场景
    this->addChild(sprite, 0);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	  MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
```
















