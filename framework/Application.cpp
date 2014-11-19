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
		onPreRender();
		onRender();
		onPostRender();

		window->swapBuffers();
		window->pollEvents();
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