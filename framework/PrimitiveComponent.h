#pragma once

#include "IComponent.h"

class PrimitiveComponent : public IComponent
{
public:
	virtual void onRender(const Camera& camera, const glm::mat4& worldMatrix) override;

	virtual void updateRenderResources() {}
};