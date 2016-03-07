#include "PrimitiveComponent.h"

PrimitiveComponent::PrimitiveComponent()
	: mGLSLProgram(nullptr)
{

}

void PrimitiveComponent::setGLSLProgram(GLSLProgram* glslProgram)
{
	mGLSLProgram = glslProgram;
}

void PrimitiveComponent::onRender(const Camera& camera, const glm::mat4& worldMatrix)
{

}
