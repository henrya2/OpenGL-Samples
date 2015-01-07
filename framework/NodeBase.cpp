#include "NodeBase.h"
#include "Scene.h"
#include "IComponent.h"

NodeBase* NodeBase::getParent()
{
	return mParent;
}

void NodeBase::setParent(NodeBase* parent)
{
	onParentChanged(parent);
	mParent = parent;
}

NodeBase::NodeBase()
{
	mTransform = new Transform();
}

NodeBase::~NodeBase()
{
	delete mTransform;
}

void NodeBase::addChild(NodeBase* node)
{
	mChildren.push_back(node);
	node->setParent(this);
}

void NodeBase::removeChild(NodeBase* node)
{
	auto iter = std::find(mChildren.begin(), mChildren.end(), node);
	if (iter != mChildren.end())
	{
		mChildren.erase(iter);
	}
}

void NodeBase::internalUpdate()
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

void NodeBase::internalLateUpdate()
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

	mTransform->clearDirty();
}

void NodeBase::cameraRender(const Camera& camera) const
{
	for (auto component : mComponents)
	{
		component->onRender(camera);
	}

	onRender(camera);
}

void NodeBase::onRender(const Camera& camera) const
{

}
