#pragma once
#include"IProvider.h"
#include"Singleton.h"
#include"../Component/IBehavior.h"
namespace NeneLabyrinth
{
	namespace Component
	{
		class BehaviorProvider :
			public Utility::IProvider<Component::IBehavior>,
			public Utility::Singleton<BehaviorProvider>
		{
		public:
			void Dispatch() override
			{
				for (auto& behavior : receivers)
				{
					behavior->Update();
				}
			}

		};
	}
}
