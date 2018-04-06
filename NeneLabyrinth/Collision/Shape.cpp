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
			D3DXVECTOR3 outer = GetDistance(_point);

			if (outer == D3DXVECTOR3(0, 0, 0))
			{
				return -1;
			}

			return D3DXVec3Length(&outer);
		}

		D3DXVECTOR3 OBB::GetDistance(const D3DXVECTOR3 & _point)
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
			return outer;
		}

		D3DXVECTOR3 OBB::GetNerNormalize(const D3DXVECTOR3 & _vec)
		{
			std::array<D3DXVECTOR3, 6> normals;
			normals[0] = localAxis[0];
			normals[1] = localAxis[1];
			normals[2] = localAxis[2];
			normals[3] = -localAxis[0];
			normals[4] = -localAxis[1];
			normals[5] = -localAxis[2];

			D3DXVECTOR3 result;
			D3DXVECTOR3 normaled;
			D3DXVec3Normalize(&normaled, &_vec);

			float dot = 0;
			for (auto& v : normals)
			{
				auto d = D3DXVec3Dot(&v, &normaled);

				if (d > dot)
				{
					dot = d;
					result = v;
				}
			}
			return result;
		}

		void OBB::Updata(std::shared_ptr<Component::Transform> _spTransform)
		{
			center = _spTransform->Position;

			auto rotateVec = _spTransform->Rotation;
			D3DXMATRIX rotate;
			D3DXMatrixIdentity(&rotate);
			D3DXMatrixRotationYawPitchRoll(&rotate,
				D3DXToRadian(rotateVec.y),
				D3DXToRadian(rotateVec.x),
				D3DXToRadian(rotateVec.z));

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
			half.x *= (crrentScale.x / prevScale.x);
			half.y *= (crrentScale.y / prevScale.y);
			half.z *= (crrentScale.z / prevScale.z);

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