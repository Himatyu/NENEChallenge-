#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>

#include"Base.h"
#include"../Dto/Mesh.h"
#include"../Dao/Mesh.h"
namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			class Mesh :
				public Base<Dao::Mesh>
			{
				ID3D11Buffer* pVertexBuffer;
				ID3D11Buffer* pIndexBuffer;

				std::string name;
				std::string materialFile;
				std::string materialName;

				size_t vertexSize;
				size_t offset;
				size_t vertexCont;
				size_t normalCount;
				size_t faceCont;
			public:

				PROPERTY_REF_R_ONLY(pVertexBuffer, VertexBuffer, ID3D11Buffer*);
				PROPERTY_REF_R_ONLY(pIndexBuffer, IndexBuffer, ID3D11Buffer*);

				PROPERTY_REF_R_ONLY(name, Name, std::string);
				PROPERTY_REF_R_ONLY(materialFile, MaterialFile, std::string);
				PROPERTY_REF_R_ONLY(materialName, MaterialName, std::string);

				PROPERTY_REF_R_ONLY(vertexSize, VertexSize, size_t);
				PROPERTY_REF_R_ONLY(offset, Offset, size_t);
				PROPERTY_REF_R_ONLY(vertexCont, VertexCont, size_t);
				PROPERTY_REF_R_ONLY(normalCount, NormalCount, size_t);
				PROPERTY_REF_R_ONLY(faceCont, FaceCont, size_t);

				Mesh(std::shared_ptr<DTO> _spDto);
				~Mesh();
			};
		}
	}
}