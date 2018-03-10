#pragma once
#include<string>
namespace NeneLabyrinth
{
	namespace Utility
	{
		/// <summary>
		/// �t�@�C���x�[�X�N���X.
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
			/// �t�@�C���ǂݍ���.
			/// </summary>
			/// <param name="_path">�t�@�C���p�X</param>
			/// <returns>�ǂݍ��ݐ�������</returns>
			virtual void Read(std::string _path) = 0 {}

			/// <summary>
			/// ��������.
			/// </summary>
			/// <param name="_path">�t�@�C���p�X</param>
			/// <returns>�������ݐ�������</returns>
			virtual void Write(std::string _path = "") = 0 {}

		protected:
			/// <summary>
			/// �t�@�C�����ƃp�X���Z�b�g.
			/// </summary>
			/// <param name="_path">�t�@�C���p�X</param>
			void SetFilePathInfo(std::string _path);
		};
	}
}