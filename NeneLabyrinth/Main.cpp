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
//必要なライブラリファイルのロード


using namespace NeneLabyrinth;
using namespace NeneLabyrinth::Utility;

struct Vertex
{
	D3DXVECTOR3 Pos; //位置
};
//Simpleシェーダー用のコンスタントバッファーのアプリ側構造体 
struct Buffer
{
	D3DXMATRIX mWVP;//ワールド、ビュー、射影の合成変換行列
};


ID3D11VertexShader* pVertexShader;
ID3D11PixelShader* pPixelShader;
ID3D11Buffer* pConstantBuffer;

ID3D11InputLayout* pVertexLayout;
ID3D11Buffer* pVertexBuffer;

void RenderingResourceSetup()
{
	auto& graphics = Rendering::Graphics::Instantiate();

	//Blobはデータバッファ
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;

	//ファイルからシェーダ読み込み
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
		___THROW_EXCEPTION_POINT(Utility::Exception, "シェーダ読み込みに失敗");
	}
	SAFE_RELEASE(pErrors);

	//ブロブからバーテックスシェーダー作成
	if (FAILED(graphics.Device->CreateVertexShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL, &pVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		___THROW_EXCEPTION_POINT(Utility::Exception, "バーテックスシェーダー作成に失敗");
	}

	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//頂点インプットレイアウトを作成
	if (FAILED(graphics.Device->CreateInputLayout(
		layout,
		numElements,
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		&pVertexLayout)))
	{
		___THROW_EXCEPTION_POINT(Utility::Exception, "頂点インプットレイアウトに失敗");
	}


	//ブロブからピクセルシェーダー作成
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
		___THROW_EXCEPTION_POINT(Utility::Exception, "シェーダ読み込みに失敗");
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(graphics.Device->CreatePixelShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&pPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		___THROW_EXCEPTION_POINT(Utility::Exception, "ピクセルシェーダー作成に失敗");
	}

	SAFE_RELEASE(pCompiledShader);

	//コンスタントバッファー作成
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(Buffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(graphics.Device->CreateBuffer(&cb, NULL, &pConstantBuffer)))
	{
		___THROW_EXCEPTION_POINT(Utility::Exception, "コンスタントバッファー作成に失敗");
	}

	//バーテックスバッファー作成
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
		___THROW_EXCEPTION_POINT(Utility::Exception, "バーテックスバッファー作成に失敗");
	}
}

void PolygonRendering()
{
	auto& graphics = Rendering::Graphics::Instantiate();

	D3DXMATRIX mWorld;
	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	//ワールドトランスフォーム（絶対座標変換）
	D3DXMatrixRotationY(&mWorld, timeGetTime() / 110.0f);//単純にyaw回転させる

	// ビュートランスフォーム（視点座標変換）
	D3DXVECTOR3 vEyePt(0.0f, 1.0f, -2.0f); //カメラ（視点）位置
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);//注視位置
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//上方位置
	D3DXMatrixLookAtLH(&mView, &vEyePt, &vLookatPt, &vUpVec);

	// プロジェクショントランスフォーム（射影変換）
	D3DXMatrixPerspectiveFovLH(
		&mProj,
		D3DX_PI / 4,
		(FLOAT)graphics.Width / (FLOAT)graphics.Height,
		0.1f, 110.0f);

	//使用するシェーダーの登録
	graphics.DeviceContext->VSSetShader(pVertexShader, NULL, 0);
	graphics.DeviceContext->PSSetShader(pPixelShader, NULL, 0);

	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	Buffer cb;
	if (SUCCEEDED(graphics.DeviceContext->Map(
		pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) //ロックする
	{
		//ワールド、カメラ、射影行列を書き込む
		D3DXMATRIX m = mWorld*mView*mProj;
		D3DXMatrixTranspose(&m, &m);
		cb.mWVP = m;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		graphics.DeviceContext->Unmap(pConstantBuffer, 0);	//アンロック
	}

	//このコンスタントバッファーを、どのシェーダーで使うかを指定
	graphics.DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);//バーテックスバッファーで使う
	graphics.DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);//ピクセルシェーダーでの使う

	//バーテックスバッファーをセット
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	graphics.DeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);

	//頂点インプットレイアウトをセット
	graphics.DeviceContext->IASetInputLayout(pVertexLayout);
	//プリミティブ・トポロジーをセット
	graphics.DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//プリミティブをレンダリング
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
		___LOG("不明なエラー終了");
	}
	return 0;
}