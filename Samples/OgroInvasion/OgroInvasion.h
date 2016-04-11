#pragma once

#include "Application.h"

class OgroInvasion : public Application
{
public:
	OgroInvasion();
	~OgroInvasion();

	virtual void onRender() override;

	virtual void onPreRender() override;

	virtual void onPostRender() override;

	virtual bool onBeforeRun() override;

	virtual void onShutdown() override;

	void customInit();

protected:
	class Texture* mTexture;
};
