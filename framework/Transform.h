#pragma once

#include <glm/glm.hpp>
#include <functional>
#include <map>

class Transform
{
public:
	typedef std::function<void(const Transform& transform)> TransformChangedCallback;
public:
	Transform();
	virtual ~Transform();

	const glm::vec3& getPosition() const;
	void setPosition(const glm::vec3& position);

	const glm::quat& getRotation() const;
	void setRotation(const glm::quat& rotation);

	const glm::vec3& getScale() const;
	void setScale(const glm::vec3& scale);

	const glm::mat4& getWorldMatrix() const;
	const glm::mat4& getLocalMatrix() const;

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
};