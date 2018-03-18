#pragma once
#include<memory>

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			template<class Dao>
			class Base
			{
			protected:
			public:
				std::shared_ptr<typename Dao::DTO> spDto;//TODO ê›åv
				using DAO = Dao;
				using DTO = typename Dao::DTO;

				Base(std::shared_ptr<DTO> _spDto) :
					spDto(_spDto)
				{
				}
			};
		}
	}
}