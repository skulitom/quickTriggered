#ifndef RENDER_RECT_H
#define RENDER_RECT_H

#include "Vector2d.h"
#include <vector>

struct Vertex
{

	Vertex(Vector2d& pos) { this->Position = pos; };
	Vector2d Position;
	Vector2d TexCoord;

};

struct RenderRectDesc
{

	Vector2d Position;
	Vector2d Sizes;

	XMFLOAT4 Color;

};

class RenderRect
{

public: 
	RenderRect();

	void ApplySettings(RenderRectDesc& settings);

	std::vector<Vertex>& GetVertices();
	std::vector<UINT>& GetIndices();
	
private:

	void BuildGeometry();

private:

	std::vector<Vertex> Vertices;
	std::vector<UINT> Indices;

	RenderRectDesc Properties;
	
};

#endif //RENDER_RECT_H