#include "Object.h"
#include "../Core/Scene.h"
#include "../Provider/BehaviorProvider.h"
#include "Estd.h"
#include<typeindex>

namespace NeneLabyrinth
{
	namespace Component
	{
		Object::Object(std::shared_ptr<Core::Scene> _spScene) :
			IBehavior(typeid(IBehavior)),
			spScene(_spScene)
		{
			BehaviorProvider::Instantiate().Register(this);
		}

		Object::~Object()
		{
			BehaviorProvider::Instantiate().UnRegister(this);
			Dispose();
		}

		void Object::Update()
		{
			for (auto& component : components)
			{
				component->Update();
			}

			for (auto& behavior : deletableComponents)
			{
				Utility::Estd::remove_if(
					components,
					[behavior](std::shared_ptr<Behavior>& _)
				{
					return _ == behavior;
				});
			}
		}

		void Object::Dispose()
		{
			spScene->Destroy(shared_from_this());
		}

		void Object::RemoveComponent(SpBehavior _pBehavior)
		{
			deletableComponents.push_back(_pBehavior);
		}
	}
}


