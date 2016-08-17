#include "ShaderManager.h"
#include "Files.h"

#include "DXInclude\D3Dcompiler.h"
#include "DXInclude\d3dx11effect.h"
ShaderManager::ShaderManager(D3DAPP* d3dApp, char shaderModel)
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

	this->ShaderModel = shaderModel;

	this->IndexOfVP = -1;

	//////////////////////////////////////////
	//**Create Samplers
	//////////////////////////////////////////

	this->AdvanceSampler = this->D3dApp->SCreateSampler(D3D11_TEXTURE_ADDRESS_BORDER, D3D11_FILTER_ANISOTROPIC, 16);

	this->SimpleSampler = this->D3dApp->SCreateSampler(D3D11_TEXTURE_ADDRESS_WRAP, D3D11_FILTER_ANISOTROPIC, 16);

	////////////////////////////////////////////////
	//**Create Buffers
	////////////////////////////////////////////////

	this->CBPSInput = this->D3dApp->CreateSConstantBuffer(sizeof(CBSPSInput));
	this->CBVSInput = this->D3dApp->CreateSConstantBuffer(sizeof(CBSVSInput));

	///////////////////////////////////////
	//**VertexBuffer
	///////////////////////////////////////
	this->VertexBuffer = this->D3dApp->CreateSVertexBuffer(true, sizeof(ShaderManager::Vertex2d), 10);

	///////////////////////////////////////
	//**Rectangle
	///////////////////////////////////////
	ShaderManager::Vertex2d VertexArray[10];

	VertexArray[0].Pos = Vector2d(-0.5f, -0.5f);
	VertexArray[0].TexturePos = Vector2d(0, 1);

	VertexArray[1].Pos = Vector2d(-0.5f, 0.5f);
	VertexArray[1].TexturePos = Vector2d(0, 0);

	VertexArray[2].Pos = Vector2d(0.5f, 0.5f);
	VertexArray[2].TexturePos = Vector2d(1, 0);

	VertexArray[3].Pos = Vector2d(0.5f, -0.5f);
	VertexArray[3].TexturePos = Vector2d(1, 1);

	///////////////////////////////////////
	//**Hexagon
	///////////////////////////////////////

	const float AVal = 0.866f*0.5f;
	const float HalfVal = 0.5f*0.5f;

	VertexArray[4].Pos = Vector2d(-HalfVal, -AVal);
	VertexArray[4].TexturePos = Vector2d(0.25f, 0.933f);

	VertexArray[5].Pos = Vector2d(-0.5f, 0);
	VertexArray[5].TexturePos = Vector2d(0.f, 0.5f);

	VertexArray[6].Pos = Vector2d(-HalfVal, AVal);
	VertexArray[6].TexturePos = Vector2d(0.25f, 0.134f);

	VertexArray[7].Pos = Vector2d(HalfVal, AVal);
	VertexArray[7].TexturePos = Vector2d(0.75f, 0.134f);

	VertexArray[8].Pos = Vector2d(0.5f, 0);
	VertexArray[8].TexturePos = Vector2d(1.f, 0.5f);

	VertexArray[9].Pos = Vector2d(HalfVal, -AVal);
	VertexArray[9].TexturePos = Vector2d(0.75f, 0.933f);

	D3D11_MAPPED_SUBRESOURCE MSR;
	this->D3dApp->DeviceContext->Map(this->VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MSR);
	memcpy(MSR.pData, &VertexArray[0], sizeof(ShaderManager::Vertex2d) * ARRAYSIZE(VertexArray));
	this->D3dApp->DeviceContext->Unmap(this->VertexBuffer, 0);

	////////////////////////////////////
	//**Index Buffer
	////////////////////////////////////

	////////////////////////////////////
	//**Rectangle
	////////////////////////////////////
	std::vector <UINT> IndexArray(18);
	IndexArray[0] = 0;
	IndexArray[1] = 1;
	IndexArray[2] = 2;
	IndexArray[3] = 0;
	IndexArray[4] = 2;
	IndexArray[5] = 3;

	///////////////////////////////////////
	//**Hexagon
	///////////////////////////////////////

	IndexArray[6] = 4;
	IndexArray[7] = 5;
	IndexArray[8] = 6;
	IndexArray[9] = 4;
	IndexArray[10] = 6;
	IndexArray[11] = 9;
	IndexArray[12] = 6;
	IndexArray[13] = 7;
	IndexArray[14] = 9;
	IndexArray[15] = 9;
	IndexArray[16] = 7;
	IndexArray[17] = 8;

	this->IndexBuffer = this->D3dApp->CreateSIndexBuffer(IndexArray);

	////////////////////////////////////////
	//**Create Standart Shaders
	////////////////////////////////////////

	this->StandartVShader = this->CreateVertexShader("StandartVShader.fx", "VSMain");
	this->StandartPShader = this->CreatePixelShader("StandartPShader.fx", "PSMain");

	////////////////////////////////////////
	//**Init Matrices
	////////////////////////////////////////

	D3DXMatrixLookAtLH(&this->ViewMatrix, &D3DXVECTOR3(0, 0, -1), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&this->ViewMatrix, &this->ViewMatrix);
	this->VSInput.ViewMatrix = this->ViewMatrix;

	ShaderManager::InitAllShaders();

}

void ShaderManager::SetFilter()
{

	//if (GetAsyncKeyState('1'))
	//	this->Filter = D3D11_FILTER_COMPARISON_ANISOTROPIC;
	//else if (GetAsyncKeyState('2'))
	//	this->Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	//else if (GetAsyncKeyState('3'))
	//	this->Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	//else if (GetAsyncKeyState('4'))
	//	this->Filter = D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
	//this->Filter = D3D11_FILTER_ANISOTROPIC;
	//if (GetAsyncKeyState('1'))
	//	this->AdvanceSampler = this->D3dApp->SCreateSampler(D3D11_TEXTURE_ADDRESS_BORDER, D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT, 1);
	//else if (GetAsyncKeyState('2'))
	//	this->AdvanceSampler = this->D3dApp->SCreateSampler(D3D11_TEXTURE_ADDRESS_WRAP, D3D11_FILTER_COMPARISON_ANISOTROPIC, 1);


	//this->AdvanceSampler = this->D3dApp->SCreateSampler(D3D11_TEXTURE_ADDRESS_BORDER, this->Filter, this->MaxAnis);

}

ShaderManager::~ShaderManager()
{

	this->DeleteAllShaders();

	D3DRelease(this->BlobVShader);
	D3DRelease(this->StandartVShader);
	D3DRelease(this->StandartPShader);
	D3DRelease(this->VertexBuffer);
	D3DRelease(this->IndexBuffer);
	D3DRelease(this->InputLayout);
	D3DRelease(this->SimpleSampler);
	D3DRelease(this->AdvanceSampler);
	D3DRelease(this->CBPSInput);
	D3DRelease(this->CBVSInput);

}

ID3D11VertexShader* ShaderManager::CreateVertexShader(LPCSTR fileName, LPCSTR func)
{

	this->BlobVShader = 0;
	ID3DBlob* compilationMessage = 0;

	std::string SMString;

	ID3D11VertexShader* VShader;

	if (this->ShaderModel == SHADER_MODEL_4_0)
		SMString = "vs_4_0";
	else if (this->ShaderModel == SHADER_MODEL_4_1)
		SMString = "vs_4_1";
	else if (this->ShaderModel == SHADER_MODEL_5_0)
		SMString = "vs_5_0";
	else
		return nullptr;

	HRESULT hr = D3DX11CompileFromFile(fileName, 0, 0, func, SMString.c_str(), this->ShaderFlags, 0, 0, &this->BlobVShader, &compilationMessage, 0);
	if (compilationMessage != 0)
	{
		MessageBox(this->D3dApp->GetWindow(), "Compilation shader failed (VS)", "Error!", MB_ICONERROR);
	}
	if (FAILED(hr))
	{
		MessageBox(this->D3dApp->GetWindow(), "Vertex shader load failed!", "Shader load ERROR", MB_ICONERROR);
		D3DRelease(this->BlobVShader);
		return nullptr;
	}
	hr = this->D3dApp->Device->CreateVertexShader(this->BlobVShader->GetBufferPointer(), this->BlobVShader->GetBufferSize(),
		0, &VShader);
	if(FAILED(hr))
	{
		MessageBox(this->D3dApp->GetWindow(), "Create vertex shader failed!", "Vertex shader error!", MB_ICONERROR);
		D3DRelease(this->BlobVShader);
		return nullptr;
	}

	///////////////////////////////////////
	//**Create InputLayout
	///////////////////////////////////////
	D3D11_INPUT_ELEMENT_DESC IED[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	this->D3dApp->Device->CreateInputLayout(IED, ARRAYSIZE(IED), this->BlobVShader->GetBufferPointer(),
		this->BlobVShader->GetBufferSize(), &this->InputLayout);

	this->D3dApp->DeviceContext->IASetInputLayout(this->InputLayout);

	return VShader;

}

ID3D11PixelShader* ShaderManager::CreatePixelShader(LPCSTR fileName, LPCSTR func)
{

	ID3DBlob* BlobPShader = 0;
	ID3DBlob* compilationMessage = 0;

	ID3D11PixelShader* PShader;

	std::string SMString;

	if (this->ShaderModel == SHADER_MODEL_4_0)
		SMString = "ps_4_0";
	else if (this->ShaderModel == SHADER_MODEL_4_1)
		SMString = "ps_4_1";
	else if (this->ShaderModel == SHADER_MODEL_5_0)
		SMString = "ps_5_0";
	else
		return false;

	HRESULT hr = D3DX11CompileFromFile(fileName, 0, 0, func, SMString.c_str(), this->ShaderFlags, 0, 0, &BlobPShader, &compilationMessage, 0);
	if (compilationMessage != 0)
	{
		MessageBox(this->D3dApp->GetWindow(), "Compilation shader warning (PS)", fileName, MB_ICONWARNING);
	}
	if (FAILED(hr))
	{
		MessageBox(this->D3dApp->GetWindow(), "Pixel shader load failed!", fileName, MB_ICONERROR);
		D3DRelease(BlobPShader);
		return false;
	}
	hr = this->D3dApp->Device->CreatePixelShader(BlobPShader->GetBufferPointer(), BlobPShader->GetBufferSize(),
		0, &PShader);
	if (FAILED(hr))
	{
		MessageBox(this->D3dApp->GetWindow(), "Create pixel shader failed!", fileName, MB_ICONERROR);
		D3DRelease(BlobPShader);
		return false;
	}

	return PShader;

}

void ShaderManager::InitAllShaders()
{

	FileManager* FManager;

	std::vector<std::string> Files = FileHelp::FindFiles(std::string(this->D3dApp->GetCatalogName() + "\\*PS.fx"));

	for (int i = 0; i < Files.size(); i++)
	{

		Shader* NShader = new Shader();

		NShader->Name = Files.at(i).substr(0,Files.at(i).size() - 3);
		NShader->PPixelShader = this->CreatePixelShader(Files.at(i).c_str(), "PSMain");

		this->Shaders.push_back(NShader);

	}

}

void ShaderManager::DeleteAllShaders()
{

	for (int i = 0; i < this->Shaders.size(); i++)
	{

		D3DRelease(this->Shaders.at(i)->PPixelShader);
		D3DDelete(this->Shaders.at(i));

	}

}

ID3D11PixelShader* ShaderManager::GetPixelShader(std::string& shaderName)
{

	for (int i = 0; i < this->Shaders.size(); i++)
	{

		if (!this->Shaders.at(i)->Name.compare(shaderName.c_str()))
		{
			return this->Shaders.at(i)->PPixelShader;
		}

	}

	return nullptr;

}

void ShaderManager::Render(short indexOfVP, XMFLOAT4& color, Vector2d& pos, float rotation, Vector2d& size, Material* pMaterial,
	XMFLOAT4& userVars, XMFLOAT4& aColor)
{

	PrepareShader(pMaterial, this);

	this->PStrides = sizeof(ShaderManager::Vertex2d);
	this->POffSet = 0;
	this->D3dApp->DeviceContext->IASetVertexBuffers(0, 1, &this->VertexBuffer, &PStrides, &POffSet);
	this->D3dApp->DeviceContext->IASetIndexBuffer(this->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	this->D3dApp->DeviceContext->RSSetState(this->D3dApp->GetStandartRastState());
	this->D3dApp->DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (this->IndexOfVP < 0 || this->IndexOfVP != indexOfVP)
	{
		this->D3dApp->SetViewPort(indexOfVP);
		this->IndexOfVP = indexOfVP;
	}

	D3DXMatrixIdentity(&this->WorldMatrix);
	D3DXMatrixTranslation(&this->WorldMatrix, pos.X, pos.Y, 0);
	D3DXMatrixScaling(&this->ScaleMatrix, size.X, size.Y, 1);

	if (rotation)
	{
		D3DXMatrixRotationZ(&this->RotateMatrix, rotation);
		D3DXMatrixMultiply(&this->WorldMatrix, &this->RotateMatrix, &this->WorldMatrix);
	}

	D3DXMatrixMultiply(&this->WorldMatrix, &this->ScaleMatrix, &this->WorldMatrix);

	D3DXMatrixTranspose(&this->WorldMatrix, &this->WorldMatrix);

	this->VSInput.ProjMatrix = this->D3dApp->GetVPMatrix(this->IndexOfVP);
	this->VSInput.WorldMatrix = this->WorldMatrix;
	this->VSInput.Color = color;
	this->VSInput.AColor = aColor;
	this->VSInput.UseGlobalCoords = (UINT)pMaterial->UseGlobalCoords;
	this->VSInput.TextureOffset = pMaterial->TextureOffset;
	this->VSInput.Scale = pMaterial->Scale;

	this->SetVShader(nullptr);
	this->D3dApp->DeviceContext->UpdateSubresource(this->CBVSInput, 0, 0, &this->VSInput, 0, 0);
	this->D3dApp->DeviceContext->VSSetConstantBuffers(0, 1, &this->CBVSInput);

	this->PSInput.DeltaTime = this->D3dApp->GetTimer()->GetDeltaTime();
	this->PSInput.Time = this->D3dApp->GetTimer()->GetTotalTime();
	this->PSInput.UseAlpha = (UINT)pMaterial->UseAlpha;
	this->PSInput.UserVars = userVars;

	this->SetPShader(pMaterial->EffectShader);
	this->D3dApp->DeviceContext->UpdateSubresource(this->CBPSInput, 0, 0, &this->PSInput, 0, 0);
	this->D3dApp->DeviceContext->PSSetConstantBuffers(0, 1, &this->CBPSInput);
	if (this->IsAdvanceRender)
		this->D3dApp->DeviceContext->PSSetSamplers(0, 1, &this->AdvanceSampler);
	else 
		this->D3dApp->DeviceContext->PSSetSamplers(0, 1, &this->SimpleSampler);
	this->D3dApp->DeviceContext->PSSetShaderResources(0, 1, &pMaterial->Texture);
	this->D3dApp->DeviceContext->PSSetShaderResources(1, 1, &pMaterial->AdditionalTexture);

}

void ShaderManager::SetVShader(ID3D11VertexShader* vShader)
{

	if (vShader)
		this->D3dApp->DeviceContext->VSSetShader(vShader, 0, 0);
	else if (this->StandartVShader)
		this->D3dApp->DeviceContext->VSSetShader(this->StandartVShader, 0, 0);

}

void ShaderManager::SetPShader(ID3D11PixelShader* pShader)
{

	if (pShader)
		this->D3dApp->DeviceContext->PSSetShader(pShader, 0, 0);
	else if (this->StandartPShader)
		this->D3dApp->DeviceContext->PSSetShader(this->StandartPShader, 0, 0);

}

ID3D10Blob* ShaderManager::GetBlobVShader()
{

	if (this->BlobVShader)
		return this->BlobVShader;
	return nullptr;

}
