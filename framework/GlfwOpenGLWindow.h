#pragma once

#include "IWindow.h"
#include "IInputManager.h"

struct GLFWwindow;

class GlfwInputManager : public IInputManager
{

};

class GlfwOpenGLWindow : public IWindow
{
public:
	GlfwOpenGLWindow();

	virtual void setWindowTitle(const std::string& title);

	virtual void createWindow(const std::string& title, int width, int height);

	virtual bool isWindowCreated() const;

	virtual bool windowShouldClose() const;

	virtual glm::ivec2 getViewSize() const;

	virtual void setGLVersion(int major, int minor);

	virtual void pollEvents();

	virtual void swapBuffers();

	virtual bool initGL();

	virtual void destroy();

	virtual IInputManager* GetInputManager();

private:
	GLFWwindow* mGlfwWindow;
	GlfwInputManager* mInputManager;

	int glMajorVersion;
	int glMinorVersion;
};