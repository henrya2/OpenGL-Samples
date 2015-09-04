#ifndef HELLO_GLSL_H
#define HELLO_GLSL_H

#include "Application.h"

class Playground : public Application
{
public:
	Playground();
	~Playground();

	virtual void onRender();

	virtual void onPreRender();

	virtual void onPostRender();

	virtual bool onBeforeRun();

	void customInit();

};

#endif