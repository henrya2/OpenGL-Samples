#pragma once

#include "NodeBase.h"

#include "GLSLProgram.h"

class PrimitiveNode : public NodeBase
{
public:
	PrimitiveNode(int width = 10, int depth = 10);
	virtual ~PrimitiveNode();

	virtual void onRender(const Camera& camera) const override;

private:
	GLSLProgram* mGLSLProgram;

	GLuint mVBOId;
	GLuint mIBOId;
};