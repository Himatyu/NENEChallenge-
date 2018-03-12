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
				ID3D11Buffer* pIndexBuffer;
				size_t vertexSize;
				size_t offset;
				size_t vertexCont;
				size_t faceCont;
				std::string name;
			public:
				PROPERTY_REF_R_ONLY(pVertexBuffer, VertexBuffer, ID3D11Buffer*);
				PROPERTY_REF_R_ONLY(pIndexBuffer, IndexBuffer, ID3D11Buffer*);
				PROPERTY_REF(vertexSize, SizeOfVertex, size_t);
				PROPERTY_REF(offset, Offset, size_t);
				PROPERTY_REF(vertexCont, VertexCont, size_t);
				PROPERTY_REF(faceCont, FaceCont, size_t);
				PROPERTY_REF(name, Name, std::string);

				Mesh();
				~Mesh();
			};
		}
	}
}