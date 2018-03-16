#include "IBehavior.h"


namespace NeneLabyrinth
{
	namespace Component
	{
		IBehavior::IBehavior(Behavior& _owner, std::type_index _type) :
			type(_type),
			owner(_owner)
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
	}
}