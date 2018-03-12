#pragma once
#include <windows.h>

namespace NeneLabyrinth
{
	namespace Core
	{
		/// <summary>
		/// ESCまたは閉じるボタンで終了するWindowを生成する
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
			/// 生成と出現を行う
			/// </summary>
			void Create();

			/// <summary>
			/// 終了命令を受け取った場合真を返す
			/// </summary>
			bool IsReceiveQuitMessage();

			operator HWND() const;

		private:
			void Preparation();
		};

	}
}
