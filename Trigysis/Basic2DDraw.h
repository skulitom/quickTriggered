#ifndef BASIC_2D_DRAW_H
#define BASIC_2D_DRAW_H

#include "D3DAPP.h"
#include "Vector2d.h"
#include "Basic2DDrawPipeline.h"

class Basic2DDraw
{
public:
	Basic2DDraw(D3DAPP* d3dApp);
	~Basic2DDraw() { D3DDelete(this->Shader); }
	void DrawLine(Vector2d& pos1, Vector2d& pos2, XMFLOAT4& color, short indexOfVP = 0);
	void DrawTriangle(Vector2d& pos1, Vector2d& pos2, Vector2d& pos3, short indexOfVP, XMFLOAT4 color = XMFLOAT4(0, 0, 0, 1));
	void DrawRectangle(Vector2d& pos, Vector2d& sizes, short indexOfVP,
		XMFLOAT4 color = XMFLOAT4(0, 0, 0, 1),ID3D11ShaderResourceView* pTexture = nullptr, std::string& textureName = std::string(""));
	void DrawCircle(Vector2d& pos, FLOAT radius, XMFLOAT4& color, short indexOfVP = 0);
private:
	Basic2DDrawPipeline* Shader;
	D3DAPP* D3dApp;
	Basic2DDrawPipeline::Vertex2d Vertices[3];
};
#endif //BASIC_2D_DRAW_H