#ifndef HELLO_GLSL_H
#define HELLO_GLSL_H

#include "Application.h"

class HelloGLSL : public Application
{
public:
	HelloGLSL();
	~HelloGLSL();

	virtual void init();

	virtual void onRender();

	virtual void onPreRender();

	virtual void onPostRender();

	virtual void onBeforeRun();

};

#endif