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
			virtual bool Execution(IShape*, IShape*) = 0;
		protected:
			ShpaePair CastShpaes(IShape* _pShapeL, IShape* _pShapeR)
			{
				auto pTL = dynamic_cast<TPointer>(_pShapeL);
				auto pUR = dynamic_cast<UPointer>(_pShapeR);

				if (pTL != nullptr && pUR != nullptr)
				{
					return std::make_pair(pTL, pUR);
				}

				auto pTR = dynamic_cast<TPointer>(_pShapeR);
				auto pUL = dynamic_cast<UPointer>(_pShapeL);

				if (pTR != nullptr && pUL != nullptr)
				{
					return std::make_pair(pTR, pUL);
				}

				return std::make_pair(nullptr, nullptr);

			}

		};

		class SphereAndOBB :
			public ICollider<OBB, Sphere>
		{
		public:
			bool Execution(IShape* _pShapeL, IShape* _pShapeR)
			{
				auto pair = CastShpaes(_pShapeL, _pShapeR);
				auto distanceToCenter = pair.first->IsInside(pair.second->Center);

				return distanceToCenter <= pair.second->Radius;
			}
		};
#include"Collider.inl"
	}
}