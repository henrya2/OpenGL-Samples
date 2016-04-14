#pragma once

#include "NodeBase.h"

class Camera;

class CameraNode : public NodeBase
{
public:
	CameraNode();

	~CameraNode();

	Camera* getCamera() { return camera; }

	virtual void onAttachedToScene() override;

	virtual void onDetachedToScene() override;

protected:
	Camera* camera;
};