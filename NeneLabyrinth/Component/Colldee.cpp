#include "Colldee.h"
#include "../Provider/CollisionProvider.h"

namespace NeneLabyrinth
{
	namespace Component
	{
		IColldee::IColldee(
			Behavior& _owner,
			std::type_index _type,
			Collision::IShape * _pShape) :
			IBehavior(_owner, _type),
			pColldeShape(_pShape)
		{
			Collision::CollisionProvider::Instantiate().Register(this);
		}

		IColldee::~IColldee()
		{
			Collision::CollisionProvider::Instantiate().UnRegister(this);
		}


	}
}