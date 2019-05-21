#include "DxLayer.h"
#include "testcode/testdefs.h"
#define SCHEDULE_DXLAYER_SHOW_EVENT "SCHEDULE_DXLAYER_SHOW_EVENT"


namespace DxUtils {

	void DxLayer::RemoveLayer(float dx, float delay, std::function<void()> removeFinishedCallback)
	{
		//this->setScale(0.2);
		Vector<FiniteTimeAction*> actions;
		this->setAnchorPoint(Vec2::ZERO);
		auto scale = ScaleTo::create(dx, 0.2);
		//auto reversescale = scale->reverse();
		this->setScale(1.0);
		actions.pushBack(scale);
		
		if (removeFinishedCallback != nullptr)
		{
			auto delayAction = DelayTime::create(delay);
			actions.pushBack(delayAction);

			auto callback = CallFunc::create(removeFinishedCallback);
			actions.pushBack(callback);
		}

		auto removeself = [&]() {
			this->removeFromParentAndCleanup(true);
		};
		actions.pushBack(CallFunc::create(removeself));
		this->runAction(Sequence::create(actions));
	}

	void DxLayer::ShowLayer()
	{
		if (!_showLayerZoomEnable)
		{
			return;
		}

		
		_orgPosition = this->getPosition();
		this->setAnchorPoint(Vec2::ZERO);
		DX_LOG("pos = %f,%f,anchor = %f,%f", _orgPosition.x,_orgPosition.y,this->getAnchorPoint().x,this->getAnchorPoint().y);
		float dx = _showLayerZoomDx;
		float delay = _showLayerFinishDelay;
		std::function<void()> showFinishedCallback = _showFinishedCallback;
		this->setScale(0);
		this->runAction(FadeOut::create(0.0f));
		this->runAction(ScaleTo::create(dx, 1.0f));
		this->runAction(FadeIn::create(20.0f));
		this->runAction(CallFunc::create([&]() 
								{
									//this->setTouchEnabled(true); 
								})); // 缩放完成后使能触摸
		this->setTouchEnabled(false); // 缩放完成前禁用触摸

		if (showFinishedCallback != nullptr)
		{
			auto delayAction = DelayTime::create(delay);
			this->runAction(delayAction);

			auto callback = CallFunc::create(showFinishedCallback);
			this->runAction(callback);
		}

		//// 定时调用，直到scale == 1
		//this->schedule([&](float dx) {
		//	if (this->getScale() >= 0.9999f)
		//	{
		//		this->unschedule(SCHEDULE_DXLAYER_SHOW_EVENT);
		//	}
		//	else
		//	{
		//		this->setPosition(_orgPosition);
		//	}
		//}, SCHEDULE_DXLAYER_SHOW_EVENT);
		//void schedule(const std::function<void(float)>& callback, const std::string &key);
	}

	void DxLayer::setContentSize(const Size & size)
	{
		LayerColor::setContentSize(size);
	}

	DxLayer * DxLayer::create(Color4B color /*= Color4B(0, 0, 0, 100)*/)
	{
		DxLayer *layer = new DxLayer();
		if (layer != nullptr && layer->init(color))
		{
			layer->autorelease();
			return layer;
		}

		CC_SAFE_DELETE(layer);
		return layer;
	}

	DxLayer * DxLayer::create(GLfloat width, GLfloat height, Color4B color /*= Color4B(0, 0, 0, 100)*/)
	{
		DxLayer *layer = new DxLayer();
		if (layer != nullptr && layer->init(width, height, color))
		{
			layer->autorelease();
			return layer;
		}

		CC_SAFE_DELETE(layer);
		return layer;
	}




void DxLayer::onEnter()
{
	LayerColor::onEnter();
	this->ShowLayer();
}

void DxLayer::enableShowLayerZoom(bool bEnable)
{
	if (_showLayerZoomEnable != bEnable)
	{
		_showLayerZoomEnable = bEnable;
	}
}

void DxLayer::setShowLayerZoom(float dx, float delay, std::function<void()> showFinishedCallback)
{
	_showLayerZoomDx = dx;
	_showLayerFinishDelay = delay;
	_showFinishedCallback = showFinishedCallback;
}

DxLayer::DxLayer()
{
	_showFinishedCallback = nullptr;
	_showLayerZoomEnable = false;
	_showLayerZoomDx = 1.5f;
	_showLayerFinishDelay = 0.0f;
}

bool DxLayer::init(Color4B color /*= Color4B(0, 0, 0, 100)*/)
{
	if (!LayerColor::initWithColor(color))
	{
		return false;
	}

		return true;
	}

	bool DxLayer::init(GLfloat width, GLfloat height, Color4B color /*= Color4B(0, 0, 0, 100)*/)
	{
		if (!LayerColor::initWithColor(color, width, height))
		{
			return false;
		}

		return true;
	}

}