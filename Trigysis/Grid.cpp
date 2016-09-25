#include "Grid.h"

// custom exception for figure type errors
struct FigureTypeException : public std::exception
{
	const char * what() const throw () {
		return "***Figure TYPE error***";
	}
};

Grid::Grid(BasicInterface* super, short indexOfVP)
{

	this->indexOfVP = indexOfVP;

	this->endTurn = false;
	this->fmanager = new FigureManager();
	this->toMove = false;
	this->enti = new Entities(super);
	this->super = super;
	// net will keep figures (basically representig the board)
	this->net = new std::vector<std::vector<FigureB*>>(((2 * BOARD_SIZE) / BOARD_INTERVAL)+1);
	for (int t = 0; t <= (2 * BOARD_SIZE) / BOARD_INTERVAL; t++)
	{
		// reserve memory for the board
		this->net->at(t).resize(((2 * BOARD_SIZE) / BOARD_INTERVAL)+1);
	}
	for (int i = 0; i <= (2 * BOARD_SIZE) / BOARD_INTERVAL; i++)
	{
		for (int j = 0; j <= (2 * BOARD_SIZE) / BOARD_INTERVAL; j++)
		{
			this->net->at(i).at(j) = nullptr;
		}
	}


}


void Grid::Update(BasicInterface* super)
{
	// first round logic is for all code that must run first
	FirstRoundLogic(super);
	// second round logic is for code that won't run correctly before completely scanning the board first time
	SecondRoundLogic(super);
}

void Grid::FirstRoundLogic(BasicInterface* super)
{
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			if (!(this->net->at(i).at(j) == nullptr))
			{
				checkBreaks();
			    // delete on right click --DEMO_ONLY-- (TODO: remove){
				if (super->GetInput()->GetStatus(DX_MOUSE_DOWN_RIGHT) && this->net->at(i).at(j)->isDragged())
				{
					deleteAt(i,j);
					this->endTurn = true;
				}
				//}
			
				if (j - 1 >= 0)
				{
					if (this->net->at(i).at(j - 1) == nullptr)
					{
						int counter = 1;
						while (this->net->at(i).at(j - counter) == nullptr)
						{
							this->net->at(i).at(j - counter) = this->net->at(i).at(j - counter + 1);
							this->net->at(i).at(j - counter + 1) = nullptr;
							counter++;
							if (counter > j)
								break;
						}
					}
				}
			}





		}
	}
}

void Grid::clearBreaks()
{
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			if (this->net->at(i).at(j) != nullptr)
				this->net->at(i).at(j)->recoverFig();
		}
	}
}

void Grid::freezFigures(bool freez)
{
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			if (this->net->at(i).at(j) != nullptr)
				this->net->at(i).at(j)->setFreez(freez);
		}
	}
}

void Grid::moveBackAll()
{
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			if (this->net->at(i).at(j) != nullptr)
			{
				this->net->at(i).at(j)->setPositionB(this->net->at(i).at(j)->getOriginalPos());
				swap(i, j, POINT_TO_LOCATION(this->net->at(i).at(j)->getOriginalPos().X), POINT_TO_LOCATION(this->net->at(i).at(j)->getOriginalPos().Y), false);
			}
		}
	}
}

void Grid::updateOriginalPos()
{
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			if (this->net->at(i).at(j) != nullptr)
			{
				this->net->at(i).at(j)->setOriginalPos(this->net->at(i).at(j)->getPositionB());
			}
		}
	}
}

bool Grid::checkBreaks()
{
	bool oneBreak = false;
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			if (this->net->at(i).at(j) != nullptr)
			{
				// scans board for at least 3 consequitive types in a row
				// first scans horizontaly and second vertically
				//horizontal
				if (j >= 2 )
					if (this->net->at(i).at(j - 1) != nullptr && this->net->at(i).at(j - 2) != nullptr)
						if (compareAt(i, j, i, j - 1) && compareAt(i, j, i, j - 2))
						{
							this->net->at(i).at(j)->breakFig();
							this->net->at(i).at(j - 1)->breakFig();
							this->net->at(i).at(j - 2)->breakFig();
							oneBreak = true;
						}
				// vertical
				if (i >= 2)
					if (this->net->at(i - 1).at(j) != nullptr && this->net->at(i - 2).at(j) != nullptr)
						if (compareAt(i, j, i - 1, j) && compareAt(i, j, i - 2, j))
						{
							this->net->at(i).at(j)->breakFig();
							this->net->at(i - 1).at(j)->breakFig();
							this->net->at(i - 2).at(j)->breakFig();
							oneBreak = true;
						}
			}
		}
	}
	return oneBreak;
}


void Grid::SecondRoundLogic(BasicInterface* super)
{
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		// throw figure from top of the board if empty slot
		if (this->net->at(i).at(GRID_FIGURE_WIDTH-1) == nullptr)
		{
			generateFig(super, LOCATION_TO_POINT(i), BOARD_SIZE);
		}
		for (int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			breakIt(i, j);
			if (this->net->at(i).at(j) != nullptr)
			{
				if (this->toMove && !this->net->at(movingFig.X).at(movingFig.Y)->getIsMoving())
				{
					this->toMove = false;
					this->toBreak = true;
					this->enti->destroyBorders();
				}
				//Vector2d pos = this->net->at(i).at(j)->getPositionB();
				// fall to updated position if not already falling
				if (!this->net->at(i).at(j)->getIsFalling() && !this->toMove)
				{
					if (this->net->at(i).at(j)->getPositionB().X != LOCATION_TO_POINT(i) || this->net->at(i).at(j)->getPositionB().Y != LOCATION_TO_POINT(j))
					{
						if (!this->net->at(i).at(j)->getIsMoving()){
							this->net->at(i).at(j)->FallToPos(Vector2d(LOCATION_TO_POINT(i), LOCATION_TO_POINT(j)));
						}
					}

				}
				if (this->net->at(i).at(j)->getIsMoving())
				{
					this->toMove = true;		
					this->movingFig.X = i;
					this->movingFig.Y = j;
					if (!this->enti->checkSpawn())
						this->enti->spawnBordersAt(Vector2d(this->net->at(i).at(j)->getOriginalPos()), this->indexOfVP);

					smartInsertAt(this->net->at(i).at(j)->getPositionB().X, this->net->at(i).at(j)->getPositionB().Y, this->net->at(i).at(j)->getLastPos());
					
				}
				
			}
		}
	}
}

void Grid::breakIt(int i, int j)
{
	// breaks all figures with break flag
	if (this->net->at(i).at(j) != nullptr && !this->net->at(i).at(j)->getIsFalling() && !this->toMove)
		if (this->net->at(i).at(j)->getToBreak())
		{
			deleteAt(i, j);
		}

}

// generates a random board such that no figures allign
void Grid::setBoard(BasicInterface* super)
{
	bool round = fmanager->getRandomBool();
	for (int i = -BOARD_SIZE; i <= BOARD_SIZE; i += BOARD_INTERVAL)
	{
		for (int j = -BOARD_SIZE; j <= BOARD_SIZE; j += BOARD_INTERVAL)
		{
			/*
				every third figure will always be different as round is alternated
				this means there will be no horizontal allignment
				since the number of figures in a horizontal axis is odd
				there will never be vertical allignment either			
			*/
			if (j%3==0)
			{
				generateFig(super, i, j, round);
				round = !round;
			}
			else
			{
				generateFig(super, i, j);
			}

		}
	}
}

// safely compares two figure types at locations (x1,y1) and (x2,y2) in net
bool Grid::compareAt(int x1, int y1, int x2, int y2)
{
	if (x1 >= GRID_FIGURE_WIDTH || x2 >= GRID_FIGURE_WIDTH || x1 < 0 || x2 < 0)
	{
		return false;
	}
	else if (y1 >= GRID_FIGURE_HEIGHT || y2 >= GRID_FIGURE_HEIGHT || y1 < 0 || y2 < 0)
	{
		return false;
	}
	else if (net->at(x1).at(y1) == nullptr || net->at(x2).at(y2)== nullptr)
	{
		return false;
	}
	if (net->at(x1).at(y1)->getType() == net->at(x2).at(y2)->getType())
	{
		return true;
	}
	return false;
}

void Grid::generateFig(BasicInterface* super, int i, int j)
{
	int drop = fmanager->FigureToDrop();
	this->fig = new FigureB(super, drop);	
	this->fig->Spawn(Vector2d(i, j), this->indexOfVP);
	this->fig->setOriginalPos(Vector2d(i, j));
	this->fig->setLastPos(Vector2d(i, j));
	insertAt(POINT_TO_LOCATION(i), POINT_TO_LOCATION(j), this->fig);
}

// overloarding previous generateFig
// allows a round to be chosen, which determines the type list that will be used
void Grid::generateFig(BasicInterface* super, int i, int j, bool round)
{
	int drop = fmanager->FigureToDrop(round);
	this->fig = new FigureB(super, drop);
	this->fig->Spawn(Vector2d(i, j), this->indexOfVP);
	this->fig->setOriginalPos(Vector2d(i, j));
	this->fig->setLastPos(Vector2d(i, j));
	insertAt(POINT_TO_LOCATION(i), POINT_TO_LOCATION(j), this->fig);
}

void Grid::insertAt(int x, int y, FigureB* fig)
{
	net->at(x).at(y) = nullptr;
	net->at(x).at(y) = fig;
}

// TODO: finish to match figure move
void Grid::smartInsertAt(int x, int y, Vector2d originalPos)
{
	x = round(x);
	y = round(y);
	//this->super->GetFont2D()->DrawA(Vector2d(0, 0), COLOR_RED_3, 2, "x and y: %d , %d", (int)movingFig.X, (int)movingFig.Y);
	if (x < -BOARD_SIZE || x > BOARD_SIZE || y < -BOARD_SIZE || y > BOARD_SIZE)
	{
		// do nothing
	}
	else if ((originalPos.X == x && originalPos.Y == y) || (originalPos.X != x && originalPos.Y != y))
	{
        //do nothing
	}
	else
	{
		swap(POINT_TO_LOCATION(originalPos.X), POINT_TO_LOCATION(originalPos.Y), POINT_TO_LOCATION(x), POINT_TO_LOCATION(y), true);
		
	}
}
int Grid::round(int x)
{
	if (x%BOARD_INTERVAL > BOARD_INTERVAL / 2 || x%BOARD_INTERVAL < -BOARD_INTERVAL / 2)
	{
		if (x%BOARD_INTERVAL<0)
		{
			x -= x%BOARD_INTERVAL;
			x -= BOARD_INTERVAL;
		}
		else
		{
			x -= x%BOARD_INTERVAL;
			x += BOARD_INTERVAL;
		}
		return x;
	}
	else
	{
		x -= x%BOARD_INTERVAL;
	}
}

void Grid::swap(int x1, int y1, int x2, int y2, bool drag)
{
	if (this->net->at(x1).at(y1) != nullptr && this->net->at(x2).at(y2) != nullptr)
	{
		FigureB* holder = this->net->at(x1).at(y1);
		this->net->at(x1).at(y1) = this->net->at(x2).at(y2);
		this->net->at(x1).at(y1)->setPositionB(Vector2d(LOCATION_TO_POINT(x1),LOCATION_TO_POINT(y1)));
		this->net->at(x2).at(y2) = holder;
	//	this->net->at(x2).at(y2)->setPositionB(Vector2d(LOCATION_TO_POINT(x2), LOCATION_TO_POINT(y2)));
		this->net->at(x2).at(y2)->setLastPos(Vector2d(LOCATION_TO_POINT(x2), LOCATION_TO_POINT(y2)));
		if (drag)
		{
			this->movingFig.X = x2;
			this->movingFig.Y = y2;
		}
		this->net->at(x1).at(y1)->setLastPos(this->net->at(x1).at(y1)->getPositionB());
		holder = nullptr;
	}
}



void Grid::deleteAt(int x, int y)
{
	if (this->net->at(x).at(y)!=nullptr)
		this->net->at(x).at(y)->Delete();
	this->net->at(x).at(y) = nullptr;
}







Grid::~Grid()
{
	ElementDelete(fig);
	D3DDelete(net);
}