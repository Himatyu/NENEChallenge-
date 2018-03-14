#include "Mesh.h"
#include "../Rendering/Graphics.h"
#include"../Dto/Mesh.h"

#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			Mesh::Mesh(std::shared_ptr<DTO> _spDto) :
				Base(_spDto),
				vertexSize(_spDto->VertexSize),
				offset(_spDto->Offset),
				vertexCont(_spDto->VertexCont),
				normalCount(_spDto->NormalCount),
				faceCont(_spDto->FaceCont)
			{

				auto& graphics = Rendering::Graphics::Instantiate();

				//バーテックスバッファーを作成
				D3D11_BUFFER_DESC bd;
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(Dto::Vertex) * VertexCont;
				bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				bd.CPUAccessFlags = 0;
				bd.MiscFlags = 0;
				D3D11_SUBRESOURCE_DATA InitData;
				InitData.pSysMem = spDto->VertexBuffer.data();
				if (FAILED(graphics.Device->CreateBuffer(&bd, &InitData, &pVertexBuffer)))
				{
					___THROW_EXCEPTION_POINT(Utility::Exception, "VertexBuffer失敗");
				}

				//インデックスバッファーを作成
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(int) * FaceCont * 3;
				bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
				bd.CPUAccessFlags = 0;
				bd.MiscFlags = 0;
				InitData.pSysMem = spDto->FaceBuffer.data();
				InitData.SysMemPitch = 0;
				InitData.SysMemSlicePitch = 0;
				if (FAILED(graphics.Device->CreateBuffer(&bd, &InitData, &pIndexBuffer)))
				{
					___THROW_EXCEPTION_POINT(Utility::Exception, "IndexBuffer失敗");
				}
			}

			Mesh::~Mesh()
			{
				SAFE_RELEASE(pVertexBuffer);
				SAFE_RELEASE(pIndexBuffer);
			}
		}
	}
}