#include "IBehavior.h"
#include "Object.h"


namespace NeneLabyrinth
{
	namespace Component
	{
		IBehavior::IBehavior(std::type_index _type) :
			type(_type)
		{
		}
		IBehavior::~IBehavior()
		{
		}
		bool IBehavior::operator==(const std::type_index & _Type)
		{
			return type == _Type;
		}
		bool IBehavior::operator!=(const std::type_index & _Type)
		{
			return type != _Type;
		}
		Behavior::Behavior(Object& _owner, std::type_index _type) :
			IBehavior(_type),
			owner(_owner)
		{
		}
		Behavior::~Behavior()
		{
		}
		void Behavior::Dispose()
		{
			owner.RemoveComponent(shared_from_this());
		}
	}
}