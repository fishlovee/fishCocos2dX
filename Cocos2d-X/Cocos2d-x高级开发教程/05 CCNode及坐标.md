# 05 CCNode及坐标

> CCNode 定义了一个可绘制对象的通用特性，包括位置、缩放、是否可见、旋转角度等。节点的最基本的功能包括：

- 包含其他 CCNode 对象；
- 接受各种事件与回调函数，如定时器事件；
- 运行动作。

## 坐标系与绘图属性
### Cocos2d- -x x 中的坐标系

#### 绘图坐标系
> 它是最常见的坐标系，与 OpenGL 采用的坐标系相同，以左下角为原点，向右为 x 轴正方向，向上为 y 轴正方向。在 Cocos2d-x 中，一切绘图相关的操作都使用绘图坐标系，如游戏元素中的 Position 和 AnchorPoint等属性。

#### 纹理坐标系
> 纹理坐标系以左上角为原点，向右为 x 轴正方向，向下为 y 轴正方向。在 Cocos2d-x 中，只有从纹理中截取部分矩形时才使用这个坐标系，如 CCSprite 的 TextureRect 属性。

### 绘图属性

| 属性      |   说明 |
| :-------- | :--------|
| CCRect ContentSize  | 获取或设置此节点的内容大小。对于精灵来说，ContentSize 是它的纹理显示部分的大小；对于层或场景等全屏的大型节点来说，ContentSize 则是屏幕大小。 | 
| CCPoint AnchorPoint| AnchorPoint 用于设置一个锚点，以便精确地控制节点的位置和变换。 |
| CCPoint Position|  用于设置节点的位置。由于 Position 指的是锚点在父节点中的坐标值，节点显示的位置通常与锚点有关。每个节点的位置实际上都是自身锚点相对于父亲左下角的位置。 |
|IgnoreAnchorPointForPosition 属性|为 true，此时引擎会认为AnchorPoint 永远为(0,0)|
|float Rotation|获取或设置节点的旋转角度。节点以自己的锚点为中心顺时针旋转一定量，单位是角度。|
|float Scale|Scale 用于获取或设置节点的缩放比例。节点以锚点为中心缩放该比例。|
|bool Visible|获取或设置节点的可见性。当 Visible 为 true 时，节点会被显示，反之节点不会被显示。在节点不被显示的时候，也不会被调用绘图方法（visit 与 draw）。|
|float SkewX/SkewY|获取或设置斜切角度。节点以锚点为中心，平行 x 轴或 y 轴方向作一定角度的变形。|
|int Tag|获取或设置节点的标号。Tag 的作用类似于标识符，以便快速地从节点的所有子节点中找出所需节点。Tag 可以用于定位子节点，因此添加到同一节点的所有 CCNode 之中，不能有两个节点的 Tag 相同，否则就给定位带来了麻烦。|
|void* UserData|获取或设置与节点相关的额外信息。UserData 为 void*类型，我们可以利用这个属性来保存任何数据。|





