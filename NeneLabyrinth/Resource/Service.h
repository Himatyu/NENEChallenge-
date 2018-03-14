#pragma once
#include<unordered_map>
#include<typeindex>
#include<memory>
#include"Estd.h"
#include"Singleton.h"
namespace NeneLabyrinth
{
	namespace Resource
	{
		class Service :
			public Utility::Singleton<Service>
		{
			using EntityRecord = std::unordered_map<std::string, std::shared_ptr<void>>;
			using Database = std::unordered_map<std::type_index, EntityRecord>;

			Database database;
		public:

			template<class Entity>
			std::shared_ptr<Entity> CreateEntity(std::string _filePath)
			{
				using DAO = Entity::DAO;
				using DTO = Entity::DTO;

				//TODO 登録済みオブジェクトの検索

				DAO dao;
				auto spDto = dao.From(_filePath);
				auto spEntity = std::make_shared<Entity>(spDto);

				database.emplace(typeid(Entity), EntityRecord());
				database[typeid(Entity)][_filePath] = spEntity;

				return spEntity;
			}
		};

	}
}