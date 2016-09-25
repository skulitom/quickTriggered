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
	this->localTime = 0;
}

void PrimaryGame::init()
{
	this->grid->setBoard(this->super);

}

void PrimaryGame::Update()
{
	if (!this->turns->isEndTurn())
		this->turns->Update();
	this->grid->Update(this->super);

	if (!turns->isEndGame())
	{
		continueGame();
	}
	else
	{
		this->grid->freezFigures(true);
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

void PrimaryGame::continueGame()
{
	if (this->grid->getToBreak())
	{
		this->grid->setToBreak(false);
		this->grid->clearBreaks();
		this->grid->checkBreaks();
		if (this->grid->getMovingFigBreak())
		{
			this->grid->setEndTurn(true);
			this->grid->Update(super);
			this->grid->updateOriginalPos();
		}
		else
		{
			
			this->grid->moveBackAll();
			
			
		}
	}
	if (this->grid->getEndTurn())
	{
		this->turns->endTurn();
		this->grid->setEndTurn(false);
	}
	if (turns->isEndTurn())
	{
		this->grid->freezFigures(true);
		if (!this->grid->checkBreaks())
		{
			this->grid->freezFigures(false);
			this->turns->Update();
			localTime = 0;
		}
	}
	else{
		super->GetFont2D()->DrawA(Vector2d(100, -220), COLOR_BLACK_3, 1, "%s: %d", "Turn", this->turns->getTurn());
		super->GetFont2D()->DrawA(Vector2d(100, -250), COLOR_BLACK_3, 1, "%s: %d", "Time", this->turns->getTime());
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