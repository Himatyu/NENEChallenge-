#pragma once
#include"../Resource/Entity/Mesh.h"
#include"../Rendering/Material.h"
#include"../Rendering/Shader.h"
#include"../Rendering/IRenderable.h"
#include"../Component/IBehavior.h"
#include"../Component/Object.h"
namespace NeneLabyrinth
{
	namespace Component
	{
		using namespace Resource;
		class MeshRender :
			public Rendering::IRenderable,
			public Behavior
		{
			std::shared_ptr<Entity::Mesh> spMeshEntity;
			Rendering::MeshShader shader;
		public:
			PROPERTY_REF(shader, Shader, Rendering::MeshShader);

			MeshRender(Object& _owner, std::string _objPath, std::string _shaderPath);
			~MeshRender();

			void Update() override;
			void Render() override;
		};
	}
}
