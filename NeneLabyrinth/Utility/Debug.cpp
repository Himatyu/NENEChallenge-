#include <windows.h>
#include <tchar.h>
#include <io.h>
#include <Fcntl.h>
#include<direct.h>
#include<iostream>

#include "Debug.h"
#include "TextFile.h"

namespace NeneLabyrinth
{
	namespace Utility
	{
		Debug::Debug() :
			isUseVSDebugOutput(true),
			isUseOutputLog(true),
			isUseDebugConsole(false),
			pStdOut(nullptr)
		{
#ifdef _DEBUG
			fileDirectory = "DebugOutputLog/";
#else
			fileDirectory = "OutputLog/";
#endif 
			//ディレクトリ作成
			_mkdir(fileDirectory.c_str());

#ifdef _DEBUG
			Log("Debug");
#else
			Log("Release");
#endif // _DEBUG
			Log("");
		}

		Debug::~Debug()
		{

			for (auto& it : fileMap)
			{
				(*it.second).Write(it.second->FilePath);
				delete it.second;
			}

			if (pStdOut)
			{
				::fclose(pStdOut);
				pStdOut = nullptr;
			}

			if (isUseDebugConsole)
			{
				FreeConsole();
				isUseDebugConsole = false;
			}
		}

		void Debug::Log(const std::string& _msg, std::string _mapKey)
		{
			if (isUseVSDebugOutput)
			{
#ifdef UNICODE
				std::wstring dest;
				wchar_t *wcs = new wchar_t[_msg.length() + 1];
				mbstowcs(wcs, _msg.c_str(), _msg.length() + 1);
				dest = wcs;
				delete[] wcs;
				OutputDebugString(dest.c_str());
				OutputDebugString("\n");
#else
				OutputDebugString(_msg.c_str());
				OutputDebugString("\n");
#endif
			}

			if (isUseDebugConsole)
			{
				std::cout << _msg << std::endl;
			}

			if (isUseOutputLog)
			{
				auto it = fileMap.find(_mapKey);
				if (it != fileMap.end())
				{
					(*(*it).second).Buffer += _msg + "\n";
					return;
				}
				auto pFile = new TextFile(fileDirectory + _mapKey + ".txt");

				fileMap[_mapKey] = pFile;
				(*pFile).Buffer += _msg + "\n";
			}

		}

		void Debug::ActivateDebugConsole(int _posX, int _posY, int _width, int _height)
		{
			if (isUseDebugConsole || !AllocConsole())
			{
				return;
			}

			//使用状態に
			isUseDebugConsole = true;

			//ハンドル取得
			stdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);

			// カーソルを消す
			CONSOLE_CURSOR_INFO cursorInfo;						// カーソル情報構造体
			::GetConsoleCursorInfo(stdOutput, &cursorInfo);	// カーソル情報を取得
			cursorInfo.bVisible = FALSE;						// カーソル情報を変更
			::SetConsoleCursorInfo(stdOutput, &cursorInfo);	// カーソル情報を設定
			::SetConsoleTitle("DebugConsole");					// タイトル変更

			//位置・サイズ変更
			debugConsoleWinddowHandel = ::GetConsoleWindow();
			HMENU hMenu = ::GetSystemMenu(debugConsoleWinddowHandel, FALSE);
			::MoveWindow
			(debugConsoleWinddowHandel, _posX, _posY, _width, _height, FALSE);

			// 閉じる/最大化を無効化
			//::RemoveMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
			::RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);

			// 標準出力先の変更
			freopen_s(&pStdOut, "CON", "w", stdout);

		}
	}
}