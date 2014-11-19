#pragma once

class IWindow;

class Director
{
public:
	static Director* getInstance();
	void init();

	IWindow* getWindow();
	void setWindow(IWindow* window);

	void mainLoop();

	IWindow* createDefaultWindow();

private:
	Director();

private:
	IWindow* mWindow;
};