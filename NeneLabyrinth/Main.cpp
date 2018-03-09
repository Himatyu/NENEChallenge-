#include <windows.h>
#include "Core/Window.h"
#include"Rendering\Graphics.h"
#include"Core/GamePad.h"

using namespace NeneLabyrinth;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
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

	while (!window.IsReceiveQuitMessage())
	{
		pad.UpdateInputState();

		if (pad.IsUp(pad.A))
		{
			pad.BeginVibration(30000, 3000);
		}

		if (pad.IsDown(pad.LeftStickLeft))
		{
			break;
		}

		//DO Update
		graphics.ClearBackBuffer();

		//DO Rendring
		graphics.Presetnt();
	}

	return 0;
}