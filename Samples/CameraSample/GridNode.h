#include "NodeBase.h"

#include "GLSLProgram.h"

class GridNode : public NodeBase
{
public:
	GridNode(int width = 10, int depth = 10);
	virtual ~GridNode();

	virtual void onRender(const Camera& camera) const override;

private:
	GLSLProgram* mGLSLProgram;
};