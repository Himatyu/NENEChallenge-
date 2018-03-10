#include"TimerServer.h"
#include"Timer.h"
#include"Estd.h"

using namespace std::chrono;
using namespace std::literals::chrono_literals;

namespace NeneLabyrinth
{
	namespace Utility
	{
		float TimerServer::DeltaTime = 0;
		float TimerServer::TimeScale = 1.0;

		TimerServer::TimerServer()
		{
			start = system_clock::now();
		}

		TimerServer::~TimerServer()
		{

		}

		void TimerServer::Update()
		{
			end = system_clock::now();
			auto elapsed = end - start;
			DeltaTime =
				static_cast<float>(
					duration_cast<duration<double, std::ratio<1, 1>>>(elapsed)
					.count() * TimeScale);
			start = system_clock::now();

			Estd::for_each(timers, [&](Timer* _) {_->Update(); });
		}

		void TimerServer::Register(Timer * _pTimer)
		{
			auto result = Estd::find(timers, _pTimer);
			if (result != timers.end())
			{
				return;
			}
			timers.push_back(_pTimer);
		}

		void TimerServer::UnRegister(Timer * _pTimer)
		{
			Estd::remove_if(timers, [_pTimer](Timer* _) {return _ == _pTimer; });
		}
	}
}
