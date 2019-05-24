#include "adLayer.h"
#include "dxutils.h"
#include "ui/UIButton.h"


#define AD_AUTO_MOVEPAGE_EVENT	"AD_AUTO_MOVEPAGE_EVENT"

void CAdLayer::runCase()
{
	this->setShowLayerZoom(3.5f, 0.0f, nullptr);
	this->enableShowLayerZoom(false);
	//this->ShowLayer(); // 在此处调用和在onEnter中调用效果一样。

	Vec2 orgPos = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
	this->setAnchorPoint(Vec2::ZERO);  
	this->setPosition(orgPos.x + winSize.width/2,orgPos.y + 10);
	
	this->addItem("ad/adpic1.png");
	this->addItem("ad/adpic2.png");
	this->addItem("ad/adpic1.png");
	this->showItems();
	this->scheduleUpdate();

	DX_LOG("adlayer is touchable:%s", this->isTouchEnabled()?"true":"false");
}

bool CAdLayer::init(CCSize size)
{
	if (!DxLayer::init())
	{
		return false;
	}

	// 添加scrollview
	do 
	{
		_container = DxLayer::create();
		CC_BREAK_IF(_container == nullptr);

		_scrollview = ScrollView::create(this->getContentSize(), _container);
		//_scrollview = ScrollView::create(this->getContentSize());
		CC_BREAK_IF(_scrollview == nullptr);

		string strDotName = "ad/ad_curpage.png";
		_curdotSprite = Sprite::create(strDotName);
		CC_BREAK_IF(_curdotSprite == nullptr);

		this->addChild(_curdotSprite,2);
		return true;
	} while (0);

	CC_SAFE_DELETE(_scrollview);
	CC_SAFE_DELETE(_container);
	CC_SAFE_DELETE(_curdotSprite);
	return false;
}

CAdLayer * CAdLayer::create(CCSize size)
{
	auto layer = new CAdLayer();
	if (layer && layer->init(size))
	{
		layer->autorelease();
		layer->setContentSize(size);
	}
	else
	{
		CC_SAFE_DELETE(layer);
	}
	return layer;
}


void CAdLayer::showItems()
{
	_container->setPosition(0, 0);
	//_container->setContentSize(size);

	int nCount = 0;

	// 图片展示
	for each (auto item in _spriteItems)
	{
		item->setAnchorPoint(Vec2::ZERO);
		item->setPosition(item->getContentSize().width*nCount, 0);
		_container->addChild(item);
		nCount++;
	}

	// 页面小圆点展示
	auto curdotSprite = Sprite::create("ad/ad_curpage.png");
	float fDotWidth = curdotSprite->getContentSize().width + 2;
	float fDotHeightPos = this->getContentSize().height / 10;
	float fDotWidthPosBegin = this->getContentSize().width / 2 - nCount / 2 * fDotWidth - (nCount % 2) * fDotWidth/2 + fDotWidth/2;
	for (int index = 0;index < nCount;++index)
	{
		string strDotName = "ad/ad_page.png";
		auto dotSprite = Sprite::create(strDotName);
		dotSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		dotSprite->setPosition(getDotPosByIndex(index + 1));
		this->addChild(dotSprite, 2);
	}
	

	_curdotSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_curdotSprite->setPosition(getDotPosByIndex(_curPageIndex));
	_container->setContentSize(CCSize(this->getContentSize().width*_spriteItems.size(), this->getContentSize().height));

	//_scrollview->setContainer(_container);                               // 使用  ScrollView::create(this->getContentSize(), _container); 创建的scrollview，不能重复设置，否则会导致无法正常显示。
	_scrollview->setContentSize(_container->getContentSize()); // 要么不设置，要么设置为容器的size，否则滑动时会出现黑边或者部分无法滑动的问题
	_scrollview->setPosition(0, 0);
	_scrollview->setDirection(ScrollView::Direction::HORIZONTAL);	// 水平
	//_scrollview->setAnchorPoint(Vec2(0, 0));
	_scrollview->setViewSize(this->getContentSize());
	_scrollview->setBounceable(false);										// 禁用bounce，重写父类的 void scrollViewDidScroll(ScrollView* view) 方法
	_scrollview->setDelegate(this);
	this->addChild(_scrollview);

	// 注册触摸事件
	auto onBegan = CC_CALLBACK_2(CAdLayer::onTouchBegan, this);
	auto onMove = CC_CALLBACK_2(CAdLayer::onTouchMoved, this);
	auto onEnd = CC_CALLBACK_2(CAdLayer::onTouchEnded, this);
	auto onCancel = nullptr;
	DxEvenRegister::getInstance().RegisterTouchEventOneByOne(this, onBegan,onMove,onEnd, onCancel);

	//auto oneTouch = EventListenerTouchOneByOne::create();
	//oneTouch->setSwallowTouches(true);
	//oneTouch->onTouchBegan = CC_CALLBACK_2(CAdLayer::onTouchBegan, this);
	//oneTouch->onTouchMoved = NULL;
	//oneTouch->onTouchEnded = CC_CALLBACK_2(CAdLayer::onTouchEnded, this);
	//oneTouch->onTouchCancelled = NULL;

	//EventDispatcher *pDispatcher = CCDirector::getInstance()->getEventDispatcher();
	//pDispatcher->addEventListenerWithSceneGraphPriority(oneTouch, this);

	auto cclosebuttonb = ui::Button::create("img/guanbi.png");
	auto closeCallback = [&](Ref * ref) {
		//this->removeFromParentAndCleanup(true);
		this->RemoveLayer(2.0f, 2.0f, nullptr);
	};
	cclosebuttonb->addClickEventListener(closeCallback);
	cclosebuttonb->setPosition(Vec2(20, 20));
	this->addChild(cclosebuttonb, 10);

	this->autoMovePage();
}

void CAdLayer::autoMovePage()
{
	// C++11可以很方便的想lua一样写local函数了，爽！！！
	auto autoMovePage = [&](float dx) {
		if ( _spriteItems.size() == 1)
		{
			return;
		}

		switch (_emoveDir)
		{
		case CAdLayer::eMoveDirRight:
		{
			if (_curPageIndex == _spriteItems.size())
			{
				_emoveDir = eMoveDirLeft;
				this->_targetPageIndex = _spriteItems.size() - 1;
			}
			else
			{
				this->_targetPageIndex = _curPageIndex + 1;
			}
			break;
		}
		case CAdLayer::eMoveDirLeft:
		{
			if (_curPageIndex == 1)
			{
				_emoveDir = eMoveDirRight;
				this->_targetPageIndex = _curPageIndex + 1;
			}
			else
			{
				this->_targetPageIndex = _curPageIndex - 1;
			}
			break;
		}
		default:
			_emoveDir = eMoveDirRight;
			this->_targetPageIndex = 1;
			break;
		}

		moveToPage(0.75f); // 
	};

	// 可以指定调用次数的schedule原型如下：
	// void schedule(const ccSchedulerFunc& callback, void *target, float interval, bool paused, const std::string& key);
	// 第一个参数如下： typedef std::function<void(float)> ccSchedulerFunc;
	this->schedule(autoMovePage, 5.0f, 1, 5.0f, AD_AUTO_MOVEPAGE_EVENT);
	auto cclosebuttonb = ui::Button::create("img/guanbi.png");
	auto closeCallback = [&](Ref * ref) {
		//this->removeFromParentAndCleanup(true);
		this->RemoveLayer(2.0f, 2.0f, nullptr);
	};
	cclosebuttonb->addClickEventListener(closeCallback);
	cclosebuttonb->setPosition(Vec2(20, 20));
	this->addChild(cclosebuttonb, 10);
}



cocos2d::Vec2 CAdLayer::getDotPosByIndex(int nPageIndex)
{
	float fDotWidth = _curdotSprite->getContentSize().width + 2;
	float fDotHeightPos = this->getContentSize().height / 10;
	float fDotWidthPosBegin = this->getContentSize().width / 2 - _spriteItems.size() / 2 * fDotWidth - (_spriteItems.size() % 2) * fDotWidth / 2 + fDotWidth / 2;
	return Vec2(fDotWidthPosBegin + (nPageIndex - 1) * fDotWidth, fDotHeightPos);
}

void CAdLayer::addItem(Sprite *item)
{
	if (item != nullptr)
	{
		_spriteItems.push_back(item);
	}
	return ;
}

void CAdLayer::addItem(string imgpath)
{
	auto item = Sprite::create(imgpath);
	if (item == nullptr)
	{
		return;
	}

	this->addItem(item);
}


void CAdLayer::addItems(vector<Sprite *> items)
{
	_spriteItems.insert(_spriteItems.end(), items.begin(),items.end());
	//for each (auto it in items)
	//{
	//	if (it != nullptr)
	//	{
	//		this->addItem(it);
	//	}
	//}
	return ;
}


bool CAdLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto target = unused_event->getCurrentTarget();
	//Vec2 pos = target->convertToNodeSpace(touch->getLocation());
	Vec2 pos = touch->getLocation();                                 // 返回的是在其父节点的相对坐标
	auto box = this->boundingBox();									// 返回的是在气父节点的相对坐标组成的rect
	//CCLOG("touchbegin:x = %f,y = %f", pos.x, pos.y);
	//CCLOG("boudingbox:minX = %f,minY = %f,maxX = %f,maxY = %f", box.getMinX(), box.getMinY(), box.getMaxX(), box.getMaxY());

	if (!this->boundingBox().containsPoint(pos))
	{
		return false;
	}

	this->unschedule(AD_AUTO_MOVEPAGE_EVENT);
	_firstTouchPos = pos;
	return true;
}

void CAdLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{
	this->autoMovePage();
}

void CAdLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	_preTouchPos = touch->getLocation();
	//CCLOG("_preTouchPos:x = %f,y = %f,offset = %f", _preTouchPos.x, _scrollview->getContentOffset().x);
	//float currentX = _container->getPositionX();
	//if (currentX > 0)
	//{
	//	if (currentX >= _scrollview->getContentSize().width / 3)
	//	{
	//		_container->setPosition(Vec2(_scrollview->getContentSize().width / 3, 0));
	//	}
	//}
	//else if (currentX < _scrollview->getContentSize().width / 3 - _container->getContentSize().width)
	//{
	//	//_scrollview->setContentOffset(cocos2d::Vec2(_scrollview->getContentSize().width / 3 - _container->getContentSize().width, 0));
	//	_container->setPosition(Vec2(_scrollview->getContentSize().width / 3 - _container->getContentSize().width, 0));
	//}
	//CCLOG("_afterTouchPos:x = %f,y = %f,offset = %f", _preTouchPos.x, _scrollview->getContentOffset().x);
}

void CAdLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	Vec2 _curPos = touch->getLocation();
	//Vec2 _curPos = touch->getLocation();
	int nMovePageCount = (_firstTouchPos.x - _curPos.x) / (this->getContentSize().width / 2);
	_targetPageIndex = _curPageIndex + nMovePageCount;
	if (!isInRange(_targetPageIndex, AD_MIN_LAYER_INDEX,(int)_spriteItems.size()))
	{
		_targetPageIndex = nMovePageCount < 0 ? AD_MIN_LAYER_INDEX:_spriteItems.size();
	}
	
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(CAdLayer::moveToPage), 0.5f);   // 不能直接调用movetopage，因为bounce设置为了true，
																															 // 要等一段时间后再回调，否则bounce引起的滑动会造成位置和预期不符
	
}


void CAdLayer::moveToPage(float dx)
{
	//if (nPageIndex == _curPageIndex)
	//{
	//	return;
	//}
	int nPageIndex = this->_targetPageIndex;
	float xPos =  (nPageIndex - 1)*this->getContentSize().width*-1;
	MoveTo *to = MoveTo::create(1.0f, Vec2(xPos, 0));
	_container->runAction(to);
	
	Vector<FiniteTimeAction *> actions;
	if (_curPageIndex != nPageIndex)
	{
		MoveTo *to = MoveTo::create(1.0f, getDotPosByIndex(nPageIndex));
		actions.pushBack(to);
	}
	
	auto onRunFinished = [&]() {
		this->autoMovePage();
	};

	auto callback = CallFunc::create(onRunFinished);
	actions.pushBack(callback);
	_curdotSprite->runAction(Sequence::create(actions)); 
	_curPageIndex = nPageIndex;
	//CCLOG("moveto page = %d,x = %f", nPageIndex, xPos);
}

void CAdLayer::scrollViewDidScroll(ScrollView* view)
{
	return;
	//取消弹性
	auto layout = view->getContainer();
	float currentX = layout->getPositionX();

	if (currentX > 0)
	{
		if (currentX < view->getContentSize().width/3)
		{
			view->setContentOffset(cocos2d::Vec2(currentX, 0));
		}
		else
		{
			view->setContentOffset(cocos2d::Vec2(view->getContentSize().width / 3, 0));
		}
	}

	if (-currentX > layout->getContentSize().width - view->getViewSize().width)
	{
		view->setContentOffset(cocos2d::Vec2(-layout->getContentSize().width + view->getViewSize().width,0));
	}

	return;
	auto container = view->getContainer();
	auto x = container->getPosition().x;
	auto width = container->getContentSize().width;
	auto y = view->getPosition().y;
	auto nPageCount = _spriteItems.size();
	auto fMaxOffset = width * (nPageCount - 1.0/3);
	if (x < -1*fMaxOffset)
	{
		x = fMaxOffset * -1;
	}
	else if (x > width/3.0f)
	{
		x = width / 3.0f;
	}

	view->setContentOffset(Vec2(x, y), true);
}

void CAdLayer::update(float delta)
{
	Layer::update(delta);
	
	//DX_LOG("CAdLayer::update:delta = %f,1/delta = %f",delta,1/delta);
}

void CAdLayer::onExit()
{
	this->unschedule(AD_AUTO_MOVEPAGE_EVENT);
	DxLayer::onExit();
}

void CAdLayer::onEnter()
{
	DxLayer::onEnter();
}

CAdLayer::CAdLayer()
{
	_scrollview = nullptr;
	_container = nullptr;
	_curPageIndex = 1;
	_curdotSprite = nullptr;
	_targetPageIndex = 1;
	_emoveDir = eMoveDirRight;
}

