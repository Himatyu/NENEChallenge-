#include <windows.h>
#include "Core/Window.h"
using namespace NeneLabyrinth;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	Core::Window window(hInstance);
	window.Create();

	while (!window.IsReceiveQuitMessage())
	{
		// Do something
	}

	return 0;
}