#include "Basic2DDrawPipeline.h"
#include <Directx\D3Dcompiler.h>
#include <Directx\d3dx11effect.h>
Basic2DDrawPipeline::Basic2DDrawPipeline(D3DAPP* d3dApp)
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
	
	this->WorldMatrixCBuffer = this->D3dApp->CreateSConstantBuffer(192);
	this->VertexBuffer = this->D3dApp->CreateSVertexBuffer(true, sizeof(Basic2DDrawPipeline::Vertex2d), 3);
}

Basic2DDrawPipeline::~Basic2DDrawPipeline()
{
	D3DRelease(WorldMatrixCBuffer);
	D3DRelease(Sampler);
	D3DRelease(ResourceTexture);
	D3DRelease(RenderBufferResource);
	D3DRelease(BlobVShader);
	D3DRelease(VertexShader);
	D3DRelease(PixelShader);
	D3DRelease(this->VertexBuffer);
	D3DRelease(this->InputLayout);
}

bool Basic2DDrawPipeline::CreateVertexShader(LPCSTR fileName, LPCSTR func)
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
	///////////////////////////////////////
	//**Create InputLayout
	///////////////////////////////////////
	D3D11_INPUT_ELEMENT_DESC IED[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	this->D3dApp->dxDevice->CreateInputLayout(IED, ARRAYSIZE(IED), this->BlobVShader->GetBufferPointer(),
		this->BlobVShader->GetBufferSize(), &this->InputLayout);
	return true;
}

bool Basic2DDrawPipeline::CreatePixelShader(LPCSTR fileName, LPCSTR func)
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
	D3D11_SAMPLER_DESC SD;
	ZeroMemory(&SD, sizeof(D3D11_SAMPLER_DESC));
	SD.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SD.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SD.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	SD.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SD.MaxAnisotropy = 1;
	hr = this->D3dApp->dxDevice->CreateSamplerState(&SD, &this->Sampler);
	return true;
}

void Basic2DDrawPipeline::Apply(short indexOfVP)
{
	UINT PStrides = sizeof(Basic2DDrawPipeline::Vertex2d);
	UINT POffSet = 0;
	this->D3dApp->dxDeviceCon->IASetVertexBuffers(0, 1, &this->VertexBuffer, &PStrides, &POffSet);
	this->D3dApp->dxDeviceCon->IASetInputLayout(this->InputLayout);
	this->D3dApp->dxDeviceCon->RSSetState(this->D3dApp->GetStandartRastState());
	D3DXMatrixIdentity(&this->WorldMatrix);
	D3DXMatrixOrthoLH(&this->ProjectMatrix, this->D3dApp->GetViewPort(indexOfVP).Width,
		this->D3dApp->GetViewPort(indexOfVP).Height, 0, 1);
	this->D3dApp->SetViewPort(indexOfVP);
	D3DXMatrixLookAtLH(&this->ViewMatrix, &D3DXVECTOR3(0, 0, -1), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&this->ViewMatrix, &this->ViewMatrix);
	this->SWMCBuffer.ProjMatrix = this->ProjectMatrix;
	this->SWMCBuffer.WorldMatrix = this->WorldMatrix;
	this->SWMCBuffer.ViewMatrix = this->ViewMatrix;
	this->SetVShader();
	this->D3dApp->dxDeviceCon->UpdateSubresource(this->WorldMatrixCBuffer, 0, 0, &this->SWMCBuffer, 0, 0);
	this->D3dApp->dxDeviceCon->VSSetConstantBuffers(0, 1, &this->WorldMatrixCBuffer);
	this->SetPShader();
	this->D3dApp->dxDeviceCon->PSSetSamplers(0, 1, &this->Sampler);
	this->D3dApp->dxDeviceCon->PSSetShaderResources(0, 1, &this->RenderBufferResource);
} 

void Basic2DDrawPipeline::SetVShader()
{
	if (this->VertexShader)
		this->D3dApp->dxDeviceCon->VSSetShader(this->VertexShader, 0, 0);
}

void Basic2DDrawPipeline::SetPShader()
{
	if (this->PixelShader)
		this->D3dApp->dxDeviceCon->PSSetShader(this->PixelShader, 0, 0);
}

ID3D10Blob* Basic2DDrawPipeline::GetBlobVShader()
{
	if (this->BlobVShader)
		return this->BlobVShader;
	return nullptr;
}