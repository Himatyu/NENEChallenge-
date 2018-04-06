#include "Colldee.h"
#include "../Provider/CollisionProvider.h"

namespace NeneLabyrinth
{
	namespace Component
	{
		IColldee::IColldee(
			Object& _owner,
			std::type_index _type,
			Collision::IShape * _pShape) :
			Behavior(_owner, _type),
			pColldeShape(_pShape)
		{
			Collision::CollisionProvider::Instantiate().Register(this);
		}

		IColldee::~IColldee()
		{
			Collision::CollisionProvider::Instantiate().UnRegister(this);
		}

		bool IColldee::IsRigidbody()
		{
			return spRigidbody != nullptr;
		}

		void IColldee::Update()
		{
			if (spRigidbody == nullptr)
			{
				spRigidbody = Owner.GetComponent<Rigidbody>();
			}
			if (spTransform == nullptr)
			{
				spTransform = Owner.GetComponent<Transform>();
			}
		}

	}
}