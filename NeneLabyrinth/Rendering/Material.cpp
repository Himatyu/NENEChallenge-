#include "Material.h"

namespace NeneLabyrinth
{
	namespace Rendering
	{

		Material::Material(Resource::Entity::Material & _entity, Shader & _shader) :
			entity(_entity),
			shader(_shader)
		{

		}

		void Material::Apply()
		{
			//Fî•ñ‚Ìpush

			shader.Apply();
		}
	}
}


