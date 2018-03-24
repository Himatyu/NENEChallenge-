#pragma once

#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include"IBehavior.h"
#include"../Provider/CameraProvider.h"

namespace NeneLabyrinth
{
	namespace Component
	{
		class Camera :
			public Component::Behavior,
			public IView
		{
			D3DXMATRIX View;
			D3DXMATRIX Proj;
		public:
			Camera(Object& _owner);
			~Camera();

			void Update() override;
			void ViewUpdata();
			D3DXMATRIX GetVPMatrix();

		};
	}
}