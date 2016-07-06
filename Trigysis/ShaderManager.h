#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#define SHADER_MODEL_4_0 0
#define SHADER_MODEL_4_1 1
#define SHADER_MODEL_5_0 2

#include "D3DAPP.h"

struct CBUserVars
{

	CBUserVars() {
		Val0 = 0;
		Val1 = 0;
		Val2 = 0;
		Val3 = 0;
	}

	float Val0;
	float Val1;
	float Val2;
	float Val3;

};

struct CBSPSInput
{

	float Time;
	float DeltaTime;
	unsigned int UseAlpha;
	float Pad;
	XMFLOAT4 UserVars;
};

struct CBSVSInput
{
	D3DXMATRIX ViewMatrix;
	D3DXMATRIX ProjMatrix;
	D3DXMATRIX WorldMatrix;
	XMFLOAT4 TextureOffset;
	XMFLOAT4 Color;
	XMFLOAT4 AColor;
	XMFLOAT2 Scale;
	unsigned int UseGlobalCoords;
	unsigned int Pad;
};

struct Shader
{

	std::string Name;
	ID3D11PixelShader* PPixelShader;

};

class ShaderManager
{

public:

	ShaderManager(D3DAPP* d3dApp, char shaderModel);
	~ShaderManager();

	virtual ID3D11VertexShader* CreateVertexShader(LPCSTR fileName, LPCSTR func);
	virtual ID3D11PixelShader* CreatePixelShader(LPCSTR fileName, LPCSTR func);
	virtual void SetVShader(ID3D11VertexShader* vShader);
	virtual void SetPShader(ID3D11PixelShader* pShader);
	ID3D10Blob* GetBlobVShader();

	ID3D11PixelShader* GetPixelShader(std::string& shaderName);

	void SetIsAdvanceRender(bool isAdvanceRender) { this->IsAdvanceRender = isAdvanceRender; }

	void InitAllShaders();

	void Render(short indexOfVP, XMFLOAT4& color, Vector2d& pos, Vector2d& size, Material* pMaterial, XMFLOAT4& userVars,
		XMFLOAT4& aColor = XMFLOAT4(0,0,0,0));

public:

	struct Vertex2d
	{
		Vertex2d() { Pos = Vector2d(); TexturePos = Vector2d(); }
		Vector2d Pos;
		Vector2d TexturePos;
	};

private:

	void DeleteAllShaders();

private:

	bool IsAdvanceRender;

protected:

	D3DXMATRIX WorldMatrix;
	D3DXMATRIX ScaleMatrix;
	D3DXMATRIX ProjectMatrix;
	D3DXMATRIX ViewMatrix;

	D3DAPP* D3dApp;
	ID3D11Buffer* VertexBuffer; //<-Ch
	ID3D11Buffer* IndexBuffer; //<-Ch
	ID3DBlob* BlobVShader; //<-Ch
	ID3D11VertexShader* StandartVShader; //<-Ch
	ID3D11PixelShader* StandartPShader; //<-Ch
	ID3D11InputLayout* InputLayout; //<-Ch
	ID3D11SamplerState* SimpleSampler; //<-Ch
	ID3D11SamplerState* AdvanceSampler; //<-Ch

	ID3D11Buffer* CBPSInput;
	CBSPSInput PSInput;

	ID3D11Buffer* CBVSInput;
	CBSVSInput VSInput;

	char ShaderModel;

	DWORD ShaderFlags; //<-Ch

	std::vector<Shader*> Shaders;

	int IndexOfVP;

	UINT PStrides;
	UINT POffSet;

};

#endif // !SHADER_MANAGER_H
