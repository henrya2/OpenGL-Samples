#include "SceneNode.h"
#include "Scene.h"
#include "IComponent.h"

SceneNode* SceneNode::getParent()
{
	return mParent;
}

void SceneNode::setParent(SceneNode* parent)
{
	onParentChanged(parent);
	mParent = parent;
}

SceneNode::SceneNode()
{
	mTransform = new Transform();
}

SceneNode::~SceneNode()
{
	delete mTransform;
}

void SceneNode::addChild(SceneNode* node)
{
	mChildren.push_back(node);
	node->setParent(this);
}

void SceneNode::removeChild(SceneNode* node)
{
	auto iter = std::find(mChildren.begin(), mChildren.end(), node);
	if (iter != mChildren.end())
	{
		mChildren.erase(iter);
	}
}

void SceneNode::internalUpdate()
{
	onUpdate();

	for (auto component : mComponents)
	{
		component->onUpdate();
	}

	for (auto child : mChildren)
	{
		child->internalUpdate();
	}
}

void SceneNode::internalLateUpdate()
{
	onLateUpdate();

	for (auto component : mComponents)
	{
		component->onLateUpdate();
	}

	for (auto child : mChildren)
	{
		child->internalLateUpdate();
	}
}

void SceneNode::render(const Camera& camera) const
{

}
