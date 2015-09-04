#include "PrimitiveNode.h"
#include "CameraSample.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include "Utils.h"

static GLuint vao = 0;
static GLint positionLoc = 0;

PrimitiveNode::PrimitiveNode(int width /*= 10*/, int depth /*= 10*/)
	: NodeBase()
{
	mGLSLProgram = new GLSLProgram();

	try
	{
		mGLSLProgram->loadShader(GLSLShaderType::VERTEX, g_programName + "/" + "CameraSample.vert");
		mGLSLProgram->loadShader(GLSLShaderType::FRAGMENT, g_programName + "/" + "CameraSample.frag");
	}
	catch (GLSLProgramException& e)
	{
		printf("%s\n", e.what());
		system("pause");
		exit(EXIT_FAILURE);
	}

	mGLSLProgram->link();

	/*
	std::vector<glm::vec3> verts;
	std::vector<glm::u16> indices;

	glm::vec3 center(0, 0, 0);

	Utils::genTriGrid(width, depth, 1.0f, 1.0f, center, verts, indices);
	*/

	glm::vec3 vertices[4];
	vertices[0] = glm::vec3(-0.75f, 0.75f, 0);
	vertices[1] = glm::vec3(-0.75f, -0.75f, 0);
	vertices[2] = glm::vec3(0.75f, -0.75f, 0);
	vertices[3] = glm::vec3(0.75f, 0.75f, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &mVBOId);
	glBindBuffer(GL_ARRAY_BUFFER, mVBOId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	positionLoc = mGLSLProgram->getAttributeLocation("position");
	glEnableVertexAttribArray(positionLoc);
	glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	unsigned int indices[] = { 
		0, 1, 2,
		0, 2, 3
	};

	glGenBuffers(1, &mIBOId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBOId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

PrimitiveNode::~PrimitiveNode()
{
	glDeleteBuffers(1, &mVBOId);
	glDeleteBuffers(1, &mIBOId);

	delete mGLSLProgram;
}

void PrimitiveNode::onRender(const Camera& camera) const
{
	glm::mat4 mvp = camera.getVP() * mTransform->getWorldMatrix();

	mGLSLProgram->use();

	mGLSLProgram->setUniform("MVP", mvp);

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	mGLSLProgram->unUse();
}
