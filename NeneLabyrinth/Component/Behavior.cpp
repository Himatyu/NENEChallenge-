#include "Behavior.h"
#include "Estd.h"
#include "BehaviorAdministrator.h"
#include<typeindex>

namespace NeneLabyrinth
{
	namespace Component
	{
		Behavior::Behavior() :
			IBehavior(*this, typeid(IBehavior))
		{
		}

		Behavior::~Behavior()
		{

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


