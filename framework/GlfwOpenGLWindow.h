#pragma once

#include "IWindow.h"
#include "IInputManager.h"

struct GLFWwindow;
class GlfwOpenGLInputManager;

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

	virtual void endDrawing();

	virtual void swapBuffers();

	virtual void resizeOpenGLViewport(int width, int height);

	virtual bool initGL();

	virtual void destroy();

	virtual IInputManager* getInputManager();

	GLFWwindow* getInternalGlfwWindow() const { return mGlfwWindow;  }
	void notifyViewSizeChanged(int width, int height);

	virtual void setVSync(bool vsync);

	virtual bool isVSync() const;

private:
	GLFWwindow* mGlfwWindow;
	GlfwOpenGLInputManager* mInputManager;

	int glMajorVersion;
	int glMinorVersion;

	int mWidth;

	int MHeight;

	bool mVSync;
};