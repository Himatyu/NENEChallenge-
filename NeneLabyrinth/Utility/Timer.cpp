#include"Timer.h"
#include"TimerServer.h"

namespace NeneLabyrinth
{
	namespace Utility
	{
		Timer::Timer(double _time, bool _isActive, bool _isOnce) :
			rest(_time),
			setTime(_time),
			isActive(_isActive),
			isOnce(_isOnce),
			isElapsed(false)
		{
			auto& server = TimerServer::Instantiate();
			server.Register(this);
		}

		Timer::~Timer()
		{
			auto& server = TimerServer::Instantiate();
			ASSERT_EXPR(&server != nullptr, L"TimerServer‚æ‚è‚àŽõ–½‚ª’·‚¢Timer‚ª‚ ‚è‚Ü‚·");
			server.UnRegister(this);
		}

		void Timer::Reset(double newTime)
		{
			isElapsed = false;
			if (newTime == -1)
			{
				rest = setTime;
				return;
			}
			setTime = rest = newTime;

		}

		void Timer::Update()
		{
			if (!isActive)
			{
				return;
			}
			if (isElapsed)
			{
				if (isOnce)
				{
					return;
				}
				isActive = true;
				Reset(setTime);
				return;
			}
			rest -= TimerServer::DeltaTime;
			if (rest <= 0)
			{
				isElapsed = true;
			}
		}

		void Timer::SetTimeNotify()
		{
			rest = setTime;
		}

	}
}