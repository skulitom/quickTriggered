#ifndef RENDER_SHADER_H
#define RENDER_SHADER_H

#include "D3DAPP.h"
//#include "Element.h"

struct WorldMatrixCBufferStruct
{

	D3DXMATRIX ViewMatrix;
	D3DXMATRIX ProjMatrix;
	D3DXMATRIX WorldMatrix;
	XMFLOAT4 Color;

};

struct PerFrameCBufferStruct
{

	Vector2d BrushPos;

};

class RenderShader
{

public:

	RenderShader(D3DAPP* d3dApp);
	~RenderShader();

public:

	bool CreateVertexShader(LPCSTR fileName, LPCSTR func);
	bool CreatePixelShader(LPCSTR fileName, LPCSTR func);

	void SetVShader();
	void SetPShader();

	//void UpdatePerMeshInputs(void* elementToRender, XMFLOAT2& windowMouseVPCoord, FLOAT totalTime);
	void UpdateStandartInputs();

	ID3D10Blob* GetBlobVShader();
	
public:
	D3DXMATRIX WorldMatrix;
	D3DXMATRIX ScaleMatrix;
	D3DXMATRIX ProjectMatrix;
	D3DXMATRIX ViewMatrix;

	
	ID3D11Buffer* WorldMatrixCBuffer; //<-Ch
	WorldMatrixCBufferStruct SWMCBuffer;

	ID3D11Buffer* PerFrameCBuffer; //<-Ch
	PerFrameCBufferStruct SPFBuffer;

	ID3D11ShaderResourceView* RenderBufferResource; //<-Ch

private:

	D3DAPP* D3dApp;

	ID3DBlob* BlobVShader; //<-Ch
	ID3D11VertexShader* VertexShader; //<-Ch

	ID3D11PixelShader* PixelShader; //<-Ch

	DWORD ShaderFlags; //<-Ch

	ID3D11Texture2D* ResourceTexture; //<-Ch

	ID3D11SamplerState* Sampler; //<-Ch

};

#endif //RENDER_SHADER_H