#include "GlfwOpenGLWindow.h"
#include "GlfwOpenGLInputManager.h"
#include "EventKeyboard.h"

GlfwOpenGLInputManager::GlfwOpenGLInputManager(GlfwOpenGLWindow* openGLWindow)
	: mOpenGLWindow(openGLWindow)
{

}

bool GlfwOpenGLInputManager::isKeyPressed(KeyCode keyCode) const
{
	return mKeysMap[static_cast<int>(keyCode)];
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
}

void GlfwOpenGLInputManager::clearEventStates()
{

}
