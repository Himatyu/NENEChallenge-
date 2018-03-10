#pragma once
#include <windows.h>

namespace NeneLabyrinth
{
	namespace Core
	{
		/// <summary>
		/// ESC�܂��͕���{�^���ŏI������Window�𐶐�����
		/// </summary>
		class Window final
		{
			HWND		hWnd;
			HINSTANCE	hInstance;
			LPCTSTR		windowName;
			LPCTSTR		className;
			int			width;
			int			height;
			int			x;
			int			y;

		public:
			Window(
				HINSTANCE	_hInstance,
				LPCTSTR		_windowName = "NeneLabyrinth",
				LPCTSTR		_className = "NeneLabyrinth",
				int			_width = CW_USEDEFAULT,
				int			_height = CW_USEDEFAULT,
				int			_x = CW_USEDEFAULT,
				int			_y = CW_USEDEFAULT
			);

			/// <summary>
			/// �����Əo�����s��
			/// </summary>
			void Create();

			/// <summary>
			/// �I�����߂��󂯎�����ꍇ�^��Ԃ�
			/// </summary>
			bool IsReceiveQuitMessage();

			operator HWND() const;

		private:
			void Preparation();
		};

	}
}
