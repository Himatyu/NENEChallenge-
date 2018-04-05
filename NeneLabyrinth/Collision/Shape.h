#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <array>
#include "../Component/Transform.h"
#include "../Resource/Entity/Mesh.h"
#include "../Resource/Service.h"

namespace NeneLabyrinth
{
	namespace Collision
	{
		class IShape
		{
		public:
			virtual void Updata(std::shared_ptr<Component::Transform>) = 0;
			virtual void FormEntity(Resource::Entity::Mesh&) = 0;
		};

		class OBB :
			public IShape
		{
			using AxisType = std::array<D3DXVECTOR3, 3>;
			D3DXVECTOR3		half = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3		center = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3		prevScale = D3DXVECTOR3(1, 1, 1);
			std::array<D3DXVECTOR3, 3>	localAxis;
		public:

			PROPERTY_REF(half, Half, D3DXVECTOR3);
			PROPERTY_REF(center, Center, D3DXVECTOR3);
			PROPERTY_REF(localAxis[0], LocalAxisX, D3DXVECTOR3);
			PROPERTY_REF(localAxis[1], LocalAxisY, D3DXVECTOR3);
			PROPERTY_REF(localAxis[2], LocalAxisZ, D3DXVECTOR3);
			PROPERTY_REF(localAxis, LocalAxis, AxisType);

			OBB();
			OBB(D3DXVECTOR3& _center, D3DXVECTOR3 _half);

			float IsInside(const D3DXVECTOR3 & _point);
			D3DXVECTOR3 GetDistance(const D3DXVECTOR3 & _point);
			D3DXVECTOR3 GetNerNormalize(const D3DXVECTOR3 & _vec);
			void Updata(std::shared_ptr<Component::Transform>) override;
			void FormEntity(Resource::Entity::Mesh&) override;

		};

		class Sphere :
			public IShape
		{
			float radius;
			D3DXVECTOR3 center = D3DXVECTOR3(0, 0, 0);
		public:
			PROPERTY_REF(radius, Radius, float);
			PROPERTY_REF(center, Center, D3DXVECTOR3);

			void Updata(std::shared_ptr<Component::Transform>) override;
			void FormEntity(Resource::Entity::Mesh&) override;

		};

	}
}