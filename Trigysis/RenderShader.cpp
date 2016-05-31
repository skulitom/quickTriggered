#include "RenderShader.h"

#include <Directx\D3Dcompiler.h>
#include <Directx\d3dx11effect.h>
RenderShader::RenderShader(D3DAPP* d3dApp)
{

	this->D3dApp = d3dApp;

	this->ShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	this->ShaderFlags |= D3D10_SHADER_DEBUG;
	this->ShaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
	this->ShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	this->ShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	D3D11_BUFFER_DESC RBD;
	ZeroMemory(&RBD, sizeof(D3D11_BUFFER_DESC));
	RBD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	RBD.MiscFlags = 0;
	RBD.StructureByteStride = 0;
	RBD.Usage = D3D11_USAGE_DEFAULT;

	RBD.ByteWidth = 272;
	this->D3dApp->dxDevice->CreateBuffer(&RBD, 0, &this->WorldMatrixCBuffer);

	RBD.ByteWidth = 16;
	this->D3dApp->dxDevice->CreateBuffer(&RBD, 0, &this->PerFrameCBuffer);

	ID3D11Texture2D* RenderBufferTexture;
	D3D11_TEXTURE2D_DESC T2DD;
	ZeroMemory(&T2DD, sizeof(D3D11_TEXTURE2D_DESC));
	T2DD.ArraySize = 1;
	T2DD.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	T2DD.CPUAccessFlags = 0;
	T2DD.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	T2DD.Height = 350;
	T2DD.Width = 350;
	T2DD.MipLevels = 1;
	T2DD.MiscFlags = 0;
	T2DD.SampleDesc.Count = 1;
	T2DD.SampleDesc.Quality = 0;
	T2DD.Usage = D3D11_USAGE_DEFAULT;
	this->D3dApp->dxDevice->CreateTexture2D(&T2DD, 0, &RenderBufferTexture);

	this->ResourceTexture = RenderBufferTexture;
	D3D11_SHADER_RESOURCE_VIEW_DESC SRVD;
	ZeroMemory(&SRVD, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	SRVD.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SRVD.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	SRVD.Buffer.ElementOffset = 0;
	SRVD.Buffer.FirstElement = 0;
	SRVD.Buffer.NumElements = 1;
	SRVD.BufferEx.FirstElement = 0;
	SRVD.BufferEx.Flags = 0;
	SRVD.BufferEx.NumElements = 1;
	SRVD.Texture2D.MipLevels = 1;
	SRVD.Texture2D.MostDetailedMip = 0;
	this->D3dApp->dxDevice->CreateShaderResourceView(RenderBufferTexture, &SRVD, &this->RenderBufferResource);

}

RenderShader::~RenderShader()
{

	D3DRelease(WorldMatrixCBuffer);
	D3DRelease(Sampler);
	D3DRelease(PerFrameCBuffer);
	D3DRelease(ResourceTexture);
	D3DRelease(RenderBufferResource);
	D3DRelease(BlobVShader);
	D3DRelease(VertexShader);
	D3DRelease(PixelShader)

}

bool RenderShader::CreateVertexShader(LPCSTR fileName, LPCSTR func)
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

	return true;
}

bool RenderShader::CreatePixelShader(LPCSTR fileName, LPCSTR func)
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

	return true;
}

//void RenderShader::UpdatePerMeshInputs(Element* elementToRender, XMFLOAT2& windowMouseVPCoord, FLOAT totalTime)
//{
//
//	this->D3dApp->SetViewPort(elementToRender->GetIndexOfViewPort());
//
//	////////////////////////////////////////
//	//**Set Vertex Shader
//	////////////////////////////////////////
//
//	////////////////////////////////////////
//	//**Set Matrix
//	////////////////////////////////////////
//	D3DXMatrixIdentity(&this->ScaleMatrix);
//	D3DXMatrixIdentity(&this->WorldMatrix);
//
//	D3DXMatrixScaling(&ScaleMatrix, elementToRender->GetSizes().X, elementToRender->GetSizes().Y, 1);
//	D3DXMatrixTranslation(&this->WorldMatrix,
//		elementToRender->GetPosition().X, elementToRender->GetPosition().Y, 0);
//
//	D3DXMatrixMultiply(&this->WorldMatrix, &ScaleMatrix, &this->WorldMatrix);
//
//	D3DXMatrixOrthoLH(&this->ProjectMatrix, this->D3dApp->GetViewPort(elementToRender->GetIndexOfViewPort()).Width,
//		this->D3dApp->GetViewPort(elementToRender->GetIndexOfViewPort()).Height, 0, 1);
//
//	D3DXMatrixTranspose(&this->WorldMatrix, &this->WorldMatrix);
//	this->SWMCBuffer.WorldMatrix = this->WorldMatrix;
//	this->SWMCBuffer.Color = elementToRender->GetColors();
//	this->SWMCBuffer.ProjMatrix = this->ProjectMatrix;
//	if (elementToRender->GetIsNeedBlink())
//		this->SWMCBuffer.Color.y = sinf(totalTime);
//
//	this->D3dApp->dxDeviceCon->UpdateSubresource(this->WorldMatrixCBuffer, 0, 0, &this->SWMCBuffer, 0, 0);
//	this->D3dApp->dxDeviceCon->VSSetConstantBuffers(0, 1, &this->WorldMatrixCBuffer);
//
//	////////////////////////////////////////
//	//**Set Pixel Shader
//	////////////////////////////////////////
//
//	this->RenderBufferResource = elementToRender->GetTextureViewPtr();
//
//	this->SPFBuffer.BrushPos = windowMouseVPCoord;
//	this->D3dApp->dxDeviceCon->UpdateSubresource(this->PerFrameCBuffer, 0, 0, &this->SPFBuffer, 0, 0);
//	this->D3dApp->dxDeviceCon->PSSetConstantBuffers(0, 1, &this->PerFrameCBuffer);
//
//	this->D3dApp->dxDeviceCon->PSSetShaderResources(0, 1, &this->RenderBufferResource);
//
//}

void RenderShader::UpdateStandartInputs()
{

	this->SetVShader();
	this->SetPShader();

	D3DXMatrixLookAtLH(&this->ViewMatrix, &D3DXVECTOR3(0, 0, -1), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));

	////////////////////////////////////////////////////
	//**Set Sampler
	////////////////////////////////////////////////////
	D3D11_SAMPLER_DESC SD;
	ZeroMemory(&SD, sizeof(D3D11_SAMPLER_DESC));
	SD.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SD.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SD.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	SD.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SD.MaxAnisotropy = 1;

	HRESULT hr = this->D3dApp->dxDevice->CreateSamplerState(&SD, &this->Sampler);
	///////////////////////////////////////////////////////
	//**Set Vertex Shader
	//**Set View And Project Matrix
	///////////////////////////////////////////////////////

	D3DXMatrixTranspose(&this->ViewMatrix, &this->ViewMatrix);

	this->SWMCBuffer.ViewMatrix = this->ViewMatrix;

	///////////////////////////////////////////////////////
	//**Set Pixel Shader
	//**Set Sampler
	///////////////////////////////////////////////////////

	this->D3dApp->dxDeviceCon->PSSetSamplers(0, 1, &this->Sampler);

}

void RenderShader::SetVShader()
{

	if (this->VertexShader)
		this->D3dApp->dxDeviceCon->VSSetShader(this->VertexShader, 0, 0);

}

void RenderShader::SetPShader()
{

	if (this->PixelShader)
		this->D3dApp->dxDeviceCon->PSSetShader(this->PixelShader, 0, 0);

}

ID3D10Blob* RenderShader::GetBlobVShader()
{

	if (this->BlobVShader)
		return this->BlobVShader;

	return nullptr;

}