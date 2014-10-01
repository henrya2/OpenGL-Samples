#include "Application.h"
#include <gl\glew.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <stdio.h>
#include <assert.h>

#include "SamplesHelper.h"

class Application::ApplicationImpl
{
public:
	ApplicationImpl();
	~ApplicationImpl();

	GLFWwindow* mWindow;

	bool shouldClose;

	int glMajorVersion;
	int glMinorVersion;
};

Application::ApplicationImpl::ApplicationImpl()
	: mWindow(nullptr)
	, shouldClose(false)
{

}

Application::ApplicationImpl::~ApplicationImpl()
{

}

Application::Application()
{
	mImpl = new ApplicationImpl();
}

Application::~Application()
{
	destroy();
	delete mImpl;
}

void Application::init()
{
	SamplesHelper::setupTheCurrentDirectoryToAssets();

	if (!glfwInit()) 
	{
		exit(EXIT_FAILURE);
	}
}

void Application::createWindow(const std::string& title, int width, int height)
{
	mImpl->mWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
}

bool Application::isWindowCreated() const
{
	return mImpl->mWindow != nullptr;
}

void Application::setGLVersion(int major, int minor)
{
	mImpl->glMajorVersion = major;
	mImpl->glMinorVersion = minor;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::setWindowTitle(const std::string& title)
{
	assert(mImpl);
	assert(mImpl->mWindow);
	glfwSetWindowTitle(mImpl->mWindow, title.c_str());
}

#ifdef WIN32
#define snprintf _snprintf
#endif

bool Application::initGL()
{
	assert(mImpl);
	assert(mImpl->mWindow);
	glfwMakeContextCurrent(mImpl->mWindow);

	// Load the OpenGL functions.
	glewExperimental = true;
	GLenum err = glewInit();
	if (GLEW_OK != err)	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	}

	char versionStr[128];
	snprintf(versionStr, 127, "GL_VERSION_%d_%d", mImpl->glMajorVersion, mImpl->glMinorVersion);

	if (!glewIsSupported(versionStr))
	{
		std::cerr << "Error: OpenGL version " << mImpl->glMajorVersion << "." << mImpl->glMinorVersion << " not supported" << std::endl;
		return false;
	}

	//print information on screen
	std::cout << "\tUsing GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "\tVendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "\tRenderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "\tVersion: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "\tGLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	int width, height;
	glfwGetFramebufferSize(mImpl->mWindow, &width, &height);

	glViewport(0, 0, width, height);

	return true;
}

void Application::destroy()
{
	assert(mImpl);
	assert(mImpl->mWindow);

	glfwDestroyWindow(mImpl->mWindow);
}

void Application::run()
{
	onBeforeRun();
	while (!glfwWindowShouldClose(mImpl->mWindow))
	{
		onPreRender();
		onRender();
		onPostRender();

		glfwPollEvents();
	}

shouldEnd:
	mImpl->shouldClose = true;
}

void Application::onPreRender()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::onRender()
{

}

void Application::onPostRender()
{
	glfwSwapBuffers(mImpl->mWindow);
}

void Application::setVerticalSync(bool sync)
{
	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	glfwSwapInterval(sync ? 1 : 0);
}
