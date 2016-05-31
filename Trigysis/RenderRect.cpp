#include "RenderRect.h"

RenderRect::RenderRect()
{

	

}

void RenderRect::ApplySettings(RenderRectDesc& settings)
{

	ZeroMemory(&this->Properties, sizeof(RenderRectDesc));

	this->Properties = settings;

	this->BuildGeometry();

}

void RenderRect::BuildGeometry()
{

	this->Vertices.clear();
	this->Indices.clear();

	this->Indices.push_back(0);
	this->Vertices.push_back(Vertex(Vector2d(this->Properties.Position.X - this->Properties.Sizes.X * 0.5,
		this->Properties.Position.Y - this->Properties.Sizes.Y * 0.5 )));

	this->Indices.push_back(1);
	this->Vertices.push_back(Vertex(Vector2d(this->Properties.Position.X + this->Properties.Sizes.X * 0.5,
		this->Properties.Position.Y - this->Properties.Sizes.Y * 0.5)));

	this->Indices.push_back(2);
	this->Vertices.push_back(Vertex(Vector2d(this->Properties.Position.X - this->Properties.Sizes.X * 0.5,
		this->Properties.Position.Y + this->Properties.Sizes.Y * 0.5)));

	this->Indices.push_back(2);
	this->Indices.push_back(1);

	this->Indices.push_back(3);
	this->Vertices.push_back(Vertex(Vector2d(this->Properties.Position.X + this->Properties.Sizes.X * 0.5,
		this->Properties.Position.Y + this->Properties.Sizes.Y * 0.5)));


	/////////////////////////////////////
	//**TexCoords
	/////////////////////////////////////
	this->Vertices.at(0).TexCoord.X = 0;
	this->Vertices.at(0).TexCoord.Y = 0;

	this->Vertices.at(1).TexCoord.X = 1;
	this->Vertices.at(1).TexCoord.Y = 0;

	this->Vertices.at(2).TexCoord.X = 0;
	this->Vertices.at(2).TexCoord.Y = 1;

	this->Vertices.at(3).TexCoord.X = 1;
	this->Vertices.at(3).TexCoord.Y = 1;

}

std::vector<Vertex>& RenderRect::GetVertices()
{

	return this->Vertices;

}

std::vector<UINT>& RenderRect::GetIndices()
{

	return this->Indices;

}