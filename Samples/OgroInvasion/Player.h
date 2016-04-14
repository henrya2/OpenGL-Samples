#pragma once

#include "NodeBase.h"

class CameraNode;

class Player : public NodeBase
{
public:
	Player();

	~Player();

	virtual void onAttachedToScene() override;

protected:
	CameraNode* cameraNode;
};