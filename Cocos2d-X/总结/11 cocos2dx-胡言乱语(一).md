# 11 cocos2dx-胡言乱语(一)

## 场景和layer
> 看cocos自动生成的helloworld类，它是一个继承于 Layer 的类，提供了 createScene 工厂函数来返回一个包含了layer的场景。但是实际工程中，很多时候并不是使用的继承于 CCLayer 的类并提供 createScene 工厂方法来创建场景实例，而是提供继承于 CCSene 的类，然后再在类的 init 函数中做相关的初始化。

截图如下：
![createScene工厂方法和init函数](_v_images/_createscen_1532338583_25617.png)

> 上面的 CWelcomeScene 类继承于 Scene 类，在该类的 init 函数中，创建一个继承于 Layer 的类 CWelcomeLayer 的实例，然后添加到该场景中。

## 为什么使用this指针
> 看了很多cocos2d-x工程代码，发现即使在该类的成员函数中访问该类的成员变量，也很喜欢使用 this 指针来指向。感觉很奇怪。概念中，在子类中调用一个函数，如果子类重写了父类的func函数的实现，那么缺省就调用子类的实现，除非前面使用了 base::func，为什么不管是访问成员变量还是调用成员函数都要添加个 this 指针？奇也怪哉。

**后续思考**
> 观察发现，cocos的代码中变量的命名都没有前缀，不像平时使用C++的时候，成员变量的前缀为 m_ 如果是 int 则可能命名为 m_nXXX 或者 m_iXXX，如果是结构体则是 m_stXXX等，可以很好的从变量名称区分该变量是局部变量还是成员变量，而cocos中的变量却不能直观的进行区分，所以对于成员变量，书写时都带有 this 指针。另外，cocos2d-x继承于cocos-iphone，所以在语法、命名规则上很大部分也进行也继承，而且还定义了很多诡异的宏，展开后就是没有前缀的成员变量，所以，为了命名的统一以及方便他人阅读代码，使用的时候还是随大流，对于成员变量前面还是加个this指针比较好。

![cocos中使用this指针示例](_v_images/_cocos中使用th_1532338976_4296.png)

## cocos中的单例模式与工厂函数
 具体可以参考 "cocos2d-x/cocos源码阅读/cocos内存管理.md"



## setRelativeSearchPaths



```c++
void CCFileUtils::setRelativeSearchPaths(const std::vector<std::string>& searchPaths)
{
    m_fullPathCache.clear();
    m_relativeSearchPathArray.clear();
    for (std::vector<std::string>::const_iterator iter = searchPaths.begin(); iter != searchPaths.end(); ++iter)
    {
        if (iter->length() > 0 && (*iter)[iter->length()-1] != '/') // 为什么是这样的？
        {
			m_relativeSearchPathArray.push_back(*iter + "/");
        }
		else
		{
			m_relativeSearchPathArray.push_back(*iter);
		}
    }
}
```

>  在win32环境中，如果一个 *Iter 为 “D:\android\workspace\jjgame\proj.win32\Debug.win32\Hall\”,那么最终的结果将是 “D:\android\workspace\jjgame\proj.win32\Debug.win32\Hall\/”，为什么这样？？？







