#pragma once
namespace NeneLabyrinth
{
	namespace Utility
	{
		class TimerServer;
		/// <summary>
		/// �񓯊��ōX�V����^�C�}
		/// �P�ʂ͕b
		/// �J��Ԃ��Ȃ��ꍇ�A�o�߂������ɐ^
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