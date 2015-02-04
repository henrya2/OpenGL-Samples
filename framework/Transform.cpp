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

	bool dirty;
};

const glm::mat4& Transform::getWorldMatrix() const
{
	return dImpl->matrix;
}

const glm::mat4& Transform::getLocalMatrix() const
{
	return dImpl->localMatrix;
}

Transform::Transform()
	: _nextCallbackId(1)
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
	dImpl->dirty = true;

	notifyChanged();
}

const glm::quat& Transform::getRotation() const
{
	return dImpl->rotation;
}

void Transform::setRotation(const glm::quat& rotation)
{
	dImpl->rotation = rotation;
	dImpl->dirty = true;

	notifyChanged();
}

const glm::vec3& Transform::getScale() const
{
	return dImpl->scale;
}

void Transform::setScale(const glm::vec3& scale)
{
	dImpl->scale = scale;
	dImpl->dirty = true;

	notifyChanged();
}

void Transform::notifyChanged() const
{
	for (auto& callbackPair : mCallbackmaps)
	{
		callbackPair.second(*this);
	}
}

bool Transform::isDirty() const
{
	return dImpl->dirty;
}

void Transform::clearDirty()
{
	dImpl->dirty = false;
}

int Transform::addChangedCallback(TransformChangedCallback callback)
{
	int callbackId = _nextCallbackId++;

	mCallbackmaps[callbackId] = callback;

	return callbackId;
}

void Transform::removeChangedCallback(int id)
{
	mCallbackmaps.erase(id);
}
