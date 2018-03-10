#include<fstream>
#include "TextFile.h"
namespace NeneLabyrinth
{
	namespace Utility
	{
		using namespace std;

		TextFile::TextFile(std::string _Path) :
			File(_Path) {	}

		void TextFile::Read(std::string _path)
		{
			SetFilePathInfo(_path);
			ifstream ifs(filePath);

			if (ifs.fail())
			{//���s
				___THROW_EXCEPTION_POINT(Exception, "�t�@�C���X�g���[���̐����Ɏ��s : " + fileName);
			}

			//�t�@�C���̊J�n����I���܂ł��o�b�t�@�ɃZ�b�g
			istreambuf_iterator<char> it(ifs);
			istreambuf_iterator<char> last;
			buffer = string(it, last);
		}

		void TextFile::Write(std::string _path)
		{
			SetFilePathInfo(_path);
			//��C�ɏ����o��
			if (buffer.empty())
			{
				return;
			}
			ofstream ofs(filePath);
			ofs << buffer << endl;
		}
	}
}