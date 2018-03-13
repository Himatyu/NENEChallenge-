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
			//今回はvs.ps同ファイルで扱い、psに固定バッファを使用しない
			class Shader final :
				public Base<Dao::Shader>
			{
				ID3D11InputLayout* pVertexLayout;
				ID3D11VertexShader* pVertexShader;
				ID3D11PixelShader* pPixelShader;
				ID3D11Buffer* pConstantBuffer;
			public:
				PROPERTY_REF_R_ONLY(pVertexLayout, VertexLayout, ID3D11InputLayout*);
				PROPERTY_REF_R_ONLY(pVertexShader, VertexShader, ID3D11VertexShader*);
				PROPERTY_REF_R_ONLY(pPixelShader, PixelShader, ID3D11PixelShader*);
				PROPERTY_REF_R_ONLY(pConstantBuffer, ConstantBuffer, ID3D11Buffer*);

				Shader(std::shared_ptr<DTO> _spDto);
				~Shader();

				template<class Buffer>
				void CreateConstantBuffer();
			};
#include"Shader.inl"
		}
	}
}
