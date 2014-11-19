#include "Director.h"
#include "SamplesHelper.h"
#include "GlfwOpenGLWindow.h"

static Director* s_sharedInstance = nullptr;

Director* Director::getInstance()
{
	if (!s_sharedInstance)
	{
		s_sharedInstance = new Director();
		s_sharedInstance->init();
	}

	return s_sharedInstance;
}

Director::Director()
	:mWindow(nullptr)
{

}

void Director::init()
{
	SamplesHelper::setupTheCurrentDirectoryToAssets();
}

void Director::setWindow(IWindow* window)
{
	mWindow = window;
}

IWindow* Director::createDefaultWindow()
{
	return new GlfwOpenGLWindow();
}

void Director::mainLoop()
{

}

IWindow* Director::getWindow()
{
	return mWindow;
}
