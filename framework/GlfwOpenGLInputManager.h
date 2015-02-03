#pragma once

#include "IInputManager.h"
#include "Event.h"

#include <map>
#include <bitset>

class GlfwOpenGLWindow;

class GlfwOpenGLInputManager : public IInputManager
{
	friend GlfwOpenGLWindow;
public:
	virtual int addEventListener(InputEventCallback eventCallback);
	virtual void removeEventListener(int id);

	virtual bool isKeyPressed(KeyCode keyCode) const override;

	virtual double getMousePosX() const override;
	virtual double getMousePosY() const override;
	virtual std::tuple<double, double> getMousePosition() const override;

	virtual double getMouseDeltaX() const;
	virtual double getMouseDeltaY() const;
	virtual std::tuple<double, double> getMouseDelta() const;


	virtual bool isMouseButtonDown(MouseButtonCode buttonCode) const override;

	void notifyEvent(const Event& event);


	// called by GlfwOpenGLWindow Module
	void processMousePosition(double xPos, double yPos);
	void processMouseButton(int button, int action, int modify);
	void processKeyboard(int key, int scancode, int action, int mods);

	void clearEventStates();

protected:
	GlfwOpenGLInputManager(GlfwOpenGLWindow* openGLWindow);
protected:
	GlfwOpenGLWindow* mGlfwOpenGLWindow;

private:
	std::map<int, InputEventCallback> mEventCallbacks;

	int mNextCallbackId;
private:
	std::bitset<static_cast<int>(KeyCode::NUMBER_OF_KEYS)> mKeysMap;

	double _oldXMousePos;
	double _oldYMousePos;

	double _deltaXPos;
	double _deltaYPos;
};