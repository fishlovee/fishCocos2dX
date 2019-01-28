# 01 CC_CALLBACK 系列函数

```c++
// new callbacks based on C++11
#define CC_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CC_CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define CC_CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define CC_CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)
```

**__VA_ARGS__**
> __VA_ARGS__ 是在C99规范中新增的一个可变参数的宏。实现思想就是宏定义中参数列表的最后一个参数为省略号（也就是三个点）。这样预定义宏_ _VA_ARGS_ _就可以被用在替换部分中，替换省略号所代表的字符串。省略号只能代替最后面的宏参数。
```c
#define PR(...) printf(__VA_ARGS__)
#define W(x,...,y)    //错误 —— 省略号只能用在最后一个参数

int main()
{
    int wt=1,sp=2;
    PR("hello\n");
    PR("weight = %d, shipping = %d",wt,sp);
    return 0;
}

//输出结果：
//hello
//weight = 1, shipping = 2
```

**bind函数**
> bind是C++11引入的成员，可以将bind函数看作一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表.调用bind的一般形式为：auto newCallback = bind(callback,arg_list);其中，newCallback是一个可调用对象，arg_list是可以用逗号分隔的参数列表，至于是啥参数，那就看callback函数里有啥参数啦。也就是说，当我们调用newCallback时，newCallback会调用函数callback,并传递参数arg_list给callback.

**bind示例**
```c++
#include <iostream>
#include <functional>

using namespace std;

int sum(int a, int b, int c)
{
	return a + b + c;
}

int main()
{
	auto fc = std::bind(sum, std::placeholders::_1, std::placeholders::_2,10);   // _1,_2表示调用 fc 时的第一个、第二个参数，10则是其第三个参数的缺省值
	int ret = fc(2, 5);
	cout << ret << endl; // 输出17，相当于调用 sum(2,5,10)

  ret = fc(2,5,15);
  cout << ret << endl; // 输出17，相当于调用 sum(2,5,10)。fc只取前2个参数

  ret = fc(8);         // 输出： “int (int,int,int)”: 不能将参数 2 从“void”转换为“int”
	cout << ret << endl;
	return 0;
}
```


**cocos调用说明**




