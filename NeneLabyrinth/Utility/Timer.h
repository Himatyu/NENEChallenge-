#pragma once
namespace NeneLabyrinth
{
	namespace Utility
	{
		class TimerServer;
		/// <summary>
		/// 非同期で更新するタイマ
		/// 単位は秒
		/// 繰り返さない場合、経過した後常に真
		/// </summary>
		class Timer final
		{
			friend class TimerServer;

			bool isElapsed;
			bool isOnce;
			bool isActive;

			double	setTime, rest;

		public:
			PROPERTY_CR_R_ONLY(isElapsed, IsElapsed, bool);
			PROPERTY_REF(isOnce, IsOnce, bool);
			PROPERTY_REF(isActive, IsActive, bool);
			PROPERTY_REF_W_HOOKABLE(setTime, SetTime, double, SetTimeNotify);

			Timer(double _time, bool _isActive = false, bool isOnce = false);
			~Timer();

			void Reset(double newTime = -1);

		private:
			void Update();
			void SetTimeNotify();
		};
	}
}

//-----------------------------------------------------------
// EOF
//-----------------------------------------------------------