#include "GlfwOpenGLWindow.h"
#include "GlfwOpenGLInputManager.h"
#include "EventTypeDefines.h"

#include <unordered_map>
#include <glfw/glfw3.h>

struct keyCodeItem
{
	int glfwKeyCode;
	KeyCode keyCode;
};

static std::unordered_map<KeyCode, int> g_KeyCode2RawGlfwCodeMap;

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

GlfwOpenGLInputManager::GlfwOpenGLInputManager(GlfwOpenGLWindow* openGLWindow)
	: mGlfwOpenGLWindow(openGLWindow)
	, mNextCallbackId(1)
{
	for (auto& keyItem : g_keyCodeStructArray)
	{
		g_KeyCode2RawGlfwCodeMap[keyItem.keyCode] = keyItem.glfwKeyCode;
	}

	glfwGetCursorPos(mGlfwOpenGLWindow->getInternalGlfwWindow(), &_oldXMousePos, &_oldYMousePos);
	_deltaXPos = 0;
	_deltaYPos = 0;
}

bool GlfwOpenGLInputManager::isKeyPressed(KeyCode keyCode) const
{
	return glfwGetKey(mGlfwOpenGLWindow->getInternalGlfwWindow(), g_KeyCode2RawGlfwCodeMap[keyCode]) == GLFW_PRESS;
}

void GlfwOpenGLInputManager::notifyEvent(const Event& event)
{
	switch (event.getType())
	{
	case Event::Type::KEYBOARD:
		{
			const EventKeyboard& eventKeyboard = (const EventKeyboard&)event;
			mKeysMap[static_cast<int>(eventKeyboard.mKeyCode)] = eventKeyboard.mIsPressed;
		}
		break;
	}

	for (auto& eventCallback : mEventCallbacks)
	{
		eventCallback.second(event);
	}
}

void GlfwOpenGLInputManager::clearEventStates()
{

}

double GlfwOpenGLInputManager::getMousePosX() const
{
	double posX, posY;
	glfwGetCursorPos(mGlfwOpenGLWindow->getInternalGlfwWindow(), &posX, &posY);

	return posX;
}

double GlfwOpenGLInputManager::getMousePosY() const
{
	double posX, posY;
	glfwGetCursorPos(mGlfwOpenGLWindow->getInternalGlfwWindow(), &posX, &posY);

	return posY;
}

std::tuple<double, double> GlfwOpenGLInputManager::getMousePosition() const
{
	double posX, posY;
	glfwGetCursorPos(mGlfwOpenGLWindow->getInternalGlfwWindow(), &posX, &posY);

	return std::make_tuple(posX, posY);
}

double GlfwOpenGLInputManager::getMouseDeltaX() const
{
	return _deltaXPos;
}

double GlfwOpenGLInputManager::getMouseDeltaY() const
{
	return _deltaYPos;
}

std::tuple<double, double> GlfwOpenGLInputManager::getMouseDelta() const
{
	return std::make_tuple(_deltaXPos, _deltaYPos);
}

bool GlfwOpenGLInputManager::isMouseButtonDown(MouseButtonCode buttonCode) const
{
	int result = glfwGetMouseButton(mGlfwOpenGLWindow->getInternalGlfwWindow(), static_cast<int>(buttonCode));
	return result == GLFW_PRESS;
}

int GlfwOpenGLInputManager::addEventListener(InputEventCallback eventCallback)
{
	int id = mNextCallbackId++;

	mEventCallbacks[id] = eventCallback;

	return id;
}

void GlfwOpenGLInputManager::removeEventListener(int id)
{
	mEventCallbacks.erase(id);
}

void GlfwOpenGLInputManager::processMousePosition(double xPos, double yPos)
{
	double deltaX = xPos - _oldXMousePos;
	double deltaY = yPos - _oldYMousePos;

	_deltaXPos = deltaX;
	_deltaYPos = deltaY;

	EventMousePosition eventMousePosition;
	eventMousePosition.setPositon(xPos, yPos);
	eventMousePosition.setDelta(deltaX, deltaY);

	notifyEvent(eventMousePosition);

	_oldXMousePos = xPos;
	_oldYMousePos = yPos;
}

void GlfwOpenGLInputManager::processMouseButton(int button, int action, int modify)
{

}

void GlfwOpenGLInputManager::processKeyboard(int key, int scancode, int action, int mods)
{

}
