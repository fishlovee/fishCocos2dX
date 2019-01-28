# 08 addImageAsync-异步加载图片

## 示例
```c++
void CLoadingScene::onEnter()
{
	CCScene::onEnter();
	m_pBackgroundLayer = BackgroundLayer::create();
	this->addChild(m_pBackgroundLayer);

	CCDirector::getInstance()->getTextureCache()->addImageAsync("atlas.png", CC_CALLBACK_1(CLoadingScene::OnLoadingFinished,this));
}


void CLoadingScene::OnLoadingFinished(CCTexture2D *texture)
{
	CImgManager::GetInstance()->LoadAtlas("atlas.txt", texture);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg",true);


	// 播放背景音乐
	CWelcomeScene *wlScene = CWelcomeScene::create();
	TransitionScene *trans = TransitionScene::create(1, wlScene);
	CCDirector::getInstance()->replaceScene(trans);
}
```

当要加载的图片较大时，可以使用**addImageAsync**函数进行异步加载，第一个参数是要加载的图片，第二个参数是构造的回调函数。当图片加载完成时，将图片以纹理的方式传递给回调函数。