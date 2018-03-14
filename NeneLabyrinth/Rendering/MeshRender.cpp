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

			UINT stride = meshEntity.VertexSize;
			UINT offset = meshEntity.Offset;

			graphics.DeviceContext->IASetVertexBuffers(0, 1, &meshEntity.VertexBuffer, &stride, &offset);

			stride = sizeof(int);
			offset = 0;
			graphics.DeviceContext->IASetIndexBuffer(meshEntity.IndexBuffer, DXGI_FORMAT_R32_UINT, 0);


			//プリミティブ・トポロジーをセット
			graphics.DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			//プリミティブをレンダリング
			graphics.DeviceContext->DrawIndexed(meshEntity.FaceCont * 3, 0, 0);

		}
	}
}