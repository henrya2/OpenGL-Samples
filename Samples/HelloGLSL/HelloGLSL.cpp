#include "framework.h"
#include "HelloGLSL.h"

HelloGLSL::HelloGLSL()
{

}

HelloGLSL::~HelloGLSL()
{

}

void HelloGLSL::onRender()
{

}

/* Our program's entry point */
int main(int argc, char *argv[])
{
	HelloGLSL app;
	app.init();
	app.createWindow("HelloGLSL", 640, 480);
	app.setGLVersion(3, 3);
	app.initGL();

	app.run();

	return 0;
}
