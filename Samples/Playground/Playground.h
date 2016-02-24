#ifndef HELLO_GLSL_H
#define HELLO_GLSL_H

#include "Application.h"

class Playground : public Application
{
public:
	Playground();
	~Playground();

	virtual void onRender() override;

	virtual void onPreRender() override;

	virtual void onPostRender() override;

	virtual bool onBeforeRun() override;

	virtual void onShutdown() override;

	void customInit();

protected:
	class Texture* mTexture;
};

#endif