#include "MeshRender.h"
#include"Graphics.h"
namespace NeneLabyrinth
{
	namespace Rendering
	{

		MeshRender::MeshRender(Entity::Mesh & _mesh, Material & _material) :
			meshEntity(_mesh),
			material(_material)
		{
		}

		void MeshRender::Render()
		{
			material.Apply();

			auto& graphics = Rendering::Graphics::Instantiate();

			UINT stride = meshEntity.SizeOfVertex;
			UINT offset = meshEntity.Offset;

			auto buffer = meshEntity.VertexBuffer;
			graphics.DeviceContext->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

			//�v���~�e�B�u�E�g�|���W�[���Z�b�g
			graphics.DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			//�v���~�e�B�u�������_�����O
			graphics.DeviceContext->Draw(meshEntity.VertexCont, 0);
		}
	}
}