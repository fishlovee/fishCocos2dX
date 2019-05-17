#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include "testcode/testdefs.h"
//#include <GUI/CCScrollView/CCScrollView.h>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;


#define AD_MIN_LAYER_INDEX (1)
#define MOVE_ONEPAGE_SECOND	(2)

// 将要显示的图片添加到
class CAdLayer:public Layer, public ScrollViewDelegate
{
public:
	void runCase();
	bool init(CCSize size);
	static CAdLayer * create(CCSize size =  CCSize(271,455));
	void addItem(Sprite *item);
	void addItem(string imgpath);
	void addItems(vector<Sprite *> items);
	void showItems();
	Vec2 getDotPosByIndex(int nPageIndex);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	
	void moveToPage(float dx);
	CREATE_TEST_FUNC(CAdLayer);
protected:
	void update(float delta);
	CAdLayer();
private:
	vector<Sprite *> _spriteItems;
	cocos2d::extension::ScrollView *_scrollview;
	int     _curPageIndex;
	Layer *_container;
	Vec2 _firstTouchPos;
	Vec2 _preTouchPos;
	Sprite *_curdotSprite;
	int _targetPageIndex;
	//const static int _minPageIndex = 1;
};

