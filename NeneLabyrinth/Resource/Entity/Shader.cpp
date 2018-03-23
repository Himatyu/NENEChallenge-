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

				//Blob�̓f�[�^�o�b�t�@
				ID3DBlob *pCompiledShader = NULL;
				ID3DBlob *pErrors = NULL;

				//�t�@�C������V�F�[�_�ǂݍ���
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

				//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
				if (FAILED(graphics.Device->CreateVertexShader(
					pCompiledShader->GetBufferPointer(),
					pCompiledShader->GetBufferSize(),
					NULL, &pVertexShader)))
				{
					SAFE_RELEASE(pCompiledShader);
					___THROW_EXCEPTION_POINT(Utility::Exception, "�o�[�e�b�N�X�V�F�[�_�[�쐬�Ɏ��s");
				}

				//�u���u����s�N�Z���V�F�[�_�[�쐬
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
					___THROW_EXCEPTION_POINT(Utility::Exception, "�V�F�[�_�ǂݍ��݂Ɏ��s");
				}
				SAFE_RELEASE(pErrors);

				if (FAILED(graphics.Device->CreatePixelShader(
					pCompiledShader->GetBufferPointer(),
					pCompiledShader->GetBufferSize(),
					NULL,
					&pPixelShader)))
				{
					SAFE_RELEASE(pCompiledShader);
					___THROW_EXCEPTION_POINT(Utility::Exception, "�s�N�Z���V�F�[�_�[�쐬�Ɏ��s");
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