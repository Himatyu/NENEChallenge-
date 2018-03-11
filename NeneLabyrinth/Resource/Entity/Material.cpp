#include "Material.h"
#include "Shader.h"

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			Material::Material(Shader* _shader)
			{
				Diffuse = Ambient = Specular = Emissive = { };
				Power = 0;

				pShader = _shader;
			}

			Material::~Material()
			{
			}

		}
	}
}