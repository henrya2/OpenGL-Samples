#pragma once

class SceneNode;

class IComponent
{
public:
	IComponent()
		: mSceneNode(nullptr)
	{

	}
	~IComponent() {}

	virtual void onUpdate() {};
	virtual void onLateUpdate() {};

	SceneNode* getSceneNode() { return mSceneNode; }

protected:
	void setSceneNode(SceneNode* sceneNode) { mSceneNode = sceneNode; }

protected:
	SceneNode* mSceneNode;
};