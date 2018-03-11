#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			//TODO ServiceÇ©ÇÁçÏê¨
			class Mesh
			{
				ID3D11Buffer* pVertexBuffer;
				size_t vertexSize;
				size_t offset;
				size_t vertexCont;

			public:
				PROPERTY_R_ONLY(pVertexBuffer, VertexBuffer, ID3D11Buffer*);
				PROPERTY_R_ONLY(vertexSize, SizeOfVertex, size_t);
				PROPERTY_R_ONLY(offset, Offset, size_t);
				PROPERTY_R_ONLY(vertexCont, VertexCont, size_t);

				Mesh();
				~Mesh();
			};
		}
	}
}