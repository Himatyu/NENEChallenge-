#include <windows.h>
#include "Core/Window.h"
#include"Rendering\Graphics.h"
#include"Core/GamePad.h"

#include"Debug.h"
#include"Timer.h"
#include"Estd.h"
#include"TimerServer.h"
#include"IProvider.h"

#include"Rendering\Material.h"
#include"Component\MeshRender.h"
#include"Rendering\Shader.h"
#include"Provider\RenderProvider.h"
#include"Provider\BehaviorProvider.h"
#include"Provider\CollisionProvider.h"

#include"Resource\Entity\Material.h"
#include"Resource\Entity\Mesh.h"
#include"Resource\Entity\Shader.h"
#include"Resource\Service.h"
#include"Component\Transform.h"
#include"Component\Camera.h"
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
#include <array>

#include "Component\Behavior.h"
#include "Component\Colldee.h"

class SphereComp :
	public Component::MeshColldee<Collision::Sphere>
{
public:
	SphereComp(
		Component::Behavior& _owner,
		std::string _path) :
		MeshColldee<Collision::Sphere>(_owner, typeid(SphereComp), _path)
	{
	}

	void Update() override
	{
		Colldee::Update();
		Owner.GetComponent<Component::Transform>()->Position.x -= 0.001f;
	}
	void OnTriggerEnter(Component::Behavior*) override
	{
		___LOG("OnTriggerEnter");
	};
	void OnTriggerStay(Component::Behavior*) override
	{
		___LOG("OnTriggerStay");


	};
	void OnTriggerExit(Component::Behavior*) override
	{
		___LOG("OnTriggerExit");


	};

};

class BoxComp :
	public Component::MeshColldee<Collision::OBB>
{
public:
	BoxComp(
		Component::Behavior& _owner,
		std::string _path) :
		MeshColldee<Collision::OBB>(_owner, typeid(BoxComp), _path)
	{
	}

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


		Component::Behavior box;
		auto& transform = box.AddComponent<Component::Transform>();
		auto& boxRender = box.AddComponent < Component::MeshRender >("box.object", "Simple.hlsl");
		box.AddComponent<BoxComp>("box.object");

		Component::Behavior sphereObj;
		auto& transform2 = sphereObj.AddComponent<Component::Transform>();
		auto& sphereRender = sphereObj.AddComponent <Component::MeshRender>("sphere.object", "Simple.hlsl");
		sphereObj.AddComponent<SphereComp>("sphere.object");


		transform2->Position.x += 3;

		Component::Behavior cameraObj;
		auto& cameraTransform = cameraObj.AddComponent<Component::Transform>();
		auto& camera = cameraObj.AddComponent<Component::Camera>();

		cameraTransform->Position.z -= 10;

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
			Component::CameraProvider::Instantiate().Dispatch();


			transform->Rotation.y = timeGetTime() / 100.0f;
			transform2->Rotation.y = timeGetTime() / 100.0f;
			//transform2->Position.x -= 0.0004f;

			Component::BehaviorProvider::Instantiate().Dispatch();
			Collision::CollisionProvider::Instantiate().Dispatch();
			//obb.Update(*transform.get());
			//sphere.Update(*transform2.get());

			//D3DXVECTOR4 color(1, 0.5, 1, 1);
			//if (IsCollision(obb, sphere))
			//{
			//	color = { 0,1,1,1 };
			//}

			graphics.ClearBackBuffer();


			Rendering::RenderProvider::Instantiate().Dispatch();

			graphics.Presetnt();
		}
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
	SingletonFinalizer::Finalize();

	return 0;
}