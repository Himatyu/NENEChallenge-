#include "Mesh.h"
#include "../Rendering/Graphics.h"

namespace NeneLabyrinth
{
	namespace Resource
	{
		namespace Entity
		{
			Mesh::Mesh() :
				vertexSize(0),
				offset(0),
				vertexCont(0)
			{
				//����͌Œ�l�A�{���T�[�r�X���O���t�@�C�����琶������
				auto& graphics = Rendering::Graphics::Instantiate();

				vertexSize = sizeof(D3DXVECTOR3);
				vertexCont = 3;
				//�o�[�e�b�N�X�o�b�t�@�[�쐬
				D3D11_BUFFER_DESC bd;
				bd.Usage = D3D11_USAGE_DEFAULT;
				bd.ByteWidth = sizeof(D3DXVECTOR3) * 3;
				bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				bd.CPUAccessFlags = 0;
				bd.MiscFlags = 0;

				D3DXVECTOR3 vertices[] =
				{
					D3DXVECTOR3(0.0f, 0.5f, 0.0f),
					D3DXVECTOR3(0.5f, -0.5f, 0.0f),
					D3DXVECTOR3(-0.5f, -0.5f, 0.0f),
				};

				D3D11_SUBRESOURCE_DATA InitData;
				InitData.pSysMem = vertices;

				if (FAILED(graphics.Device->CreateBuffer(&bd, &InitData, &pVertexBuffer)))
				{
					___THROW_EXCEPTION_POINT(Utility::Exception, "�o�[�e�b�N�X�o�b�t�@�[�쐬�Ɏ��s");
				}

			}
			Mesh::~Mesh()
			{
				SAFE_RELEASE(pVertexBuffer);
			}
		}
	}
}