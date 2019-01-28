# cocos内存管理

## 概述
> 内存管理的核心是动态分配的对象必须保证在使用完毕后有效地释放内存。另一方面，过于零散的对象分配回收可能导致堆中的内存碎片化，降低内存的使用效率。因此，我们需要一个合适的机制来缓解这个问题。cocos使用引用计数和垃圾回收的双重机制来进行内存管理。cocos内存管理主要涉及的类有 Ref 、 AutoreleasePool 、 PoolManager 类。 ref 负责引用计数的自增自减，AutoreleasePool 负责将 ref 对象添加到管理池，PoolManager 为管理池，为单例模式，负责整个cocos内存池的管理。

## 版本及说明
- cocos版本：cocos2dx-3.10
- 不对脚本语言的支持及内存泄漏检测进行讨论


## 现有的智能内存管理技术
> 目前，主要有两种实现智能管理内存的技术，一是引用计数，一是垃圾回收。

### 引用计数
> 它是一种很有效的机制，通过给每个对象维护一个引用计数器，记录该对象当前被引用的次数。在需要维持对象生存的程序段的开始和结束分别增加和减少一次引用计数。对于程序员来说，维护引用计数比维护生命周期信息轻松了许多。引用计数解决了对象的生命周期管理问题，但堆碎片化和管理烦琐的问题仍然存在。

### 垃圾回收
> 它通过引入一种自动的内存回收器，试图将程序员从复杂的内存管理任务中完全解放出来。它会自动跟踪每一个对象的所有引用，以便找到所有正在使用的对象，然后释放其余不再需要的对象。垃圾回收器还可以压缩使用中的内存，以缩小堆所需要的工作空间。垃圾回收可以防止内存泄露，有效地使用可用内存。但是，垃圾回收器通常是作为一个单独的低级别的线程运行的，在不可预知的情况下对内存堆中已经死亡的或者长时间没有使用过的对象进行清除和回收，程序员不能手动指派垃圾回收器回收某个对象。回收机制包括分代复制垃圾回收、标记垃圾回收和增量垃圾回收。



## 精彩实现
- Ref 作为大多数cocos的基类，其构造函数被声明为 protected ，保证 Ref 不能直接实例化，只能通过其子类来进行实例化
- 在自增自减之前，都做了大于0的判定，保证被操作的 Ref 对象本身是未被释放的！！
- 声明 Ref 为 AutoreleasePool 的友元，以便访问 AutoreleasePool 类的私有及保护成员
- PoolManager 以单例模式实现，其内维护一个单例的指针及 std::vector<AutoreleasePool*> 的私有对象，所有的 AutoreleasePool 对象都通过 push 和 pop 来管理


## 自动管理的代价
- autorelease 相对于 release ，不立即释放对象，延长了对象的生命周期，占用内存
- autorelease 需要对 PoolManager 和 AutoreleasePool 进行额外的数据存取，增加CPU负担


## 优化内存管理
- 程序段必须成对执行 retain()和 release()或者执行 autorelease()来声明开始和结束对象的引用
- 工厂方法返回前，应通过 autorelease()结束对该对象的引用；
- 对象传值时，应考虑到新旧对象相同的特殊情况——先 retain 再 release
- 尽量使用 release()而不是 autorelease()来释放对象引用，以确保性能最优
- 如果要自动管理，尽量额外声明一个 AutoreleasePool 对象进行管理，而不是完全依赖cocos单例的 PoolManager 


# Ref

## release 和 autorelease
- release 对应  retain，autorelease 对应 new
- 在cocos中，所有 create 的返回都是一个在 autorelease pool 中的对象，因此不需要人为的调用 release 或者 autorelease。如果你自己写了一个类，则该类必须继承于Ref，并且在该类的工厂函数返回前手动滴哦啊用 autorelease 将创建的对象加入 autorelease pool 中。

## 代码注释
```c++
// CCDeprecated.h
typedef Ref CCObject;    // cocos的CCObject实际就是 Ref 类
```

```c++
// CCRef.h
class CC_DLL Ref
{
public:
    void retain();                                 // 保留所有权，将引用计数加一
    void release();                                // 立即释放所有权，引用计数减一，如果减一后引用计数为0，则Ref立即被析构
    Ref* autorelease();                            // 在下次内存池自动清理时将其引用计数减一，其他与 release 一样
    unsigned int getReferenceCount() const;        // 获取引用计数

protected:
    Ref();                                         // 构造函数声明为 protected ，Ref 不能直接实例化，只能通过其子类来进行实例化

public:
    virtual ~Ref();                                // 析构

protected:
    unsigned int _referenceCount;                    // 引用计数，声明为 protected 保证不被外部修改——只能 Ref 类或者其子类可以直接访问
    friend class AutoreleasePool;                    // 声明为 friend ，以便访问 AutoreleasePool 类的私有及保护成员
};
```


```c++
// CCRef.cpp
Ref::Ref(): _referenceCount(1){}                     // 构造函数，引用计数初始化为1
Ref::~Ref(){}                                        // 析构函数，啥也不做

void Ref::retain()                                    // 引用计数加一，自增前保证本身不为0——即保证 Ref 是未被释放对象
{
    CCASSERT(_referenceCount > 0, "reference count should be greater than 0");
    ++_referenceCount;
}

void Ref::release()
{
    CCASSERT(_referenceCount > 0, "reference count should be greater than 0");
    --_referenceCount;

    if (_referenceCount == 0)
    {
        auto poolManager = PoolManager::getInstance();
        if (!poolManager->getCurrentPool()->isClearing() && poolManager->isObjectInPools(this))
        {
            // Trigger an assert if the reference count is 0 but the Ref is still in autorelease pool.
            // This happens when 'autorelease/release' were not used in pairs with 'new/retain'.
            //
            // Wrong usage (1):
            //
            // auto obj = Node::create();   // Ref = 1, but it's an autorelease Ref which means it was in the autorelease pool.
            // obj->autorelease();   // Wrong: If you wish to invoke autorelease several times, you should retain `obj` first.
            //
            // Wrong usage (2):
            //
            // auto obj = Node::create();
            // obj->release();   // Wrong: obj is an autorelease Ref, it will be released when clearing current pool.
            //
            // Correct usage (1):
            //
            // auto obj = Node::create();
            //                     |-   new Node();     // `new` is the pair of the `autorelease` of next line
            //                     |-   autorelease();  // The pair of `new Node`.
            //
            // obj->retain();
            // obj->autorelease();  // This `autorelease` is the pair of `retain` of previous line.
            //
            // Correct usage (2):
            //
            // auto obj = Node::create();
            // obj->retain();
            // obj->release();   // This `release` is the pair of `retain` of previous line.
            CCASSERT(false, "The reference shouldn't be 0 because it is still in autorelease pool.");
        }
        delete this;
    }
}

Ref* Ref::autorelease()    // 将 ref 对象添加到管理池中
{
    PoolManager::getInstance()->getCurrentPool()->addObject(this);
    return this;
}

unsigned int Ref::getReferenceCount() const
{
    return _referenceCount;
}
```

## AutoreleasePool 和 PoolManager
> AutoreleasePool 内管理一个 std::vector<Ref*> 对象，通过 addObject 可以将需要 autorelease 的 ref 对象添加到管理池中。AutoreleasePool 创建后会自动被添加到 PoolManager 的std::vector<AutoreleasePool*> _releasePoolStack 中，可以通过 AutoreleasePool::clear 主动释放，未被主动释放的则在 poolmanager 销毁时在其析构中完释放。


```c++
class CC_DLL AutoreleasePool
{
public:
    std::vector<Ref*> _managedObjectArray;    // 内存池，需要 autorelease 的所有 ref 对象通过 addObject 添加到 _managedObjectArray 中
    void addObject(Ref *object);
    ...
};

class CC_DLL PoolManager
{
public:
    CC_DEPRECATED_ATTRIBUTE static PoolManager* sharedPoolManager() { return getInstance(); }
    static PoolManager* getInstance();

    CC_DEPRECATED_ATTRIBUTE static void purgePoolManager() { destroyInstance(); }
    static void destroyInstance();
	void clear();
    /**
     * Get current auto release pool, there is at least one auto release pool that created by engine.
     * You can create your own auto release pool at demand, which will be put into auto release pool stack.
     */
    AutoreleasePool *getCurrentPool() const;
    bool isObjectInPools(Ref* obj) const;
    friend class AutoreleasePool;
private:
    PoolManager();
    ~PoolManager();
    void push(AutoreleasePool *pool);
    void pop();
    static PoolManager* s_singleInstance;
    std::vector<AutoreleasePool*> _releasePoolStack;
};

AutoreleasePool::AutoreleasePool(const std::string &name)
: _name(name), _isClearing(false)
{
    _managedObjectArray.reserve(150);
    PoolManager::getInstance()->push(this);
}

void AutoreleasePool::clear()
{
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    _isClearing = true;
#endif
    std::vector<Ref*> releasings;
    releasings.swap(_managedObjectArray);
    for (const auto &obj : releasings)
    {
        obj->release();
    }
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    _isClearing = false;
#endif
}

PoolManager* PoolManager::s_singleInstance = nullptr;
PoolManager* PoolManager::getInstance()
{
    if (s_singleInstance == nullptr)
    {
        s_singleInstance = new (std::nothrow) PoolManager();
        // Add the first auto release pool
        new AutoreleasePool("cocos2d autorelease pool");
    }
    return s_singleInstance;
}

```



## cocos内存管理的流程

> CCDirector 包含一个管理引擎逻辑的方法——CCDirector::mainLoop()方法——负责调用定时器，绘图，发送全局通知，并处理内存回收池，cocos的主循环为Application::run()中while循环，该方法按帧调用mainloop，每帧调用一次，而帧间间隔取决于两个因素，一个是预设的帧率，默认为 60 帧每秒；另一个是每帧的计算量大小。mainLoop逻辑如下：

```c++
void DisplayLinkDirector::mainLoop()
{
    if (_purgeDirectorInNextLoop)
    {
        _purgeDirectorInNextLoop = false;
        purgeDirector();
    }
    else if (_restartDirectorInNextLoop)
    {
        _restartDirectorInNextLoop = false;
        restartDirector();
    }
    else if (! _invalid) // 非动画绘制过程进入，先绘制场景，然后释放内存
    {
        drawScene();
     
        // 在这里释放内存
        PoolManager::getInstance()->getCurrentPool()->clear();
    }
}
```



> 当每帧调用mainloop的时候，poolmanager将所有对象的引用计数减一，如果为0则释放该对象。



## cocos内存自动管理的使用



### 自定义类

> 对于自定义类，一般必须提供工厂函数create，该函数使用cocos提供的CREATE_FUNC宏自动进行扩展，加入你有一个HelloWold的场景，那么其实现应该是这样的：

```c++
#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

// 
```

```c++
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // 实现该类的静态工厂函数——create
    CREATE_FUNC(HelloWorld);
};
```



```c++
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
```



> HelloWorld::create() 会new一个对象，并将它添加到aotorelease poll中。我们可以看出



### 内存池的使用



```c++
// 新建一个回收池
CCPoolManager::sharedPoolManager()->push();

// 将n个对象加入新建的回收池中
for(int i=0; i<n; i++) {
    obj_array[i]->autorelease();
}

// 释放新建的回收池，让原回收池接管
CCPoolManager::sharedPoolManager()->pop();
```



### 工厂函数的使用



```c++
CCObject* factoryMethod() {
  CCObject* ret = new CCObject();
  
  // dosomething
    
  // 防止返回前ret被析构，由于加入回收池，直到下一帧才会进行真正的回收，有充足的时间进行 retain 
  ret->autorelease(); 
  return ret;
}
```



### 赋值

> 在C++中，赋值时的深拷贝、浅拷贝永远是一个热门话题，而cocos的代码风格中全部使用指针进行参数传递，解决了拷贝的问题，但是赋值中的自赋值问题如果操作不当还是会存在问题。当给当this->object进行赋值的时候需要先将引用计数减一，然后再retain后进行赋值，看以下函数：

```c++
void SomeClass::setObject(CCObject* other) {
  this->object->release();
  other->retain();
  this->object = other;
}
```

> 如果this->object和other指向同一对象，并且其引用计数为1，那么当你release的时候other已经被释放，再进行赋值的时候other已经是个无效值，为了避免自赋值的问题，需要先retain然后再release，如下：

```c++
void SomeClass::setObject(CCObject* other) {
  other->retain();
  this->object->release();
  this->object = other;
}
```

