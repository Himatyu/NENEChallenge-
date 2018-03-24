#pragma once
#include<list>
#include<memory>
#include"Estd.h"
#include"../Component/Object.h"

namespace NeneLabyrinth
{
	namespace Core
	{
		///�R���X�g���N�^��shard_form_this���g���Ɨ�O
		/// APP���ŃR���X�g���N�^�������sp����Ă邩��
		class Scene :
			public std::enable_shared_from_this<Scene>
		{
			std::list<std::shared_ptr<Component::Object>> objects;
		protected:
			using spObject = std::shared_ptr<Component::Object>;

			template <class Type, class ...Param>
			std::shared_ptr<Type> Instantiate(Param&&...);

			spObject FindObject(std::string _name);

		public:
			virtual void Initialize();
			virtual void Updata();
			void Destroy(spObject _spObject);
		};

		template<class Type, class ...Param>
		inline std::shared_ptr<Type> Scene::Instantiate(Param && ...)
		{
			auto& ins =
				std::make_shared<Type>(shared_from_this(), std::forward<Param>(_param)...);

			objects.push_back(ins);

			return ins;
		}
	}
}

