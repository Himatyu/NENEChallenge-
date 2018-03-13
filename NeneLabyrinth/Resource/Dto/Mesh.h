#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Dto
		{
			struct Vertex
			{
				D3DXVECTOR3 position;
				D3DXVECTOR3 normal;
			};

			class Mesh
			{
			public:
				std::string Name;
				std::string MaterialFile;
				std::string MaterialName;

				std::vector<Vertex> VertexBuffer;
				std::vector<D3DXVECTOR3> Coord;
				std::vector<D3DXVECTOR3> Normal;
				std::vector<int> FaceBuffer;

				size_t VertexSize;
				size_t Offset;
				size_t VertexCont;
				size_t NormalCount;
				size_t FaceCont;
			};
		}
	}
}