#include "CameraNode.h"
#include "Camera.h"
#include "Director.h"
#include "IWindow.h"

CameraNode::CameraNode()
{
	auto cameraComponent = addComponent<Camera>();
}

CameraNode::~CameraNode()
{

}

#define MOVE_SPEED 4

void CameraNode::onUpdate(double delta)
{
	float fDelta = (float)delta;
	IInputManager* inputManager = Director::getInstance()->getInputManager();

	/*
	if (true)
	{
		printf("timeCount: %f\n", delta);
	}
	*/
	glm::vec3 position = getTransform()->getPosition();
	glm::vec3 rotationEuler = getTransform()->getRotation();

	glm::mat3 rotationMat = glm::mat3_cast(glm::quat(rotationEuler));

	glm::vec3 zAxis = glm::normalize(rotationMat[2]);
	glm::vec3 xAxis = glm::normalize(rotationMat[0]);

	if (inputManager->isKeyPressed(KeyCode::KEY_W))
	{
		position -= MOVE_SPEED * fDelta * zAxis;
	}
	if (inputManager->isKeyPressed(KeyCode::KEY_S))
	{
		position += MOVE_SPEED * fDelta * zAxis;
	}
	if (inputManager->isKeyPressed(KeyCode::KEY_A))
	{
		position -= MOVE_SPEED * fDelta * xAxis;
	}
	if (inputManager->isKeyPressed(KeyCode::KEY_D))
	{
		position += MOVE_SPEED * fDelta * xAxis;
	}

	if (glm::abs(inputManager->getMouseDeltaX()) > glm::epsilon<float>())
	{
		rotationEuler.y += inputManager->getMouseDeltaX() * fDelta / 180 * glm::pi<float>() * MOVE_SPEED;
	}
	if (glm::abs(inputManager->getMouseDeltaY()) > glm::epsilon<float>())
	{
		rotationEuler.x += inputManager->getMouseDeltaY() * fDelta / 180 * glm::pi<float>() * MOVE_SPEED;
	}

	if (position != getTransform()->getPosition())
	{
		getTransform()->setPosition(position);
	}

	if (rotationEuler != getTransform()->getRotation())
	{
		getTransform()->setRotation(rotationEuler);
	}
}

void CameraNode::start()
{
	Transform* transform = getTransform();
	if (transform)
	{
		transform->setPosition(glm::vec3(0, 0, 2.f));
	}
}

void CameraNode::onAttachedToScene()
{
	auto cameraComponent = getComponent<Camera>();

	glm::ivec2 viewSize = Director::getInstance()->getWindow()->getViewSize();
	cameraComponent->setProjection(90.0f, (float)viewSize.x / viewSize.y);
}

