#include "adLayer.h"


void CAdLayer::runCase()
{
	this->setAnchorPoint(Vec2::ZERO);
	this->setPosition(0, 0);
	
	this->addItem("ad/adpic1.png");
	this->addItem("ad/adpic2.png");
	this->showItems();
}

bool CAdLayer::init(CCSize size)
{
	if (!Layer::init())
	{
		return false;
	}

	// ���scrollview
	do 
	{
		_container = Layer::create();
		if (_container == nullptr)
		{
			break;
		}

		_scrollview = ScrollView::create(this->getContentSize(), _container);
		if (_scrollview == nullptr)
		{
			break;
		}

		return true;
	} while (0);

	CC_SAFE_DELETE(_scrollview);
	CC_SAFE_DELETE(_container);
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


void CAdLayer::test1()
{
	CCSprite* ad1 = CCSprite::create("ad/adpic1.png");
	CCSprite* ad2 = CCSprite::create("ad/adpic2.png");

	CCSize visableSize = ad1->getContentSize(); //��Ļ��С
	CCSize mysize = CCSize(visableSize.width*2, visableSize.height);						 //������С

	//�������������ô�С
	LayerColor* scrollLayer = LayerColor::create(ccc4(255, 255, 255, 255));
	scrollLayer->setContentSize(mysize);

	//�����еĶ���
	ad1->setAnchorPoint(Vec2::ZERO);
	ad2->setAnchorPoint(Vec2::ZERO);
	ad1->setPosition(ccp(0, 0));
	ad2->setPosition(ccp(ad1->getContentSize().width,0));
	scrollLayer->addChild(ad1);
	scrollLayer->addChild(ad2);


	//����������ͼCCScrollView
	ScrollView* scrollView = ScrollView::create();

	//ί�д���
	scrollView->setDelegate(this);

	//��������
	scrollView->setContainer(scrollLayer);  //��������
	scrollView->setViewSize(visableSize); //���������С
	scrollView->setBounceable(true);        //�Ƿ���е���

	this->addChild(scrollView, 0, 1);
}

void CAdLayer::showItems()
{
	_container->setPosition(0, 0);
	//_container->setContentSize(size);

	int nCount = 0;
	for each (auto item in _spriteItems)
	{
		item->setAnchorPoint(Vec2::ZERO);
		item->setPosition(item->getContentSize().width*nCount, 0);
		_container->addChild(item);
		nCount++;
	}

	_container->setContentSize(CCSize(this->getContentSize().width*_spriteItems.size(), this->getContentSize().height));

	//_scrollview->setContainer(_container);                               // ʹ��  ScrollView::create(this->getContentSize(), _container); ������scrollview�������ظ����ã�����ᵼ���޷�������ʾ��
	_scrollview->setContentSize(_container->getContentSize()); // Ҫô�����ã�Ҫô����Ϊ������size�����򻬶�ʱ����ֺڱ߻��߲����޷�����������
	_scrollview->setPosition(0, 0);
	_scrollview->setDirection(ScrollView::Direction::HORIZONTAL);	// ˮƽ
	//_scrollview->setAnchorPoint(Vec2(0, 0));
	_scrollview->setViewSize(this->getContentSize());
	_scrollview->setBounceable(true);
	_scrollview->setDelegate(this);
	this->addChild(_scrollview);
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

void CAdLayer::setItemPosition(Sprite *item)
{
	if (item == nullptr)
	{
		return;
	}

	auto size = item->getContentSize();
	item->setAnchorPoint(Vec2::ZERO);
	item->setPosition(_containerWidth,0);
	_containerWidth += size.width;
}

void CAdLayer::addItems(vector<Sprite *> items)
{
	//_spriteItems.insert(_spriteItems.end(), items.begin(),items.end());
	for each (auto it in items)
	{
		if (it != nullptr)
		{
			this->addItem(it);
		}
	}
	return ;
}


bool CAdLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return false;
}

void CAdLayer::onTouchCancelled(Touch *touch, Event *unused_event)
{

}

void CAdLayer::update(float delta)
{
	Layer::update(delta);


}

CAdLayer::CAdLayer()
{
	_scrollview = nullptr;
	_containerWidth = 0.0f;
	_container = nullptr;
}

