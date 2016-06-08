#pragma once

#include "Event.h"

class EventKeyboard : public Event
{
public:
	EventKeyboard(KeyCode keyCode, bool isPressed);

public:
	KeyCode keyCode;
	bool isPressed;
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

class EventMouseButton : public Event
{
public:
	EventMouseButton(MouseButtonCode button, bool pressed);

public:
	MouseButtonCode buttonCode;

	bool isPressed;
};

class EventChar : public Event
{
public:
	EventChar(unsigned int charCode);

public:
	unsigned int charCode;
};