#pragma once

#include "NodeBase.h"

class CameraNode : public NodeBase
{
public:
	CameraNode();
	~CameraNode();

	virtual void onUpdate(double delta) override;

	virtual void start();

	virtual void onAttachedToScene();

};
