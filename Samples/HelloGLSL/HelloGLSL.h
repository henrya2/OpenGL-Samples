#ifndef HELLO_GLSL_H
#define HELLO_GLSL_H

#include "Application.h"

class HelloGLSL : public Application
{
public:
	HelloGLSL();
	~HelloGLSL();

	virtual void onRender();

};

#endif