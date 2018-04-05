#pragma once
#include"Singleton.h"
#include"IProvider.h"
#include"../Component/Colldee.h"

namespace NeneLabyrinth
{
	namespace Collision
	{
		class CollisionProvider :
			public Utility::IProvider<Component::IColldee>,
			public Utility::Singleton<CollisionProvider>
		{
			enum State
			{
				Enter,
				Stay,
				Exit,
			};
			SphereAndOBB collider;
		public:
			using RegisterRecord =
				std::tuple<Component::IColldee*, Component::IColldee*, State, bool, D3DXVECTOR3>;
		private:
			std::vector<RegisterRecord> records;
		public:
			void Dispatch() override;
		};
	}
}