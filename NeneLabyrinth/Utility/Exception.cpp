#include"Exception.h"
namespace NeneLabyrinth
{
	namespace Utility
	{
		Exception::Exception(const std::string& _msg)
			:summary(_msg),
			detail("Err : " + _msg)
		{}

		Exception::Exception
		(
			const char* _file,
			const char* _func,
			const int _line,
			const std::string& _msg
		)
			: summary(_msg),
			fileName(_file),
			functionName(_func),
			line(_line),
			detail(
				" Err : " + _msg +
				" Function : " + _func +
				" Line : " + std::to_string(_line) +
				" File : " + _file)
		{
		}
	}
}