#include <windows.h>
#include "Core/Window.h"
#include"Rendering\Graphics.h"

using namespace NeneLabyrinth;

#include<Xinput.h>
#pragma comment (lib, "xinput.lib")

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

	XINPUT_STATE state;
	XINPUT_VIBRATION vib{ 10000 ,10000 };

	while (!window.IsReceiveQuitMessage())
	{

		XInputGetState(0, &state);

		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			XInputSetState(0, &vib);
			XInputEnable(true);
		}

		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			break;
		}

		//DO Update
		graphics.ClearBackBuffer();

		//DO Rendring
		graphics.Presetnt();
	}

	XInputEnable(false);

	return 0;
}