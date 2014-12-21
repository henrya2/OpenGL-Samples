#include "EventKeyboard.h"

EventKeyboard::EventKeyboard(KeyCode keyCode, bool isPressed)
	: Event(Type::KEYBOARD)
	, mKeyCode(keyCode)
	, mIsPressed(isPressed)
{

}
