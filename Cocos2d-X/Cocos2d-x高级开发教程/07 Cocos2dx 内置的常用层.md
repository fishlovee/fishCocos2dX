# 07 Cocos2dx 内置的常用层

为了方便游戏开发者，Cocos2d-x 内置了 3 种特殊的 CCLayer:
- CCLayerColor：一个单纯的实心色块
- CCLayerGradient：一个色块，但可以设置两种颜色的渐变效果。
- CCMenu：十分常用的游戏菜单。

## CCLayerColor 与 CCLayerGradient
> 这两个层十分简单，都仅仅包含一个色块。不同的是，前者创建的是一个实色色块，而后者创建的是一个渐变色块。

### CCLayerColor
```C++
static CCLayerColor * create(const ccColor4B& color);
static CCLayerColor * create(const ccColor4B& color, GLfloat width, GLfloat height);
bool initWithColor(const ccColor4B& color);
bool initWithColor(const ccColor4B& color, GLfloat width, GLfloat height);
```

### CCLayerGradient
```c++
static CCLayerGradient* create(const ccColor4B& start, const ccColor4B& end);
static CCLayerGradient* create(const ccColor4B& start, const ccColor4B& end,const CCPoint& v);
bool initWithColor(const ccColor4B& start, const ccColor4B& end);
bool initWithColor(const ccColor4B& start, const ccColor4B& end, const CCPoint& v);
```

### 修改色块大小
```C++
void changeWidth(GLfloat w);
void changeHeight(GLfloat h);
void changeWidthAndHeight(GLfloat w ,GLfloat h);
```

## CCMenu
> 菜单使用起来比较麻烦，一般可以使用button代替。



