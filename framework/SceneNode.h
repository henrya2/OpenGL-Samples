#pragma once

#include <vector>

#include "Transform.h"

class Camera;
class IComponent;

class SceneNode
{
	friend class Scene;
	friend class Director;
	friend class IComponent;
public:
	SceneNode();
	virtual ~SceneNode();

	virtual void render(const Camera& camera) const;
	virtual void onUpdate() {}

	virtual void onLateUpdate() {}

	SceneNode* getParent();

	void addChild(SceneNode* node);
	void removeChild(SceneNode* node);

	const std::vector<SceneNode*>& getAllChildren() const { return mChildren; }

	Transform* getTransform() { return mTransform; }

	template <typename T>
	void addComponent()
	{
		T* component = new T();

		component->setSceneNode(this);

		mComponents.push_back(component);
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
	void onParentChanged(SceneNode* newParent) {}

private:
	void setParent(SceneNode* parent);

	void internalUpdate();

	void internalLateUpdate();
private:
	SceneNode* mParent;

	Transform* mTransform;

	std::vector<IComponent*> mComponents;

	std::vector<SceneNode*> mChildren;
};