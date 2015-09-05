#include "framework.h"
#include "Scene.h"
#include "CameraSample.h"

#include "CameraNode.h"

#include "Utils.h"

#include <iostream>
#include "PrimitiveNode.h"

CameraSample::CameraSample()
{

}

CameraSample::~CameraSample()
{

}

void CameraSample::onUpdate(double delta)
{
	IInputManager* inputManager = Director::getInstance()->getInputManager();

	static auto oldMousePosition = inputManager->getMousePosition();

	auto mousePosition = inputManager->getMousePosition();

	std::tuple_element<0, decltype(mousePosition)>::type posX = std::get<0>(mousePosition);
	std::tuple_element<1, decltype(mousePosition)>::type posY = std::get<1>(mousePosition);

	if (oldMousePosition != mousePosition)
	{
		std::cout << "MousePosX: " << posX << ", " << "MousePosY: " << posY << std::endl;
		std::cout << "DeltaPosX: " << inputManager->getMouseDeltaX() << ", " << "DeltaPosY: " << inputManager->getMouseDeltaY() << std::endl;
	}

	oldMousePosition = mousePosition;
}

void CameraSample::onRender()
{
	return;
}

void CameraSample::onPreRender()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
}

void CameraSample::onPostRender()
{

}

void CameraSample::setupViewPort(const glm::ivec2& viewSize)
{
	glViewport(0, 0, viewSize.x, viewSize.y);
}

void CameraSample::onViewSizeChanged(const glm::ivec2& viewSize)
{
	setupViewPort(viewSize);
}

bool CameraSample::onBeforeRun()
{
	auto window = Director::getInstance()->getWindow();

	if (!window)
	{
		window = Director::getInstance()->createDefaultWindow();
		window->viewSizeChangedCallback = std::bind(&CameraSample::onViewSizeChanged, this, std::placeholders::_1);
		window->setGLVersion(3, 3);
		window->createWindow("Hello", 640, 480);
		bool result = window->initGL();
		if (!result)
			return false;

		Director::getInstance()->setWindow(window);

		Director::getInstance()->getInputManager()->setRelativeMouseMode(true);
	}

	Director::getInstance()->runWithScene(new Scene());

	CameraNode* cameraNode = new CameraNode;
	Director::getInstance()->getRunningScene()->addChild(cameraNode);

	PrimitiveNode* primitiveNode = new PrimitiveNode;
	Director::getInstance()->getRunningScene()->addChild(primitiveNode);

	return true;
}

/* Our program's entry point */
int main(int argc, char *argv[])
{
	CameraSample app;

	app.run();

	return 0;
}
