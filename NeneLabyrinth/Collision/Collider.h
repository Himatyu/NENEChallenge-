#pragma once
#include<utility>
#include<memory>
#include"Shape.h"

namespace NeneLabyrinth
{
	namespace Collision
	{
		template<class T, class U>
		class ICollider
		{
		public:
			using TPointer = T*;
			using UPointer = U*;
			using ShpaePair = std::pair<TPointer, UPointer>;
			bool IsAppropriate(IShape* _pShapeL, IShape* _pShapeR);
			virtual D3DXVECTOR3 Execution(IShape*, IShape*) = 0;
		protected:
			ShpaePair CastShpaes(IShape* _pShapeL, IShape* _pShapeR);

		};
#include"Collider.inl"

		class SphereAndOBB :
			public ICollider<OBB, Sphere>
		{
		public:
			D3DXVECTOR3 Execution(IShape* _pShapeL, IShape* _pShapeR);
		};

	}
}