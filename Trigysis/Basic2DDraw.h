#ifndef BASIC_2D_DRAW_H
#define BASIC_2D_DRAW_H

#include "D3DAPP.h"
#include "Vector2d.h"
#include "ShaderManager.h"

#define BASIC_2DDRAWP_RECTANGLE_I_START 0
#define BASIC_2DDRAWP_RECTANGLE_I_NUM 6

#define BASIC_2DDRAWP_HEXAGON_I_START 6
#define BASIC_2DDRAWP_HEXAGON_I_NUM 12

class Basic2DDraw
{
public:
	Basic2DDraw(D3DAPP* d3dApp);
	~Basic2DDraw() { D3DDelete(this->Shader); }
	void DrawLine(Vector2d& pos1, Vector2d& pos2, XMFLOAT4& color, short indexOfVP = 0);
	void DrawTriangle(Vector2d& pos1, Vector2d& pos2, Vector2d& pos3,
		Vector2d& tPos1, Vector2d& tPos2, Vector2d& tPos3, short indexOfVP, XMFLOAT4& color = XMFLOAT4(0, 0, 0, 1));
	void DrawRectangle(Vector2d& pos, float rotation, Vector2d& sizes, short indexOfVP, XMFLOAT4& userVars,
		XMFLOAT4& color = XMFLOAT4(0, 0, 0, 1), Material* pMaterial = nullptr, XMFLOAT4& aColor = XMFLOAT4(0, 0, 0, 0));
	void DrawCircle(Vector2d& pos, FLOAT radius, XMFLOAT4& color, short indexOfVP = 0);
	void DrawHexagon(Vector2d& pos, Vector2d& sizes, short indexOfVP, XMFLOAT4& userVars,
		XMFLOAT4& color = XMFLOAT4(0, 0, 0, 1), Material* pMaterial = nullptr, XMFLOAT4& aColor = XMFLOAT4(0, 0, 0, 0));

	ShaderManager* GetShaderManager() { return this->Shader; }

	void UpdateMaterial(Material* pMaterial);

private:
	XMFLOAT4X4 PMatrix;
	ShaderManager* Shader;
	D3DAPP* D3dApp;
	ShaderManager::Vertex2d Vertices[3];
};
#endif //BASIC_2D_DRAW_H
