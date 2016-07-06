//#include "Basic2DDrawPipeline.h"
//#include "MathHelper.h"
//Basic2DDrawPipeline::Basic2DDrawPipeline(D3DAPP* d3dApp, char shaderModel)
//	:Shader(d3dApp, shaderModel)
//{
//
//	this->IndexOfVP = -1;
//
//	D3DXMatrixLookAtLH(&this->ViewMatrix, &D3DXVECTOR3(0, 0, -1), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
//	D3DXMatrixTranspose(&this->ViewMatrix, &this->ViewMatrix);
//	this->SWMCBuffer.ViewMatrix = this->ViewMatrix;
//
//	this->WorldMatrixCBuffer = this->D3dApp->CreateSConstantBuffer(224);
//	this->RandomVarCBuffer = this->D3dApp->CreateSConstantBuffer(16);
//
//	///////////////////////////////////////
//	//**VertexBuffer
//	///////////////////////////////////////
//	this->VertexBuffer = this->D3dApp->CreateSVertexBuffer(true, sizeof(Basic2DDrawPipeline::Vertex2d), 10);
//
//	///////////////////////////////////////
//	//**Rectangle
//	///////////////////////////////////////
//	Basic2DDrawPipeline::Vertex2d VertexArray[10];
//
//	VertexArray[0].Pos = Vector2d(-0.5f, -0.5f);
//	VertexArray[0].TexturePos = Vector2d(0, 1);
//
//	VertexArray[1].Pos = Vector2d(-0.5f, 0.5f);
//	VertexArray[1].TexturePos = Vector2d(0, 0);
//
//	VertexArray[2].Pos = Vector2d(0.5f, 0.5f);
//	VertexArray[2].TexturePos = Vector2d(1, 0);
//
//	VertexArray[3].Pos = Vector2d(0.5f, -0.5f);
//	VertexArray[3].TexturePos = Vector2d(1, 1);
//
//	///////////////////////////////////////
//	//**Hexagon
//	///////////////////////////////////////
//
//	const float AVal = 0.866f*0.5f;
//	const float HalfVal = 0.5f*0.5f;
//
//	VertexArray[4].Pos = Vector2d(-HalfVal,-AVal);
//	VertexArray[4].TexturePos = Vector2d(0.25f, 0.933f);
//
//	VertexArray[5].Pos = Vector2d(-0.5f, 0);
//	VertexArray[5].TexturePos = Vector2d(0.f, 0.5f);
//
//	VertexArray[6].Pos = Vector2d(-HalfVal, AVal);
//	VertexArray[6].TexturePos = Vector2d(0.25f, 0.134f);
//
//	VertexArray[7].Pos = Vector2d(HalfVal, AVal);
//	VertexArray[7].TexturePos = Vector2d(0.75f, 0.134f);
//
//	VertexArray[8].Pos = Vector2d(0.5f, 0);
//	VertexArray[8].TexturePos = Vector2d(1.f, 0.5f);
//
//	VertexArray[9].Pos = Vector2d(HalfVal, -AVal);
//	VertexArray[9].TexturePos = Vector2d(0.75f, 0.933f);
//
//	D3D11_MAPPED_SUBRESOURCE MSR;
//	this->D3dApp->dxDeviceCon->Map(this->VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MSR);
//	memcpy(MSR.pData, &VertexArray[0], sizeof(Basic2DDrawPipeline::Vertex2d) * ARRAYSIZE(VertexArray));
//	this->D3dApp->dxDeviceCon->Unmap(this->VertexBuffer, 0);
//
//	////////////////////////////////////
//	//**Index Buffer
//	////////////////////////////////////
//
//	////////////////////////////////////
//	//**Rectangle
//	////////////////////////////////////
//	std::vector <UINT> IndexArray(18);
//	IndexArray[0] = 0;
//	IndexArray[1] = 1;
//	IndexArray[2] = 2;
//	IndexArray[3] = 0;
//	IndexArray[4] = 2;
//	IndexArray[5] = 3;
//
//	///////////////////////////////////////
//	//**Hexagon
//	///////////////////////////////////////
//
//	IndexArray[6] = 4;
//	IndexArray[7] = 5;
//	IndexArray[8] = 6;
//	IndexArray[9] = 4;
//	IndexArray[10] = 6;
//	IndexArray[11] = 9;
//	IndexArray[12] = 6;
//	IndexArray[13] = 7;
//	IndexArray[14] = 9;
//	IndexArray[15] = 9;
//	IndexArray[16] = 7;
//	IndexArray[17] = 8;
//
//	this->IndexBuffer = this->D3dApp->CreateSIndexBuffer(IndexArray);
//
//	this->CreateVertexShader("B2DVShader.fx", "VSMain");
//	this->CreatePixelShader("B2DPShader.fx", "PSMain");
//
//}
//
//Basic2DDrawPipeline::~Basic2DDrawPipeline()
//{
//	D3DRelease(WorldMatrixCBuffer);
//	D3DRelease(Sampler);
//	D3DRelease(ResourceTexture);
//	D3DRelease(RenderBufferResource);
//	D3DRelease(this->RandomVarCBuffer);
//	D3DRelease(this->InputLayout);
//	D3DRelease(this->IndexBuffer);
//}
//
//bool Basic2DDrawPipeline::CreateVertexShader(LPCSTR fileName, LPCSTR func)
//{
//	
//	Shader::CreateVertexShader(fileName, func);
//
//	///////////////////////////////////////
//	//**Create InputLayout
//	///////////////////////////////////////
//	D3D11_INPUT_ELEMENT_DESC IED[] =
//	{
//		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 }
//	};
//	this->D3dApp->dxDevice->CreateInputLayout(IED, ARRAYSIZE(IED), this->BlobVShader->GetBufferPointer(),
//		this->BlobVShader->GetBufferSize(), &this->InputLayout);
//
//	this->D3dApp->dxDeviceCon->IASetInputLayout(this->InputLayout);
//	return true;
//}
//
//bool Basic2DDrawPipeline::CreatePixelShader(LPCSTR fileName, LPCSTR func)
//{
//	
//	Shader::CreatePixelShader(fileName, func);
//
//	////////////////////////
//	//ID3DBlob* BlobPShader = 0;
//	//ID3DBlob* compilationMessage = 0;
//	//std::string SMString;
//	//if (this->ShaderModel == SHADER_MODEL_4_0)
//	//	SMString = "ps_4_0";
//	//else if (this->ShaderModel == SHADER_MODEL_4_1)
//	//	SMString = "ps_4_1";
//	//else if (this->ShaderModel == SHADER_MODEL_5_0)
//	//	SMString = "ps_5_0";
//	//else
//	//	return false;
//	////this->ShaderFlags |= D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY;
//	//HRESULT hr = D3DX11CompileFromFile("TPPShader.fx", 0, 0, "PSNoise", SMString.c_str(), this->ShaderFlags, 0, 0, &BlobPShader, &compilationMessage, 0);
//	//if (compilationMessage != 0)
//	//{
//	//	MessageBox(this->D3dApp->GetWindow(), "Compilation shader failed (PS2)", "Error!", MB_ICONERROR);
//	//}
//	//if (FAILED(hr))
//	//{
//	//	MessageBox(this->D3dApp->GetWindow(), "Pixel shader 2 load failed!", "Shader load ERROR", MB_ICONERROR);
//	//	D3DRelease(BlobPShader);
//	//	return false;
//	//}
//	//hr = this->D3dApp->dxDevice->CreatePixelShader(BlobPShader->GetBufferPointer(), BlobPShader->GetBufferSize(),
//	//	0, &this->APixelShader);
//	//if (FAILED(hr))
//	//{
//	//	MessageBox(this->D3dApp->GetWindow(), "Create pixel shader 2 failed!", "Pixel shader error!", MB_ICONERROR);
//	//	D3DRelease(BlobPShader);
//	//	return false;
//	//}
//	//this->ShaderFlags &= (~D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY);
//	////////////////////////
//
//	D3D11_SAMPLER_DESC SD;
//	ZeroMemory(&SD, sizeof(D3D11_SAMPLER_DESC));
//	SD.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
//	SD.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
//	SD.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
//	SD.Filter = D3D11_FILTER_COMPARISON_ANISOTROPIC;
//	SD.MaxAnisotropy = 1;
//	HRESULT hr = this->D3dApp->dxDevice->CreateSamplerState(&SD, &this->Sampler);
//	return true;
//}
//
//void Basic2DDrawPipeline::Apply(short indexOfVP, XMFLOAT4& color, Vector2d& pos, Vector2d& size)
//{
//
//	//this->D3dApp->dxDeviceCon->IASetVertexBuffers(0, 1, &this->VertexBuffer, &PStrides, &POffSet);
//	//this->D3dApp->dxDeviceCon->IASetInputLayout(this->InputLayout);
//	//this->D3dApp->dxDeviceCon->RSSetState(this->D3dApp->GetStandartRastState());
//
//	
//
//	this->PStrides = sizeof(Basic2DDrawPipeline::Vertex2d);
//	this->POffSet = 0;
//	this->D3dApp->dxDeviceCon->IASetVertexBuffers(0, 1, &this->VertexBuffer, &PStrides, &POffSet);
//	this->D3dApp->dxDeviceCon->IASetIndexBuffer(this->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
//	this->D3dApp->dxDeviceCon->RSSetState(this->D3dApp->GetStandartRastState());
//	this->D3dApp->dxDeviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//	if (this->IndexOfVP < 0 || this->IndexOfVP != indexOfVP)
//	{
//		this->D3dApp->SetViewPort(indexOfVP);
//		this->IndexOfVP = indexOfVP;
//		this->SWMCBuffer.ProjMatrix = this->D3dApp->GetVPMatrix(this->IndexOfVP);
//	}
//
//	D3DXMatrixIdentity(&this->WorldMatrix);
//	D3DXMatrixTranslation(&this->WorldMatrix, pos.X, pos.Y, 0);
//	D3DXMatrixScaling(&this->ScaleMatrix, size.X, size.Y, 1);
//
//	D3DXMatrixMultiply(&this->WorldMatrix, &this->ScaleMatrix, &this->WorldMatrix);
//
//	//D3DXMatrixOrthoLH(&this->ProjectMatrix, this->D3dApp->GetViewPort(indexOfVP).Width,
//	//	this->D3dApp->GetViewPort(indexOfVP).Height, 0, 1);
//
//	//D3DXMatrixLookAtLH(&this->ViewMatrix, &D3DXVECTOR3(0, 0, -1), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
//	//D3DXMatrixTranspose(&this->ViewMatrix, &this->ViewMatrix);
//
//	D3DXMatrixTranspose(&this->WorldMatrix, &this->WorldMatrix);
//
//	this->SWMCBuffer.WorldMatrix = this->WorldMatrix;
//	this->SWMCBuffer.Color = color;
//	this->SRVCBuffer.RandVar = RAND(0.f, 100.f)/ 100.f;
//	//this->SRVCBuffer.Time = this->SRVCBuffer.Time + deltaTime;
//
//	this->SetVShader();
//	this->D3dApp->dxDeviceCon->UpdateSubresource(this->WorldMatrixCBuffer, 0, 0, &this->SWMCBuffer, 0, 0);
//	this->D3dApp->dxDeviceCon->VSSetConstantBuffers(0, 1, &this->WorldMatrixCBuffer);
//	/*this->D3dApp->dxDeviceCon->PSSetShader(this->APixelShader, 0, 0);
//	this->D3dApp->dxDeviceCon->UpdateSubresource(this->RandomVarCBuffer, 0, 0, &this->SRVCBuffer, 0, 0);
//	this->D3dApp->dxDeviceCon->PSSetConstantBuffers(0, 1, &this->RandomVarCBuffer);
//	this->D3dApp->dxDeviceCon->PSSetSamplers(0, 1, &this->Sampler);
//	this->D3dApp->dxDeviceCon->PSSetShaderResources(0, 1, &this->RenderBufferResource);*/
//	this->SetPShader();
//	this->D3dApp->dxDeviceCon->UpdateSubresource(this->RandomVarCBuffer, 0, 0, &this->SRVCBuffer, 0, 0);
//	this->D3dApp->dxDeviceCon->PSSetConstantBuffers(0, 1, &this->RandomVarCBuffer);
//	this->D3dApp->dxDeviceCon->PSSetSamplers(0, 1, &this->Sampler);
//	this->D3dApp->dxDeviceCon->PSSetShaderResources(0, 1, &this->RenderBufferResource);
//}
