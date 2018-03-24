#include "Scene.h"

namespace NeneLabyrinth
{
	namespace Core
	{
		void Scene::Destroy(spObject _spObject)
		{
			objects.remove(_spObject);
		}

		std::shared_ptr<Component::Object> Scene::FindObject(std::string _name)
		{
			auto result =
				Utility::Estd::find_if(
					objects,
					[_name](spObject& _spBehavopr)
			{
				return _spBehavopr->Name == _name;
			});

			return *result;
		}
		void Scene::Initialize()
		{
		}
		void Scene::Updata()
		{
		}
	}
}