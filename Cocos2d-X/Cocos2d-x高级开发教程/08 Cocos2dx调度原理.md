# 08 Cocos2dx调度原理

Cocos2d 的一大特色就是提供了事件驱动的游戏框架，引擎会在合适的时候调用事件处理函数，我们只需要在函数中添加对各种游戏事件的处理，就可以完成一个完整的游戏了。Cocos2d 的调度原理管理着所有的事件。

## 游戏主循环

 CCDirector 包含一个管理引擎逻辑的方法——CCDirector::mainLoop()方法——负责调用定时器，绘图，发送全局通知，并处理内存回收池。该方法按帧调用，每帧调用一次，而帧间间隔取决于两个因素，一个是预设的帧率，默认为 60 帧每秒；另一个是每帧的计算量大小。
