#include <windows.h>
#include "Core/Window.h"
#include"Rendering\Graphics.h"
#include"Core/GamePad.h"

#include"Debug.h"
#include"Timer.h"
#include"Estd.h"
#include"TimerServer.h"

#include"Rendering\Material.h"
#include"Rendering\MeshRender.h"
#include"Rendering\Shader.h"

#include"Resource\Entity\Material.h"
#include"Resource\Entity\Mesh.h"
#include"Resource\Entity\Shader.h"
#include"Resource\Service.h"
#include"Component\Transform.h"
#include<vector>

using namespace NeneLabyrinth;
using namespace NeneLabyrinth::Utility;
using namespace NeneLabyrinth::Utility::Estd;
using namespace NeneLabyrinth::Resource;

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Component\Behavior.h"

struct ConstantBuffer
{
	D3DXMATRIX W;//ワールド行列
	D3DXMATRIX WVP;
	D3DXVECTOR4 LightDir;  //ライトの方向ベクトル
	D3DXVECTOR4 Ambient;//アンビエント光
	D3DXVECTOR4 Diffuse; //拡散反射(色）
	D3DXVECTOR4 Specular;//鏡面反射
};

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

		auto& service = Service::Instantiate();

		auto meshEntity =
			service.CreateEntity<Entity::Mesh>("box.object");
		auto shaderEntity =
			service.CreateEntity<Entity::Shader>("Simple.hlsl");
		auto materialEntity =
			service.CreateEntity<Entity::Material>("box.object");

		shaderEntity->CreateConstantBuffer<ConstantBuffer>();

		Rendering::Shader shader(*shaderEntity);
		Rendering::Material material(*materialEntity, shader);
		Rendering::MeshRender mesh(*meshEntity, material);

		Component::Behavior behavior;
		auto& transform = behavior.AddComponent<Component::Transform>();
		behavior.RemoveComponents<Component::Transform>();

		while (!window.IsReceiveQuitMessage())
		{
			pad.UpdateInputState();

			if (pad.IsInput(pad.A))
			{
			}

			if (pad.IsDown(pad.LeftStickLeft))
			{
				break;
			}


			//DO Update
			transform->Rotation.y = timeGetTime() / 100.0f;
			//transform->Scale.y = sin(timeGetTime() / 100.0f);

			behavior.Update();

			D3DXMATRIX View;
			D3DXMATRIX Proj;
			//ワールドトランスフォーム
			// ビュートランスフォーム
			D3DXVECTOR3 vEyePt(0.0f, 1, -10); //視点位置
			D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);//注視位置
			D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);//上方位置
			D3DXMatrixLookAtLH(&View, &vEyePt, &vLookatPt, &vUpVec);
			// プロジェクショントランスフォーム
			D3DXMatrixPerspectiveFovLH(&Proj, D3DX_PI / 4, (FLOAT)640 / (FLOAT)480, 0.1f, 100.0f);

			//使用するシェーダーのセット
			D3DXMATRIX m = transform->World *View*Proj;
			D3DXMatrixTranspose(&m, &m);

			ConstantBuffer buffer;
			buffer.WVP = m;

			D3DXMATRIX m2 = transform->World;
			D3DXMatrixTranspose(&m2, &m2);
			buffer.W = m2;

			buffer.Ambient = materialEntity->Ambient;
			buffer.Diffuse = D3DXVECTOR4(1, 0.5, 1, 1);//materialEntity->Diffuse;
			buffer.Specular = materialEntity->Specular;

			buffer.LightDir = D3DXVECTOR4(0, 0, -1, 1);

			shader.DatePush<ConstantBuffer>(&buffer);

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