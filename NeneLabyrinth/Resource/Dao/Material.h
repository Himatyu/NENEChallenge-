#pragma once
#include"../Dto/Material.h"
#include"Base.h"

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Dao
		{
			class Material :
				public Base<Dto::Material>
			{
			public:
				std::shared_ptr<DTO> From(std::string _filePath) override;
			};
		}
	}
}