#pragma once

#include <cocos2d.h>

USING_NS_CC;

namespace DxUtils {

	class DxLayer :public LayerColor
	{
		// 计划实现弹出、放大缩小2、普通三种展示、关闭效果
		enum EN_DXLAYER_SHOWMODE
		{
			eDxLayer_AllNormal = 0,
			eDxLayer_CenterPop,		// 以中心点为anchor进行缩放，类似pop效果
			eDxLayer_OrgScale,          // 以左下角为原点进行缩放
		};
	public:
		void RemoveLayer(float dx = 0.75f, float delay = 0.0f, std::function<void()> removeFinishedCallback = nullptr);
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