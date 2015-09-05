#include "CameraNode.h"
#include "Camera.h"
#include "Director.h"
#include "IWindow.h"
#include "EventTypeDefines.h"

#include <glm/gtc/matrix_transform.hpp>

CameraNode::CameraNode()
{
	auto cameraComponent = addComponent<Camera>();
}

CameraNode::~CameraNode()
{

}

#define MOVE_SPEED 4

void CameraNode::onUpdate(float delta)
{
	float fDelta = delta;
	IInputManager* inputManager = Director::getInstance()->getInputManager();

	if (!inputManager->getRelativeMouseMode())
		return;

	glm::vec3 position = getTransform()->getPosition();
	glm::vec3 moveOffset;
	glm::vec3 rotationEuler = getTransform()->getRotation();

	glm::mat3 rotationMat = glm::mat3_cast(glm::quat(rotationEuler));

	if (inputManager->isKeyPressed(KeyCode::KEY_W))
	{
		moveOffset.z -= MOVE_SPEED * fDelta;
	}
	if (inputManager->isKeyPressed(KeyCode::KEY_S))
	{
		moveOffset.z += MOVE_SPEED * fDelta;
	}
	if (inputManager->isKeyPressed(KeyCode::KEY_A))
	{
		moveOffset.x -= MOVE_SPEED * fDelta;
	}
	if (inputManager->isKeyPressed(KeyCode::KEY_D))
	{
		moveOffset.x += MOVE_SPEED * fDelta;
	}

	if (glm::abs(inputManager->getMouseDeltaX()) > glm::epsilon<float>())
	{
		rotationEuler.y -= inputManager->getMouseDeltaX() * fDelta / 180 * glm::pi<float>() * MOVE_SPEED;

		if (rotationEuler.y > glm::pi<float>())
		{
			rotationEuler.y += -glm::pi<float>() * 2;
		}
		else if (rotationEuler.y <= -glm::pi<float>())
		{
			rotationEuler.y += glm::pi<float>() * 2;
		}
	}
	if (glm::abs(inputManager->getMouseDeltaY()) > glm::epsilon<float>())
	{
		rotationEuler.x -= inputManager->getMouseDeltaY() * fDelta / 180 * glm::pi<float>() * MOVE_SPEED;

		rotationEuler.x = glm::clamp(rotationEuler.x, -glm::pi<float>() / 2, glm::pi<float>() / 2);
	}

	if (moveOffset != glm::zero<glm::vec3>())
	{
		getTransform()->setPosition(position + rotationMat * moveOffset);
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
		transform->setPosition(glm::vec3(0, 0, 7.f));
	}

	IInputManager* inputMananger = Director::getInstance()->getInputManager();
	inputMananger->addEventListener(std::bind(&CameraNode::handleInputEvent, this, std::placeholders::_1));
}

void CameraNode::onAttachedToScene()
{
	auto cameraComponent = getComponent<Camera>();

	glm::ivec2 viewSize = Director::getInstance()->getWindow()->getViewSize();
	cameraComponent->setProjection(90.0f, (float)viewSize.x / viewSize.y);
}

void CameraNode::handleInputEvent(const Event& event)
{
	IInputManager* inputManager = Director::getInstance()->getInputManager();
	switch (event.getType())
	{
	case Event::Type::KEYBOARD:
	{
		const EventKeyboard& eventKeyboard = (const EventKeyboard&)event;

		if (eventKeyboard.mKeyCode == KeyCode::KEY_Q && eventKeyboard.mIsPressed)
		{
			bool oldRelativeMode = inputManager->getRelativeMouseMode();
			inputManager->setRelativeMouseMode(!oldRelativeMode);
		}
	}
	break;
	}
}

