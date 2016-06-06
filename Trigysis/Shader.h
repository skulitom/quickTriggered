#ifndef SHADER_H
#define SHADER_H

#include "D3DAPP.h"

class Shader
{

public:

	Shader(D3DAPP* d3dApp);
	~Shader();

	virtual bool CreateVertexShader(LPCSTR fileName, LPCSTR func);
	virtual bool CreatePixelShader(LPCSTR fileName, LPCSTR func);
	virtual void SetVShader();
	virtual void SetPShader();
	ID3D10Blob* GetBlobVShader();

private:

protected:

	D3DAPP* D3dApp;
	ID3D11Buffer* VertexBuffer; //<-Ch
	ID3DBlob* BlobVShader; //<-Ch
	ID3D11VertexShader* VertexShader; //<-Ch
	ID3D11PixelShader* PixelShader; //<-Ch

	DWORD ShaderFlags; //<-Ch
};

#endif // !SHADER_H
