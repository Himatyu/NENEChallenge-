#include "MeshRender.h"
#include"../Rendering/Graphics.h"
#include"../Provider/RenderProvider.h"
#include"../Provider/CameraProvider.h"
#include"../Resource/Service.h"
#include"../Component/Transform.h"
#include"IBehavior.h"
namespace NeneLabyrinth
{
	namespace Component
	{

		MeshRender::MeshRender(Behavior& _owner, std::string _path, std::string _shaderPath) :
			IBehavior(_owner, typeid(MeshRender)),
			shader(_shaderPath)
		{
			spMeshEntity = Resource::Service::Instantiate().CreateEntity<Entity::Mesh>(_path);
			Rendering::RenderProvider::Instantiate().Register(this);

			shader.Configurate();
		}
		MeshRender::~MeshRender()
		{
			Rendering::RenderProvider::Instantiate().UnRegister(this);
		}

		void MeshRender::Update()
		{
			auto pView = CameraProvider::Instantiate().pCurrent;
			auto spTransform = Owner.GetComponent <Component::Transform>();
			shader.Buffer.WVP = spTransform->World* pView->GetVPMatrix();
			D3DXMatrixTranspose(&shader.Buffer.WVP, &shader.Buffer.WVP);

			shader.Buffer.W = spTransform->World;
			D3DXMatrixTranspose(&shader.Buffer.W, &shader.Buffer.W);
		}

		void MeshRender::Render()
		{
			shader.Apply();

			auto& graphics = Rendering::Graphics::Instantiate();

			UINT stride = spMeshEntity->VertexSize;
			UINT offset = spMeshEntity->Offset;

			graphics.DeviceContext->IASetVertexBuffers(0, 1, &spMeshEntity->VertexBuffer, &stride, &offset);

			stride = sizeof(int);
			offset = 0;
			graphics.DeviceContext->IASetIndexBuffer(spMeshEntity->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);


			//プリミティブ・トポロジーをセット
			graphics.DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			//プリミティブをレンダリング
			graphics.DeviceContext->DrawIndexed(spMeshEntity->FaceCont * 3, 0, 0);

		}

	}
}