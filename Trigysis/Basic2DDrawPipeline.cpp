#include "Basic2DDrawPipeline.h"
Basic2DDrawPipeline::Basic2DDrawPipeline(D3DAPP* d3dApp)
	:Shader(d3dApp)
{

	this->WorldMatrixCBuffer = this->D3dApp->CreateSConstantBuffer(192);
	this->VertexBuffer = this->D3dApp->CreateSVertexBuffer(true, sizeof(Basic2DDrawPipeline::Vertex2d), 3);
}

Basic2DDrawPipeline::~Basic2DDrawPipeline()
{
	D3DRelease(WorldMatrixCBuffer);
	D3DRelease(Sampler);
	D3DRelease(ResourceTexture);
	D3DRelease(RenderBufferResource);
	D3DRelease(this->InputLayout);
}

bool Basic2DDrawPipeline::CreateVertexShader(LPCSTR fileName, LPCSTR func)
{
	
	Shader::CreateVertexShader(fileName, func);

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
	
	Shader::CreatePixelShader(fileName, func);

	D3D11_SAMPLER_DESC SD;
	ZeroMemory(&SD, sizeof(D3D11_SAMPLER_DESC));
	SD.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SD.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SD.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	SD.Filter = D3D11_FILTER_COMPARISON_ANISOTROPIC;
	SD.MaxAnisotropy = 1;
	HRESULT hr = this->D3dApp->dxDevice->CreateSamplerState(&SD, &this->Sampler);
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
