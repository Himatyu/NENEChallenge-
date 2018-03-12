#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			class Shader;

			//TODO テクスチャ対応
			//TODO Serviceから作成
			class Material final
			{
				Shader* pShader;
			public:
				PROPERTY_R_ONLY(pShader, pEffect, Shader*);

				Material(Shader* _shader);
				~Material();

				D3DXVECTOR4 Diffuse;
				D3DXVECTOR4 Ambient;
				D3DXVECTOR4 Specular;
				D3DXVECTOR4 Emissive;
				float Power;
			};
		}
	}
}