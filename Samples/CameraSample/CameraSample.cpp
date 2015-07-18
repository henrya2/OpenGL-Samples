#include "framework.h"
#include "Scene.h"
#include "CameraSample.h"

#include "CameraNode.h"

#include "Utils.h"

#include <iostream>
#include "GridNode.h"

GLSLProgram glslProgram;

const float vertexPositions[] = {
	0.75f, 0.75f, 0.0f,
	0.75f, -0.75f, 0.0f,
	-0.75f, -0.75f, 0.0f,
};

GLuint positionBufferObject;
GLuint vao;

CameraSample::CameraSample()
{

}

CameraSample::~CameraSample()
{

}

void CameraSample::onUpdate()
{
	static int testCount = 0;

	testCount++;

	IInputManager* inputManager = Director::getInstance()->getInputManager();

	if (inputManager->isKeyPressed(KeyCode::KEY_A))
	{
		printf("KeyCode::KEY_A is pressed\n");
	}

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
	glslProgram.use();

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glslProgram.unUse();
	glBindVertexArray(0);
}

void CameraSample::onPreRender()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
		window->createWindow("Hello", 640, 480);
		window->setGLVersion(3, 3);
		bool result = window->initGL();
		if (!result)
			return false;

		Director::getInstance()->setWindow(window);
	}

	Director::getInstance()->runWithScene(new Scene());

	CameraNode* cameraNode = new CameraNode;
	Director::getInstance()->getRunningScene()->addChild(cameraNode);

	//GridNode* gridNode = new GridNode;
	//Director::getInstance()->getRunningScene()->addChild(gridNode);

	customInit();

	return true;
}

void CameraSample::customInit()
{
	try
	{
		glslProgram.loadShader(GLSLShaderType::VERTEX, g_programName + "/" + "CameraSample.vert");
		glslProgram.loadShader(GLSLShaderType::FRAGMENT, g_programName + "/" + "CameraSample.frag");
	}
	catch (GLSLProgramException& e)
	{
		printf("%s\n", e.what());
		system("pause");
		exit(EXIT_FAILURE);
	}

	glslProgram.link();

	glGenBuffers(1, &positionBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLint positionLoc = glslProgram.getAttributeLocation("position");
	glEnableVertexAttribArray(positionLoc);
	glVertexAttribPointer(positionLoc, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	std::vector<glm::vec3> verts;
	std::vector<glm::u16> indices;

	glm::vec3 center(0, 0, 0);

	Utils::genTriGrid(100, 100, 1.0f, 1.0f, center, verts, indices);

	printf("\n");
}

/* Our program's entry point */
int main(int argc, char *argv[])
{
	CameraSample app;

	app.run();

	return 0;
}
