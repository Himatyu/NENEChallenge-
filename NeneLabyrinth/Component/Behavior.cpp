#include "Behavior.h"
#include "../Provider/BehaviorProvider.h"
#include "Estd.h"
#include<typeindex>

namespace NeneLabyrinth
{
	namespace Component
	{
		Behavior::Behavior() :
			IBehavior(*this, typeid(IBehavior))
		{
			BehaviorProvider::Instantiate().Register(this);
		}

		Behavior::~Behavior()
		{
			BehaviorProvider::Instantiate().UnRegister(this);
		}

		void Behavior::Update()
		{
			for (auto& component : components)
			{
				component->Update();
			}

			for (auto& behavior : deletableComponents)
			{
				Utility::Estd::remove_if(
					components,
					[behavior](std::shared_ptr<IBehavior>& _)
				{
					return _ == behavior;
				});
			}
		}

		void Behavior::RemoveComponent(SpBehavior _pBehavior)
		{
			deletableComponents.push_back(_pBehavior);
		}
	}
}


