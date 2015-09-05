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
			detachFromScene();
		}

		if (mScene != parent->getAttachedScene())
		{
			mScene = parent->getAttachedScene();
			attachToScene();
		}
	}
	else
	{
		if (mScene != nullptr)
		{
			detachFromScene();
		}

		mScene = nullptr;
	}

	mParent = parent;
}

void NodeBase::attachToScene()
{
	onAttachedToScene();

	for (auto component : mComponents)
	{
		component->onAttachedToScene();
	}
}

void NodeBase::detachFromScene()
{
	_alreadyPassFirstUpdate = false;

	onDetachedToScene();

	for (auto component : mComponents)
	{
		component->onDetachedToScene();
	}
}

NodeBase::NodeBase()
	: mScene(nullptr)
	, mParent(nullptr)
{
	mTransform = new Transform(this);

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

void NodeBase::internalUpdate(float delta)
{
	if (!_alreadyPassFirstUpdate)
	{
		start();
		_alreadyPassFirstUpdate = true;
	}

	onUpdate(delta);

	for (auto component : mComponents)
	{
		component->onUpdate(delta);
	}

	for (auto child : mChildren)
	{
		child->internalUpdate(delta);
	}
}

void NodeBase::internalLateUpdate()
{
	mTransform->updateMatrix();
	mTransform->clearDirty();

	for (auto component : mComponents)
	{
		component->onLateUpdate();
	}

	for (auto child : mChildren)
	{
		child->internalLateUpdate();
	}

	onLateUpdate();
}

void NodeBase::cameraRender(const Camera& camera, const glm::mat4& parentMatrix) const
{
	glm::mat4 combineMatrix = parentMatrix * (getTransform()->getLocalMatrix());
	for (auto child : mChildren)
	{
		child->cameraRender(camera, combineMatrix);
	}

	for (auto component : mComponents)
	{
		component->onRender(camera, combineMatrix);
	}

	onRender(camera, combineMatrix);
}

void NodeBase::onRender(const Camera& camera, const glm::mat4& worldMatrix) const
{

}
