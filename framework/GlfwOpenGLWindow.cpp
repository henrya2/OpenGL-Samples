#include "GlfwOpenGLWindow.h"
#include "GlfwOpenGLInputManager.h"
#include "EventTypeDefines.h"
#include <gl/glew.h>
#include <glfw/glfw3.h>
#include "AntTweakBar.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <assert.h>
#include <map>
#include <unordered_map>

typedef std::map<GLFWwindow*, GlfwOpenGLWindow*> GlfwWindowMapT;
static GlfwWindowMapT allGlfwWindows;

static void RegisterGlfwWindows(GlfwOpenGLWindow* glfwWindow)
{
	allGlfwWindows[glfwWindow->getInternalGlfwWindow()] = glfwWindow;
}

static void unRegisterGlfwWindows(GlfwOpenGLWindow* glfwWindow)
{
	allGlfwWindows.erase(glfwWindow->getInternalGlfwWindow());
}

////////////////////////////////////////////////////

struct keyCodeItem
{
	int glfwKeyCode;
	KeyCode keyCode;
};

static std::unordered_map<int, KeyCode> g_keyCodeMap;

static keyCodeItem g_keyCodeStructArray[] = {
	/* The unknown key */
	{ GLFW_KEY_UNKNOWN, KeyCode::KEY_NONE },

	/* Printable keys */
	{ GLFW_KEY_SPACE, KeyCode::KEY_SPACE },
	{ GLFW_KEY_APOSTROPHE, KeyCode::KEY_APOSTROPHE },
	{ GLFW_KEY_COMMA, KeyCode::KEY_COMMA },
	{ GLFW_KEY_MINUS, KeyCode::KEY_MINUS },
	{ GLFW_KEY_PERIOD, KeyCode::KEY_PERIOD },
	{ GLFW_KEY_SLASH, KeyCode::KEY_SLASH },
	{ GLFW_KEY_0, KeyCode::KEY_0 },
	{ GLFW_KEY_1, KeyCode::KEY_1 },
	{ GLFW_KEY_2, KeyCode::KEY_2 },
	{ GLFW_KEY_3, KeyCode::KEY_3 },
	{ GLFW_KEY_4, KeyCode::KEY_4 },
	{ GLFW_KEY_5, KeyCode::KEY_5 },
	{ GLFW_KEY_6, KeyCode::KEY_6 },
	{ GLFW_KEY_7, KeyCode::KEY_7 },
	{ GLFW_KEY_8, KeyCode::KEY_8 },
	{ GLFW_KEY_9, KeyCode::KEY_9 },
	{ GLFW_KEY_SEMICOLON, KeyCode::KEY_SEMICOLON },
	{ GLFW_KEY_EQUAL, KeyCode::KEY_EQUAL },
	{ GLFW_KEY_A, KeyCode::KEY_A },
	{ GLFW_KEY_B, KeyCode::KEY_B },
	{ GLFW_KEY_C, KeyCode::KEY_C },
	{ GLFW_KEY_D, KeyCode::KEY_D },
	{ GLFW_KEY_E, KeyCode::KEY_E },
	{ GLFW_KEY_F, KeyCode::KEY_F },
	{ GLFW_KEY_G, KeyCode::KEY_G },
	{ GLFW_KEY_H, KeyCode::KEY_H },
	{ GLFW_KEY_I, KeyCode::KEY_I },
	{ GLFW_KEY_J, KeyCode::KEY_J },
	{ GLFW_KEY_K, KeyCode::KEY_K },
	{ GLFW_KEY_L, KeyCode::KEY_L },
	{ GLFW_KEY_M, KeyCode::KEY_M },
	{ GLFW_KEY_N, KeyCode::KEY_N },
	{ GLFW_KEY_O, KeyCode::KEY_O },
	{ GLFW_KEY_P, KeyCode::KEY_P },
	{ GLFW_KEY_Q, KeyCode::KEY_Q },
	{ GLFW_KEY_R, KeyCode::KEY_R },
	{ GLFW_KEY_S, KeyCode::KEY_S },
	{ GLFW_KEY_T, KeyCode::KEY_T },
	{ GLFW_KEY_U, KeyCode::KEY_U },
	{ GLFW_KEY_V, KeyCode::KEY_V },
	{ GLFW_KEY_W, KeyCode::KEY_W },
	{ GLFW_KEY_X, KeyCode::KEY_X },
	{ GLFW_KEY_Y, KeyCode::KEY_Y },
	{ GLFW_KEY_Z, KeyCode::KEY_Z },
	{ GLFW_KEY_LEFT_BRACKET, KeyCode::KEY_LEFT_BRACKET },
	{ GLFW_KEY_BACKSLASH, KeyCode::KEY_BACK_SLASH },
	{ GLFW_KEY_RIGHT_BRACKET, KeyCode::KEY_RIGHT_BRACKET },
	{ GLFW_KEY_GRAVE_ACCENT, KeyCode::KEY_GRAVE },
	{ GLFW_KEY_WORLD_1, KeyCode::KEY_GRAVE },
	{ GLFW_KEY_WORLD_2, KeyCode::KEY_NONE },

	/* Function keys */
	{ GLFW_KEY_ESCAPE, KeyCode::KEY_ESCAPE },
	{ GLFW_KEY_ENTER, KeyCode::KEY_KP_ENTER },
	{ GLFW_KEY_TAB, KeyCode::KEY_TAB },
	{ GLFW_KEY_BACKSPACE, KeyCode::KEY_BACKSPACE },
	{ GLFW_KEY_INSERT, KeyCode::KEY_INSERT },
	{ GLFW_KEY_DELETE, KeyCode::KEY_DELETE },
	{ GLFW_KEY_RIGHT, KeyCode::KEY_RIGHT_ARROW },
	{ GLFW_KEY_LEFT, KeyCode::KEY_LEFT_ARROW },
	{ GLFW_KEY_DOWN, KeyCode::KEY_DOWN_ARROW },
	{ GLFW_KEY_UP, KeyCode::KEY_UP_ARROW },
	{ GLFW_KEY_PAGE_UP, KeyCode::KEY_KP_PG_UP },
	{ GLFW_KEY_PAGE_DOWN, KeyCode::KEY_KP_PG_DOWN },
	{ GLFW_KEY_HOME, KeyCode::KEY_KP_HOME },
	{ GLFW_KEY_END, KeyCode::KEY_END },
	{ GLFW_KEY_CAPS_LOCK, KeyCode::KEY_CAPS_LOCK },
	{ GLFW_KEY_SCROLL_LOCK, KeyCode::KEY_SCROLL_LOCK },
	{ GLFW_KEY_NUM_LOCK, KeyCode::KEY_NUM_LOCK },
	{ GLFW_KEY_PRINT_SCREEN, KeyCode::KEY_PRINT },
	{ GLFW_KEY_PAUSE, KeyCode::KEY_PAUSE },
	{ GLFW_KEY_F1, KeyCode::KEY_F1 },
	{ GLFW_KEY_F2, KeyCode::KEY_F2 },
	{ GLFW_KEY_F3, KeyCode::KEY_F3 },
	{ GLFW_KEY_F4, KeyCode::KEY_F4 },
	{ GLFW_KEY_F5, KeyCode::KEY_F5 },
	{ GLFW_KEY_F6, KeyCode::KEY_F6 },
	{ GLFW_KEY_F7, KeyCode::KEY_F7 },
	{ GLFW_KEY_F8, KeyCode::KEY_F8 },
	{ GLFW_KEY_F9, KeyCode::KEY_F9 },
	{ GLFW_KEY_F10, KeyCode::KEY_F10 },
	{ GLFW_KEY_F11, KeyCode::KEY_F11 },
	{ GLFW_KEY_F12, KeyCode::KEY_F12 },
	{ GLFW_KEY_F13, KeyCode::KEY_NONE },
	{ GLFW_KEY_F14, KeyCode::KEY_NONE },
	{ GLFW_KEY_F15, KeyCode::KEY_NONE },
	{ GLFW_KEY_F16, KeyCode::KEY_NONE },
	{ GLFW_KEY_F17, KeyCode::KEY_NONE },
	{ GLFW_KEY_F18, KeyCode::KEY_NONE },
	{ GLFW_KEY_F19, KeyCode::KEY_NONE },
	{ GLFW_KEY_F20, KeyCode::KEY_NONE },
	{ GLFW_KEY_F21, KeyCode::KEY_NONE },
	{ GLFW_KEY_F22, KeyCode::KEY_NONE },
	{ GLFW_KEY_F23, KeyCode::KEY_NONE },
	{ GLFW_KEY_F24, KeyCode::KEY_NONE },
	{ GLFW_KEY_F25, KeyCode::KEY_NONE },
	{ GLFW_KEY_KP_0, KeyCode::KEY_0 },
	{ GLFW_KEY_KP_1, KeyCode::KEY_1 },
	{ GLFW_KEY_KP_2, KeyCode::KEY_2 },
	{ GLFW_KEY_KP_3, KeyCode::KEY_3 },
	{ GLFW_KEY_KP_4, KeyCode::KEY_4 },
	{ GLFW_KEY_KP_5, KeyCode::KEY_5 },
	{ GLFW_KEY_KP_6, KeyCode::KEY_6 },
	{ GLFW_KEY_KP_7, KeyCode::KEY_7 },
	{ GLFW_KEY_KP_8, KeyCode::KEY_8 },
	{ GLFW_KEY_KP_9, KeyCode::KEY_9 },
	{ GLFW_KEY_KP_DECIMAL, KeyCode::KEY_PERIOD },
	{ GLFW_KEY_KP_DIVIDE, KeyCode::KEY_KP_DIVIDE },
	{ GLFW_KEY_KP_MULTIPLY, KeyCode::KEY_KP_MULTIPLY },
	{ GLFW_KEY_KP_SUBTRACT, KeyCode::KEY_KP_MINUS },
	{ GLFW_KEY_KP_ADD, KeyCode::KEY_KP_PLUS },
	{ GLFW_KEY_KP_ENTER, KeyCode::KEY_KP_ENTER },
	{ GLFW_KEY_KP_EQUAL, KeyCode::KEY_EQUAL },
	{ GLFW_KEY_LEFT_SHIFT, KeyCode::KEY_SHIFT },
	{ GLFW_KEY_LEFT_CONTROL, KeyCode::KEY_CTRL },
	{ GLFW_KEY_LEFT_ALT, KeyCode::KEY_ALT },
	{ GLFW_KEY_LEFT_SUPER, KeyCode::KEY_HYPER },
	{ GLFW_KEY_RIGHT_SHIFT, KeyCode::KEY_SHIFT },
	{ GLFW_KEY_RIGHT_CONTROL, KeyCode::KEY_CTRL },
	{ GLFW_KEY_RIGHT_ALT, KeyCode::KEY_ALT },
	{ GLFW_KEY_RIGHT_SUPER, KeyCode::KEY_HYPER },
	{ GLFW_KEY_MENU, KeyCode::KEY_MENU },
	{ GLFW_KEY_LAST, KeyCode::KEY_NONE }
};

static void SizeChangedCallback(GLFWwindow* window, int width, int height)
{
	GlfwOpenGLWindow* glfwOpenGLWindow = allGlfwWindows[window];
	glfwOpenGLWindow->notifyViewSizeChanged(width, height);

	TwWindowSize(width, height);
}

static void MousePositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	GlfwOpenGLWindow* glfwOpenGLWindow = allGlfwWindows[window];
	GlfwOpenGLInputManager* openGLInputManager = (GlfwOpenGLInputManager*)glfwOpenGLWindow->getInputManager();

	if (openGLInputManager->getRelativeMouseMode() || !TwEventMousePosGLFW((int)xPos, (int)yPos))
	{
		openGLInputManager->processMousePosition(xPos, yPos);
	}
}

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int modify)
{
	GlfwOpenGLWindow* glfwOpenGLWindow = allGlfwWindows[window];
	GlfwOpenGLInputManager* openGLInputManager = (GlfwOpenGLInputManager*)glfwOpenGLWindow->getInputManager();

	if (openGLInputManager->getRelativeMouseMode() || !TwEventMouseButtonGLFW(button, action))
	{
		openGLInputManager->processMouseButton(button, action, modify);
	}
}

static void ScrollCallback(GLFWwindow* window, double xPosition, double yPosition)
{
	GlfwOpenGLWindow* glfwOpenGLWindow = allGlfwWindows[window];
	GlfwOpenGLInputManager* openGLInputManager = (GlfwOpenGLInputManager*)glfwOpenGLWindow->getInputManager();

	if (openGLInputManager->getRelativeMouseMode() || !TwEventMouseWheelGLFW(yPosition))
	{
		openGLInputManager->processMouseWheel(static_cast<int>(yPosition));
	}
}

static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GlfwOpenGLWindow* glfwOpenGLWindow = allGlfwWindows[window];
	GlfwOpenGLInputManager* openGLInputManager = (GlfwOpenGLInputManager*)glfwOpenGLWindow->getInputManager();

	if (openGLInputManager->getRelativeMouseMode() || !TwEventKeyGLFW(key, action))
	{
		openGLInputManager->processKeyboard(key, scancode, action, mods);
	}
}

static void CharCallback(GLFWwindow* window, unsigned int charCode)
{
	GlfwOpenGLWindow* glfwOpenGLWindow = allGlfwWindows[window];
	GlfwOpenGLInputManager* openGLInputManager = (GlfwOpenGLInputManager*)glfwOpenGLWindow->getInputManager();

	if (openGLInputManager->getRelativeMouseMode() || !TwEventCharGLFW(charCode, GLFW_PRESS))
	{
		openGLInputManager->processChar(charCode);
	}
}

GlfwOpenGLWindow::GlfwOpenGLWindow()
	: mGlfwWindow(nullptr)
	, mInputManager(new GlfwOpenGLInputManager(this))
	, mVSync(false)
{
	g_keyCodeMap.clear();
	for (auto& item : g_keyCodeStructArray)
	{
		g_keyCodeMap[item.glfwKeyCode] = item.keyCode;
	}
}

void GlfwOpenGLWindow::setWindowTitle(const std::string& title)
{
	glfwSetWindowTitle(mGlfwWindow, title.c_str());
}

void GlfwOpenGLWindow::createWindow(const std::string& title, int width, int height)
{
	glfwInit();

	// Use core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVersion);
	//glfwWindowHint(GLFW_CONTEXT_REVISION, 0);

	mGlfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	RegisterGlfwWindows(this);

	glfwSetWindowSizeCallback(mGlfwWindow, &SizeChangedCallback);
	glfwSetMouseButtonCallback(mGlfwWindow, &MouseButtonCallback);
	glfwSetCursorPosCallback(mGlfwWindow, &MousePositionCallback);
	glfwSetScrollCallback(mGlfwWindow, &ScrollCallback);
	glfwSetKeyCallback(mGlfwWindow, &KeyboardCallback);
	glfwSetCharCallback(mGlfwWindow, &CharCallback);
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

	resizeOpenGLViewport(width, height);

	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);

	TwInit(TW_OPENGL_CORE, nullptr);
	TwDefine(" GLOBAL fontSize=3 help='This example illustrates the definition of custom structure type as well as many other features.' ");

	TwWindowSize(width, height);

	return true;
}

void GlfwOpenGLWindow::destroy()
{
	unRegisterGlfwWindows(this);
	//glfwDestroyWindow(mGlfwWindow);

	TwTerminate();
	glfwTerminate();
}

IInputManager* GlfwOpenGLWindow::getInputManager()
{
	return mInputManager;
}

bool GlfwOpenGLWindow::windowShouldClose() const
{
	return glfwWindowShouldClose(mGlfwWindow) != 0;
}

void GlfwOpenGLWindow::pollEvents()
{
	mInputManager->clearEventStates();
	glfwPollEvents();
}

void GlfwOpenGLWindow::endDrawing()
{
	TwDraw();
}

void GlfwOpenGLWindow::swapBuffers()
{
	glfwSwapBuffers(mGlfwWindow);
}

void GlfwOpenGLWindow::resizeOpenGLViewport(int width, int height)
{
	glViewport(0, 0, width, height);
	mWidth = width;
	MHeight = height;
}

glm::ivec2 GlfwOpenGLWindow::getViewSize() const
{
	glm::ivec2 viewSize;
	glfwGetFramebufferSize(mGlfwWindow, &viewSize.x, &viewSize.y);

	return viewSize;
}

void GlfwOpenGLWindow::notifyViewSizeChanged(int width, int height)
{
	if (viewSizeChangedCallback)
		viewSizeChangedCallback(glm::ivec2(width, height));

	resizeOpenGLViewport(width, height);
}

void GlfwOpenGLWindow::setVSync(bool vsync)
{
	mVSync = vsync;
	glfwSwapInterval(vsync ? 1 : 0);
}

bool GlfwOpenGLWindow::isVSync() const
{
	return mVSync;
}
