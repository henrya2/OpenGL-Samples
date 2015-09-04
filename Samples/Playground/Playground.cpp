#include "framework.h"
#include "Playground.h"

#include "Utils.h"

const std::string g_programName = "Playground";

GLSLProgram glslProgram;

enum VAO_IDS { Triangles, NumVAOs };
enum Buffer_IDS { ArrayBuffer, NumBuffers };
enum Attrib_IDS { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

const float vertexPositions[] = {
	0.75f, 0.75f, 0.0f, 1.0f,
	0.75f, -0.75f, 0.0f, 1.0f,
	-0.75f, -0.75f, 0.0f, 1.0f,
};


Playground::Playground()
{

}

Playground::~Playground()
{

}

void Playground::onRender()
{
	glslProgram.use();

	glBindVertexArray(VAOs[Triangles]);

	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	glBindVertexArray(0);

	glslProgram.unUse();
}

void Playground::onPreRender()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Playground::onPostRender()
{

}

bool Playground::onBeforeRun()
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

void Playground::customInit()
{
	try
	{
		glslProgram.loadShader(GLSLShaderType::VERTEX, g_programName + "/" + "Playground.vert");
		glslProgram.loadShader(GLSLShaderType::FRAGMENT, g_programName + "/" + "Playground.frag");
	}
	catch (GLSLProgramException& e)
	{
		printf("%s\n", e.what());
		system("pause");
		exit(EXIT_FAILURE);
	}

	glslProgram.link();

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat vertices[NumVertices][2] = {
		{ -0.90f, -0.90f }, // Triangle 1
		{ 0.85f, -0.90f },
		{ -0.90f, 0.85f },
		{ 0.90f, -0.85f }, // Triangle 2
		{ 0.90f, 0.90f },
		{ -0.85f, 0.90f }
	};

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/* Our program's entry point */
int main(int argc, char *argv[])
{
	Playground app;

	app.run();

	return 0;
}
