# 03 Cocos2d-x代码风格
>  Cocos2d-x 源自于 Cocos2d-iPhone，Cocos2d-x 也就沿袭了 Objective-C 的代码风格。这么做的主要原因如下：出于对 Cocos2d-iPhone 程序员习惯的照顾，以及对该引擎的尊敬；方便不同语言下 Cocos2d游戏的移植；为了实现 Objective-C 风格的内存管理，要求引擎采用特殊的命名规范。

## 命名空间与类名称
- Cocos2d-x 拥有一个包含其他所有头文件的文件"cocos2d.h"。通常，我们只需要在使用时包含这个头文件，就可以使用引擎的全部功能了。
- Cocos2d-x 的类都放置于 cocos2d 命名空间下。在游戏中，使用引擎提供的宏 USING_NS_CC 来引用 cocos2d 命名空间即可。

## 构造函数与初始化
> 在 Cocos2d-x 中创建对象的方法与 C++开发者的习惯迥乎不同。Cocos2d-x 不使用传统的值类型，所有的对象都创建在堆上，然后通过指针引用。

**创建 Cocos2d-x 对象通常有两种方法**
- 第一种是首先使用 new 操作符创造一个未初始化的对象，然后调用 init 系列方法来初始化；
- 第二种是使用静态的工厂方法直接创建一个对象。

**new初始化的例子**
```C++
CCSprite* sprite1 = new CCSprite();
sprite1->initWithFile("HelloWorld.png");
```

**工厂函数的例子**
```C++
CCSprite* sprite2 = CCSprite::spriteWithFile("HelloWorld.png");    // 旧版本的
CCSprite* sprite3 = CCSprite::create("HelloWorld.png");            // cocos2.0之后版本的，两者等效
```

**两种方法的区别**
> 主要区别在于内存管理方面。使用构造函数创建的对象，它的所有权已经属于调用者了，使用工厂方法创建的对象的所有权却并不属于调用者，因此，使用构造函数创建的对象需要调用者负责释放，而使用工厂方法创建的对象则不需要。

**初始化函数**

> cocos的初始化函数需要先调用基类的初始化，然后再进行自身的初始化。
```C++
bool CCHelloWorld::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    // 在这里进行初始化
    return true;
}
```


## cocos内存管理

> 前面提到cocos的对象有2种初始化方法，其中很重要的一点区别就是所有权的问题——也就是创建的对象属于创建者还是属于cocos对象池管理器，如果使用new方法创建的对象属于创建者自身，如果使用类的工厂函数创建的对象所有权属于cocos的对象池管理器。new出来的对象需要自己进行内存管理，在合适的地方进行释放，使用工厂函数创建的对象则由cocos自动管理。具体的cocos内存管理细节，参见《cocos源码阅读/cocos内存管理.md》

