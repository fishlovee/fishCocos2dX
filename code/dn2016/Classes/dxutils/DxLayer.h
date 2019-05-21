#pragma once

#include <cocos2d.h>

USING_NS_CC;

namespace DxUtils {

	class DxLayer :public LayerColor
	{
	public:
		void RemoveLayer(float dx, float delay, std::function<void()> removeFinishedCallback);
	void ShowLayer();
		void setContentSize(const Size & size);
		static DxLayer *create(Color4B color = Color4B(0, 0, 0, 100));
		static DxLayer *create(GLfloat width, GLfloat height, Color4B color = Color4B(0, 0, 0, 100));

	virtual void onEnter();
	void enableShowLayerZoom(bool bEnable);
	void setShowLayerZoom(float dx, float delay, std::function<void()> showFinishedCallback);
	DxLayer();
	protected:
		bool init(Color4B color = Color4B(0, 0, 0, 100));
		bool init(GLfloat width, GLfloat height, Color4B color = Color4B(0, 0, 0, 100));
	private:
	std::function<void()> _showFinishedCallback;
	bool _showLayerZoomEnable;
	float _showLayerZoomDx;
	float _showLayerFinishDelay;
	Vec2 _orgPosition;
	};


}