#include "Director.h"
#include "Scene.h"
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
	: mWindow(nullptr)
	, mCurrentScene(nullptr)
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
	if (mCurrentScene)
	{
		mCurrentScene->internalUpdate();

		mCurrentScene->internalLateUpdate();

		mCurrentScene->internalLastUpdate();
	}
}

IWindow* Director::getWindow()
{
	return mWindow;
}

IInputManager* Director::getInputManager()
{
	if (mWindow)
	{
		return mWindow->getInputManager();
	}

	return nullptr;
}

void Director::runWithScene(Scene* scene)
{
	if (scene == mCurrentScene)
		return;

	if (mCurrentScene)
	{
		mCurrentScene->onLeave();
	}

	scene->onEnter();
	mCurrentScene = scene;
}

Scene* Director::getRunningScene()
{
	return mCurrentScene;
}
