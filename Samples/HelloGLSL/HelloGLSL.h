#ifndef HELLO_GLSL_H
#define HELLO_GLSL_H

#include "Application.h"

class HelloGLSL : public Application
{
public:
	HelloGLSL();
	~HelloGLSL();

	virtual void onRender();

	virtual void onPreRender();

	virtual void onPostRender();

	virtual bool onBeforeRun();

	void customInit();

};

#endif