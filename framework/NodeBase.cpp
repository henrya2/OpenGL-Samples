#include "NodeBase.h"
#include "Scene.h"
#include "IComponent.h"

NodeBase* NodeBase::getParent()
{
	return mParent;
}

Scene* NodeBase::getAttachedScene()
{
	return mScene;
}

void NodeBase::setParent(NodeBase* parent)
{
	onParentChanged(parent);

	if (parent != nullptr)
	{
		if (mScene != nullptr)
		{
			DetachToScene();
		}

		if (mScene != parent->getAttachedScene())
		{
			mScene = parent->getAttachedScene();
			AttachToScene();
		}
	}
	else
	{
		if (mScene != nullptr)
		{
			DetachToScene();
		}

		mScene = nullptr;
	}

	mParent = parent;
}

void NodeBase::AttachToScene()
{
	onAttachedToScene();

	for (auto component : mComponents)
	{
		component->onAttachedToScene();
	}
}

void NodeBase::DetachToScene()
{
	_alreadyPassFirstUpdate = false;

	onDetachedToScene();

	for (auto component : mComponents)
	{
		component->onDetachedToScene();
	}
}

NodeBase::NodeBase()
{
	mTransform = new Transform();

	_alreadyPassFirstUpdate = false;
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
	if (!_alreadyPassFirstUpdate)
	{
		start();
		_alreadyPassFirstUpdate = true;
	}

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
