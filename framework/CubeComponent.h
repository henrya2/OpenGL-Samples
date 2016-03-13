#pragma once

#include "PrimitiveComponent.h"
#include "GL/glew.h"

class Texture;

class CubeComponent : public PrimitiveComponent
{
public:
	CubeComponent();

	~CubeComponent();

	void setSize(float width, float height, float depth, bool needUpdateResources = true);

	virtual void onRender(const Camera& camera, const glm::mat4& worldMatrix) override;

	virtual void updateRenderResources() override;

	void setTexture(Texture* texture);

	Texture* GetTexture() const { return mTexture; }

protected:
	void freeResources();

protected:
	float mWidth;
	float mHeight;
	float mDepth;

protected:
	GLuint mVertexBufferId;
	GLuint mIndexBufferId;

	Texture* mTexture;
};