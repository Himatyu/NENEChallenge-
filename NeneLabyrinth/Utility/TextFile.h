#pragma once
#include"File.h"
#include"Macro.h"
namespace NeneLabyrinth
{
	namespace Utility
	{
		/// <summary>
		/// テキストファイル入出力クラス
		/// </summary>
		class TextFile :
			public File
		{
		protected:
			/// <summary>
			/// バッファ
			/// </summary>
			std::string buffer;

		public:

			PROPERTY_REF(buffer, Buffer, std::string);

			/// <summary>
			/// コンストラクタ
			/// </summary>
			TextFile() = default;

			/// <summary>
			/// コンストラクタ
			/// </summary>
			/// <param name="_Filename">ファイル名</param>
			explicit TextFile(std::string _Filename);

			/// <summary>
			/// デストラクタ
			/// </summary>
			virtual ~TextFile() = default;

			/// <summary>
			/// textファイル読み込み
			/// </summary>
			void Read(std::string) override;

			/// <summary>
			/// textファイル書き込み
			/// </summary>
			void Write(std::string) override;

		};
	}
}
