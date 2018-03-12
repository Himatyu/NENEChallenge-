#include "Shader.h"
#include"Graphics.h"
namespace NeneLabyrinth
{
	namespace Rendering
	{

		Shader::Shader(Resource::Entity::Shader& _entity) :
			entity(_entity)
		{
		}
		void Shader::Apply()
		{
			auto& graphics = Rendering::Graphics::Instantiate();


			//�g�p����V�F�[�_�[�̓o�^
			graphics.DeviceContext->VSSetShader(entity.VertexShader, NULL, 0);
			graphics.DeviceContext->PSSetShader(entity.PixelShader, NULL, 0);

			graphics.DeviceContext->IASetInputLayout(entity.VertexLayout);
			//�R���X�^���g�o�b�t�@�[���A�ǂ̃V�F�[�_�[�Ŏg�������w��

			graphics.DeviceContext->VSSetConstantBuffers(0, 1, &entity.ConstantBuffer);
			graphics.DeviceContext->PSSetConstantBuffers(0, 1, &entity.ConstantBuffer);

		}
	}
}

