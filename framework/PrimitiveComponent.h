#pragma once

#include "IComponent.h"

class GLSLProgram;

class PrimitiveComponent : public IComponent
{
public:
	PrimitiveComponent();

	void setGLSLProgram(GLSLProgram* glslProgram);

	GLSLProgram* getGLSLProgram() const { return mGLSLProgram; }

	virtual void onRender(const Camera& camera, const glm::mat4& worldMatrix) override;

	virtual void updateRenderResources() {}

protected:
	GLSLProgram* mGLSLProgram;
};