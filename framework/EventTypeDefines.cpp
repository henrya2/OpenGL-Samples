#include "EventTypeDefines.h"

EventKeyboard::EventKeyboard(KeyCode keyCode, bool isPressed)
	: Event(Type::KEYBOARD)
	, keyCode(keyCode)
	, isPressed(isPressed)
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

EventMouseButton::EventMouseButton(MouseButtonCode button, bool pressed)
	: Event(Type::MOUSE_BUTTON)
	, buttonCode(button)
	, isPressed(pressed)
{

}

EventChar::EventChar(unsigned int charCode)
	: Event(Type::CHARACTER)
	, charCode(charCode)
{

}
