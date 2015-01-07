#pragma once

class NodeBase;
class Camera;

class IComponent
{
public:
	IComponent()
		: mSceneNode(nullptr)
	{

	}
	~IComponent() {}

	virtual void onRender(const Camera& camera) {};
	virtual void onUpdate() {};
	virtual void onLateUpdate() {};

	NodeBase* getSceneNode() { return mSceneNode; }

	virtual void onAttached() {}
	virtual void onDettached() {}

protected:
	void setSceneNode(NodeBase* sceneNode) { mSceneNode = sceneNode; }

protected:
	NodeBase* mSceneNode;
};