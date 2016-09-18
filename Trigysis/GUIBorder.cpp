#include "GUIBorder.h"

GUIBorder::GUIBorder(BasicInterface* super)
	:Element(super)
{

	this->SetMaterial(std::string("Border"));
	this->SetBlendState(DX_BS_TRANSPARENCY);

}

GUIBorder::~GUIBorder()
{



}

void GUIBorder::Spawn(Vector2d& startPos, Vector2d& endPos, __int16 width, XMFLOAT3& color, short indexOfVP)
{

	this->Color = XMFLOAT4(color.x, color.y, color.z, 1);

	if (startPos.X == endPos.X)
	{
		this->Sizes = Vector2d(width, abs(startPos.Y - endPos.Y));
		Element::Spawn(Vector2d(startPos.X, abs(startPos.Y - endPos.Y)*0.5f + startPos.Y), indexOfVP);

		if (startPos.Y == endPos.Y)
			this->Rotation = D3DXToRadian(90);
	}
	else if (startPos.Y == endPos.Y)
	{
		this->Sizes = Vector2d(width, abs(startPos.X - endPos.X));
		Element::Spawn(Vector2d(abs(startPos.X - endPos.X)*0.5f + startPos.X, startPos.Y), indexOfVP);
		this->Rotation = D3DXToRadian(90);
	}
}

bool GUIBorder::Update()
{

	if (!Element::Update())
		return false;

	return true;

}
