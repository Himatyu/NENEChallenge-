#include "Mesh.h"
#include"../Dto/Mesh.h"
#include"Estd.h"
#include"../Rendering\Graphics.h"
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Dao
		{
			using Vertex = Dto::Vertex;
			using namespace Utility::Estd;

			std::shared_ptr<Dto::Mesh> Mesh::From(std::string _filePath)
			{
				auto spDto = std::make_shared<Dto::Mesh>();

				std::ifstream fileStream(_filePath);

				if (fileStream.fail())
				{
					___THROW_EXCEPTION_POINT(Utility::Exception, _filePath + "オープン失敗");
				}

				//今回はこの二樹類
				int vertexCount = 0;
				int normalCount = 0;
				int faceCount = 0;

				std::string line;
				std::string Name;
				std::string materialFile;

				while (getline(fileStream, line))
				{
					if (line.find("#") != std::string::npos)
					{
						continue;
					}

					if (line.find("o") != std::string::npos)
					{
						continue;
					}
					if (line.find("s") != std::string::npos)
					{
						continue;
					}
					if (line.find("mtllib") != std::string::npos)
					{
						auto splited = Split(line, ' ');
						spDto->MaterialFile = splited[1];
						continue;
					}
					if (line.find("usemtl") != std::string::npos)
					{
						auto splited = Split(line, ' ');
						spDto->MaterialName = splited[1];
						continue;
					}

					if (line.find("vn") != std::string::npos)
					{
						normalCount++;
						continue;
					}
					if (line.find("v") != std::string::npos)
					{
						vertexCount++;
						continue;
					}
					if (line.find("f") != std::string::npos)
					{
						faceCount++;
						continue;
					}
				}

				spDto->Name = Name;
				spDto->VertexCont = vertexCount;
				spDto->VertexSize = sizeof(Vertex);
				spDto->FaceCont = faceCount;

				spDto->VertexBuffer.resize(spDto->VertexCont);

				fileStream.clear();
				fileStream.seekg(0, std::ios_base::beg);

				while (getline(fileStream, line))
				{
					if (line.find("#") != std::string::npos)
					{
						continue;
					}

					if (line.find("o") != std::string::npos)
					{
						continue;
					}
					if (line.find("s") != std::string::npos)
					{
						continue;
					}
					if (line.find("mtllib") != std::string::npos)
					{
						continue;
					}
					if (line.find("usemtl") != std::string::npos)
					{
						continue;
					}
					if (line.find("vn") != std::string::npos)
					{
						auto splited = Split(line, ' ');
						D3DXVECTOR3 normal;
						normal.x = -std::atof(splited[1].c_str());
						normal.y = std::atof(splited[2].c_str());
						normal.z = std::atof(splited[3].c_str());
						spDto->Normal.push_back(normal);
						continue;
					}
					if (line.find("v") != std::string::npos)
					{
						auto splited = Split(line, ' ');
						D3DXVECTOR3 coord;

						coord.x = -std::atof(splited[1].c_str());
						coord.y = std::atof(splited[2].c_str());
						coord.z = std::atof(splited[3].c_str());
						spDto->Coord.push_back(coord);
						continue;
					}
					if (line.find("f") != std::string::npos)
					{
						auto splitedVertex = Split(line, ' ');
						auto vertex1 = Split(splitedVertex[1], '//');
						auto vertex2 = Split(splitedVertex[2], '//');
						auto vertex3 = Split(splitedVertex[3], '//');

						auto v1Index = std::atoi(vertex1[0].c_str()) - 1;
						auto v2Index = std::atoi(vertex2[0].c_str()) - 1;
						auto v3Index = std::atoi(vertex3[0].c_str()) - 1;

						spDto->FaceBuffer.push_back(v1Index);
						spDto->FaceBuffer.push_back(v2Index);
						spDto->FaceBuffer.push_back(v3Index);

						Vertex v1, v2, v3;

						v1.position = spDto->Coord[std::atoi(vertex1[0].c_str()) - 1];
						v2.position = spDto->Coord[std::atoi(vertex2[0].c_str()) - 1];
						v3.position = spDto->Coord[std::atoi(vertex3[0].c_str()) - 1];
						v1.normal = spDto->Normal[std::atoi(vertex1[2].c_str()) - 1];
						v2.normal = spDto->Normal[std::atoi(vertex2[2].c_str()) - 1];
						v3.normal = spDto->Normal[std::atoi(vertex3[2].c_str()) - 1];

						spDto->VertexBuffer[v1Index] = v1;
						spDto->VertexBuffer[v2Index] = v2;
						spDto->VertexBuffer[v3Index] = v3;

						continue;
					}
				}

				return spDto;
			}
		}
	}
}