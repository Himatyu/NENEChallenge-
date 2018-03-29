#include "Material.h"
#include "../Resource/Entity/Material.h"
#include "../Resource/Service.h"

namespace NeneLabyrinth
{
	namespace Rendering
	{
		IMaterial::IMaterial(IShader & _shader) :
			shader(_shader)
		{

		}

		Material::Material(std::string _path, IShader& _shader) :
			IMaterial(_shader)
		{
			auto spEntity = Resource::Service::Instantiate()
				.CreateEntity<Resource::Entity::Material>(_path);

			Diffuse = spEntity->Diffuse;
			Ambient = spEntity->Ambient;
			Specular = spEntity->Specular;
			Emissive = spEntity->Emissive;
		}

		void Material::Apply()
		{
			//Fî•ñ‚Ìpush

			shader.Apply();
		}


	}
}


