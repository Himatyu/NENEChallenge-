#pragma once
#include"Shader.h"

template<class Buffer>
void Shader::CreateConstantBuffer()
{
	auto& graphics = Rendering::Graphics::Instantiate();

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
}