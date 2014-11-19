#include "framework.h"
#include "HelloGLSL.h"

const std::string g_programName = "HelloGLSL";

GLSLProgram glslProgram;

const float vertexPositions[] = {
	0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,
};

GLuint positionBufferObject;
GLuint vao;

HelloGLSL::HelloGLSL()
{

}

HelloGLSL::~HelloGLSL()
{

}

void HelloGLSL::onRender()
{
	glslProgram.use();

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glslProgram.unUse();
	glBindVertexArray(0);
}

void HelloGLSL::onPreRender()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void HelloGLSL::onPostRender()
{

}

bool HelloGLSL::onBeforeRun()
{
	auto window = Director::getInstance()->getWindow();

	if (!window)
	{
		window = Director::getInstance()->createDefaultWindow();
		window->createWindow("Hello", 640, 480);
		window->setGLVersion(3, 3);
		bool result = window->initGL();
		if (!result)
			return false;

		Director::getInstance()->setWindow(window);
	}

	customInit();

	return true;
}

void HelloGLSL::customInit()
{
	try
	{
		glslProgram.loadShader(GLSLShaderType::VERTEX, g_programName + "/" + "HelloGLSL.vert");
		glslProgram.loadShader(GLSLShaderType::FRAGMENT, g_programName + "/" + "HelloGLSL.frag");
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
}

/* Our program's entry point */
int main(int argc, char *argv[])
{
	HelloGLSL app;

	app.run();

	return 0;
}
