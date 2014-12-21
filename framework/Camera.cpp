#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Camera.h"
#include "SceneNode.h"
#include "Director.h"
#include "Scene.h"

struct Camera::Impl
{
	glm::mat4 transformMat;
	glm::vec3 position;
	glm::quat rotation;


	// projection
	float fovy;
	float aspectRatio;
	float near;
	float far;

	glm::mat4 projectionMat;

	// view

	glm::mat4 viewMat;
};

Camera::Camera()
	: dImpl(new Impl)
{

}

void Camera::setPosition(const glm::vec3& pos)
{
	dImpl->position = pos;
	
	updateViewMatrix();
}

const glm::vec3& Camera::getPosition() const
{
	return dImpl->position;
}

void Camera::setRotation(const glm::quat& rot)
{
	dImpl->rotation = rot;

	updateViewMatrix();
}

const glm::quat& Camera::getRotation() const
{
	return dImpl->rotation;
}

const glm::mat4& Camera::getTransformMatrix() const
{
	return dImpl->transformMat;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
	return dImpl->projectionMat;
}

void Camera::setProjection(float fovy, float aspectRatio, float near /*= 0.1f*/, float far /*= 1000.0f*/)
{
	dImpl->fovy = fovy;
	dImpl->aspectRatio = aspectRatio;
	dImpl->near = near;
	dImpl->far = far;

	dImpl->projectionMat = glm::perspective(fovy, aspectRatio, near, far);
}

const glm::mat4& Camera::getViewMatrix() const
{
	return dImpl->viewMat;
}

void Camera::updateViewMatrix()
{
	updateTransformMatrix();

	dImpl->viewMat = glm::transpose(dImpl->transformMat);
}

void Camera::updateTransformMatrix()
{
	glm::mat4 matrix = glm::mat4_cast(dImpl->rotation);
	dImpl->transformMat = glm::translate(matrix, dImpl->position);
}

void Camera::render(SceneNode* sceneNode)
{
	sceneNode->render(*this);

	for (auto childNode : sceneNode->getAllChildren())
	{
		childNode->render(*this);
	}
}

const glm::mat4& Camera::getVP() const
{
	static glm::mat4 mvpMat;
	mvpMat = dImpl->projectionMat * dImpl->viewMat;

	return mvpMat;
}

void Camera::onLateUpdate()
{
	if (mSceneNode)
	{
		Transform* nodeTransform = mSceneNode->getTransform();

		setPosition(nodeTransform->getPosition());
		setRotation(nodeTransform->getRotation());

		render(Director::getInstance()->getRunningScene());
	}
}

void Camera::onUpdate()
{

}
