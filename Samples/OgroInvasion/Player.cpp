#include "Player.h"
#include "Camera.h"
#include "CameraNode.h"

Player::Player()
	: cameraNode(nullptr)
{

}

Player::~Player()
{

}

void Player::onAttachedToScene()
{
	cameraNode = new CameraNode;
	addChild(cameraNode);
}
