#pragma once

#include "NodeBase.h"

class Event;

class CameraNode : public NodeBase
{
public:
	CameraNode();
	~CameraNode();

	virtual void onUpdate(float delta) override;

	virtual void start();

	virtual void onAttachedToScene();

protected:
	void handleInputEvent(const Event& event);

};
