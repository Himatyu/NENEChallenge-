#pragma once
#include<list>
#include<memory>
#include"Estd.h"
#include"../Component/Object.h"

namespace NeneLabyrinth
{
	namespace Core
	{
		///コンストラクタでshard_form_thisを使うと例外
		/// APP側でコンストラクタ完了後にsp作ってるから
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

