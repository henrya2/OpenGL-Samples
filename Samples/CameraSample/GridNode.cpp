#include "GridNode.h"
#include "CameraSample.h"
#include <glm/glm.hpp>

GridNode::GridNode(int width /*= 10*/, int depth /*= 10*/)
{
	mGLSLProgram = new GLSLProgram();

	mGLSLProgram->loadShader(GLSLShaderType::VERTEX, g_programName + "/" + "CameraSample.vert");
	mGLSLProgram->loadShader(GLSLShaderType::FRAGMENT, g_programName + "/" + "CameraSample.frag");
}

GridNode::~GridNode()
{
	delete mGLSLProgram;
}

void GridNode::render(const Camera& camera) const
{

}
