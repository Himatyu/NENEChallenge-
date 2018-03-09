#include "Graphics.h"

namespace NeneLabyrinth
{
	namespace Rendering
	{
		Graphics::Graphics(HWND _hWnd, int _width, int _height) :
			hWnd(_hWnd),
			width(_width),
			height(_height)
		{
		}

		Graphics::~Graphics()
		{
			SAFE_RELEASE(pSwapChain);
			SAFE_RELEASE(pBackBuffer_Tex);
			SAFE_RELEASE(pBackBuffer_TexRTV);
			SAFE_RELEASE(pBuckBuffer_DSTex);
			SAFE_RELEASE(pBuckBuffer_DSTexDSV);
			SAFE_RELEASE(pDevice);
			SAFE_RELEASE(pDeviceContext);
		}

		void Graphics::Initialize()
		{
			// �f�o�C�X�ƃX���b�v�`�F�[���̍쐬
			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.BufferCount = 1;
			sd.BufferDesc.Width = width;
			sd.BufferDesc.Height = height;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.RefreshRate.Numerator = 60;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.OutputWindow = hWnd;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.Windowed = TRUE;

			D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
			D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

			if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
				0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &pSwapChain, &pDevice,
				pFeatureLevel, &pDeviceContext)))
			{
				//TODO Excption
				return;
			}

			//�o�b�N�o�b�t�@����e�N�X�`���擾
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer_Tex);
			pDevice->CreateRenderTargetView(pBackBuffer_Tex, NULL, &pBackBuffer_TexRTV);


			//�f�v�X�X�e���V���r���[�p�̃e�N�X�`���[���쐬
			D3D11_TEXTURE2D_DESC descDepth;
			descDepth.Width = width;
			descDepth.Height = height;
			descDepth.MipLevels = 1;
			descDepth.ArraySize = 1;
			descDepth.Format = DXGI_FORMAT_D32_FLOAT;
			descDepth.SampleDesc.Count = 1;
			descDepth.SampleDesc.Quality = 0;
			descDepth.Usage = D3D11_USAGE_DEFAULT;
			descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			descDepth.CPUAccessFlags = 0;
			descDepth.MiscFlags = 0;
			pDevice->CreateTexture2D(&descDepth, NULL, &pBuckBuffer_DSTex);
			//���̃e�N�X�`���[�ɑ΂��f�v�X�X�e���V���r���[(DSV)���쐬
			pDevice->CreateDepthStencilView(pBuckBuffer_DSTex, NULL, &pBuckBuffer_DSTexDSV);

			//�����_�[�^�[�Q�b�g�r���[�ƃf�v�X�X�e���V���r���[���p�C�v���C���ɃZ�b�g
			pDeviceContext->OMSetRenderTargets(1, &pBackBuffer_TexRTV, pBuckBuffer_DSTexDSV);

			//�r���[�|�[�g�̐ݒ�
			D3D11_VIEWPORT vp;
			vp.Width = width;
			vp.Height = height;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			pDeviceContext->RSSetViewports(1, &vp);

			//���X�^���C�Y�ݒ�
			D3D11_RASTERIZER_DESC rdc;
			ZeroMemory(&rdc, sizeof(rdc));
			rdc.CullMode = D3D11_CULL_NONE;
			rdc.FillMode = D3D11_FILL_SOLID;
			ID3D11RasterizerState* pIr = NULL;
			pDevice->CreateRasterizerState(&rdc, &pIr);
			pDeviceContext->RSSetState(pIr);
		}

		void Graphics::ClearBackBuffer()
		{
			float ClearColor[4] = { 0,0,0.5,1 };// �N���A�F�@RGBA�̏�
			pDeviceContext->ClearRenderTargetView(pBackBuffer_TexRTV, ClearColor);//�J���[�o�b�t�@�N���A
			pDeviceContext->ClearDepthStencilView(pBuckBuffer_DSTexDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);//�f�v�X�X�e���V���o�b�t�@�N���A
		}

		void Graphics::Presetnt()
		{
			pSwapChain->Present(0, 0);//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
		}
	}
}