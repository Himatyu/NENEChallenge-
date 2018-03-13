#include "Material.h"
#include "Shader.h"
#include "Estd.h"

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
			using namespace Utility::Estd;
			std::shared_ptr<Dto::Material> Material::From(std::string _filePath)
			{
				auto spDto = std::make_shared<Dto::Material>();

				std::ifstream fileStream(_filePath);

				if (fileStream.fail())
				{
					___THROW_EXCEPTION_POINT(Utility::Exception, _filePath + "オープン失敗");
				}

				std::string line;

				while (getline(fileStream, line))
				{
					if (line.find("#") != std::string::npos)
					{
						continue;
					}
					if (line.find("usemtl") != std::string::npos)
					{
						spDto->Name = Split(line, ' ')[1];
						continue;
					}

					if (line.find("mtllib") != std::string::npos)
					{
						spDto->MaterialFile = Split(line, ' ')[1];
						continue;
					}
				}

				std::ifstream materialFileStream(spDto->MaterialFile);
				if (materialFileStream.fail())
				{
					___THROW_EXCEPTION_POINT(Utility::Exception, spDto->MaterialFile + "オープン失敗");
				}

				while (getline(materialFileStream, line))
				{
					if (line.find("#") != std::string::npos)
					{
						continue;
					}
					if (line.find("newmtl") != std::string::npos)
					{
						spDto->Name = Split(line, ' ')[1];
						continue;
					}
					if (line.find("Ka") != std::string::npos)
					{
						auto color = Split(line, ' ');
						spDto->Ambient.x = std::atof(color[1].c_str());
						spDto->Ambient.y = std::atof(color[2].c_str());
						spDto->Ambient.z = std::atof(color[3].c_str());
						continue;
					}
					if (line.find("Kd") != std::string::npos)
					{
						auto color = Split(line, ' ');
						spDto->Diffuse.x = std::atof(color[1].c_str());
						spDto->Diffuse.y = std::atof(color[2].c_str());
						spDto->Diffuse.z = std::atof(color[3].c_str());
						continue;
					}
					if (line.find("Ks") != std::string::npos)
					{
						auto color = Split(line, ' ');
						spDto->Specular.x = std::atof(color[1].c_str());
						spDto->Specular.y = std::atof(color[2].c_str());
						spDto->Specular.z = std::atof(color[3].c_str());
						continue;
					}
					if (line.find("Ke") != std::string::npos)
					{
						auto color = Split(line, ' ');
						spDto->Emissive.x = std::atof(color[1].c_str());
						spDto->Emissive.y = std::atof(color[2].c_str());
						spDto->Emissive.z = std::atof(color[3].c_str());
						continue;
					}

					if (line.find("illum") != std::string::npos)
					{
						spDto->Power = std::atof(Split(line, ' ')[1].c_str());
						continue;
					}

				}

				return spDto;
			}

		}
	}
}