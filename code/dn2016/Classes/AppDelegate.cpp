#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        //glview = GLViewImpl::createWithRect(toUtf8String(DX_ZN_CODE,DX_APP_WINTITLE), Rect(0, 0, 960, 640));
		glview = GLViewImpl::create(toUtf8String(DX_ZN_CODE, DX_APP_WINTITLE));
		glview->setFrameSize(DX_DESIGNE_WINDOW_WIDTH*0.7, DX_DESIGNE_WINDOW_HIGHT*0.7);
        director->setOpenGLView(glview);
    }
	
    director->getOpenGLView()->setDesignResolutionSize(DX_DESIGNE_WINDOW_WIDTH, DX_DESIGNE_WINDOW_HIGHT, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");
	FileUtils::getInstance()->addSearchPath("res/img");
	FileUtils::getInstance()->addSearchPath("res/ui");
	//FileUtils::getInstance()->addSearchPath("res/img");

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
