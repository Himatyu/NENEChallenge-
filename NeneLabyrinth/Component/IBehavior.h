#pragma once
#include<typeindex>
namespace NeneLabyrinth
{
	namespace Component
	{
		class Object;
		class IBehavior
		{
		protected:
			std::type_index type;
			std::string name;
		public:
			PROPERTY_REF(name, Name, std::string);
			PROPERTY_REF_R_ONLY(type, Type, std::type_index);

			IBehavior(std::type_index);
			virtual ~IBehavior();
			virtual void Update() = 0;
			virtual void Dispose() = 0;

			template<class T>
			bool IsSame()
			{
				return type == typeid(T);
			}
			bool operator==(const std::type_index& _Type);
			bool operator!=(const std::type_index& _Type);

		};

		class Behavior :
			public IBehavior,
			public std::enable_shared_from_this<Behavior>
		{
		protected:
			Object&	owner;
		public:
			PROPERTY_REF_R_ONLY(owner, Owner, Object);

			Behavior(Object&, std::type_index);
			virtual ~Behavior();
			virtual void Dispose() override;
		};
	}
}