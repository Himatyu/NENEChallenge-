#pragma once
#include"File.h"
#include"Macro.h"
namespace NeneLabyrinth
{
	namespace Utility
	{
		/// <summary>
		/// �e�L�X�g�t�@�C�����o�̓N���X
		/// </summary>
		class TextFile :
			public File
		{
		protected:
			/// <summary>
			/// �o�b�t�@
			/// </summary>
			std::string buffer;

		public:

			PROPERTY_REF(buffer, Buffer, std::string);

			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			TextFile() = default;

			/// <summary>
			/// �R���X�g���N�^
			/// </summary>
			/// <param name="_Filename">�t�@�C����</param>
			explicit TextFile(std::string _Filename);

			/// <summary>
			/// �f�X�g���N�^
			/// </summary>
			virtual ~TextFile() = default;

			/// <summary>
			/// text�t�@�C���ǂݍ���
			/// </summary>
			void Read(std::string) override;

			/// <summary>
			/// text�t�@�C����������
			/// </summary>
			void Write(std::string) override;

		};
	}
}
