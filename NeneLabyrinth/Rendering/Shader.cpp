#include "Shader.h"
#include"Graphics.h"
#include "..\Resource\Dao\Shader.h"
#include "..\Resource/Service.h"
namespace NeneLabyrinth
{
	namespace Rendering
	{

		IShader::IShader(std::string _path)
		{
			spEntity = Resource::Service::Instantiate()
				.CreateEntity<Resource::Entity::Shader>(_path);
		}

		IShader::~IShader()
		{
		}

		void IShader::Apply()
		{
			auto& graphics = Rendering::Graphics::Instantiate();

			//�g�p����V�F�[�_�[�̓o�^
			graphics.DeviceContext->VSSetShader(spEntity->VertexShader, NULL, 0);
			graphics.DeviceContext->PSSetShader(spEntity->PixelShader, NULL, 0);

			graphics.DeviceContext->IASetInputLayout(pVertexLayout);
			//�R���X�^���g�o�b�t�@�[���A�ǂ̃V�F�[�_�[�Ŏg�������w��

			graphics.DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			graphics.DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);

		}
	}
}

