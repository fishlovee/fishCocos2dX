# 05 cocos资源路径

## 资源路径的设置与获取
> cocos2dX-3.10版本资获取资源路径存在问题！在cocos中的文件操作的类有CCFileUnits和CCDictionary，其中CCFileUnits中有个设置缺省资源的函数，如下：
```c++
class CC_DLL FileUtils
{
public:
    void setDefaultResourceRootPath(const std::string& path);
protected:
    std::string _defaultResRootPath;
};

void FileUtils::setDefaultResourceRootPath(const std::string& path)
{
    _defaultResRootPath = path;
}
```

> 从上面代码可以看出，使用 setDefaultResourceRootPath 可以设置自己的缺省资源路径，而且要是绝对路径。但是cocos2dx-3.10将 _defaultResRootPath 设置为了protected，却没有提供对应的get函数，有点反智了。


## Windows调试路径
> 在Windows中，使用vs2013调试时，其default路径为运行路径，即"工程名\proj.win32\Debug.win32\"，调试时，将对应的资源拷贝到该目录，并将需要资源目录添加到搜索路径即可

**添加搜索路径**
```c++
	FileUtils::getInstance()->addSearchPath("Resources");
	FileUtils::getInstance()->addSearchPath("Resources/fonts");
	FileUtils::getInstance()->addSearchPath("Resources/image");
	FileUtils::getInstance()->addSearchPath("Resources/sounds");
	FileUtils::getInstance()->addSearchPath("Resources/res");
```

**Windows下获取运行路径**
```c++
CString theAppPath,theAppName; 
char Path[MAX_PATH]; 
GetModuleFileName(NULL,Path,MAX_PATH);//得到应用程序的全路径 
```