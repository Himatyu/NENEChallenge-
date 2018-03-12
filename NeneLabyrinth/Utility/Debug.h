
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
		/// �f�o�b�N�T�|�[�g�N���X
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
			/// �o��.
			/// ��{��log.text�ɏo�́A���̃t�@�C���ɏo�͂������ꍇ�Ƀt�@�C�������w�肷��
			/// </summary>
			/// <param name="_msg">���O���b�Z�[�W</param>
			/// <param name="_mapKey">�t�@�C���L�[</param>
			void Log(const std::string& _msg, std::string _mapKey = std::string("Log"));

			/// <summary>
			/// �f�o�b�N�R���\�[�����g�p����
			/// </summary>
			/// <param name="_posX">X���W</param>
			/// <param name="_posY">Y���W</param>
			/// <param name="_width">����</param>
			/// <param name="_height">�c��</param>
			void ActivateDebugConsole(int _posX = 1000, int _posY = 400, int _width = 500, int _height = 400);

		};
	}
}
