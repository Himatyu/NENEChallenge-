#pragma once
#include<memory>
#include<string>
namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Dao
		{
			template<class Dto>
			class Base
			{
			public:
				using DTO = Dto;

				virtual std::shared_ptr<Dto> From(std::string _filePath) = 0;
			};
		}
	}
}