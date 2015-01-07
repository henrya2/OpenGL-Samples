#include "Scene.h"
#include <algorithm>

struct Scene::LastUpdateStructTypeCompare
{
	bool operator()(const LastUpdateStructType& left, const LastUpdateStructType& right) const
	{
		return left.priority < right.priority;
	}
};

Scene::Scene()
{

}

void Scene::registerLastUpdate(IComponent* component, int priority, LastUpdateFunctorType functor)
{
	LastUpdateStructType lastUpdateStructType;
	lastUpdateStructType.componet = component;
	lastUpdateStructType.priority = priority;
	lastUpdateStructType.functor = functor;

	mLastUpdateComponents.push_back(lastUpdateStructType);

	std::stable_sort(mLastUpdateComponents.begin(), mLastUpdateComponents.end(), LastUpdateStructTypeCompare());
}

void Scene::unRegisterLastUpdate(IComponent* componet)
{
	auto iter = std::find_if(mLastUpdateComponents.begin(), mLastUpdateComponents.end(), 
		[=](const LastUpdateStructType& lastUpdateStructType) {
		if (lastUpdateStructType.componet == componet)
			return true;
		return false;
	});

	if (iter != mLastUpdateComponents.end())
	{
		mLastUpdateComponents.erase(iter);
	}
}
