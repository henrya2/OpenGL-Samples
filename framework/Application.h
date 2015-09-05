#pragma once

#include <string>

class Application
{
public:
	Application();
	virtual ~Application();

	virtual void onPreRender();
	virtual void onRender();
	virtual void onPostRender();

	virtual bool onBeforeRun() { return true; };

	void run();

	virtual void onUpdate(float delta);

	void setMaxFrame();

private:
	int mMaxFrame;
};
