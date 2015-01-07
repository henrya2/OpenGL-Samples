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

	virtual void onRender(const Camera& camera) const;
	virtual void onUpdate() {}

	virtual void onLateUpdate() {}

	NodeBase* getParent();

	void addChild(NodeBase* node);
	void removeChild(NodeBase* node);

	const std::vector<NodeBase*>& getAllChildren() const { return mChildren; }

	Transform* getTransform() { return mTransform; }

	template <typename T>
	void addComponent()
	{
		IComponent* component = new T();

		component->setSceneNode(this);

		mComponents.push_back(component);

		component->onAttached();
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
				return dynamic_cast<T>(component);
			}
		}
	}

protected:
	void onParentChanged(NodeBase* newParent) {}

private:
	void setParent(NodeBase* parent);

	void internalUpdate();

	void internalLateUpdate();
	void cameraRender(const Camera& camera) const;
protected:
	NodeBase* mParent;

	Transform* mTransform;
private:

	std::vector<IComponent*> mComponents;

	std::vector<NodeBase*> mChildren;
};