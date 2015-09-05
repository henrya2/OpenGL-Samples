#include "PrimitiveNode.h"
#include "CameraSample.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Utils.h"

static GLuint vao = 0;
static GLint positionLoc = 0;

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, -1.0f, // triangle 1 : begin
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f, -1.0f, // triangle 2 : begin
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f, // triangle 2 : end
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
	0.583f, 0.771f, 0.014f,
	0.609f, 0.115f, 0.436f,
	0.327f, 0.483f, 0.844f,
	0.822f, 0.569f, 0.201f,
	0.435f, 0.602f, 0.223f,
	0.310f, 0.747f, 0.185f,
	0.597f, 0.770f, 0.761f,
	0.559f, 0.436f, 0.730f,
	0.359f, 0.583f, 0.152f,
	0.483f, 0.596f, 0.789f,
	0.559f, 0.861f, 0.639f,
	0.195f, 0.548f, 0.859f,
	0.014f, 0.184f, 0.576f,
	0.771f, 0.328f, 0.970f,
	0.406f, 0.615f, 0.116f,
	0.676f, 0.977f, 0.133f,
	0.971f, 0.572f, 0.833f,
	0.140f, 0.616f, 0.489f,
	0.997f, 0.513f, 0.064f,
	0.945f, 0.719f, 0.592f,
	0.543f, 0.021f, 0.978f,
	0.279f, 0.317f, 0.505f,
	0.167f, 0.620f, 0.077f,
	0.347f, 0.857f, 0.137f,
	0.055f, 0.953f, 0.042f,
	0.714f, 0.505f, 0.345f,
	0.783f, 0.290f, 0.734f,
	0.722f, 0.645f, 0.174f,
	0.302f, 0.455f, 0.848f,
	0.225f, 0.587f, 0.040f,
	0.517f, 0.713f, 0.338f,
	0.053f, 0.959f, 0.120f,
	0.393f, 0.621f, 0.362f,
	0.673f, 0.211f, 0.457f,
	0.820f, 0.883f, 0.371f,
	0.982f, 0.099f, 0.879f
};

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

	glm::vec3 vertices[24];
	vertices[0] = glm::vec3(-0.75f, 0.75f, 0.75);
	vertices[1] = glm::vec3(-0.75f, -0.75f, 0.75);
	vertices[2] = glm::vec3(0.75f, -0.75f, 0.75);
	vertices[3] = glm::vec3(0.75f, 0.75f, 0.75);

	vertices[4] = glm::vec3(0.75f, 0.75f, 0.75);
	vertices[5] = glm::vec3(0.75f, 0.75f, 0.75);
	vertices[6] = glm::vec3(0.75f, 0.75f, -0.75);
	vertices[7] = glm::vec3(0.75f, 0.75f, -0.75);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &mVBOId);
	glBindBuffer(GL_ARRAY_BUFFER, mVBOId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	positionLoc = mGLSLProgram->getAttributeLocation("position");
	glEnableVertexAttribArray(positionLoc);
	glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &mVBOId);
	glBindBuffer(GL_ARRAY_BUFFER, mVBOId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	positionLoc = mGLSLProgram->getAttributeLocation("vertexColor");
	glEnableVertexAttribArray(positionLoc);
	glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	unsigned int indices[] = { 
		0, 1, 2,
		0, 2, 3
	};

	glGenBuffers(1, &mIBOId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBOId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

PrimitiveNode::~PrimitiveNode()
{
	glDeleteBuffers(1, &mVBOId);
	glDeleteBuffers(1, &mIBOId);

	delete mGLSLProgram;
}

void PrimitiveNode::onRender(const Camera& camera, const glm::mat4& worldMatrix) const
{
	glm::mat4 mvp = camera.getVP() * worldMatrix;

	mGLSLProgram->use();

	mGLSLProgram->setUniform("MVP", mvp);

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

	glBindVertexArray(0);

	mGLSLProgram->unUse();
}
