#pragma once
#include"Shader.h"
template<class Buffer>
inline void Shader::DatePush(Buffer * _buffer)
{
	auto& graphics = Rendering::Graphics::Instantiate();

	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(graphics.DeviceContext->Map(
		entity.ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) //ロックする
	{
		memcpy_s(pData.pData, pData.RowPitch, (void*)(_buffer), sizeof(Buffer));
		graphics.DeviceContext->Unmap(entity.ConstantBuffer, 0);	//アンロック
	}
}