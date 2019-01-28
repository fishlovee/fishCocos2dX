# 06 cocos中的onEnter函数

## 概述
场景的OnEnter函数继承自CCNode类，cocos文档对该函数有以下描述：
```
Event callback that is invoked every time when Node enters the 'stage'.

If the Node enters the 'stage' with a transition, this event is called when the transition starts. During onEnter you can't access a "sister/brother" node. If you override onEnter, you shall call its parent's one, e.g., Node::onEnter().

Reimplemented in TransitionFadeTR, TransitionSplitCols, TransitionTurnOffTiles, TransitionCrossFade, TransitionFade, ParticleSystem, TransitionZoomFlipAngular, TransitionZoomFlipY, Widget, TransitionZoomFlipX, TransitionFlipAngular, TextField, TransitionFlipY, ScrollView, TransitionFlipX, EditBox, TransitionShrinkGrow, Layout, TransitionSlideInL, TransitionMoveInL, Camera, WebView, TransitionJumpZoom, TransitionRotoZoom, VideoPlayer, Menu, ProtectedNode, ScrollViewBar, ClippingNode, TransitionScene, TransitionPageTurn, TransitionProgress, and UICCTextField.


```

其代码如下：
```C++
void Node::onEnter()
{
    if (_onEnterCallback)
        _onEnterCallback();

    if (_componentContainer && !_componentContainer->isEmpty())
    {
        _componentContainer->onEnter();
    }

    _isTransitionFinished = false;

    for( const auto &child: _children)
        child->onEnter();

    this->resume();
    _running = true;
}
```

可以看出，当调用onEnter函数时，会回调自身的 _onEnterCallback以及其子节点的onEnter，并且如果重写了onEnter，则必须先调用Node::onEnter，并且在该函数调用过程中，不能访问当前节点的兄弟节点。

## 重写onEnter
```c++

class GameScene :
	public cocos2d::CCScene
{
public:
	GameScene();
	~GameScene();

	void onEnter() override;
	bool init();
	BackgroundLayer *m_pBackgroundLayer;
	CREATE_FUNC(GameScene);
};

void GameScene::onEnter()
{
	CCScene::onEnter();
	m_pBackgroundLayer = BackgroundLayer::create();
	this->addChild(m_pBackgroundLayer);
}

```

在重写的onEnter函数中，调用了其基类CCScene的onEnter函数，而跟踪代码，调用的实际上是CCNode::onEnter。如果不调用基类的onEnter函数，则运行时会黑屏，创建的精灵无法显示出来。

**PS**将CCScene::onEnter放到函数末尾也可以。。。我也不知道为啥子。
