#include "FigureB.h"


FigureB::FigureB(BasicInterface* super, int type)
	: Element(super)
{
		
		this->type = type;
		this->fig = new Figure(super);
		this->fig->SetFigureType(0);
		this->fig->SetFigureSuperType(0);
		this->toBreak = false;
		this->IsMoving = false;
		this->frozen = false;
		this->originalPos = getPositionB();
		this->lastPos = getPositionB();
		this->newPos = getPositionB();

}

bool FigureB::Update()
{
	if (!Element::Update())
	{
		return false;
	}
	// check if figure is pressed in which case move the figure with cursor
	if (this->fig->GetButton()->GetStatus(DX_BUTTON_STATUS_IS_PRESSING) && !this->frozen)
		 {
		if (!IsMoving)
			{
				this->Input->GetMousePosCenterVPort(this->Super->GetVPStruct(1), &this->PrevMPos);
				this->originalPos = getPositionB();
				IsMoving = true;
			}
		else
			 PrevMPos = MPos;
		
	   		this->Input->GetMousePosCenterVPort(this->Super->GetVPStruct(1), &this->MPos);
			this->newPos = this->fig->GetPosition() + MPos - PrevMPos;
			if ((this->originalPos.X + DISTANCE_DELTA > this->newPos.X && this->originalPos.X - DISTANCE_DELTA < this->newPos.X) || (this->originalPos.Y + DISTANCE_DELTA > this->newPos.Y && this->originalPos.Y - DISTANCE_DELTA < this->newPos.Y))
			{
				this->fig->SetPosition(this->newPos);
			}

		}
	else
	{
		IsMoving = false;
	}

	return true;
}

//this->Super->GetFont2D()->DrawA(Vector2d(100, 60), COLOR_RED_3, 1, "%f", MPos.X - PrevMPos.X);

void FigureB::Spawn(Vector2d& pos, short indexOfVP)
{
	Element::Spawn(pos, indexOfVP);
	this->fig->SetFigureSuperType(0);
	this->fig->SetFigureType(0);	
	this->fig->SetColors(colorPicker());
	this->fig->Spawn(pos, this->IndexOfViewPort);
}

void FigureB::FallToPos(Vector2d& pos)
{
	this->fig->FallToPos(getPositionB(), pos);

}

Vector2d FigureB::getPositionB()
{
	Vector2d pos = this->fig->GetPosition();
	return pos;
}

XMFLOAT4 FigureB::colorPicker()
{
	// assigns colors to figure types
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