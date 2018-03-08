#pragma once
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")
#define SAFE_RELEASE(x) if(x){x->Release(); x=NULL;}

namespace NeneLabyrinth
{
	namespace Rendering
	{
		class Graphics
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
			Graphics(HWND _hWnd,
				int			width,
				int			height);
			~Graphics();

			void Initialize();

			void ClearBackBuffer();
			void Presetnt();
		};
	}
}
