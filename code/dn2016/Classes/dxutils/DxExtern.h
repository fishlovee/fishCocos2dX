


std::string op = std::string("open ").append(url);
return system(op.c_str()) != -1;



WCHAR *temp = new WCHAR[url.size() + 1];
int wchars_num = MultiByteToWideChar(CP_UTF8, 0, url.c_str(), url.size() + 1, temp, url.size() + 1);
HINSTANCE r = ShellExecuteW(NULL, L"open", temp, NULL, NULL, SW_SHOWNORMAL);
delete[] temp;
return (size_t)r > 32;


bool Application::openURL(const std::string &url)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WINRT
	auto dispatcher = cocos2d::GLViewImpl::sharedOpenGLView()->getDispatcher();
	dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new DispatchedHandler([url]() {
		auto uri = ref new Windows::Foundation::Uri(PlatformStringFromString(url));
		concurrency::task<bool> launchUriOperation(Windows::System::Launcher::LaunchUriAsync(uri));
	}));
	return true;
#else
	if (m_openURLDelegate)
	{
		m_openURLDelegate(PlatformStringFromString(url));
		return true;
	}
	else
	{
		return false;
	}
#endif
}

bool Application::openURL(const std::string &url)
{
	return openURLJNI(url.c_str());
}