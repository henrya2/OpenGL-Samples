#include "Application.h"

#include <assert.h>

#include "SamplesHelper.h"
#include "Director.h"
#include "IWindow.h"

Application::Application()
{

}

Application::~Application()
{

}

void Application::run()
{
	if (!onBeforeRun())
		return;

	auto director = Director::getInstance();
	auto window = director->getWindow();

	while (!window->windowShouldClose())
	{
		window->pollEvents();

		onUpdate();

		onPreRender();
		onRender();
		onPostRender();

		director->mainLoop();

		window->swapBuffers();
	}
}

void Application::onPreRender()
{
}

void Application::onRender()
{

}

void Application::onPostRender()
{

}

void Application::onUpdate()
{

}
