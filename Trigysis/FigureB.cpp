#include "FigureB.h"


FigureB::FigureB(BasicInterface* super, int type)
	: Element(super)
{
		
		this->type = type;
		fig = new Figure(super);
		this->toBreak = false;

}

bool FigureB::Update()
{
	if (!Element::Update())
	{
		return false;
	}
	this->fig->SetPosition(this->Position);
	return true;
}

void FigureB::Spawn(Vector2d& pos, short indexOfVP)
{
	Element::Spawn(pos, indexOfVP);
	this->fig->SetFigureSuperType(0);
	this->fig->SetFigureType(0);
	
	this->fig->SetColors(colorPicker());
	this->fig->Spawn(pos, 1);

}

XMFLOAT4 FigureB::colorPicker()
{
	switch(this->type)
	{
	case MEXICANS:
		return XMFLOAT4(0, 0, 1, 0);
	case JEWS:
		return XMFLOAT4(0, 1, 1, 0);
	case WOMEN:
		return XMFLOAT4(0, 1, 0, 0);
	case BLACK:
		return XMFLOAT4(0,0,0,0);
	case ASIAN:
		return XMFLOAT4(1, 0, 0, 0);
	case WHITE_SUPREME:
		return XMFLOAT4(1, 1, 1, 0);
	default:
		return XMFLOAT4(1, 1, 0, 0);

	}
}

FigureB::~FigureB()
{
	ElementDelete(fig);
}