# 动画与按钮

## 创建动画

> cocos2d-x 可以使用 CCArmature 播放一个从 cocos动画编辑器导出的动画。cocos动画编辑器导出一个包含plist和ExportJson的文件，plist包含了导出的原始图片在大图中的位置信息，ExportJson则可以用来创建动画。创建动画时，先使用 **addArmatureFileInfo** 将 json 文件添加到动画管理器类 **CCArmatureDataManager**  中，然后再使用json文件名来创建动画。



```lua
-- 获取管理类实例
local adInstace = CCArmatureDataManager:sharedArmatureDataManager()

-- 添加动画相关json到
adInstance:addArmatureFileInfo("gongxihuode.ExportJson")

-- 创建动画
local rewardAni = CCArmature:create("gongxihuode")

-- 播放指定index的动画
rewardAni:getAnimation():playWithIndex(index)

-- 设置动画事件
-- animation:Armature
-- movementType：0-开始 1-结束 2-循环
-- movementID:currentFrameIndex
local function animationMovementEvent(animation,  movementType, movementID)
	if movementType == 0 then
        -- 开始
    elseif movementType == 1 then
        -- 结束
    else
		-- 循环
    end
end

-- 添加动画的事件
rewardAni:getAnimation():setMovementEventCallFunc(animationMovementEvent)
```



## CCArmature 相关API（简）



### CCArmature

| 函数                         | 说明                                                         |
| ---------------------------- | ------------------------------------------------------------ |
| create(name,parentBone)      | 静态工厂函数，name为动画的json文件名，parentBone为其父节点的骨架。这两个参数都是可选的。 |
| init                         | 成员函数，功能同create                                       |
| getBone(name)                | 通过名称获取骨架，这个名称就是在动画编辑器中显示的名称，或者导出的json文件中bone_data的name字段 |
| removeBone(bone,  recursion) | bone：要移除的骨架，recursion：是否递归移除child bone        |
| getBoneDic                   | 以字典的形式返回当前动画的所有骨架，返回类型 CCDictionary    |
| setAnimation                 | 设置CCArmatureAnimation，两者可以相互转换                    |



### CCBone 

| 函数                                 | 说明                           |
| ------------------------------------ | ------------------------------ |
| create(name)                         | set name to the bone's name    |
| addDisplay(display, index)           | display是一个node，index是索引 |
| removeDisplay(index)                 | 删除指定索引                   |
| changeDisplayWithIndex(index, force) | 按索引进行切换                 |
| changeDisplayWithName(name, force)   | 按名称进行切换                 |
| addChildBone                         | 添加子节点                     |



### ArmatureAnimation

| 函数                     | 说明                                                         |
| ------------------------ | ------------------------------------------------------------ |
| setFrameEventCallFunc    | 设置桢事件                                                   |
| setMovementEventCallFunc | 设置动画事件                                                 |
| pause                    | 暂停                                                         |
| resume                   | 重新开始                                                     |
| stop                     | 停止                                                         |
| gotoAndPause             | Go to specified frame and pause current movement.            |
| gotoAndPlay              | Go to specified frame and play current movement.You need first switch to the movement you want to play, then call this function. |
| playWithNames            | 按照名字播放动画                                             |
| playWithIndexes          | 按照索引播放动画                                             |
| play                     | 播放                                                         |
| getMovementCount         | 获取动作数量                                                 |
| getCurrentMovementID     | 获取动作id                                                   |



### 动画事件



### 替换动画资源



