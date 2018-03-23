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

			//使用するシェーダーの登録
			graphics.DeviceContext->VSSetShader(spEntity->VertexShader, NULL, 0);
			graphics.DeviceContext->PSSetShader(spEntity->PixelShader, NULL, 0);

			graphics.DeviceContext->IASetInputLayout(pVertexLayout);
			//コンスタントバッファーを、どのシェーダーで使うかを指定

			graphics.DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
			graphics.DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);

		}
	}
}

