#include "EventTypeDefines.h"

EventKeyboard::EventKeyboard(KeyCode keyCode, bool isPressed)
	: Event(Type::KEYBOARD)
	, mKeyCode(keyCode)
	, mIsPressed(isPressed)
{

}

EventMousePosition::EventMousePosition()
	: Event(Type::MOUSE_MOVE)
{

}

void EventMousePosition::setPositon(double x, double y)
{
	xPos = x;
	yPos = y;
}

void EventMousePosition::setDelta(double x, double y)
{
	deltaX = x;
	deltaY = y;
}
