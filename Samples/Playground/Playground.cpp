#include "framework.h"
#include "Playground.h"

#include "Utils.h"

#include "FreeImage.h"
#include <iostream>

const std::string g_programName = "Playground";

GLSLProgram glslProgram;

enum VAO_IDS { Triangles, NumVAOs };
enum Buffer_IDS { ArrayBuffer, NumBuffers };
enum Attrib_IDS { vPosition = 0 };

GLuint vaoID;
GLuint vboVerticesID;
GLuint vboIndicesID;
GLuint textureID;

std::string filename;

const GLuint NumVertices = 6;

Playground::Playground()
{

}

Playground::~Playground()
{

}

void Playground::onRender()
{
	glslProgram.use();

	glBindVertexArray(vaoID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

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

void Playground::onShutdown()
{
	//Destroy vao and vbo
	glDeleteBuffers(1, &vboVerticesID);
	glDeleteBuffers(1, &vboIndicesID);
	glDeleteVertexArrays(1, &vaoID);

	//Delete textures
	glDeleteTextures(1, &textureID);

	FreeImage_DeInitialise();
}

void Playground::customInit()
{
	FreeImage_Initialise();

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

	//load the image using FreeImage
	int texture_width = 0, texture_height = 0, channels = 0;

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);

	fif = FreeImage_GetFileType(filename.c_str(), 0);

	dib = FreeImage_Load(fif, filename.c_str());

	if (!dib)
	{
		std::cerr << "Cannot load image: " << filename.c_str() << std::endl;
		exit(EXIT_FAILURE);
	}

	bits = FreeImage_GetBits(dib);
	texture_width = FreeImage_GetWidth(dib);
	texture_height = FreeImage_GetHeight(dib);

	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_width, texture_height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);

	glslProgram.setUniform("textureMap", 0); // GL_TEXTURE0

	FreeImage_Unload(dib);
}

/* Our program's entry point */
int main(int argc, char *argv[])
{
	Playground app;

	app.run();

	return 0;
}
