#pragma once

#include <string>
#include <functional>
#include <glm/glm.hpp>
#include "IInputManager.h"

class IWindow
{
public:
	IWindow();

	virtual ~IWindow() {}

	virtual void setWindowTitle(const std::string& title) = 0;
	virtual void createWindow(const std::string& title, int width, int height) = 0;
	virtual bool isWindowCreated() const = 0;
	virtual glm::ivec2 getViewSize() const = 0;
	virtual bool windowShouldClose() const = 0;
	virtual void pollEvents() = 0;
	virtual void swapBuffers() = 0;
	virtual void setGLVersion(int major, int minor) = 0;
	virtual bool initGL() = 0;
	virtual void destroy() = 0;
	virtual IInputManager* getInputManager() = 0;

	typedef std::function < void(const glm::ivec2& viewSize) > ViewSizeChangedCallback;
	ViewSizeChangedCallback viewSizeChangedCallback;

};