#pragma once
#include"../Dto/Mesh.h"
#include"Base.h"

#include <string>

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Dao
		{
			class Mesh :
				public Base<typename Dto::Mesh>
			{
			public:
				std::shared_ptr<DTO> From(std::string _filePath) override;
			};
		}
	}
}