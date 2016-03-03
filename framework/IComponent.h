#pragma once

#include "glm/glm.hpp"

class NodeBase;
class Camera;

class IComponent
{
	friend NodeBase;
public:
	IComponent()
		: mSceneNode(nullptr)
	{

	}
	~IComponent() {}

	virtual void onRender(const Camera& camera, const glm::mat4& worldMatrix) {};
	virtual void onUpdate(float delta) {};
	virtual void onLateUpdate() {};

	NodeBase* getSceneNode() { return mSceneNode; }

	virtual void onAttached() {}
	virtual void onDettached() {}

	virtual void onAttachedToScene() {}
	virtual void onDetachedToScene() {}

protected:
	void setSceneNode(NodeBase* sceneNode) { mSceneNode = sceneNode; }

protected:
	NodeBase* mSceneNode;
};