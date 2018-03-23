#pragma once
#include"../Collision/Collider.h"
#include"../Collision/Shape.h"
#include"../Resource/Entity/Mesh.h"
#include"../Component/Behavior.h"
#include"../Component/Transform.h"

namespace NeneLabyrinth
{
	namespace Component
	{
		class IColldee :
			public Component::IBehavior
		{
			Collision::IShape* pColldeShape;
		public:
			PROPERTY(pColldeShape, pShape, Collision::IShape*);

			IColldee(Behavior&, std::type_index, Collision::IShape*);
			virtual ~IColldee();

			virtual void OnCollisionEnter(Component::Behavior*) = 0;
			virtual void OnCollisionStay(Component::Behavior*) = 0;
			virtual void OnCollisionExit(Component::Behavior*) = 0;

			virtual void OnTriggerEnter(Component::Behavior*) = 0;
			virtual void OnTriggerStay(Component::Behavior*) = 0;
			virtual void OnTriggerExit(Component::Behavior*) = 0;
		};

		template<class T>
		class Colldee :
			public IColldee
		{
		protected:
			T BounsVolume;
		public:
			Colldee(Behavior&, std::type_index);
			virtual ~Colldee();
			virtual void Update() override;

			virtual void OnCollisionEnter(Component::Behavior*) override {};
			virtual void OnCollisionStay(Component::Behavior*) override {};
			virtual void OnCollisionExit(Component::Behavior*) override {};

			virtual void OnTriggerEnter(Component::Behavior*) override {};
			virtual void OnTriggerStay(Component::Behavior*) override {};
			virtual void OnTriggerExit(Component::Behavior*) override {};
		};

		template<class T>
		class MeshColldee :
			public Colldee<T>
		{
			std::shared_ptr< Resource::Entity::Mesh> entity;
		public:
			MeshColldee(Behavior&, std::type_index, std::string);
		};

#include"Colldee.inl"


	}
}