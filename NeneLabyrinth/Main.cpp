#include <windows.h>
#include "Core/Window.h"
#include"Rendering\Graphics.h"
#include"Core/GamePad.h"

#include"Debug.h"
#include"Timer.h"
#include"TimerServer.h"

using namespace NeneLabyrinth;
using namespace NeneLabyrinth::Utility;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	try
	{
		Core::Window window(
			hInstance,
			"NeneLabyrinth",
			"NeneLabyrinth",
			640,
			480);
		window.Create();

		Rendering::Graphics graphics(window, 640, 480);
		graphics.Initialize();

		Core::GamePad pad;

		Debug::Instantiate().ActivateDebugConsole();
		Debug::Instantiate().IsUseOutputLog = true;
		Debug::Instantiate().IsUseVSDebugOutput = true;
		___D_LOG("TestLog");

		{
			Timer timer(3, true);
			while (!window.IsReceiveQuitMessage())
			{
				pad.UpdateInputState();
				TimerServer::Instantiate().Update();

				if (pad.IsUp(pad.A))
				{
					pad.BeginVibration(30000, 3000);
				}

				if (pad.IsDown(pad.LeftStickLeft) || timer.IsElapsed)
				{
					break;
				}


				//DO Update
				graphics.ClearBackBuffer();

				//DO Rendring
				graphics.Presetnt();
			}
		}
		SingletonFinalizer::Finalize();
	}
	catch (Exception* _e)
	{
		___LOG(_e->Detail);
		delete _e;
	}
	catch (std::exception e)
	{
		___LOG(e.what());
	}
	catch (...)
	{
		___LOG("不明なエラー終了");
	}
	return 0;
}