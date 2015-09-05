#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <functional>
#include <map>

class NodeBase;

class Transform
{
public:
	typedef std::function<void(const Transform& transform)> TransformChangedCallback;
public:
	Transform(NodeBase* node);
	virtual ~Transform();

	const glm::vec3& getPosition() const;
	void setPosition(const glm::vec3& position);

	const glm::vec3& getRotation() const;
	void setRotation(const glm::vec3& rotation);

	const glm::vec3& getScale() const;
	void setScale(const glm::vec3& scale);

	const glm::mat4& getWorldMatrix() const;
	const glm::mat4& getLocalMatrix() const;

	void updateMatrix();

	bool isDirty() const;

	void clearDirty();

	int addChangedCallback(TransformChangedCallback callback);

	void removeChangedCallback(int id);

protected:
	void notifyChanged() const;
private:
	struct Impl;
	Impl* dImpl;

	int _nextCallbackId;
	std::map<int, TransformChangedCallback> mCallbackmaps;

	NodeBase* mNode;
};