#pragma once
#include"Base.h"
#include"../Dto/Shader.h"
namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Dao
		{
			class Shader :
				public Base<Dto::Shader>
			{
			public:
				std::shared_ptr<DTO> From(std::string _filePath) override;
			};
		}
	}
}