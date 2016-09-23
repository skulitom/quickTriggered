#include "Entities.h"

Entities::Entities(BasicInterface* super)
{
	this->borders = new std::vector < GUIBorder* > ;
	this->super = super;
	this->spawned = false;
}

/**
	1.   Starting Position: F.pos() + 1/2CELL_HEIGHT - 1/2CELL_WIDTH
		End Position:StartingPoint where StartingPoint.Y=BORD_HEIGHT
	2.   Starting Position:  F.pos() + 1/2CELL_HEIGHT + 1/2CELL_WIDTH
		End Position:  StartingPoint where StartingPoint.Y=BORD_HEIGHT
	3.   Starting Position: F.pos() + 1/2CELL_HEIGHT + 1/2CELL_WIDTH
		End Position: StartingPoint where StartingPoint.X=BORD_WIDTH
	4.   Starting Position: F.pos() - 1/2CELL_HEIGHT + 1/2CELL_WIDTH
		End Position:StartingPoint where StartingPoint.X=BORD_WIDTH
	5.   Starting Position: F.pos() - 1/2CELL_HEIGHT + 1/2CELL_WIDTH
		End Position:StartingPoint where StartingPoint.Y=-BORD_HEIGHT
	6.   Starting Position: F.pos() - 1/2CELL_HEIGHT - 1/2CELL_WIDTH
		End Position:StartingPoint where StartingPoint.Y=-BORD_HEIGHT
	7.   Starting Position: F.pos() - 1/2CELL_HEIGHT - 1/2CELL_WIDTH
		End Position: StartingPoint where StartingPoint.X=-BORD_WIDTH
	8.   Starting Position: F.pos() + 1/2CELL_HEIGHT - 1/2CELL_WIDTH
		End Position: StartingPoint where StartingPoint.X=-BORD_WIDTH
*/

void Entities::spawnBordersAt(Vector2d pos, short indexOfVP)
{
	for (int i = 0; i < 8; i++)
	{
		this->border = new GUIBorder(super);
		this->borders->push_back(this->border);
	}
	this->borders->at(0)->Spawn(pos + Vector2d(-0.5*(CELL_WIDTH), 0.5*(CELL_WIDTH)), Vector2d(pos.X - 0.5*(CELL_WIDTH), SIZE), BORDER_WIDTH, BORDER_COLOR, indexOfVP);
	this->borders->at(1)->Spawn(pos + Vector2d(0.5*(CELL_WIDTH), 0.5*(CELL_WIDTH)), Vector2d(pos.X + 0.5*(CELL_WIDTH), SIZE), BORDER_WIDTH, BORDER_COLOR, indexOfVP);
	this->borders->at(2)->Spawn(pos + Vector2d(0.5*(CELL_WIDTH), 0.5*(CELL_WIDTH)), Vector2d(SIZE, pos.Y + 0.5*(CELL_WIDTH)), BORDER_WIDTH, BORDER_COLOR, indexOfVP);
	this->borders->at(3)->Spawn(pos + Vector2d(0.5*(CELL_WIDTH), -0.5*(CELL_WIDTH)), Vector2d(SIZE, pos.Y - 0.5*(CELL_WIDTH)), BORDER_WIDTH, BORDER_COLOR, indexOfVP);
	this->borders->at(4)->Spawn(Vector2d(pos.X + 0.5*(CELL_WIDTH), -SIZE), pos + Vector2d(0.5*(CELL_WIDTH), -0.5*(CELL_WIDTH)), BORDER_WIDTH, BORDER_COLOR, indexOfVP);
	this->borders->at(5)->Spawn(Vector2d(pos.X - 0.5*(CELL_WIDTH), -SIZE), pos + Vector2d(-0.5*(CELL_WIDTH), -0.5*(CELL_WIDTH)), BORDER_WIDTH, BORDER_COLOR, indexOfVP);
	this->borders->at(6)->Spawn(Vector2d(-SIZE, pos.Y - 0.5*(CELL_WIDTH)), pos + Vector2d(-0.5*(CELL_WIDTH), -0.5*(CELL_WIDTH)), BORDER_WIDTH, BORDER_COLOR, indexOfVP);
	this->borders->at(7)->Spawn(Vector2d(-SIZE, pos.Y + 0.5*(CELL_WIDTH)), pos + Vector2d(-0.5*(CELL_WIDTH), 0.5*(CELL_WIDTH)), BORDER_WIDTH, BORDER_COLOR, indexOfVP);
	this->spawned = true;
}

void Entities::destroyBorders()
{
	for (int i = 0; i < 8; i++)
	{
		ElementDelete(this->borders->at(i));
		
	}
	this->borders->clear();
	this->borders->shrink_to_fit();
	this->spawned = false;

}

Entities::~Entities()
{
	D3DDelete(borders);
}