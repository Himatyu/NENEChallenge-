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

			graphics.DeviceContext->IASetInputLayout(entity.VertexLayout);

			//�g�p����V�F�[�_�[�̓o�^
			graphics.DeviceContext->VSSetShader(entity.VertexShader, NULL, 0);
			graphics.DeviceContext->PSSetShader(entity.PixelShader, NULL, 0);

			//�R���X�^���g�o�b�t�@�[���A�ǂ̃V�F�[�_�[�Ŏg�������w��
			auto buffer = entity.ConstantBuffer;
			graphics.DeviceContext->VSSetConstantBuffers(0, 1, &buffer);
			graphics.DeviceContext->PSSetConstantBuffers(0, 1, &buffer);

		}
	}
}
