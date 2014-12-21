#pragma once

#include "IInputManager.h"
#include "Event.h"

#include <bitset>
class GlfwOpenGLWindow;

class GlfwOpenGLInputManager : public IInputManager
{
	friend GlfwOpenGLWindow;
public:
	virtual bool isKeyPressed(KeyCode keyCode) const override;

	void notifyEvent(const Event& event);

	void clearEventStates();

protected:
	GlfwOpenGLInputManager(GlfwOpenGLWindow* openGLWindow);
protected:
	GlfwOpenGLWindow* mOpenGLWindow;

private:
	std::bitset<static_cast<int>(KeyCode::NUMBER_OF_KEYS)> mKeysMap;
};