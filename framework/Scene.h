#pragma once

#include "NodeBase.h"
#include <functional>
#include <vector>

class Scene : public NodeBase
{
	friend class Director;
public:
	Scene();
	virtual ~Scene() {}

	virtual void onEnter() {}
	virtual void onLeave() {}

	typedef std::function<void()> LastUpdateFunctorType;

	struct LastUpdateStructType
	{
		int priority;
		IComponent* componet;
		LastUpdateFunctorType functor;
	};

	void registerLastUpdate(IComponent* component, int priority, LastUpdateFunctorType functor);
	void unRegisterLastUpdate(IComponent* componet);

private:
	void internalLastUpdate();

	std::vector<LastUpdateStructType> mLastUpdateComponents;

	struct LastUpdateStructTypeCompare;
};