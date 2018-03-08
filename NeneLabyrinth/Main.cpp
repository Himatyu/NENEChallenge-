#include <windows.h>
#include "Core/Window.h"
#include"Rendering\Graphics.h"
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

	while (!window.IsReceiveQuitMessage())
	{
		//DO Update
		graphics.ClearBackBuffer();

		//DO Rendring
		graphics.Presetnt();
	}

	return 0;
}