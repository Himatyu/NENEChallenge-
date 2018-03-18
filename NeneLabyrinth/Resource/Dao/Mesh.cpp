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
#include <unordered_map>

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
					___THROW_EXCEPTION_POINT(Utility::Exception, _filePath + "ƒI[ƒvƒ“Ž¸”s");
				}

				//¡‰ñ‚Í‚±‚Ì“ñŽ÷—Þ
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
				spDto->VertexSize = sizeof(Vertex);
				spDto->FaceCont = faceCount;

				fileStream.clear();
				fileStream.seekg(0, std::ios_base::beg);

				using data = std::pair<Vertex, int>;

				std::unordered_map < std::string, data> vertexMap;
				using mapValue = std::unordered_map < std::string, data>::value_type;
				int index = 0;

				auto& registerBuffer =
					[&index, &vertexMap, &spDto](std::string _signature, Vertex& _vertex)
				{
					auto findResult = Utility::Estd::find_if(
						vertexMap,
						[_signature](mapValue& _)
					{
						return _.first == _signature;
					});

					if (findResult == std::end(vertexMap))
					{
						auto record = std::make_pair(_vertex, index++);
						vertexMap.insert(std::make_pair(_signature, record));
						spDto->FaceBuffer.push_back(record.second);
						return;
					}
					spDto->FaceBuffer.push_back(findResult->second.second);
				};

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

						Vertex v1, v2, v3;

						v1.position = spDto->Coord[std::atoi(vertex1[0].c_str()) - 1];
						v2.position = spDto->Coord[std::atoi(vertex2[0].c_str()) - 1];
						v3.position = spDto->Coord[std::atoi(vertex3[0].c_str()) - 1];
						v1.normal = spDto->Normal[std::atoi(vertex1[2].c_str()) - 1];
						v2.normal = spDto->Normal[std::atoi(vertex2[2].c_str()) - 1];
						v3.normal = spDto->Normal[std::atoi(vertex3[2].c_str()) - 1];


						registerBuffer(splitedVertex[1], v1);
						registerBuffer(splitedVertex[2], v2);
						registerBuffer(splitedVertex[3], v3);

						continue;
					}
				}

				spDto->VertexBuffer.resize(vertexMap.size());
				spDto->VertexCont = vertexMap.size();

				for (auto& _ : vertexMap)
				{
					auto& record = _.second;

					spDto->VertexBuffer[record.second] = record.first;
				}

				return spDto;
			}
		}
	}
}