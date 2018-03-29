#include"Shape.h"

namespace NeneLabyrinth
{
	namespace Collision
	{
		float GetElementByVector3(int i, const D3DXVECTOR3& _vector)
		{
			float result = -1;
			switch (i)
			{
			case 0:
				result = _vector.x;
				break;
			case 1:
				result = _vector.y;
				break;
			case 2:
				result = _vector.z;
				break;

			default:
				break;
			}
			return result;
		}

		OBB::OBB() :
			center(D3DXVECTOR3(0, 0, 0)),
			half(D3DXVECTOR3(1, 1, 1))
		{
			localAxis[0] = { 1, 0, 0 };
			localAxis[1] = { 0, 1, 0 };
			localAxis[2] = { 0, 0, 1 };
		}

		OBB::OBB(D3DXVECTOR3& _center, D3DXVECTOR3 _half) :
			center(_center),
			half(_half)
		{
			localAxis[0] = { 1, 0, 0 };
			localAxis[1] = { 0, 1, 0 };
			localAxis[2] = { 0, 0, 1 };
		}

		float OBB::IsInside(const D3DXVECTOR3 & _point)
		{
			D3DXVECTOR3 outer = D3DXVECTOR3(0, 0, 0);

			for (int i = 0; i < 3; i++)
			{
				auto halfLen = GetElementByVector3(i, half);
				_ASSERT_EXPR(half >= 0, _T(L"OBBì_ì‡äOîªíËÇ…ÇƒïùñîÇÕçÇÇ≥ñîÇÕâúçsÇ´Ç™ñ≥Ç¢"));

				auto scaleHalf =
					D3DXVec3Dot(&(_point - center), &localAxis[i]) / halfLen;

				scaleHalf = std::abs(scaleHalf);
				if (scaleHalf <= 1)
				{
					continue;
				}

				outer += (1 - scaleHalf) * halfLen * localAxis[i];
			}

			if (outer == D3DXVECTOR3(0, 0, 0))
			{
				return -1;
			}

			return D3DXVec3Length(&outer);
		}

		void OBB::Updata(std::shared_ptr<Component::Transform> _spTransform)
		{
			center = _spTransform->Position;

			auto rotateVec = _spTransform->Rotation;
			D3DXMATRIX rotate;
			D3DXMatrixIdentity(&rotate);
			D3DXMatrixRotationYawPitchRoll(&rotate, rotateVec.y, rotateVec.x, rotateVec.z);

			D3DXVECTOR4 rotatedX;
			D3DXVECTOR4 rotatedY;
			D3DXVECTOR4 rotatedZ;
			D3DXVec3Transform(&rotatedX, &D3DXVECTOR3{ 1, 0, 0 }, &rotate);
			D3DXVec3Transform(&rotatedY, &D3DXVECTOR3{ 0, 1, 0 }, &rotate);
			D3DXVec3Transform(&rotatedZ, &D3DXVECTOR3{ 0, 0, 1 }, &rotate);

			localAxis[0] = { rotatedX.x,rotatedX.y,rotatedX.z };
			localAxis[1] = { rotatedY.x,rotatedY.y,rotatedY.z };
			localAxis[2] = { rotatedZ.x,rotatedZ.y,rotatedZ.z };

			auto crrentScale = _spTransform->Scale;
			half.x *= (prevScale.x / crrentScale.x);
			half.y *= (prevScale.y / crrentScale.y);
			half.z *= (prevScale.z / crrentScale.z);

			prevScale = crrentScale;
		}

		void OBB::FormEntity(Resource::Entity::Mesh & _mesh)
		{
			D3DXVECTOR3 max, min;
			max = min = D3DXVECTOR3(0, 0, 0);
			for (auto& vertex : _mesh.spDto->VertexBuffer)
			{
				auto v = vertex.position;
				max.x = max(max.x, v.x);
				max.y = max(max.y, v.y);
				max.z = max(max.z, v.z);
				min.x = min(min.x, v.x);
				min.y = min(min.y, v.y);
				min.z = min(min.z, v.z);

			}
			center = D3DXVECTOR3(0, 0, 0);
			half = (max - min) / 2;
		}

		void Sphere::Updata(std::shared_ptr<Component::Transform> _spTransform)
		{
			center = _spTransform->Position;
		}

		void Sphere::FormEntity(Resource::Entity::Mesh & _mesh)
		{
			float len = 0;

			for (auto& vertex : _mesh.spDto->VertexBuffer)
			{
				auto v = vertex.position;

				if (len < D3DXVec3Length(&v))
				{
					len = D3DXVec3Length(&v);
				}
			}
			radius = len / 2;
			center = D3DXVECTOR3(0, 0, 0);
		}

	}
}