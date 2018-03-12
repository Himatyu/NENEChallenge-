#include"File.h"
namespace NeneLabyrinth
{
	namespace Utility
	{
		File::File(std::string & _filePath)
		{
			SetFilePathInfo(_filePath);
		}

		void File::SetFilePathInfo(std::string _path)
		{
			if (_path.empty())
			{
				___THROW_EXCEPTION_POINT(Exception, "ƒtƒ@ƒCƒ‹–¼‚ª‹ó");
			}

			auto fileExtensionIndex = _path.rfind(".") - 1;
			auto directoryIndex = _path.rfind("/") + 1;

			fileName = _path.substr(directoryIndex, fileExtensionIndex);
			fileDirectory = _path.substr(0, directoryIndex);
			filePath = _path;
		}
	}
}
