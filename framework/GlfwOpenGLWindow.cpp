#include "GlfwOpenGLWindow.h"
#include <gl/glew.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <assert.h>

GlfwOpenGLWindow::GlfwOpenGLWindow()
	: mGlfwWindow(nullptr)
{

}

void GlfwOpenGLWindow::setWindowTitle(const std::string& title)
{
	glfwSetWindowTitle(mGlfwWindow, title.c_str());
}

void GlfwOpenGLWindow::createWindow(const std::string& title, int width, int height)
{
	glfwInit();

	mGlfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

bool GlfwOpenGLWindow::isWindowCreated() const
{
	return mGlfwWindow != nullptr;
}

void GlfwOpenGLWindow::setGLVersion(int major, int minor)
{
	glMajorVersion = major;
	glMinorVersion = minor;
}

bool GlfwOpenGLWindow::initGL()
{
	assert(mGlfwWindow);
	glfwMakeContextCurrent(mGlfwWindow);

	// Load the OpenGL functions.
	glewExperimental = true;
	GLenum err = glewInit();
	if (GLEW_OK != err)	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	}

	std::stringstream strStream;

	strStream << "GL_VERSION_" << glMajorVersion << "_" << glMinorVersion;

	std::string versionStr = strStream.str();

	if (!glewIsSupported(versionStr.c_str()))
	{
		std::cerr << "Error: OpenGL version " << glMajorVersion << "." << glMinorVersion << " not supported" << std::endl;
		return false;
	}

	//print information on screen
	std::cout << "\tUsing GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "\tVendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "\tRenderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "\tVersion: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "\tGLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	int width, height;
	glfwGetFramebufferSize(mGlfwWindow, &width, &height);

	glViewport(0, 0, width, height);

	return true;
}

void GlfwOpenGLWindow::destroy()
{
	glfwDestroyWindow(mGlfwWindow);
}

IInputManager* GlfwOpenGLWindow::GetInputManager()
{
	return mInputManager;
}

bool GlfwOpenGLWindow::windowShouldClose() const
{
	return glfwWindowShouldClose(mGlfwWindow);
}

void GlfwOpenGLWindow::pollEvents()
{
	glfwPollEvents();
}

void GlfwOpenGLWindow::swapBuffers()
{
	glfwSwapBuffers(mGlfwWindow);
}

glm::ivec2 GlfwOpenGLWindow::getViewSize() const
{
	glm::ivec2 viewSize;
	glfwGetFramebufferSize(mGlfwWindow, &viewSize.x, &viewSize.y);

	return viewSize;
}
