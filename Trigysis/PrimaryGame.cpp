#include "PrimaryGame.h"

PrimaryGame::PrimaryGame()
{
	this->grid = new Grid();
	this->turns = new Turns(SD_MAX_TURNS, SD_MAX_TIME);
}

void PrimaryGame::init(BasicInterface* super)
{
	this->grid->setBoard(super);
	this->turns->resetClock();

}

void PrimaryGame::Update(BasicInterface* super)
{
	this->grid->Update(super);
	this->turns->Update();
}

void PrimaryGame::setBoard(BasicInterface* super)
{
	this->grid = new Grid();
	this->grid->setBoard(super);
	// start turns with standard time and num of turns
//	this->turns = new Turns(SD_MAX_TURNS, SD_MAX_TIME);
}

PrimaryGame::~PrimaryGame()
{
	D3DDelete(grid);
	D3DDelete(turns);
}