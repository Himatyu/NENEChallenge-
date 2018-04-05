#include <windows.h>
#include "Core/Window.h"
#include"Rendering\Graphics.h"
#include"Core/GamePad.h"
#include"Core/Application.h"
#include"Core/Scene.h"

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
#include"Component\Rigidbody.h"
#include<vector>

using namespace NeneLabyrinth;
using namespace NeneLabyrinth::Utility;
using namespace NeneLabyrinth::Utility::Estd;
using namespace NeneLabyrinth::Resource;
using namespace NeneLabyrinth::Component;

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <array>

#include "Component\Object.h"
#include "Component\Colldee.h"

class SphereComp :
	public Component::MeshColldee<Collision::Sphere>
{
public:
	SphereComp(
		Component::Object& _owner,
		std::string _path) :
		MeshColldee<Collision::Sphere>(_owner, typeid(SphereComp), _path)
	{
	}

	void Update() override
	{
		Colldee::Update();
		auto& trans = Owner.GetComponent<Component::Transform>();
		//trans->Rotation.y = timeGetTime() / 100.0f;
	}
	void OnTriggerEnter(Component::Object*) override
	{
		___LOG("OnTriggerEnter");
	};
	void OnTriggerStay(Component::Object*) override
	{
		___LOG("OnTriggerStay");


	};
	void OnTriggerExit(Component::Object*) override
	{
		___LOG("OnTriggerExit");


	};

};

class BoxComp :
	public Component::MeshColldee<Collision::OBB>
{
public:
	BoxComp(
		Component::Object& _owner,
		std::string _path) :
		MeshColldee<Collision::OBB>(_owner, typeid(BoxComp), _path)
	{
	}
	void Update() override
	{
		Colldee::Update();
		auto& trans = Owner.GetComponent<Component::Transform>();
		//trans->Rotation.y = timeGetTime() / 100.0f;
	}
};

class Sample :
	public Core::Scene
{
	Core::GamePad pad;
	std::shared_ptr<Rigidbody> rigidbody;
	std::shared_ptr<Rigidbody> rigidbody2;
public:
	void Initialize() override
	{
		auto& box = Instantiate<Component::Object>();
		auto& transform = box->AddComponent<Component::Transform>();
		auto& boxRender = box->AddComponent < Component::MeshRender >("box.object", "Simple.hlsl");
		box->AddComponent<BoxComp>("box.object");
		rigidbody2 = box->AddComponent<Rigidbody>();
		rigidbody2->IsUseGravity = false;
		rigidbody2->IsKinematic = true;
		rigidbody2->Drag = 0.5f;
		rigidbody2->Mass = 100;
		rigidbody2->Bound = 0.5f;
		box->Name = "box";
		//transform->Position.y -= 3;
		transform->Scale = D3DXVECTOR3(3, 0.5f, 3);
		transform->Rotation.z = -45;

		auto& sphereObj = Instantiate<Component::Object>();
		auto& transform2 = sphereObj->AddComponent<Component::Transform>();
		auto& sphereRender = sphereObj->AddComponent <Component::MeshRender>("sphere.object", "Simple.hlsl");
		sphereObj->AddComponent<SphereComp>("sphere.object");
		rigidbody = sphereObj->AddComponent<Rigidbody>();
		sphereObj->Name = "shpere";
		rigidbody->IsUseGravity = true;
		rigidbody->Drag = 0.5f;
		rigidbody->Bound = 0.5f;
		transform2->Position.y += 3;


		auto& cameraObj = Instantiate<Component::Object>();;
		auto& cameraTransform = cameraObj->AddComponent<Component::Transform>();
		auto& camera = cameraObj->AddComponent<Component::Camera>();

		cameraTransform->Position.z -= 20;
	}

	void Updata() override
	{
		pad.UpdateInputState();

		if (pad.IsUp(Core::GamePad::A))
		{
			rigidbody->AddForceImpulse(D3DXVECTOR3(-3, 0, 0));
			rigidbody2->AddForceImpulse(D3DXVECTOR3(3, 0, 0));

		}
	}
};

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE, LPSTR, int)
{
	try
	{
		auto& app = Core::Application::Instantiate();
		app.SetUp(_hInstance, 640, 480);
		app.OnLoad<Sample>();
		app.Execute();
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