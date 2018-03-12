#include <windows.h>
#include "Core/Window.h"
#include"Rendering\Graphics.h"
#include"Core/GamePad.h"

#include"Debug.h"
#include"Timer.h"
#include"TimerServer.h"

#include"Rendering\Material.h"
#include"Rendering\MeshRender.h"
#include"Rendering\Shader.h"

#include"Resource\Entity\Material.h"
#include"Resource\Entity\Mesh.h"
#include"Resource\Entity\Shader.h"

using namespace NeneLabyrinth;
using namespace NeneLabyrinth::Utility;
using namespace NeneLabyrinth::Resource;

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

		Core::GamePad pad;

		Debug::Instantiate().ActivateDebugConsole();
		Debug::Instantiate().IsUseOutputLog = true;
		Debug::Instantiate().IsUseVSDebugOutput = true;
		___D_LOG("TestLog");

		Entity::Mesh meshEntity;//TODO Serviceから生成
		Entity::Shader shaderEntity("Simple.hlsl");
		shaderEntity.CreateConstantBuffer<D3DXMATRIX>();
		Entity::Material materialEntity(&shaderEntity);

		Rendering::Shader shader(shaderEntity);
		Rendering::Material material(materialEntity, shader);
		Rendering::MeshRender mesh(meshEntity, material);


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

			D3DXMATRIX World;
			D3DXMATRIX View;
			D3DXMATRIX Proj;
			//ワールドトランスフォーム
			D3DXMatrixIdentity(&World);										// ビュートランスフォーム
			D3DXVECTOR3 vEyePt(0.0f, 1.0f, -2.0f); //視点位置
			D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);//注視位置
			D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//上方位置
			D3DXMatrixLookAtLH(&View, &vEyePt, &vLookatPt, &vUpVec);
			// プロジェクショントランスフォーム
			D3DXMatrixPerspectiveFovLH(&Proj, D3DX_PI / 4, (FLOAT)640 / (FLOAT)480, 0.1f, 100.0f);
			//使用するシェーダーのセット
			D3DXMATRIX m = World*View*Proj;
			D3DXMatrixTranspose(&m, &m);
			shader.DatePush<D3DXMATRIX>(&m);

			graphics.ClearBackBuffer();
			mesh.Render();
			//DO Rendring
			graphics.Presetnt();
		}
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