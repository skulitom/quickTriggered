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
		this->crypt = new Crypter();

}

bool FigureB::Update()
{
	if (!Element::Update())
	{
		return false;
	}
	//this->fig->SetPosition(this->Position);
	if (this->fig->GetButton()->GetStatus(DX_BUTTON_STATUS_IS_PRESSING))
		 {
		if (!IsMoving)
			{
				this->Input->GetMousePosCenterVPort(this->Super->GetVPStruct(1), &this->PrevMPos);
				IsMoving = true;
			}
		else
			 PrevMPos = MPos;
		
			this->Input->GetMousePosCenterVPort(this->Super->GetVPStruct(1), &this->MPos);
			this->fig->SetPosition( this->fig->GetPosition()+ MPos-PrevMPos );
			this->Super->GetFont2D()->DrawA(Vector2d(100,100),COLOR_RED_3,1,"%s",crypt->openFile());
			this->Super->GetFont2D()->DrawA(Vector2d(100, 80), COLOR_RED_3, 1, "%f", MPos.X);
			this->Super->GetFont2D()->DrawA(Vector2d(100, 60), COLOR_RED_3, 1, "%f", MPos.X - PrevMPos.X);

		}
	else
		 IsMoving = false;

	return true;
}

//this->Super->GetFont2D()->DrawA(Vector2d(100, 60), COLOR_RED_3, 1, "%f", MPos.X - PrevMPos.X);

void FigureB::Spawn(Vector2d& pos, short indexOfVP)
{
	Element::Spawn(pos, indexOfVP);
	this->fig->SetFigureSuperType(0);
	this->fig->SetFigureType(0);
	
	this->fig->SetColors(colorPicker());
	this->fig->Spawn(pos, 1);
}

void FigureB::FallToPos(Vector2d& pos)
{
	this->fig->FallToPos(getPositionB(), pos);

}

//Думаю, нужно поменять название 
//Небольшой конфликт имён с GetPosition()
Vector2d FigureB::getPositionB()
{
	Vector2d pos = this->fig->GetPosition();
	return pos;
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