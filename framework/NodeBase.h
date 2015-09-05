#pragma once

#include <vector>

#include "Transform.h"

class Camera;
class IComponent;

class NodeBase
{
	friend class Scene;
	friend class Director;
	friend class IComponent;
	friend class Camera;
public:
	NodeBase();
	virtual ~NodeBase();

	// when first call to onUpdate
	virtual void start() {}

	virtual void onRender(const Camera& camera, const glm::mat4& worldMatrix) const;

	virtual void onUpdate(float delta) {}

	virtual void onLateUpdate() {}

	virtual void onAttachedToScene() {};
	virtual void onDetachedToScene() {};

	Scene* getAttachedScene();
	void attachToScene();
	void detachFromScene();

	NodeBase* getParent();

	void addChild(NodeBase* node);

	void removeChild(NodeBase* node);

	const std::vector<NodeBase*>& getAllChildren() const { return mChildren; }

	Transform* getTransform() const { return mTransform; }

	template <typename T>
	T* addComponent()
	{
		IComponent* component = new T();

		component->setSceneNode(this);

		mComponents.push_back(component);

		component->onAttached();

		if (getAttachedScene())
		{
			component->onAttachedToScene();
		}

		return static_cast<T*>(component);
	}
	
	template <typename T>
	void removeComponent()
	{
		for (auto iter = mComponents.begin(); iter != mComponents.end();)
		{
			IComponent* component = *iter;

			if (typeid(T) == typeid(*component))
			{
				component->setSceneNode(nullptr);
				component->onDettached();
				if (getAttachedScene())
				{
					component->onDetachedToScene();
				}
				iter = mComponents.erase(iter);
				break;
			}
			else
			{
				++iter;
			}
		}
	}

	template <typename T>
	T* getComponent()
	{
		for (auto component : mComponents)
		{
			if (typeid(T) == typeid(*component))
			{
				return dynamic_cast<T*>(component);
			}
		}

		return nullptr;
	}

protected:
	void onParentChanged(NodeBase* newParent) {}

private:
	void setParent(NodeBase* parent);

	void internalUpdate(float delta);

	void internalLateUpdate();
	void cameraRender(const Camera& camera, const glm::mat4& parentMatrix) const;
protected:
	NodeBase* mParent;
	Scene* mScene;

	Transform* mTransform;

	bool _alreadyPassFirstUpdate;
private:

	std::vector<IComponent*> mComponents;

	std::vector<NodeBase*> mChildren;
};