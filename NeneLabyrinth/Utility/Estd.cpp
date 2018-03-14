#pragma once
#include<algorithm>
#include<functional>
#include<numeric>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include"Estd.h"
namespace NeneLabyrinth
{
	namespace Utility
	{
		namespace Estd
		{


			std::vector<std::string> Split(const std::string& _input, char _delimiter)
			{
				std::istringstream stream(_input);

				std::string field;
				std::vector<std::string> result;
				while (std::getline(stream, field, _delimiter))
				{
					result.push_back(field);
				}
				return result;
			}
		}
	}
}