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

void CameraNode::onUpdate(double delta)
{
	IInputManager* inputManager = Director::getInstance()->getInputManager();

	/*
	if (true)
	{
		printf("timeCount: %f\n", delta);
	}
	*/
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

