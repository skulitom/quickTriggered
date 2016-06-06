#include "Shader.h"

#include "DXInclude\D3Dcompiler.h"
#include "DXInclude\d3dx11effect.h"
Shader::Shader(D3DAPP* d3dApp)
{

	this->ShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	this->ShaderFlags |= D3D10_SHADER_DEBUG;
	this->ShaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
	this->ShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	this->ShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	this->D3dApp = d3dApp;

	//this->WorldMatrixCBuffer = this->D3dApp->CreateSConstantBuffer(192);
	//this->VertexBuffer = this->D3DApp->CreateSVertexBuffer(true, sizeof(Basic2DDrawPipeline::Vertex2d), 3);
}

Shader::~Shader()
{
	//D3DRelease(WorldMatrixCBuffer);
	//D3DRelease(Sampler);
	//D3DRelease(ResourceTexture);
	//D3DRelease(RenderBufferResource);
	D3DRelease(this->BlobVShader);
	D3DRelease(this->VertexShader);
	D3DRelease(this->PixelShader);
	D3DRelease(this->VertexBuffer);
	//D3DRelease(this->InputLayout);
}

bool Shader::CreateVertexShader(LPCSTR fileName, LPCSTR func)
{

	this->BlobVShader = 0;
	ID3DBlob* compilationMessage = 0;
	HRESULT hr = D3DX11CompileFromFile(fileName, 0, 0, func, "vs_5_0", this->ShaderFlags, 0, 0, &this->BlobVShader, &compilationMessage, 0);
	if (compilationMessage != 0)
	{
		MessageBox(this->D3dApp->GetWindow(), "Compilation shader failed (VS)", "Error!", MB_ICONERROR);
	}
	if (FAILED(hr))
	{
		MessageBox(this->D3dApp->GetWindow(), "Vertex shader load failed!", "Shader load ERROR", MB_ICONERROR);
		D3DRelease(this->BlobVShader);
		return false;
	}
	hr = this->D3dApp->dxDevice->CreateVertexShader(this->BlobVShader->GetBufferPointer(), this->BlobVShader->GetBufferSize(),
		0, &this->VertexShader);
	if (FAILED(hr))
	{
		MessageBox(this->D3dApp->GetWindow(), "Create vertex shader failed!", "Vertex shader error!", MB_ICONERROR);
		D3DRelease(this->BlobVShader);
		return false;
	}

}

bool Shader::CreatePixelShader(LPCSTR fileName, LPCSTR func)
{

	ID3DBlob* BlobPShader = 0;
	ID3DBlob* compilationMessage = 0;
	HRESULT hr = D3DX11CompileFromFile(fileName, 0, 0, func, "ps_5_0", this->ShaderFlags, 0, 0, &BlobPShader, &compilationMessage, 0);
	if (compilationMessage != 0)
	{
		MessageBox(this->D3dApp->GetWindow(), "Compilation shader failed (PS)", "Error!", MB_ICONERROR);
	}
	if (FAILED(hr))
	{
		MessageBox(this->D3dApp->GetWindow(), "Pixel shader load failed!", "Shader load ERROR", MB_ICONERROR);
		D3DRelease(BlobPShader);
		return false;
	}
	hr = this->D3dApp->dxDevice->CreatePixelShader(BlobPShader->GetBufferPointer(), BlobPShader->GetBufferSize(),
		0, &this->PixelShader);
	if (FAILED(hr))
	{
		MessageBox(this->D3dApp->GetWindow(), "Create pixel shader failed!", "Vertex shader error!", MB_ICONERROR);
		D3DRelease(BlobPShader);
		return false;
	}

}

void Shader::SetVShader()
{

	if (this->VertexShader)
		this->D3dApp->dxDeviceCon->VSSetShader(this->VertexShader, 0, 0);

}

void Shader::SetPShader()
{

	if (this->PixelShader)
		this->D3dApp->dxDeviceCon->PSSetShader(this->PixelShader, 0, 0);

}

ID3D10Blob* Shader::GetBlobVShader()
{

	if (this->BlobVShader)
		return this->BlobVShader;
	return nullptr;

}