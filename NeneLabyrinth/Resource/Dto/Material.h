#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Dto
		{
			class Material
			{
			public:
				D3DXVECTOR4 Diffuse;
				D3DXVECTOR4 Ambient;
				D3DXVECTOR4 Specular;
				D3DXVECTOR4 Emissive;
				float Power;

				std::string Name;
				std::string MaterialFile;
			};
		}
	}
}