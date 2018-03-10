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
			//�f�B���N�g���쐬
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

			//�g�p��Ԃ�
			isUseDebugConsole = true;

			//�n���h���擾
			stdOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);

			// �J�[�\��������
			CONSOLE_CURSOR_INFO cursorInfo;						// �J�[�\�����\����
			::GetConsoleCursorInfo(stdOutput, &cursorInfo);	// �J�[�\�������擾
			cursorInfo.bVisible = FALSE;						// �J�[�\������ύX
			::SetConsoleCursorInfo(stdOutput, &cursorInfo);	// �J�[�\������ݒ�
			::SetConsoleTitle("DebugConsole");					// �^�C�g���ύX

			//�ʒu�E�T�C�Y�ύX
			debugConsoleWinddowHandel = ::GetConsoleWindow();
			HMENU hMenu = ::GetSystemMenu(debugConsoleWinddowHandel, FALSE);
			::MoveWindow
			(debugConsoleWinddowHandel, _posX, _posY, _width, _height, FALSE);

			// ����/�ő剻�𖳌���
			//::RemoveMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
			::RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);

			// �W���o�͐�̕ύX
			freopen_s(&pStdOut, "CON", "w", stdout);

		}
	}
}