#include "Shader.h"
#include "../Rendering/Graphics.h"
#include "..\..\Rendering\Shader.h"

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			Shader::Shader(std::shared_ptr<DTO> _spDto) :
				Base(_spDto)
			{
				auto& graphics = Rendering::Graphics::Instantiate();
				auto filePath = _spDto->filePath;

				//Blobはデータバッファ
				ID3DBlob *pCompiledShader = NULL;
				ID3DBlob *pErrors = NULL;

				//ファイルからシェーダ読み込み
				if (FAILED(D3DX11CompileFromFile(
					filePath.c_str(),
					NULL,
					NULL,
					"VS",
					"vs_5_0",
					0,
					0,
					NULL,
					&pCompiledShader, &pErrors, NULL)))
				{
					___THROW_EXCEPTION_POINT(Utility::Exception, (char*)pErrors->GetBufferPointer());
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

				//ブロブからピクセルシェーダー作成
				if (FAILED(D3DX11CompileFromFile(
					filePath.c_str(),
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
				SAFE_RELEASE(pVertexShader);
				SAFE_RELEASE(pPixelShader);
			}
		}
	}
}