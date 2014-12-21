#ifndef HELLO_GLSL_H
#define HELLO_GLSL_H

#include "Application.h"

class CameraSample : public Application
{
public:
	CameraSample();
	~CameraSample();

	virtual void onUpdate() override;

	virtual void onRender();

	virtual void onPreRender();

	virtual void onPostRender();

	virtual bool onBeforeRun();

	void customInit();
	void onViewSizeChanged(const glm::ivec2& viewSize);

	void setupViewPort(const glm::ivec2& viewSize);
};

const std::string g_programName = "CameraSample";

#endif