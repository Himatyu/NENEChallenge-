#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include"IBehavior.h"

namespace NeneLabyrinth
{
	namespace Component
	{
		class Transform;
		class Rigidbody :
			public Component::Behavior
		{
			std::shared_ptr<Component::Transform> spTransform;
			D3DXVECTOR3 velocity;
			D3DXVECTOR3 acceleration;
			D3DXVECTOR3 gravity;
			bool isKinematic;
			bool isUseGravity;
			float mass;
			float drag;

		public:
			PROPERTY_REF(velocity, Velocity, D3DXVECTOR3);
			PROPERTY_REF(acceleration, Acceleration, D3DXVECTOR3);
			PROPERTY_REF(gravity, Gravity, D3DXVECTOR3);
			PROPERTY_REF(isKinematic, IsKinematic, bool);
			PROPERTY_REF(isUseGravity, IsUseGravity, bool);
			PROPERTY_REF(mass, Mass, float);
			PROPERTY_REF(drag, Drag, float);

			Rigidbody(
				Component::Object& _owner);

			void AddForce(D3DXVECTOR3& _force);

			void AddForceImpulse(D3DXVECTOR3& _force);

			void Update() override;
		};

	}
}