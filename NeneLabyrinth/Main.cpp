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
#include<vector>

using namespace NeneLabyrinth;
using namespace NeneLabyrinth::Utility;
using namespace NeneLabyrinth::Resource;

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct Vertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
};

struct ConstantBuffer
{
	D3DXMATRIX WVP;
};

std::vector<std::string> Split(const std::string& _input, char _delimiter)
{
	std::istringstream stream(_input);

	std::string field;
	std::vector<std::string> result;
	while (std::getline(stream, field, _delimiter))
	{
		result.push_back(field);
	}
	return result;
}
void CreateMaterialEntity(Entity::Material& _material, std::string _path, Entity::Shader* _pShader)
{
	std::ifstream fileStream(_path);
	if (fileStream.fail())
	{
		___THROW_EXCEPTION_POINT(Utility::Exception, _path + "オープン失敗");
	}

	std::string line;
	std::string Name;
	std::string materialFile;

	while (getline(fileStream, line))
	{
		if (line.find("#") != std::string::npos)
		{
			continue;
		}
		if (line.find("usemtl") != std::string::npos)
		{
			Name = Split(line, ' ')[1];
			continue;
		}

		if (line.find("mtllib") != std::string::npos)
		{
			materialFile = Split(line, ' ')[1];
			continue;
		}
	}

	std::ifstream materialFileStream(materialFile);
	if (materialFileStream.fail())
	{
		___THROW_EXCEPTION_POINT(Utility::Exception, materialFile + "オープン失敗");
	}

	Entity::Material entity(_pShader);
	while (getline(materialFileStream, line))
	{
		if (line.find("#") != std::string::npos)
		{
			continue;
		}
		if (line.find("newmtl") != std::string::npos)
		{
			Name = Split(line, ' ')[1];
			continue;
		}
		if (line.find("Ka") != std::string::npos)
		{
			auto color = Split(line, ' ');
			entity.Ambient.x = std::atof(color[1].c_str());
			entity.Ambient.y = std::atof(color[2].c_str());
			entity.Ambient.z = std::atof(color[3].c_str());
			continue;
		}
		if (line.find("Kd") != std::string::npos)
		{
			auto color = Split(line, ' ');
			entity.Diffuse.x = std::atof(color[1].c_str());
			entity.Diffuse.y = std::atof(color[2].c_str());
			entity.Diffuse.z = std::atof(color[3].c_str());
			continue;
		}
		if (line.find("Ks") != std::string::npos)
		{
			auto color = Split(line, ' ');
			entity.Specular.x = std::atof(color[1].c_str());
			entity.Specular.y = std::atof(color[2].c_str());
			entity.Specular.z = std::atof(color[3].c_str());
			continue;
		}
		if (line.find("Ke") != std::string::npos)
		{
			auto color = Split(line, ' ');
			entity.Emissive.x = std::atof(color[1].c_str());
			entity.Emissive.y = std::atof(color[2].c_str());
			entity.Emissive.z = std::atof(color[3].c_str());
			continue;
		}

		if (line.find("illum") != std::string::npos)
		{
			entity.Power = std::atof(Split(line, ' ')[1].c_str());
			continue;
		}

	}
}
void CreateMeshEntity(Entity::Mesh& _mesh, std::string _path)
{
	std::ifstream fileStream(_path);

	if (fileStream.fail())
	{
		___THROW_EXCEPTION_POINT(Utility::Exception, _path + "オープン失敗");
	}

	//今回はこの二樹類
	int vertexCount = 0;
	int normalCount = 0;
	int faceCount = 0;

	std::string line;
	std::string Name;
	std::string materialFile;

	while (getline(fileStream, line))
	{
		if (line.find("#") != std::string::npos)
		{
			continue;
		}

		if (line.find("o") != std::string::npos)
		{
			continue;
		}
		if (line.find("s") != std::string::npos)
		{
			continue;
		}
		if (line.find("mtllib") != std::string::npos)
		{
			continue;
		}
		if (line.find("usemtl") != std::string::npos)
		{
			continue;
		}

		if (line.find("vn") != std::string::npos)
		{
			normalCount++;
			continue;
		}
		if (line.find("v") != std::string::npos)
		{
			vertexCount++;
			continue;
		}
		if (line.find("f") != std::string::npos)
		{
			faceCount++;
			continue;
		}
	}

	_mesh.Name = Name;
	_mesh.VertexCont = vertexCount;
	_mesh.SizeOfVertex = sizeof(Vertex);
	_mesh.FaceCont = faceCount;

	std::vector<Vertex> VertexBuffer;
	std::vector<D3DXVECTOR3> Coord;
	std::vector<D3DXVECTOR3> Normal;
	std::vector<int> FaceBuffer;

	VertexBuffer.resize(_mesh.VertexCont);

	fileStream.clear();
	fileStream.seekg(0, std::ios_base::beg);

	while (getline(fileStream, line))
	{
		if (line.find("#") != std::string::npos)
		{
			continue;
		}

		if (line.find("o") != std::string::npos)
		{
			continue;
		}
		if (line.find("s") != std::string::npos)
		{
			continue;
		}
		if (line.find("mtllib") != std::string::npos)
		{
			continue;
		}
		if (line.find("usemtl") != std::string::npos)
		{
			continue;
		}
		if (line.find("vn") != std::string::npos)
		{
			auto splited = Split(line, ' ');
			D3DXVECTOR3 normal;
			normal.x = -std::atof(splited[1].c_str());
			normal.y = std::atof(splited[2].c_str());
			normal.z = std::atof(splited[3].c_str());
			Normal.push_back(normal);
			continue;
		}
		if (line.find("v") != std::string::npos)
		{
			auto splited = Split(line, ' ');
			D3DXVECTOR3 coord;

			coord.x = -std::atof(splited[1].c_str());
			coord.y = std::atof(splited[2].c_str());
			coord.z = std::atof(splited[3].c_str());
			Coord.push_back(coord);
			continue;
		}
		if (line.find("f") != std::string::npos)
		{
			auto splitedVertex = Split(line, ' ');
			auto vertex1 = Split(splitedVertex[1], '//');
			auto vertex2 = Split(splitedVertex[2], '//');
			auto vertex3 = Split(splitedVertex[3], '//');

			auto v1Index = std::atoi(vertex1[0].c_str()) - 1;
			auto v2Index = std::atoi(vertex2[0].c_str()) - 1;
			auto v3Index = std::atoi(vertex3[0].c_str()) - 1;

			FaceBuffer.push_back(v1Index);
			FaceBuffer.push_back(v2Index);
			FaceBuffer.push_back(v3Index);

			Vertex v1, v2, v3;

			v1.position = Coord[std::atoi(vertex1[0].c_str()) - 1];
			v1.normal = Normal[std::atoi(vertex1[2].c_str()) - 1];
			v2.position = Coord[std::atoi(vertex2[0].c_str()) - 1];
			v2.normal = Normal[std::atoi(vertex2[2].c_str()) - 1];
			v3.position = Coord[std::atoi(vertex3[0].c_str()) - 1];
			v3.normal = Normal[std::atoi(vertex3[2].c_str()) - 1];

			VertexBuffer[v1Index] = v1;
			VertexBuffer[v2Index] = v2;
			VertexBuffer[v3Index] = v3;

			continue;
		}
	}

	auto& graphics = Rendering::Graphics::Instantiate();

	//バーテックスバッファーを作成
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) *_mesh.VertexCont;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = VertexBuffer.data();
	if (FAILED(graphics.Device->CreateBuffer(&bd, &InitData, &_mesh.VertexBuffer)))
	{
		___THROW_EXCEPTION_POINT(Utility::Exception, "VertexBuffer失敗");
	}

	//インデックスバッファーを作成
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * _mesh.FaceCont * 3;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	InitData.pSysMem = FaceBuffer.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	if (FAILED(graphics.Device->CreateBuffer(&bd, &InitData, &_mesh.IndexBuffer)))
	{
		___THROW_EXCEPTION_POINT(Utility::Exception, "IndexBuffer失敗");
	}

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

		Entity::Mesh meshEntity;
		CreateMeshEntity(meshEntity, "untitled.object");//TODO Serviceから生成
		Entity::Shader shaderEntity("Simple.hlsl");
		shaderEntity.CreateConstantBuffer<D3DXMATRIX>();
		Entity::Material materialEntity(&shaderEntity);
		CreateMaterialEntity(materialEntity, "untitled.object", &shaderEntity);

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
			D3DXMatrixRotationY(&World, timeGetTime() / 1100.0f);
			// ビュートランスフォーム
			D3DXVECTOR3 vEyePt(0.0f, 3.0f, -4.0f); //視点位置
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