//#include "TestPipeline.h"
//#include "MathHelper.h"
//
//TestPipeline::TestPipeline(D3DAPP* d3dApp, char shaderModel)
//	:Basic2DDrawPipeline(d3dApp, shaderModel)
//{
//
//	this->RandomVCBuffer = this->D3dApp->CreateSConstantBuffer(16);
//
//	Shader::CreatePixelShader("TPPShader.fx", "PSNoise");
//
//	//D3D11_SAMPLER_DESC SD;
//	//ZeroMemory(&SD, sizeof(D3D11_SAMPLER_DESC));
//	//SD.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
//	//SD.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
//	//SD.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
//	//SD.Filter = D3D11_FILTER_COMPARISON_ANISOTROPIC;
//	//SD.MaxAnisotropy = 1;
//	//HRESULT hr = this->D3dApp->dxDevice->CreateSamplerState(&SD, &this->Sampler);
//
//}
//
//TestPipeline::~TestPipeline()
//{
//
//
//
//}
//
//void TestPipeline::Apply(ID3D11ShaderResourceView* textureView, short indexOfVP, XMFLOAT4& color, Vector2d& pos, Vector2d& size)
//{
//
//	this->SetPShader();
//
//	this->D3dApp->dxDeviceCon->PSSetShaderResources(0, 1, &textureView);
//
//	this->SRVCBuffer.RValue = RAND(0.f, 1.f);
//
//	this->D3dApp->dxDeviceCon->UpdateSubresource(this->RandomVCBuffer, 0, 0, &this->SRVCBuffer, 0, 0);
//	this->D3dApp->dxDeviceCon->PSSetConstantBuffers(0, 1, &this->RandomVCBuffer);
//
//	Basic2DDrawPipeline::Apply(indexOfVP, color, pos, size);
//
//}
