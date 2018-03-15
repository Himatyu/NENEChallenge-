#pragma once
#include<typeindex>
namespace NeneLabyrinth
{
	namespace Component
	{
		class Behavior;
		class IBehavior
		{
			std::type_index type;
			std::string name;
			Behavior&	owner;
		public:
			PROPERTY_REF(name, Name, std::string);
			PROPERTY_REF_R_ONLY(owner, Owner, Behavior);
			PROPERTY_REF_R_ONLY(type, Type, std::type_index);

			IBehavior(Behavior&, std::type_index);
			virtual ~IBehavior();
			virtual void Update() = 0;

			template<class T>
			bool IsSame()
			{
				return type == typeid(T);
			}
			bool operator==(const std::type_index& _Type);
			bool operator!=(const std::type_index& _Type);

		};
	}
}