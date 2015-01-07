#pragma once

#include "Event.h"
#include <tuple>

class IInputManager
{
public:
	IInputManager();
	virtual ~IInputManager();

	virtual bool isKeyPressed(KeyCode keyCode) const = 0;

	virtual double getMousePosX() const = 0;
	virtual double getMousePosY() const = 0;
	virtual std::tuple<double, double> getMousePosition() const = 0;

	virtual bool isMouseButtonDown(MouseButtonCode buttonCode) const = 0;
};