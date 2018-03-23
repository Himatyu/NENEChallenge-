#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
#include"File.h"
#include"Base.h"
#include"../Dao/Shader.h"

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			//�����vs.ps���t�@�C���ň����Aps�ɌŒ�o�b�t�@���g�p���Ȃ�
			class Shader final :
				public Base<Dao::Shader>
			{
				ID3D11VertexShader* pVertexShader;
				ID3D11PixelShader* pPixelShader;
			public:
				PROPERTY_REF_R_ONLY(pVertexShader, VertexShader, ID3D11VertexShader*);
				PROPERTY_REF_R_ONLY(pPixelShader, PixelShader, ID3D11PixelShader*);

				Shader(std::shared_ptr<DTO> _spDto);
				~Shader();

			};
		}
	}
}
