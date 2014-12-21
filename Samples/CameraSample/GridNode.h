#include "SceneNode.h"

#include "GLSLProgram.h"

class GridNode : public SceneNode
{
public:
	GridNode(int width = 10, int depth = 10);
	virtual ~GridNode();

	virtual void render(const Camera& camera) const override;

private:
	GLSLProgram* mGLSLProgram;
};