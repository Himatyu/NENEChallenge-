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


			//使用するシェーダーの登録
			graphics.DeviceContext->VSSetShader(entity.VertexShader, NULL, 0);
			graphics.DeviceContext->PSSetShader(entity.PixelShader, NULL, 0);

			graphics.DeviceContext->IASetInputLayout(entity.VertexLayout);
			//コンスタントバッファーを、どのシェーダーで使うかを指定

			graphics.DeviceContext->VSSetConstantBuffers(0, 1, &entity.ConstantBuffer);
			graphics.DeviceContext->PSSetConstantBuffers(0, 1, &entity.ConstantBuffer);

		}
	}
}

