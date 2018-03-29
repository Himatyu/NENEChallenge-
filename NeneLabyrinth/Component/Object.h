#pragma once
#include<memory>
#include<vector>
#include"IBehavior.h"

namespace NeneLabyrinth
{
	namespace Core
	{
		class Scene;
	}
	namespace Component
	{
		///コンストラクタ完了前にshared_from_thisを使用しないこと
		class Object :
			public IBehavior,
			public std::enable_shared_from_this<Object>
		{
			std::vector<std::shared_ptr<Behavior>> components;
			std::vector<std::shared_ptr<Behavior>> deletableComponents;
			std::shared_ptr<Core::Scene> spScene;

		public:
			using SpBehavior = std::shared_ptr<Behavior>;

			Object(std::shared_ptr<Core::Scene>);
			virtual ~Object();
			virtual void Update()override;
			virtual void Dispose() override;

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
#include"Object.inl"
	}
}
