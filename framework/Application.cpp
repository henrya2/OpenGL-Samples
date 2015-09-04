#include "Application.h"

#include <assert.h>

#include <glfw/glfw3.h>

#include <thread>
#include <chrono>

#include "SamplesHelper.h"
#include "Director.h"
#include "IWindow.h"

Application::Application()
	: mMaxFrame(30)
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

	double frameStartTime = glfwGetTime();
	double frameEndTime = glfwGetTime();
	double frameDuration = 0;

	while (!window->windowShouldClose())
	{
		frameDuration = frameEndTime - frameStartTime;

		double maxFrameInterval = 1.f / mMaxFrame;

		int sleepMS = static_cast<int>((maxFrameInterval - frameDuration) * 1000);

		if (frameDuration < maxFrameInterval && sleepMS - 3 > 0)
		{
			/*
			printf("Frame duration without sleep; %f\n", frameDuration);
			printf("SleepMS: %d\n", sleepMS - 3);
			*/
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepMS - 3));
		}

		frameDuration = glfwGetTime() - frameStartTime;

		frameStartTime = glfwGetTime();

		window->pollEvents();

		onUpdate(frameDuration);

		onPreRender();
		onRender();
		onPostRender();

		director->mainLoop(frameDuration);

		window->swapBuffers();

		frameEndTime = glfwGetTime();
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

void Application::onUpdate(double delta)
{

}
