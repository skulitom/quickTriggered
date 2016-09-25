#include "PrimaryGame.h"

/*
	This class is resposible for the core gameplay of the game
	such as:
		|Turn managment
		|FigureManager usage
		|Board configuration
		|In-primary game text
*/

PrimaryGame::PrimaryGame(BasicInterface* super)
{
	this->super = super;
	this->grid = new Grid(super, 2);
	this->turns = new Turns(SD_MAX_TURNS, SD_MAX_TIME);
	this->gameWon = false;
}

void PrimaryGame::init()
{
	this->grid->setBoard(this->super);

}

void PrimaryGame::Update()
{
	if (!turns->isEndGame())
	{
		if (this->grid->getEndTurn())
		{
			this->turns->endTurn();
			this->grid->setEndTurn(false);
		}
		if (turns->isEndTurn())
		{
			this->grid->Update(this->super);
			localTime = localTime + this->super->GetTimer()->GetDeltaTime();
			super->GetFont2D()->Draw(Vector2d(-150, 0), COLOR_BLACK_3, 3, "Turn Ended");
			if (localTime > 2)
			{
				localTime = 0;
				this->turns->Update();
			}
		}
		else{
			this->grid->Update(this->super);
			this->turns->Update();
			super->GetFont2D()->DrawA(Vector2d(280, -220), COLOR_BLACK_3, 1, "%s: %d", "Turn", this->turns->getTurn());
			super->GetFont2D()->DrawA(Vector2d(280, -250), COLOR_BLACK_3, 1, "%s: %d", "Time", this->turns->getTime());
		}
	}
	else
	{
		if (gameWon)
		{
			super->GetFont2D()->Draw(Vector2d(-150, 0), COLOR_BLACK_3, 3, "Success");
		}
		else
		{
			super->GetFont2D()->Draw(Vector2d(-150, 0), COLOR_BLACK_3, 3, "Game Over");
		}
	}
}

void PrimaryGame::setBoard()
{
	this->grid = new Grid( this->super, INDEX_OF_VP);
	this->grid->setBoard(this->super);
	// start turns with standard time and num of turns
//	this->turns = new Turns(SD_MAX_TURNS, SD_MAX_TIME);
}

PrimaryGame::~PrimaryGame()
{
	D3DDelete(grid);
	D3DDelete(turns);
}