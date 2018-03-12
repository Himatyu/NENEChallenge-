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
			{//失敗
				___THROW_EXCEPTION_POINT(Exception, "ファイルストリームの生成に失敗 : " + fileName);
			}

			//ファイルの開始から終了までをバッファにセット
			istreambuf_iterator<char> it(ifs);
			istreambuf_iterator<char> last;
			buffer = string(it, last);
		}

		void TextFile::Write(std::string _path)
		{
			SetFilePathInfo(_path);
			//一気に書き出し
			if (buffer.empty())
			{
				return;
			}
			ofstream ofs(filePath);
			ofs << buffer << endl;
		}
	}
}