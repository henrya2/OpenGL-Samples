#pragma once

#include <glm/glm.hpp>
#include "IComponent.h"

class NodeBase;
class Transform;

class Camera : public IComponent
{
public:
	Camera();

	void setProjection(float fovy, float aspectRatio, float near = 0.1f, float far = 1000.0f);

	void setPosition(const glm::vec3& pos);

	const glm::vec3& getPosition() const;

	void setRotation(const glm::vec3& rot);

	const glm::vec3& getRotation() const;

	void updateViewMatrix();

	const glm::mat4& getViewMatrix() const;

	const glm::mat4& getProjectionMatrix() const;

	const glm::mat4& getVP() const;

	void renderNodes(NodeBase* sceneNode);

	void lastUpdate();

	virtual void onUpdate(float delta);

	virtual void onLateUpdate();

	virtual void onAttached();

	virtual void onDettached();

	void onTransformChanged(const Transform& transform);

	virtual void onAttachedToScene();

	virtual void onDetachedToScene();

private:
	struct Impl;
	Impl* dImpl;
};