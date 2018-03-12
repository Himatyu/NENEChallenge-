#pragma once
#include<exception>
#include<string>
#include"Macro.h"
namespace NeneLabyrinth
{
	namespace Utility
	{
		/// <summary>
		/// �����ӏ����擾����O�𓊂���
		/// </summary>
#define ___THROW_EXCEPTION(EXCEPTION_TYPE, message) \
  throw EXCEPTION_TYPE( __FILE__, __func__, __LINE__,message) 

/// <summary>
/// �����ӏ����擾����O�|�C���^�𓊂���
/// </summary>
#define ___THROW_EXCEPTION_POINT(EXCEPTION_TYPE, message) \
  throw new EXCEPTION_TYPE( __FILE__, __func__, __LINE__,message) 

/// <summary>
/// ��O�N���X.
/// ��{�̓}�N�����g��.
/// </summary>
		class Exception :
			public std::exception
		{
			/// <summary>
			/// ��O���e
			/// </summary>
			std::string summary;

			/// <summary>
			/// ���������t�@�C��
			/// </summary>
			std::string fileName;

			/// <summary>
			/// ���������֐�
			/// </summary>
			std::string functionName;

			/// <summary>
			/// ���e�Ɣ����ӏ�
			/// </summary>
			std::string detail;

			/// <summary>
			/// �����s��
			/// </summary>
			int			line;

		public:

			PROPERTY_CR_R_ONLY(summary, Summary, std::string);
			PROPERTY_CR_R_ONLY(fileName, Filename, std::string);
			PROPERTY_CR_R_ONLY(functionName, FunctionName, std::string);
			PROPERTY_CR_R_ONLY(detail, Detail, std::string);
			PROPERTY_CR_R_ONLY(line, Line, int);

			/// <summary>
			/// �����ӏ��̓�����s��Ȃ���O
			/// </summary>
			/// <param name="_msg">���b�Z�[�W</param>
			explicit Exception(const std::string& _msg = "Unknown exception");

			/// <summary>
			/// �����ӏ����������O
			/// </summary>
			/// <param name="_file">�����t�@�C��</param>
			/// <param name="_func">�����֐�</param>
			/// <param name="_line">�������C��</param>
			/// <param name="_msg">���b�Z�[�W</param>
			Exception
			(
				const char* _file,
				const char* _func,
				const int _line,
				const std::string& _msg = "Unknown exception"
			);

			virtual ~Exception() = default;

			/// <summary>
			/// ��O���e�擾
			/// </summary>
			/// <returns>��O���e</returns>
			virtual const char* what() const noexcept override { return summary.c_str(); }

		};

	}
}


