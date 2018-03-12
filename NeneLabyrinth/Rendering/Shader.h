#pragma once
#include"../Resource/Entity/Shader.h"
namespace NeneLabyrinth
{
	namespace Rendering
	{
		class Shader
		{
			Resource::Entity::Shader& entity;
		public:
			Shader(Resource::Entity::Shader& _entity);

			template<class Buffer>
			void DatePush(Buffer* _buffer);
			void Apply();
		};
#include"Shader.inl"
	}
}