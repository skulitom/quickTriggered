#ifndef BASIC_2D_DRAW_PIPELINE_H
#define BASIC_2D_DRAW_PIPELINE_H

#include "Shader.h"

struct B2DWVPCBufferStruct
{
	D3DXMATRIX ViewMatrix;
	D3DXMATRIX ProjMatrix;
	D3DXMATRIX WorldMatrix;
};
class Basic2DDrawPipeline : public Shader
{
public:
	Basic2DDrawPipeline(D3DAPP* d3DApp);
	~Basic2DDrawPipeline();
public:
	struct Vertex2d
	{
		Vertex2d() { Pos = Vector2d(); Color = XMFLOAT4(); TexturePos = Vector2d(); }
		Vector2d Pos;
		XMFLOAT4 Color;
		Vector2d TexturePos;
	};
	virtual bool CreateVertexShader(LPCSTR fileName, LPCSTR func) override;
	virtual bool CreatePixelShader(LPCSTR fileName, LPCSTR func) override;
	void SetVertexBuffer(ID3D11Buffer* vBuffer) { this->VertexBuffer = vBuffer; }
	ID3D11Buffer* GetVertexBuffer() { return this->VertexBuffer; }
	void Apply(short indexOfVP);
	void SetShaderResourceView(ID3D11ShaderResourceView* pSRV) { this->RenderBufferResource = pSRV; }
public:
	D3DXMATRIX WorldMatrix;
	D3DXMATRIX ScaleMatrix;
	D3DXMATRIX ProjectMatrix;
	D3DXMATRIX ViewMatrix;
	ID3D11Buffer* WorldMatrixCBuffer; //<-Ch
	B2DWVPCBufferStruct SWMCBuffer;
private:
	ID3D11Texture2D* ResourceTexture; //<-Ch
	ID3D11SamplerState* Sampler; //<-Ch
	ID3D11InputLayout* InputLayout; //<-Ch
	ID3D11ShaderResourceView* RenderBufferResource; //<-Ch
	Basic2DDrawPipeline::Vertex2d Vertices[3];
};
#endif //BASIC_2D_DRAW_PIPELINE_H