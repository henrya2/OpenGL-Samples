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

	virtual float getMouseDeltaX() const;
	virtual float getMouseDeltaY() const;
	virtual std::tuple<float, float> getMouseDelta() const;


	virtual bool isMouseButtonDown(MouseButtonCode buttonCode) const override;

	void notifyEvent(const Event& event);


	// called by GlfwOpenGLWindow Module
	void processMousePosition(double xPos, double yPos);
	void processMouseButton(int button, int action, int modify);
	void processMouseWheel(int position);
	void processKeyboard(int key, int scancode, int action, int mods);
	void processChar(unsigned int charCode);

	virtual void clearEventStates() override;

	virtual void setRelativeMouseMode(bool relativeMode);

	virtual bool getRelativeMouseMode() const;

protected:
	GlfwOpenGLInputManager(GlfwOpenGLWindow* openGLWindow);

protected:
	GlfwOpenGLWindow* mGlfwOpenGLWindow;

private:
	std::map<int, InputEventCallback> mEventCallbacks;

	int mNextCallbackId;
private:

	double _oldXMousePos;
	double _oldYMousePos;

	double _deltaXPos;
	double _deltaYPos;

	bool _firstMouseMove;
};