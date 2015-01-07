#pragma once

#include <glm/glm.hpp>

class Transform
{
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
private:
	struct Impl;
	Impl* dImpl;
};