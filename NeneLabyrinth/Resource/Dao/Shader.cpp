#include"Shader.h"
#include<memory>
namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Dao
		{
			std::shared_ptr<Dto::Shader> Shader::From(std::string _filePath)
			{
				auto spShader = std::make_shared<DTO>();
				spShader->filePath = _filePath;
				return spShader;
			}
		};
	}
}
