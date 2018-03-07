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

	HWND hWnd = CreateWindow(className,	// �o�^����Ă���N���X��
		windowName,						// �E�B���h�E��
		WS_OVERLAPPEDWINDOW,			// �E�B���h�E�X�^�C��
		0, 								// �E�B���h�E�̉������̈ʒu
		0, 								// �E�B���h�E�̏c�����̈ʒu
		CW_USEDEFAULT, 					// �E�B���h�E�̕�
		CW_USEDEFAULT, 					// �E�B���h�E�̍���
		nullptr, 						// �e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
		nullptr, 						// ���j���[�n���h���܂��͎q�E�B���h�E ID
		hInstance, 						// �A�v���P�[�V�����C���X�^���X�̃n���h��
		nullptr);						// �E�B���h�E�쐬�f�[�^


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