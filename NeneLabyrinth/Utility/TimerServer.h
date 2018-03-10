#pragma once
#include<chrono>
#include<vector>
#include"Singleton.h"

namespace NeneLabyrinth
{
	namespace Utility
	{
		class Timer;
		/// <summary>
		/// フレーム感覚と時間倍率を所持する
		/// 単位はミリ秒
		/// </summary>
		class TimerServer final :
			public Utility::Singleton<TimerServer>
		{
			friend class Timer;

			std::vector<Timer*>						timers;
			std::chrono::system_clock::time_point	start;
			std::chrono::system_clock::time_point	end;

		public:
			static float DeltaTime;
			static float TimeScale;

			TimerServer();
			~TimerServer();

			/// <summary>
			/// フレーム感覚と時間倍率を更新
			/// タイマーの更新を行う
			/// </summary>
			void Update();

		private:
			void Register(Timer* _pTimer);
			void UnRegister(Timer* _pTimer);
		};
	}
}
