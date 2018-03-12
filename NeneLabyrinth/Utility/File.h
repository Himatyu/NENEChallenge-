#pragma once
#include<string>
namespace NeneLabyrinth
{
	namespace Utility
	{
		/// <summary>
		/// ファイルベースクラス.
		/// </summary>
		class File
		{
		protected:
			std::string fileName;
			std::string filePath;
			std::string fileDirectory;

		public:

			PROPERTY_CR_R_ONLY(fileName, FileName, std::string);
			PROPERTY_CR_R_ONLY(filePath, FilePath, std::string);
			PROPERTY_CR_R_ONLY(fileDirectory, FileDirectory, std::string);

			explicit File(std::string& _filePath);
			virtual ~File() = default;

			/// <summary>
			/// ファイル読み込み.
			/// </summary>
			/// <param name="_path">ファイルパス</param>
			/// <returns>読み込み成功判定</returns>
			virtual void Read(std::string _path) = 0 {}

			/// <summary>
			/// 書き込み.
			/// </summary>
			/// <param name="_path">ファイルパス</param>
			/// <returns>書き込み成功是非</returns>
			virtual void Write(std::string _path = "") = 0 {}

		protected:
			/// <summary>
			/// ファイル名とパスをセット.
			/// </summary>
			/// <param name="_path">ファイルパス</param>
			void SetFilePathInfo(std::string _path);
		};
	}
}