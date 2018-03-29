
template<class Buffer>
Shader<Buffer>::Shader(std::string _path) :
	IShader(_path)
{
}

template<class Buffer>
Shader<Buffer>::~Shader()
{
	SAFE_RELEASE(pConstantBuffer);
	SAFE_RELEASE(pVertexLayout);
}

template<class T>
void Shader<T>::Configurate()
{
	auto& graphics = Rendering::Graphics::Instantiate();
	auto filePath = spEntity->spDto->filePath;
	ID3DBlob *pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;

	//�t�@�C������V�F�[�_�ǂݍ���
	if (FAILED(D3DX11CompileFromFile(
		filePath.c_str(),
		NULL,
		NULL,
		"VS",
		"vs_5_0",
		0,
		0,
		NULL,
		&pCompiledShader, &pErrors, NULL)))
	{
		___THROW_EXCEPTION_POINT(Utility::Exception, (char*)pErrors->GetBufferPointer());
	}
	SAFE_RELEASE(pErrors);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(graphics.Device->CreateInputLayout(
		layout,
		numElements,
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		&pVertexLayout)))
	{
		___THROW_EXCEPTION_POINT(Utility::Exception, "�C���v�b�g���C�A�E�g�쐬�Ɏ��s");
	}


	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(T);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(graphics.Device->CreateBuffer(&cb, NULL, &pConstantBuffer)))
	{
		___THROW_EXCEPTION_POINT(Utility::Exception, "�R���X�^���X�o�b�t�@�쐬�Ɏ��s");
	}

}

template<class T>
void Shader<T>::Apply()
{
	auto& graphics = Rendering::Graphics::Instantiate();

	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(graphics.DeviceContext->Map(pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		memcpy_s(pData.pData, pData.RowPitch, (void*)&buffer, sizeof(T));
		graphics.DeviceContext->Unmap(pConstantBuffer, 0);
	}

	//�g�p����V�F�[�_�[�̓o�^
	graphics.DeviceContext->VSSetShader(spEntity->VertexShader, NULL, 0);
	graphics.DeviceContext->PSSetShader(spEntity->PixelShader, NULL, 0);

	graphics.DeviceContext->IASetInputLayout(pVertexLayout);
	//�R���X�^���g�o�b�t�@�[���A�ǂ̃V�F�[�_�[�Ŏg�������w��

	graphics.DeviceContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);
	graphics.DeviceContext->PSSetConstantBuffers(0, 1, &pConstantBuffer);

}