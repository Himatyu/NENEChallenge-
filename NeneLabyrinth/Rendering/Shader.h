#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
#include"../Resource/Entity/Shader.h"
#include"../Rendering/Graphics.h"

namespace NeneLabyrinth
{
	namespace Rendering
	{
		/// <summary>
		/// バッファのインターフェースとレイアウトを持つ
		/// </summary>
		class IShader
		{
		protected:
			std::shared_ptr<Resource::Entity::Shader> spEntity;
			ID3D11InputLayout* pVertexLayout;
			ID3D11Buffer* pConstantBuffer;

		public:
			PROPERTY_REF_R_ONLY(pVertexLayout, VertexLayout, ID3D11InputLayout*);
			PROPERTY_REF_R_ONLY(pConstantBuffer, ConstantBuffer, ID3D11Buffer*);

			IShader(std::string _path);
			~IShader();

			virtual void Configurate() = 0;
			virtual void Apply();
		};

		//固定バッファの実体
		template<class T>
		class Shader :
			public IShader
		{
		protected:
			T buffer;
		public:
			PROPERTY_REF(buffer, Buffer, T);

			Shader(std::string _path);
			~Shader();

			virtual void Configurate() override;
			virtual void Apply() override;
		};

		struct ConstantBuffer
		{
			D3DXMATRIX W;//ワールド行列
			D3DXMATRIX WVP;
			D3DXVECTOR4 LightDir;  //ライトの方向ベクトル
			D3DXVECTOR4 Ambient;//アンビエント光
			D3DXVECTOR4 Diffuse; //拡散反射(色）
			D3DXVECTOR4 Specular;//鏡面反射
		};

		class MeshShader
			:public Rendering::Shader<ConstantBuffer>
		{
		public:
			MeshShader(std::string _path)
				:Shader(_path)
			{
			}
			~MeshShader() {}

		};

#include"Shader.inl"
	}
}