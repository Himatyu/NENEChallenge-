#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>

#include"Base.h"
#include"../Dto/Material.h"
#include"../Dao/Material.h"

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			class Shader;

			class Material final :
				public Base<Dao::Material>
			{
			public:

				D3DXVECTOR4 Diffuse;
				D3DXVECTOR4 Ambient;
				D3DXVECTOR4 Specular;
				D3DXVECTOR4 Emissive;
				float Power;

				std::string Name;
				std::string MaterialFile;

				Material(std::shared_ptr<DTO> _spDto);
				~Material();
			};
		}
	}
}