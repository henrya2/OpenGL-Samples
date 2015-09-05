#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "LastUpdatePriorityCommon.h"
#include "Camera.h"
#include "NodeBase.h"
#include "Director.h"
#include "Scene.h"
#include "Transform.h"

struct Camera::Impl
{
	glm::vec3 position;
	glm::vec3 rotation;

	// projection
	float fovy;
	float aspectRatio;
	float near;
	float far;

	glm::mat4 projectionMat;

	// view
	glm::mat4 viewMat;

	bool dirty;

	int _transformChangedCallbackId;

	Impl()
		: dirty(false)
		, _transformChangedCallbackId(0)
	{

	}
};

Camera::Camera()
	: dImpl(new Impl)
{

}

void Camera::setPosition(const glm::vec3& pos)
{
	if (dImpl->position != pos)
	{
		dImpl->position = pos;
		dImpl->dirty = true;
	}
}

const glm::vec3& Camera::getPosition() const
{
	return dImpl->position;
}

void Camera::setRotation(const glm::vec3& rot)
{
	if (dImpl->rotation != rot)
	{
		dImpl->rotation = rot;
		dImpl->dirty = true;
	}

}

const glm::vec3& Camera::getRotation() const
{
	return dImpl->rotation;
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

	dImpl->projectionMat = glm::perspective(glm::radians(fovy), aspectRatio, near, far);
}

const glm::mat4& Camera::getViewMatrix() const
{
	return dImpl->viewMat;
}

void Camera::updateViewMatrix()
{
	glm::mat4 matrix = glm::mat4_cast(glm::quat(dImpl->rotation));
	matrix = glm::transpose(matrix);

	dImpl->viewMat = glm::translate(matrix, -dImpl->position);
}

void Camera::renderNodes(NodeBase* sceneNode)
{
	for (auto childNode : sceneNode->getAllChildren())
	{
		childNode->cameraRender(*this);
	}

	sceneNode->cameraRender(*this);
}

const glm::mat4& Camera::getVP() const
{
	static glm::mat4 mvpMat;
	mvpMat = dImpl->projectionMat * dImpl->viewMat;

	return mvpMat;
}

void Camera::onLateUpdate()
{
	if (dImpl->dirty)
	{
		updateViewMatrix();
		dImpl->dirty = false;
	}
}

void Camera::onUpdate(double delta)
{

}

void Camera::onAttached()
{
	dImpl->_transformChangedCallbackId = getSceneNode()->getTransform()->addChangedCallback(std::bind(&Camera::onTransformChanged, this, std::placeholders::_1));
	
	onTransformChanged(*getSceneNode()->getTransform());
}

void Camera::onDettached()
{
	getSceneNode()->getTransform()->removeChangedCallback(dImpl->_transformChangedCallbackId);
}

void Camera::onAttachedToScene()
{
	Scene* scene = getSceneNode()->getAttachedScene();

	if (scene)
	{
		scene->registerLastUpdate(this, CAMERA_UPDATE_PRIORITY, std::bind(&Camera::lastUpdate, this));
	}
}

void Camera::onDetachedToScene()
{
	Scene* scene = getSceneNode()->getAttachedScene();

	if (scene)
	{
		scene->unRegisterLastUpdate(this);
	}
}


void Camera::lastUpdate()
{
	if (mSceneNode)
	{
		Transform* nodeTransform = mSceneNode->getTransform();

		renderNodes(Director::getInstance()->getRunningScene());
	}
}

void Camera::onTransformChanged(const Transform& transform)
{
	setPosition(transform.getPosition());
	setRotation(transform.getRotation());
}
