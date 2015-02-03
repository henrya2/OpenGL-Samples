#include "GridNode.h"
#include "CameraSample.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include "Utils.h"

GridNode::GridNode(int width /*= 10*/, int depth /*= 10*/)
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

	std::vector<glm::vec3> verts;
	std::vector<glm::u16> indices;

	glm::vec3 center(0, 0, 0);

	Utils::genTriGrid(width, depth, 1.0f, 1.0f, center, verts, indices);
}

GridNode::~GridNode()
{
	delete mGLSLProgram;
}

void GridNode::onRender(const Camera& camera) const
{
	glm::mat4 mvp = camera.getVP() * mTransform->getWorldMatrix();

	mGLSLProgram->setUniform("MVP", mvp);
}
