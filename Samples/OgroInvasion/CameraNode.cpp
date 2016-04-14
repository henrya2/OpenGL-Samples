#include "CameraNode.h"
#include "Camera.h"

CameraNode::CameraNode()
	: camera(nullptr)
{

}

CameraNode::~CameraNode()
{

}

void CameraNode::onAttachedToScene()
{
	camera = addComponent<Camera>();
}

void CameraNode::onDetachedToScene()
{
	removeComponent<Camera>();
}
