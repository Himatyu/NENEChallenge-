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
#include <array>

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

float GetElementByVector3(int i, const D3DXVECTOR3& _vector)
{
	float result = -1;
	switch (i)
	{
	case 0:
		result = _vector.x;
		break;
	case 1:
		result = _vector.y;
		break;
	case 2:
		result = _vector.z;
		break;

	default:
		break;
	}
	return result;
}

class OBB
{
	using AxisType = std::array<D3DXVECTOR3, 3>;
	D3DXVECTOR3		half = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3		center = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3		prevScale = D3DXVECTOR3(1, 1, 1);
	std::array<D3DXVECTOR3, 3>	localAxis;
public:

	PROPERTY_REF(half, Half, D3DXVECTOR3);
	PROPERTY_REF(center, Center, D3DXVECTOR3);
	PROPERTY_REF(localAxis[0], LocalAxisX, D3DXVECTOR3);
	PROPERTY_REF(localAxis[1], LocalAxisY, D3DXVECTOR3);
	PROPERTY_REF(localAxis[2], LocalAxisZ, D3DXVECTOR3);
	PROPERTY_REF(localAxis, LocalAxis, AxisType);

	OBB(D3DXVECTOR3& _center, D3DXVECTOR3 _half) :
		center(_center),
		half(_half)
	{
		localAxis[0] = { 1, 0, 0 };
		localAxis[1] = { 0, 1, 0 };
		localAxis[2] = { 0, 0, 1 };
	}
	float IsInside(const D3DXVECTOR3 & _point)
	{
		D3DXVECTOR3 outer = D3DXVECTOR3(0, 0, 0);

		for (int i = 0; i < 3; i++)
		{
			auto halfLen = GetElementByVector3(i, half);
			_ASSERT_EXPR(half >= 0, _T(L"OBB点内外判定にて幅又は高さ又は奥行きが無い"));

			auto scaleHalf =
				D3DXVec3Dot(&(_point - center), &localAxis[i]) / halfLen;

			scaleHalf = std::abs(scaleHalf);
			if (scaleHalf <= 1)
			{
				continue;
			}

			outer += (1 - scaleHalf) * halfLen * localAxis[i];
		}

		if (outer == D3DXVECTOR3(0, 0, 0))
		{
			return -1;
		}

		return D3DXVec3Length(&outer);
	}

	void Update(Component::Transform& _transform)
	{
		center = _transform.Position;

		auto rotateVec = _transform.Rotation;
		D3DXMATRIX rotate;
		D3DXMatrixIdentity(&rotate);
		D3DXMatrixRotationYawPitchRoll(&rotate, rotateVec.y, rotateVec.x, rotateVec.z);

		D3DXVECTOR4 rotatedX;
		D3DXVECTOR4 rotatedY;
		D3DXVECTOR4 rotatedZ;
		D3DXVec3Transform(&rotatedX, &D3DXVECTOR3{ 1, 0, 0 }, &rotate);
		D3DXVec3Transform(&rotatedY, &D3DXVECTOR3{ 0, 1, 0 }, &rotate);
		D3DXVec3Transform(&rotatedZ, &D3DXVECTOR3{ 0, 0, 1 }, &rotate);

		localAxis[0] = { rotatedX.x,rotatedX.y,rotatedX.z };
		localAxis[1] = { rotatedY.x,rotatedY.y,rotatedY.z };
		localAxis[2] = { rotatedZ.x,rotatedZ.y,rotatedZ.z };

		auto crrentScale = _transform.Scale;
		half.x *= (prevScale.x / crrentScale.x);
		half.y *= (prevScale.y / crrentScale.y);
		half.z *= (prevScale.z / crrentScale.z);

		prevScale = crrentScale;
	}
};

struct Sphere
{
	float radius;
	D3DXVECTOR3 center = D3DXVECTOR3(0, 0, 0);
	void Update(Component::Transform& _transform)
	{
		center = _transform.Position;
	}
};

OBB CreateOBB(Entity::Mesh& _mesh)
{
	D3DXVECTOR3 max, min;
	max = min = D3DXVECTOR3(0, 0, 0);
	for (auto& vertex : _mesh.spDto->VertexBuffer)
	{
		auto v = vertex.position;
		max.x = max(max.x, v.x);
		max.y = max(max.y, v.y);
		max.z = max(max.z, v.z);
		min.x = min(min.x, v.x);
		min.y = min(min.y, v.y);
		min.z = min(min.z, v.z);

	}
	return OBB(D3DXVECTOR3(0, 0, 0), (max - min) / 2);
}

Sphere CreateSphere(Entity::Mesh& _mesh)
{
	float len = 0;

	for (auto& vertex : _mesh.spDto->VertexBuffer)
	{
		auto v = vertex.position;

		if (len < D3DXVec3Length(&v))
		{
			len = D3DXVec3Length(&v);
		}

	}
	return Sphere{ len,D3DXVECTOR3(0, 0, 0) };
}

bool IsCollision(OBB& _obb, Sphere& _sphere)
{
	auto distanceToCenter = _obb.IsInside(_sphere.center);

	return distanceToCenter <= _sphere.radius;
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

		Core::GamePad pad;

		Debug::Instantiate().ActivateDebugConsole();
		Debug::Instantiate().IsUseOutputLog = true;
		Debug::Instantiate().IsUseVSDebugOutput = true;
		___D_LOG("TestLog");

		auto& service = Service::Instantiate();

		auto boxMeshEntity =
			service.CreateEntity<Entity::Mesh>("box.object");
		auto boxShaderEntity =
			service.CreateEntity<Entity::Shader>("Simple.hlsl");
		auto boxMaterialEntity =
			service.CreateEntity<Entity::Material>("box.object");

		boxShaderEntity->CreateConstantBuffer<ConstantBuffer>();

		Rendering::Shader shader(*boxShaderEntity);
		Rendering::Material material(*boxMaterialEntity, shader);
		Rendering::MeshRender mesh(*boxMeshEntity, material);

		auto sphereMeshEntity =
			service.CreateEntity<Entity::Mesh>("sphere.object");
		auto sphereShaderEntity =
			service.CreateEntity<Entity::Shader>("Simple.hlsl");
		auto sphereMaterialEntity =
			service.CreateEntity<Entity::Material>("sphere.object");

		sphereShaderEntity->CreateConstantBuffer<ConstantBuffer>();

		Rendering::Shader sphereShader(*sphereShaderEntity);
		Rendering::Material sphereMaterial(*sphereMaterialEntity, sphereShader);
		Rendering::MeshRender sphereMesh(*sphereMeshEntity, sphereMaterial);

		Component::Behavior behavior;
		auto& transform = behavior.AddComponent<Component::Transform>();

		Component::Behavior behavior2;
		auto& transform2 = behavior2.AddComponent<Component::Transform>();
		transform2->Position.x += 3;



		auto obb = CreateOBB(*boxMeshEntity.get());
		auto sphere = CreateSphere(*sphereMeshEntity.get());


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
			transform2->Rotation.y = timeGetTime() / 100.0f;
			transform2->Position.x -= 0.0004f;

			behavior.Update();
			behavior2.Update();

			obb.Update(*transform.get());
			sphere.Update(*transform2.get());

			D3DXVECTOR4 color(1, 0.5, 1, 1);
			if (IsCollision(obb, sphere))
			{
				color = { 0,1,1,1 };
			}

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

			buffer.Ambient = boxMaterialEntity->Ambient;
			buffer.Diffuse = color;//materialEntity->Diffuse;
			buffer.Specular = boxMaterialEntity->Specular;

			buffer.LightDir = D3DXVECTOR4(0, 0, -1, 1);


			D3DXMATRIX dd = transform2->World *View*Proj;
			D3DXMatrixTranspose(&dd, &dd);

			ConstantBuffer buffer2;
			buffer2.WVP = dd;

			D3DXMATRIX m3 = transform2->World;
			D3DXMatrixTranspose(&m3, &m3);
			buffer2.W = m3;

			buffer2.Ambient = sphereMaterialEntity->Ambient;
			buffer2.Diffuse = D3DXVECTOR4(1, 0.5, 1, 1);//materialEntity->Diffuse;
			buffer2.Specular = sphereMaterialEntity->Specular;

			buffer2.LightDir = D3DXVECTOR4(0, 0, 1, 1);


			sphereShader.DatePush<ConstantBuffer>(&buffer2);
			shader.DatePush<ConstantBuffer>(&buffer);

			graphics.ClearBackBuffer();

			sphereMesh.Render();
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