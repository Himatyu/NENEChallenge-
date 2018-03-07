#include <windows.h>

LPCTSTR		windowName = "testWindow";
LPCTSTR		className = "testClass";

LRESULT CALLBACK WindowProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch ((char)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void RegisterWindowClass(HINSTANCE hInstance)
{
	//https://msdn.microsoft.com/ja-jp/library/ms633577.aspx
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(wcex);
	wcex.lpszClassName = className;
	wcex.lpfnWndProc = WindowProc;
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.hInstance = hInstance;
	wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
	wcex.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wcex.hIconSm = ::LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wcex);

}

bool InitializeWindow(HINSTANCE hInstance)
{

	HWND hWnd = CreateWindow(className,	// 登録されているクラス名
		windowName,						// ウィンドウ名
		WS_OVERLAPPEDWINDOW,			// ウィンドウスタイル
		0, 								// ウィンドウの横方向の位置
		0, 								// ウィンドウの縦方向の位置
		CW_USEDEFAULT, 					// ウィンドウの幅
		CW_USEDEFAULT, 					// ウィンドウの高さ
		nullptr, 						// 親ウィンドウまたはオーナーウィンドウのハンドル
		nullptr, 						// メニューハンドルまたは子ウィンドウ ID
		hInstance, 						// アプリケーションインスタンスのハンドル
		nullptr);						// ウィンドウ作成データ


	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return TRUE;
}

bool MessageProc()
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	RegisterWindowClass(hInstance);
	InitializeWindow(hInstance);

	while (MessageProc())
	{
		// Do something
	}

	return 0;
}