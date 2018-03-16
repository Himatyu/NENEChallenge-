#pragma once
#include<memory>
#include<vector>
#include"IBehavior.h"

namespace NeneLabyrinth
{
	namespace Component
	{
		class Behavior :
			public IBehavior
		{
			std::vector<std::shared_ptr<IBehavior>> components;
			std::vector<std::shared_ptr<IBehavior>> deletableComponents;
		public:
			using SpBehavior = std::shared_ptr<IBehavior>;

			Behavior();
			virtual ~Behavior();
			virtual void Update()override;

			template <class Type, class ...Param>
			std::shared_ptr<Type> AddComponent(Param&&...);

			template <class Type>
			void RemoveComponents();

			void RemoveComponent(SpBehavior);

			template <class Type>
			std::shared_ptr<Type> GetComponent();

			template <class Type>
			std::shared_ptr<Type> GetComponentFromName(std::string);

			template <class Type>
			std::vector<std::shared_ptr<Type>> GetComponents();

			template <class Type>
			bool HasComponent();
		};
#include"Behavior.inl"
	}
}
