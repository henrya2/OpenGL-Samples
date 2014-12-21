#pragma once

#include "Event.h"

class EventKeyboard : public Event
{
public:
	EventKeyboard(KeyCode keyCode, bool isPressed);

private:
	KeyCode mKeyCode;
	bool mIsPressed;

	friend class GlfwOpenGLInputManager;
};