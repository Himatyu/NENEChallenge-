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

				//Blob�̓f�[�^�o�b�t�@
				ID3DBlob *pCompiledShader = NULL;
				ID3DBlob *pErrors = NULL;

				//�t�@�C������V�F�[�_�ǂݍ���
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
					___THROW_EXCEPTION_POINT(Utility::Exception, "�V�F�[�_�ǂݍ��݂Ɏ��s");
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

				//����͌Œ�
				D3D11_INPUT_ELEMENT_DESC layout[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

				};
				UINT numElements = sizeof(layout) / sizeof(layout[0]);
				//���_�C���v�b�g���C�A�E�g���쐬
				if (FAILED(graphics.Device->CreateInputLayout(
					layout,
					numElements,
					pCompiledShader->GetBufferPointer(),
					pCompiledShader->GetBufferSize(),
					&pVertexLayout)))
				{
					___THROW_EXCEPTION_POINT(Utility::Exception, "�C���v�b�g���C�A�E�g�쐬�Ɏ��s");
				}

				//�u���u����s�N�Z���V�F�[�_�[�쐬
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
				SAFE_RELEASE(pConstantBuffer);
				SAFE_RELEASE(pVertexShader);
				SAFE_RELEASE(pPixelShader);
				SAFE_RELEASE(pVertexLayout);

			}
		}
	}
}