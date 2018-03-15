#pragma once

#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include"IBehavior.h"

namespace NeneLabyrinth
{
	namespace Component
	{
		class Behavior;
		class Transform :
			public IBehavior
		{
			D3DXMATRIX		world;

			D3DXVECTOR3		position;
			D3DXVECTOR3		rotate;
			D3DXVECTOR3		scale;
		public:

			__declspec(property(get = GetForward)) D3DXVECTOR3 Forward;
			__declspec(property(get = GetRigth)) D3DXVECTOR3 Rigth;
			__declspec(property(get = GetUp)) D3DXVECTOR3 Up;

			PROPERTY_REF(position, Position, D3DXVECTOR3);
			PROPERTY_REF(rotate, Rotation, D3DXVECTOR3);
			PROPERTY_REF(scale, Scale, D3DXVECTOR3);
			PROPERTY_REF(world, World, D3DXMATRIX);

			D3DXVECTOR3 GetRigth();
			D3DXVECTOR3 GetUp();
			D3DXVECTOR3 GetForward();

			Transform(Behavior&);
			void Update()override;

		};
	}
}