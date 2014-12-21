#pragma once

#include "SceneNode.h"

class Scene : public SceneNode
{
	friend class Director;
public:
	Scene();
	virtual ~Scene() {}

	virtual void onEnter() {}
	virtual void onLeave() {}
};