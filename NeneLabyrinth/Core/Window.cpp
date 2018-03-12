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
			hWnd = CreateWindow(className,	// �o�^����Ă���N���X��
				windowName,						// �E�B���h�E��
				WS_OVERLAPPEDWINDOW,			// �E�B���h�E�X�^�C��
				x, 								// �E�B���h�E�̉������̈ʒu
				y, 								// �E�B���h�E�̏c�����̈ʒu
				width, 							// �E�B���h�E�̕�
				height, 						// �E�B���h�E�̍���
				nullptr, 						// �e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
				nullptr, 						// ���j���[�n���h���܂��͎q�E�B���h�E ID
				hInstance, 						// �A�v���P�[�V�����C���X�^���X�̃n���h��
				nullptr);						// �E�B���h�E�쐬�f�[�^

			if (!hWnd)
			{
				___THROW_EXCEPTION(Utility::Exception, "�E�B���h�E�����Ɏ��s");
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