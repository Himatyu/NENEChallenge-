#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include "Transform.h"

namespace NeneLabyrinth
{
	namespace Component
	{
		D3DXVECTOR3 Transform::GetRigth()
		{
			return D3DXVECTOR3(world._11, world._12, world._13);
		}
		D3DXVECTOR3 Transform::GetUp()
		{
			return D3DXVECTOR3(world._21, world._22, world._33);
		}
		D3DXVECTOR3 Transform::GetForward()
		{
			return D3DXVECTOR3(world._31, world._32, world._33);
		}

		Transform::Transform() :
			position(0, 0, 0),
			rotate(0, 0, 0),
			scale(1, 1, 1)
		{
		}

		void Transform::Update()
		{
			D3DXMATRIX		matTrans;
			D3DXMATRIX		matRotate;
			D3DXMATRIX		matScale;

			D3DXMatrixIdentity(&world);
			D3DXMatrixIdentity(&matTrans);
			D3DXMatrixIdentity(&matRotate);
			D3DXMatrixIdentity(&matScale);

			D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
			D3DXMatrixRotationYawPitchRoll(&matRotate,
				D3DXToRadian(rotate.y),
				D3DXToRadian(rotate.x),
				D3DXToRadian(rotate.z));
			D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

			world = matScale * matRotate *  matTrans;
		}
	}
}