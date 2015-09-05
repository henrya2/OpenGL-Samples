#include "Transform.h"
#include "NodeBase.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Transform::Impl
{
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	glm::mat4 localMatrix;

	glm::mat4 matrix;

	Impl()
		: dirty(false)
		, localMatrix(1.0f)
		, matrix(1.0f)
	{

	}

	bool dirty;
};

const glm::mat4& Transform::getWorldMatrix() const
{
	dImpl->matrix = dImpl->localMatrix;

	NodeBase* nodeParent = mNode->getParent();

	if (nodeParent)
	{
		dImpl->matrix = nodeParent->getTransform()->getWorldMatrix() * dImpl->matrix;
	}

	return dImpl->matrix;
}

const glm::mat4& Transform::getLocalMatrix() const
{
	return dImpl->localMatrix;
}

Transform::Transform(NodeBase* node)
	: _nextCallbackId(1)
	, mNode(node)
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

const glm::vec3& Transform::getRotation() const
{
	return dImpl->rotation;
}

void Transform::setRotation(const glm::vec3& rotation)
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

void Transform::updateMatrix()
{
	if (dImpl->dirty)
	{
		glm::mat4 matrix = glm::translate(glm::mat4(1.0f), dImpl->position);

		if (dImpl->rotation != glm::zero<glm::vec3>())
		{
			matrix *= glm::mat4_cast(glm::quat(dImpl->rotation));
		}
		if (dImpl->scale != glm::zero<glm::vec3>())
		{
			matrix = glm::scale(matrix, dImpl->scale);
		}

		dImpl->localMatrix = matrix;
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
