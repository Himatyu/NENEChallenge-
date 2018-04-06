#include "Collider.h"

namespace NeneLabyrinth
{
	namespace Collision
	{
		D3DXVECTOR3 SphereAndOBB::Execution(IShape * _pShapeL, IShape * _pShapeR)
		{
			auto pair = CastShpaes(_pShapeL, _pShapeR);
			auto distanceToCenter = pair.first->IsInside(pair.second->Center);
			bool isCollision = distanceToCenter <= pair.second->Radius;

			if (isCollision)
			{
				auto toNearOBB = pair.first->GetDistance(pair.second->Center);
				D3DXVECTOR3 nor;
				D3DXVec3Normalize(&nor, &toNearOBB);
				auto origin = nor*pair.second->Radius;
				auto resistance = -origin + toNearOBB;
				auto resistanceDirect = pair.first->GetNerNormalize(resistance);
				auto result = resistanceDirect * D3DXVec3Length(&resistance);
				return result;
			}
			return D3DXVECTOR3(0, 0, 0);
		}
	}
}