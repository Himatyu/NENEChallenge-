#pragma once
#include"../Resource/Entity/Mesh.h"
#include"Material.h"
#include"IRenderable.h"
namespace NeneLabyrinth
{
	namespace Rendering
	{
		using namespace Resource;
		class MeshRender :
			public IRenderable
		{
			Entity::Mesh& meshEntity;
			Material& material;
		public:
			MeshRender(Entity::Mesh&, Material&);

			void Render() override;

		};
	}
}
