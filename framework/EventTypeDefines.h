#pragma once

#include "Event.h"

class EventKeyboard : public Event
{
public:
	EventKeyboard(KeyCode keyCode, bool isPressed);

public:
	KeyCode mKeyCode;
	bool mIsPressed;
};

class EventMousePosition : public Event
{
public:
	EventMousePosition();

	void setPositon(double x, double y);
	void setDelta(double x, double y);

public:
	double xPos, yPos;
	double deltaX, deltaY;
};