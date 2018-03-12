#pragma once
#include<exception>
#include<string>
#include"Macro.h"
namespace NeneLabyrinth
{
	namespace Utility
	{
		/// <summary>
		/// 発生箇所を取得し例外を投げる
		/// </summary>
#define ___THROW_EXCEPTION(EXCEPTION_TYPE, message) \
  throw EXCEPTION_TYPE( __FILE__, __func__, __LINE__,message) 

/// <summary>
/// 発生箇所を取得し例外ポインタを投げる
/// </summary>
#define ___THROW_EXCEPTION_POINT(EXCEPTION_TYPE, message) \
  throw new EXCEPTION_TYPE( __FILE__, __func__, __LINE__,message) 

/// <summary>
/// 例外クラス.
/// 基本はマクロを使う.
/// </summary>
		class Exception :
			public std::exception
		{
			/// <summary>
			/// 例外内容
			/// </summary>
			std::string summary;

			/// <summary>
			/// 発生したファイル
			/// </summary>
			std::string fileName;

			/// <summary>
			/// 発生した関数
			/// </summary>
			std::string functionName;

			/// <summary>
			/// 内容と発生箇所
			/// </summary>
			std::string detail;

			/// <summary>
			/// 発生行数
			/// </summary>
			int			line;

		public:

			PROPERTY_CR_R_ONLY(summary, Summary, std::string);
			PROPERTY_CR_R_ONLY(fileName, Filename, std::string);
			PROPERTY_CR_R_ONLY(functionName, FunctionName, std::string);
			PROPERTY_CR_R_ONLY(detail, Detail, std::string);
			PROPERTY_CR_R_ONLY(line, Line, int);

			/// <summary>
			/// 発生箇所の特定を行わない例外
			/// </summary>
			/// <param name="_msg">メッセージ</param>
			explicit Exception(const std::string& _msg = "Unknown exception");

			/// <summary>
			/// 発生箇所情報を受取る例外
			/// </summary>
			/// <param name="_file">発生ファイル</param>
			/// <param name="_func">発生関数</param>
			/// <param name="_line">発生ライン</param>
			/// <param name="_msg">メッセージ</param>
			Exception
			(
				const char* _file,
				const char* _func,
				const int _line,
				const std::string& _msg = "Unknown exception"
			);

			virtual ~Exception() = default;

			/// <summary>
			/// 例外内容取得
			/// </summary>
			/// <returns>例外内容</returns>
			virtual const char* what() const noexcept override { return summary.c_str(); }

		};

	}
}


