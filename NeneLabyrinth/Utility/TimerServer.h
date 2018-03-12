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
		/// �t���[�����o�Ǝ��Ԕ{������������
		/// �P�ʂ̓~���b
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
			/// �t���[�����o�Ǝ��Ԕ{�����X�V
			/// �^�C�}�[�̍X�V���s��
			/// </summary>
			void Update();

		private:
			void Register(Timer* _pTimer);
			void UnRegister(Timer* _pTimer);
		};
	}
}
