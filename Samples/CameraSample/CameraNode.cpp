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

void CameraNode::onUpdate()
{

}

void CameraNode::start()
{

}

void CameraNode::onAttachedToScene()
{
	auto cameraComponent = getComponent<Camera>();
	glm::ivec2 viewSize = Director::getInstance()->getWindow()->getViewSize();
	cameraComponent->setProjection(90.0f, (float)viewSize.x / viewSize.y);
}
