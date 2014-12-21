#include "Transform.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

struct Transform::Impl
{
	glm::vec3 localPosition;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 localScale;
	glm::quat localRotation;
	glm::quat rotation;

	glm::mat4 localMatrix;
	glm::mat4 matrix;
};

Transform::Transform()
{
	dImpl = new Impl();
}

Transform::~Transform()
{
	delete dImpl;
}

const glm::vec3& Transform::getPosition() const
{
	return dImpl->position;
}

void Transform::setPosition(const glm::vec3& position)
{
	dImpl->position = position;
}

const glm::quat& Transform::getRotation() const
{
	return dImpl->rotation;
}

void Transform::setRotation(const glm::quat& rotation)
{
	dImpl->rotation = rotation;
}

const glm::vec3& Transform::getScale() const
{
	return dImpl->scale;
}

void Transform::setScale(const glm::vec3& scale)
{
	dImpl->scale = scale;
}
