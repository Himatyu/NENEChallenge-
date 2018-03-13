#include "Material.h"
#include "Shader.h"

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			Material::Material(std::shared_ptr<DTO> _spDto) :
				Base(_spDto)
			{
				Diffuse = _spDto->Diffuse;
				Ambient = _spDto->Ambient;
				Specular = _spDto->Specular;
				Emissive = _spDto->Emissive;
				Power = _spDto->Power;
			}

			Material::~Material()
			{
			}

		}
	}
}