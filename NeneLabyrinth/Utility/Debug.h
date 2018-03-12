
#pragma once

#include<string>
#include<unordered_map>
#include"Macro.h"
#include"Singleton.h"
namespace NeneLabyrinth
{
	namespace Utility
	{
#ifdef _DEBUG

#define ___D_CALL(function,...)\
		Debug::Instance().function(__VA_ARGS__);

#define	___D_LOG(_msg) \
		::Utility::Debug::Instantiate().Log(_msg);

#else

#define	___D_CALL(function,...)
#define	___D_LOG(_msg)

#endif 

#define ___LOG(_msg) \
		::Utility::Debug::Instantiate().Log(_msg);

		class TextFile;

		/// <summary>
		/// デバックサポートクラス
		/// </summary>
		class Debug final :
			public Singleton<Debug>
		{
			using FileMap = std::unordered_map < std::string, TextFile* >;

			FileMap fileMap;
			std::string fileDirectory;
			int  consoleHandle;
			HANDLE stdOutput;
			HWND	debugConsoleWinddowHandel;
			FILE*	pStdOut;
			bool isUseVSDebugOutput;
			bool isUseOutputLog;
			bool isUseDebugConsole;

		public:

			PROPERTY(isUseVSDebugOutput, IsUseVSDebugOutput, bool);
			PROPERTY(isUseOutputLog, IsUseOutputLog, bool);
			PROPERTY_R_ONLY(isUseDebugConsole, IsUseDebugConsole, bool);
			PROPERTY_R_ONLY(fileDirectory, FileDirectory, std::string);

			Debug();
			~Debug();

			/// <summary>
			/// 出力.
			/// 基本はlog.textに出力、他のファイルに出力したい場合にファイル名を指定する
			/// </summary>
			/// <param name="_msg">ログメッセージ</param>
			/// <param name="_mapKey">ファイルキー</param>
			void Log(const std::string& _msg, std::string _mapKey = std::string("Log"));

			/// <summary>
			/// デバックコンソールを使用する
			/// </summary>
			/// <param name="_posX">X座標</param>
			/// <param name="_posY">Y座標</param>
			/// <param name="_width">横幅</param>
			/// <param name="_height">縦幅</param>
			void ActivateDebugConsole(int _posX = 1000, int _posY = 400, int _width = 500, int _height = 400);

		};
	}
}
