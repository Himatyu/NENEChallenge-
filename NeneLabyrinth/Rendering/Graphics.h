#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

#include"Singleton.h"
#define SAFE_RELEASE(x) if(x){x->Release(); x=NULL;}

namespace NeneLabyrinth
{
	namespace Rendering
	{
		class Graphics final :
			public Utility::Singleton<Graphics>
		{
			HWND		hWnd;
			int			width;
			int			height;

			ID3D11Device* pDevice;
			ID3D11DeviceContext* pDeviceContext;
			IDXGISwapChain* pSwapChain;
			ID3D11Texture2D *pBackBuffer_Tex;
			ID3D11Texture2D* pBuckBuffer_DSTex;
			ID3D11RenderTargetView* pBackBuffer_TexRTV;
			ID3D11DepthStencilView* pBuckBuffer_DSTexDSV;

		public:
			PROPERTY_R_ONLY(width, Width, int);
			PROPERTY_R_ONLY(height, Height, int);
			PROPERTY_REF_R_ONLY(pDevice, Device, ID3D11Device*);
			PROPERTY_REF_R_ONLY(pDeviceContext, DeviceContext, ID3D11DeviceContext*);

			~Graphics();

			void Initialize(HWND _hWnd,
				int			width,
				int			height);

			void ClearBackBuffer();
			void Presetnt();
		};
	}
}
