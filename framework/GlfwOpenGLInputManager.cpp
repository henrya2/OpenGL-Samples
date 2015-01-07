#include "GlfwOpenGLWindow.h"
#include "GlfwOpenGLInputManager.h"
#include "EventKeyboard.h"

#include <glfw/glfw3.h>

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

double GlfwOpenGLInputManager::getMousePosX() const
{
	double posX, posY;
	glfwGetCursorPos(mOpenGLWindow->getInternalGlfwWindow(), &posX, &posY);

	return posX;
}

double GlfwOpenGLInputManager::getMousePosY() const
{
	double posX, posY;
	glfwGetCursorPos(mOpenGLWindow->getInternalGlfwWindow(), &posX, &posY);

	return posY;
}

std::tuple<double, double> GlfwOpenGLInputManager::getMousePosition() const
{
	double posX, posY;
	glfwGetCursorPos(mOpenGLWindow->getInternalGlfwWindow(), &posX, &posY);

	return std::make_tuple(posX, posY);
}

bool GlfwOpenGLInputManager::isMouseButtonDown(MouseButtonCode buttonCode) const
{
	int result = glfwGetMouseButton(mOpenGLWindow->getInternalGlfwWindow(), static_cast<int>(buttonCode));
	return result == GLFW_PRESS;
}
