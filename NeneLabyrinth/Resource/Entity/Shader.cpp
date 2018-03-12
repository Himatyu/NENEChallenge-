#include "Shader.h"
#include "../Rendering/Graphics.h"

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			Shader::Shader(std::string _filePath)
			{
				auto& graphics = Rendering::Graphics::Instantiate();

				//Blobはデータバッファ
				ID3DBlob *pCompiledShader = NULL;
				ID3DBlob *pErrors = NULL;

				//ファイルからシェーダ読み込み
				if (FAILED(D3DX11CompileFromFile(
					_filePath.c_str(),
					NULL,
					NULL,
					"VS",
					"vs_5_0",
					0,
					0,
					NULL,
					&pCompiledShader, &pErrors, NULL)))
				{
					___THROW_EXCEPTION_POINT(Utility::Exception, "シェーダ読み込みに失敗");
				}
				SAFE_RELEASE(pErrors);

				//ブロブからバーテックスシェーダー作成
				if (FAILED(graphics.Device->CreateVertexShader(
					pCompiledShader->GetBufferPointer(),
					pCompiledShader->GetBufferSize(),
					NULL, &pVertexShader)))
				{
					SAFE_RELEASE(pCompiledShader);
					___THROW_EXCEPTION_POINT(Utility::Exception, "バーテックスシェーダー作成に失敗");
				}

				//今回は固定
				D3D11_INPUT_ELEMENT_DESC layout[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

				};
				UINT numElements = sizeof(layout) / sizeof(layout[0]);
				//頂点インプットレイアウトを作成
				if (FAILED(graphics.Device->CreateInputLayout(
					layout,
					numElements,
					pCompiledShader->GetBufferPointer(),
					pCompiledShader->GetBufferSize(),
					&pVertexLayout)))
				{
					___THROW_EXCEPTION_POINT(Utility::Exception, "インプットレイアウト作成に失敗");
				}

				//ブロブからピクセルシェーダー作成
				if (FAILED(D3DX11CompileFromFile(
					_filePath.c_str(),
					NULL,
					NULL,
					"PS",
					"ps_5_0",
					0,
					0,
					NULL,
					&pCompiledShader, &pErrors, NULL)))
				{
					___THROW_EXCEPTION_POINT(Utility::Exception, "シェーダ読み込みに失敗");
				}
				SAFE_RELEASE(pErrors);

				if (FAILED(graphics.Device->CreatePixelShader(
					pCompiledShader->GetBufferPointer(),
					pCompiledShader->GetBufferSize(),
					NULL,
					&pPixelShader)))
				{
					SAFE_RELEASE(pCompiledShader);
					___THROW_EXCEPTION_POINT(Utility::Exception, "ピクセルシェーダー作成に失敗");
				}

				SAFE_RELEASE(pCompiledShader);

			}

			Shader::~Shader()
			{
				SAFE_RELEASE(pConstantBuffer);
				SAFE_RELEASE(pVertexShader);
				SAFE_RELEASE(pPixelShader);
				SAFE_RELEASE(pVertexLayout);

			}
		}
	}
}