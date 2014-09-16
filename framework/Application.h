#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <string>

class Application
{
public:
	Application();
	virtual ~Application();

	void setVerticalSync(bool sync);

	virtual void init();

	void setWindowTitle(const std::string& title);

	void createWindow(const std::string& title, int width, int height);

	bool isWindowCreated() const;
	void setGLVersion(int major, int minor);
	void initGL();

	void destroy();

	virtual void onPreRender();
	virtual void onRender();
	virtual void onPostRender();

	virtual void onBeforeRun() {};

	void run();

protected:
	class ApplicationImpl;
	ApplicationImpl* mImpl;
};

#endif