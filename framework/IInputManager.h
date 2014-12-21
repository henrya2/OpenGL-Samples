#pragma once

#include "Event.h"

class IInputManager
{
public:
	IInputManager();
	virtual ~IInputManager();

	virtual bool isKeyPressed(KeyCode keyCode) const = 0;
};