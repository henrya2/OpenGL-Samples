#include "framework.h"
#include "OgroInvasion.h"

#include "Utils.h"

#include <iostream>

const std::string g_programName = SAMPLE_NAME;

GLSLProgram glslProgram;

enum VAO_IDS { Triangles, NumVAOs };
enum Buffer_IDS { ArrayBuffer, NumBuffers };
enum Attrib_IDS { vPosition = 0 };

GLuint vaoID;
GLuint vboVerticesID;
GLuint vboIndicesID;

std::string filename;

const GLuint NumVertices = 6;

OgroInvasion::OgroInvasion()
{
	mTexture = nullptr;
}

OgroInvasion::~OgroInvasion()
{

}

void OgroInvasion::onRender()
{
	glslProgram.use();

	glBindVertexArray(vaoID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

	glBindVertexArray(0);

	glslProgram.unUse();
}

void OgroInvasion::onPreRender()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OgroInvasion::onPostRender()
{

}

bool OgroInvasion::onBeforeRun()
{
	auto window = Director::getInstance()->getWindow();

	if (!window)
	{
		window = Director::getInstance()->createDefaultWindow();
		window->setGLVersion(3, 3);
		window->createWindow("ImageLoader", 512, 512);
		bool result = window->initGL();
		if (!result)
			return false;

		Director::getInstance()->setWindow(window);
	}

	customInit();

	return true;
}

void OgroInvasion::onShutdown()
{
	//Destroy vao and vbo
	glDeleteBuffers(1, &vboVerticesID);
	glDeleteBuffers(1, &vboIndicesID);
	glDeleteVertexArrays(1, &vaoID);

	if (mTexture)
	{
		delete mTexture;
	}
}

void OgroInvasion::customInit()
{
	filename = g_programName + "/" + "Lenna.png";

	try
	{
		glslProgram.loadShader(GLSLShaderType::VERTEX, g_programName + "/" + "shader.vert");
		glslProgram.loadShader(GLSLShaderType::FRAGMENT, g_programName + "/" + "shader.frag");
	}
	catch (GLSLProgramException& e)
	{
		printf("%s\n", e.what());
		system("pause");
		exit(EXIT_FAILURE);
	}

	glslProgram.link();

	GLint vertexAttribLoc = glslProgram.getAttributeLocation("vVertex");

	//quad vertices and indices
	glm::vec2 vertices[4];
	GLushort indices[6];

	vertices[0] = glm::vec2(0.0f, 0.0f);
	vertices[1] = glm::vec2(1.0f, 0.0f);
	vertices[2] = glm::vec2(1.0f, 1.0f);
	vertices[3] = glm::vec2(0.0f, 1.0f);

	GLushort* id = indices;
	*id++ = 0;
	*id++ = 1;
	*id++ = 2;
	*id++ = 0;
	*id++ = 2;
	*id++ = 3;

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(1, &vboVerticesID);
	glGenBuffers(1, &vboIndicesID);
	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(vertexAttribLoc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vertexAttribLoc);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	mTexture = new Texture(filename);
	mTexture->load();
	mTexture->activateTexture(0); // GL_TEXTURE0

	glslProgram.setUniform("textureMap", 0); // GL_TEXTURE0
}

/* Our program's entry point */
int main(int argc, char *argv[])
{
	OgroInvasion app;

	app.run();

	return 0;
}
