#include "PrimitiveComponent.h"

PrimitiveComponent::PrimitiveComponent()
	: mGLSLProgram(nullptr)
{

}

PrimitiveComponent::~PrimitiveComponent()
{
	if (mGLSLProgram)
	{
		delete mGLSLProgram;
	}
}

void PrimitiveComponent::setGLSLProgram(GLSLProgram* glslProgram)
{
	if (mGLSLProgram)
	{
		delete mGLSLProgram;
	}

	mGLSLProgram = glslProgram;
}

void PrimitiveComponent::onRender(const Camera& camera, const glm::mat4& worldMatrix)
{

}
