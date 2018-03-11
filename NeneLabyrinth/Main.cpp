#include <windows.h>
#include "Core/Window.h"
#include"Rendering\Graphics.h"
#include"Core/GamePad.h"

#include"Debug.h"
#include"Timer.h"
#include"TimerServer.h"

#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
//�K�v�ȃ��C�u�����t�@�C���̃��[�h


using namespace NeneLabyrinth;
using namespace NeneLabyrinth::Utility;

struct Vertex
{
	D3DXVECTOR3 Pos; //�ʒu
};
//Simple�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\���� 
struct Buffer
{
	D3DXMATRIX mWVP;//���[���h�A�r���[�A�ˉe�̍����ϊ��s��
};


ID3D11VertexShader* pVertexShader;
ID3D11PixelShader* pPixelShader;
ID3D11Buffer* pConstantBuffer;

ID3D11InputLayout* pVertexLayout;
ID3D11Buffer* pVertexBuffer;

void RenderingResourceSetup()
{
	auto& graphics = Rendering::Graphics::Instantiate();

	//Blob�̓f�[�^�o�b�t�@
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;

	//�t�@�C������V�F�[�_�ǂݍ���
	if (FAILED(D3DX11CompileFromFile(
		"Simple.hlsl",
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

	//���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
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
		___THROW_EXCEPTION_POINT(Utility::Exception, "���_�C���v�b�g���C�A�E�g�Ɏ��s");
	}


	//�u���u����s�N�Z���V�F�[�_�[�쐬
	if (FAILED(D3DX11CompileFromFile(
		"Simple.hlsl",
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

	//�R���X�^���g�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Buffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(graphics.Device->CreateBuffer(&cb, NULL, &pConstantBuffer)))
	{
		___THROW_EXCEPTION_POINT(Utility::Exception, "�R���X�^���g�o�b�t�@�[�쐬�Ɏ��s");
	}

	//�o�[�e�b�N�X�o�b�t�@�[�쐬
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	Vertex vertices[] =
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

void PolygonRendering()
{
	auto& graphics = Rendering::Graphics::Instantiate();

	D3DXMATRIX mWorld;
	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	//���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	D3DXMatrixRotationY(&mWorld, timeGetTime() / 110.0f);//�P����yaw��]������

	// �r���[�g�����X�t�H�[���i���_���W�ϊ��j
	D3DXVECTOR3 vEyePt(0.0f, 1.0f, -2.0f); //�J�����i���_�j�ʒu
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);//�����ʒu
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//����ʒu
	D3DXMatrixLookAtLH(&mView, &vEyePt, &vLookatPt, &vUpVec);

	// �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	D3DXMatrixPerspectiveFovLH(
		&mProj,
		D3DX_PI / 4,
		(FLOAT)graphics.Width / (FLOAT)graphics.Height,
		0.1f, 110.0f);

	//�g�p����V�F�[�_�[�̓o�^
	graphics.DeviceContext->VSSetShader(pVertexShader, NULL, 0);
	graphics.DeviceContext->PSSetShader(pPixelShader, NULL, 0);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	Buffer cb;
	if (SUCCEEDED(graphics.DeviceContext->Map(
		pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) //���b�N����
	{
		//���[���h�A�J�����A�ˉe�s�����������
		D3DXMATRIX m = mWorld*mView*mProj;
		D3DXMatrixTranspose(&m, &m);
		cb.mWVP = m;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		graphics.DeviceContext->Unmap(pConstantBuffer, 0);	//�A�����b�N
	}

	//���̃R���X�^���g�o�b�t�@�[���A�ǂ̃V�F�[�_�[�Ŏg�������w��
	graphics.DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);//�o�[�e�b�N�X�o�b�t�@�[�Ŏg��
	graphics.DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);//�s�N�Z���V�F�[�_�[�ł̎g��

	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	graphics.DeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	graphics.DeviceContext->IASetInputLayout(pVertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	graphics.DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//�v���~�e�B�u�������_�����O
	graphics.DeviceContext->Draw(3, 0);

}

void Release()
{
	SAFE_RELEASE(pConstantBuffer);
	SAFE_RELEASE(pVertexShader);
	SAFE_RELEASE(pPixelShader);
	SAFE_RELEASE(pVertexLayout);
	SAFE_RELEASE(pVertexBuffer);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	try
	{
		Core::Window window(
			hInstance,
			"NeneLabyrinth",
			"NeneLabyrinth",
			640,
			480);
		window.Create();

		auto& graphics = Rendering::Graphics::Instantiate();
		graphics.Initialize(window, 640, 480);
		RenderingResourceSetup();

		Core::GamePad pad;

		Debug::Instantiate().ActivateDebugConsole();
		Debug::Instantiate().IsUseOutputLog = true;
		Debug::Instantiate().IsUseVSDebugOutput = true;
		___D_LOG("TestLog");


		while (!window.IsReceiveQuitMessage())
		{
			pad.UpdateInputState();

			if (pad.IsUp(pad.A))
			{
				pad.BeginVibration(30000, 3000);
			}

			if (pad.IsDown(pad.LeftStickLeft))
			{
				break;
			}


			//DO Update
			graphics.ClearBackBuffer();

			//DO Rendring
			PolygonRendering();
			graphics.Presetnt();
		}
		Release();
		SingletonFinalizer::Finalize();
	}
	catch (Exception* _e)
	{
		___LOG(_e->Detail);
		delete _e;
	}
	catch (std::exception e)
	{
		___LOG(e.what());
	}
	catch (...)
	{
		___LOG("�s���ȃG���[�I��");
	}
	return 0;
}