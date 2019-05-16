#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include "testcode/testdefs.h"
//#include <GUI/CCScrollView/CCScrollView.h>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;


// 将要显示的图片添加到
class CAdLayer:public Layer, public ScrollViewDelegate
{
public:
	void runCase();
	bool init(CCSize size);
	static CAdLayer * create(CCSize size =  CCSize(271,455));
	void addItem(Sprite *item);
	void addItem(string imgpath);
	void setItemPosition(Sprite *item);
	void addItems(vector<Sprite *> items);
	void showItems();
	void test1();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchCancelled(Touch *touch, Event *unused_event);

	CREATE_TEST_FUNC(CAdLayer);
protected:
	void update(float delta);
	CAdLayer();
private:
	vector<Sprite *> _spriteItems;
	cocos2d::extension::ScrollView *_scrollview;
	float _containerWidth;
	Layer *_container;
};

