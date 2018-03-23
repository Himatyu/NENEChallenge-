#pragma once
#include"../Resource/Entity/Material.h"
#include"Shader.h"
namespace NeneLabyrinth
{
	namespace Rendering
	{
		class IMaterial
		{
		protected:
			IShader& shader;
		public:
			IMaterial(IShader& _shader);
			virtual void Apply() = 0;
		};

		class Material :
			public IMaterial
		{
			D3DXVECTOR4 diffuse;
			D3DXVECTOR4 ambient;
			D3DXVECTOR4 specular;
			D3DXVECTOR4 emissive;
			float power;
		public:
			PROPERTY_REF(diffuse, Diffuse, D3DXVECTOR4);
			PROPERTY_REF(ambient, Ambient, D3DXVECTOR4);
			PROPERTY_REF(specular, Specular, D3DXVECTOR4);
			PROPERTY_REF(emissive, Emissive, D3DXVECTOR4);
			PROPERTY_REF(power, Power, float);

			Material(std::string _objPath, IShader& _shader);

			void Apply() override;

		};
	}
}