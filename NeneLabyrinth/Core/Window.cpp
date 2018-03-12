#include "Window.h"
#pragma comment(lib,"winmm.lib")

namespace NeneLabyrinth
{
	namespace Core
	{
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

		Window::Window(
			HINSTANCE _hInstance,
			LPCTSTR _windowName,
			LPCTSTR _className,
			int _width,
			int _height,
			int _x,
			int _y) :
			hInstance(_hInstance),
			windowName(_windowName),
			className(_className),
			width(_width),
			height(_height),
			x(_x),
			y(_y)
		{
			Preparation();
		}

		void Window::Create()
		{
			hWnd = CreateWindow(className,	// 登録されているクラス名
				windowName,						// ウィンドウ名
				WS_OVERLAPPEDWINDOW,			// ウィンドウスタイル
				x, 								// ウィンドウの横方向の位置
				y, 								// ウィンドウの縦方向の位置
				width, 							// ウィンドウの幅
				height, 						// ウィンドウの高さ
				nullptr, 						// 親ウィンドウまたはオーナーウィンドウのハンドル
				nullptr, 						// メニューハンドルまたは子ウィンドウ ID
				hInstance, 						// アプリケーションインスタンスのハンドル
				nullptr);						// ウィンドウ作成データ

			if (!hWnd)
			{
				___THROW_EXCEPTION(Utility::Exception, "ウィンドウ生成に失敗");
				return;
			}

			ShowWindow(hWnd, SW_SHOW);
			UpdateWindow(hWnd);
		}

		Window::operator HWND() const
		{
			return hWnd;
		}

		bool Window::IsReceiveQuitMessage()
		{
			MSG msg;
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					return true;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return false;
		}

		void Window::Preparation()
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
	}
}