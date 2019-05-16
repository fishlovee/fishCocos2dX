#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/UIButton.h"

using namespace cocos2d::ui;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	Button *m_pNormButtonWithoutSelect;
	Layer *m_pAdLayer;

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void menuCloseCallback(Ref *psender);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

protected:
	HelloWorld();
};

#endif // __HELLOWORLD_SCENE_H__
