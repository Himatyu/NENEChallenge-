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
		/// �o�b�t�@�̃C���^�[�t�F�[�X�ƃ��C�A�E�g������
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

		//�Œ�o�b�t�@�̎���
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
			D3DXMATRIX W;//���[���h�s��
			D3DXMATRIX WVP;
			D3DXVECTOR4 LightDir;  //���C�g�̕����x�N�g��
			D3DXVECTOR4 Ambient;//�A���r�G���g��
			D3DXVECTOR4 Diffuse; //�g�U����(�F�j
			D3DXVECTOR4 Specular;//���ʔ���
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