#pragma once
#include"../Resource/Entity/Material.h"
#include"Shader.h"
namespace NeneLabyrinth
{
	namespace Rendering
	{
		class Material
		{
			Resource::Entity::Material& entity;
			Shader& shader;
		public:
			Material(Resource::Entity::Material& entity, Shader& _shader);

			void Apply();

		};
	}
}