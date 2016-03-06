#pragma once

#include "PrimitiveComponent.h"
#include "GL/glew.h"

class CubeComponent : public PrimitiveComponent
{
public:
	CubeComponent();

	~CubeComponent();

	virtual void onRender(const Camera& camera, const glm::mat4& worldMatrix) override;

	virtual void updateRenderResources() override;

protected:
	void freeResources();

protected:
	float mWidth;
	float mHeight;
	float mDepth;

protected:
	GLuint vertexBufferId;
	GLuint indexBufferId;
};