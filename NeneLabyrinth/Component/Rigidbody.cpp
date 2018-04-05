#include"Rigidbody.h"
#include"Transform.h"
#include"TimerServer.h"
#include"Object.h"

namespace NeneLabyrinth
{
	namespace Component
	{
		using namespace Utility;

		Rigidbody::Rigidbody(Component::Object & _owner) :
			Behavior(_owner, typeid(Rigidbody)),
			velocity(D3DXVECTOR3(0, 0, 0)),
			acceleration(D3DXVECTOR3(0, 0, 0)),
			gravity(D3DXVECTOR3(0, -9.8f, 0)),
			isKinematic(false),
			isUseGravity(true),
			mass(1.0f),
			drag(0.0f),
			bound(0.5f)
		{
		}
		void Rigidbody::AddForce(D3DXVECTOR3 & _force)
		{
			acceleration += _force;
		}
		void Rigidbody::AddForceImpulse(D3DXVECTOR3 & _force)
		{
			velocity += _force / mass;
		}
		void Rigidbody::Update()
		{
			auto a = acceleration / mass;
			velocity += a * TimerServer::DeltaTime;
			velocity *= (1.0f - drag *TimerServer::DeltaTime);

			acceleration = D3DXVECTOR3(0, 0, 0);

			if (isUseGravity)
			{
				AddForce(gravity);
			}

			if (isKinematic)
			{
				return;
			}

			if (spTransform == nullptr)
			{
				spTransform = Owner.GetComponent<Component::Transform>();
				ASSERT_EXPR(spTransform != nullptr, L"Transform•t‚¯‚Ü‚µ‚å‚¤‚Ë^^");
			}
			spTransform->Position += velocity * TimerServer::DeltaTime;
		}
	}
}