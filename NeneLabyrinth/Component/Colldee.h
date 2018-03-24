#pragma once
#include"../Collision/Collider.h"
#include"../Collision/Shape.h"
#include"../Resource/Entity/Mesh.h"
#include"../Component/Object.h"
#include"../Component/Transform.h"

namespace NeneLabyrinth
{
	namespace Component
	{
		class IColldee :
			public Component::Behavior
		{
			Collision::IShape* pColldeShape;
		public:
			PROPERTY(pColldeShape, pShape, Collision::IShape*);

			IColldee(Object&, std::type_index, Collision::IShape*);
			virtual ~IColldee();

			virtual void OnCollisionEnter(Component::Object*) = 0;
			virtual void OnCollisionStay(Component::Object*) = 0;
			virtual void OnCollisionExit(Component::Object*) = 0;

			virtual void OnTriggerEnter(Component::Object*) = 0;
			virtual void OnTriggerStay(Component::Object*) = 0;
			virtual void OnTriggerExit(Component::Object*) = 0;
		};

		template<class T>
		class Colldee :
			public IColldee
		{
		protected:
			T BounsVolume;
		public:
			Colldee(Object&, std::type_index);
			virtual ~Colldee();
			virtual void Update() override;

			virtual void OnCollisionEnter(Component::Object*) override {};
			virtual void OnCollisionStay(Component::Object*) override {};
			virtual void OnCollisionExit(Component::Object*) override {};

			virtual void OnTriggerEnter(Component::Object*) override {};
			virtual void OnTriggerStay(Component::Object*) override {};
			virtual void OnTriggerExit(Component::Object*) override {};
		};

		template<class T>
		class MeshColldee :
			public Colldee<T>
		{
			std::shared_ptr< Resource::Entity::Mesh> entity;
		public:
			MeshColldee(Object&, std::type_index, std::string);
		};

#include"Colldee.inl"
	}
}